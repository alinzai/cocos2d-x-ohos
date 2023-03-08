/****************************************************************************
 Copyright (c) 2014-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2022 Xiamen Yaji Software Co., Ltd.

 http://www.cocos.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
 worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
 not use Cocos Creator software for developing other software or tools that's
 used for developing games. You are not granted to publish, distribute,
 sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
****************************************************************************/

#include "audio/include/AudioEngine.h"
#include <condition_variable>
#include <cstdint>
#include <mutex>
#include <thread>
#include <queue>
#include "cutils/Log.h"
#include "utils/Utils.h"
#include "audio_utils/AudioFileUtils.h"


#include "AudioEngine-inl.h"


#define TIME_DELAY_PRECISION 0.0001

#ifdef ERROR
    #undef ERROR
#endif // ERROR

namespace cocos2d { namespace experimental {

const int AudioEngine::INVALID_AUDIO_ID = -1;
const float AudioEngine::TIME_UNKNOWN = -1.0F;

//audio file path,audio IDs
std::unordered_map<std::string, std::list<int>> AudioEngine::_audioPathIDMap;
//profileName,ProfileHelper
std::unordered_map<std::string, AudioEngine::ProfileHelper> AudioEngine::_audioPathProfileHelperMap;
unsigned int AudioEngine::_maxInstances = MAX_AUDIOINSTANCES;
AudioEngine::ProfileHelper *AudioEngine::_defaultProfileHelper = nullptr;
std::unordered_map<int, AudioEngine::AudioInfo> AudioEngine::_audioIDInfoMap;
AudioEngineImpl *AudioEngine::_audioEngineImpl = nullptr;

//float AudioEngine::sVolumeFactor = 1.0F;
//uint32_t AudioEngine::sOnPauseListenerID = 0;
//uint32_t AudioEngine::sOnResumeListenerID = 0;
//std::vector<int> AudioEngine::sBreakAudioID;

AudioEngine::AudioEngineThreadPool *AudioEngine::s_threadPool = nullptr;
bool AudioEngine::_isEnabled = true;

AudioEngine::AudioInfo::AudioInfo()
: filePath(nullptr),
  profileHelper(nullptr),
  volume(1.0F),
  loop(false),
  duration(TIME_UNKNOWN),
  state(AudioState::INITIALIZING) {
}

AudioEngine::AudioInfo::~AudioInfo()
{
}

class AudioEngine::AudioEngineThreadPool {
public:
    explicit AudioEngineThreadPool(int threads = 4) {
        for (int index = 0; index < threads; ++index) {
            _workers.emplace_back(std::thread([this]() {
                threadFunc();
            }));
        }
    }

    void addTask(const std::function<void()> &task) {
        std::unique_lock<std::mutex> lk(_queueMutex);
        _taskQueue.emplace(task);
        _taskCondition.notify_one();
    }

    ~AudioEngineThreadPool() {
        {
            std::unique_lock<std::mutex> lk(_queueMutex);
            _stop = true;
            _taskCondition.notify_all();
        }

        for (auto &&worker : _workers) {
            worker.join();
        }
    }

private:
    void threadFunc() {
        while (true) {
            std::function<void()> task = nullptr;
            {
                std::unique_lock<std::mutex> lk(_queueMutex);
                if (_stop) {
                    break;
                }
                if (!_taskQueue.empty()) {
                    task = std::move(_taskQueue.front());
                    _taskQueue.pop();
                } else {
                    _taskCondition.wait(lk);
                    continue;
                }
            }

            task();
        }
    }

    std::vector<std::thread> _workers;
    std::queue<std::function<void()>> _taskQueue;

    std::mutex _queueMutex;
    std::condition_variable _taskCondition;
    bool _stop{};
};

void AudioEngine::end() {
    stopAll();

    if (s_threadPool) {
        delete s_threadPool;
        s_threadPool = nullptr;
    }

    delete _audioEngineImpl;
    _audioEngineImpl = nullptr;

    delete _defaultProfileHelper;
    _defaultProfileHelper = nullptr;

//    if (sOnPauseListenerID != 0) {
//        sOnPauseListenerID = 0;
//    }

//    if (sOnResumeListenerID != 0) {
//        sOnResumeListenerID = 0;
//    }
}

bool AudioEngine::lazyInit() {
    if (_audioEngineImpl == nullptr) {
        _audioEngineImpl = new AudioEngineImpl();
        if (!_audioEngineImpl || !_audioEngineImpl->init()) {
            delete _audioEngineImpl;
            _audioEngineImpl = nullptr;
            return false;
        }
    }

#if (CC_PLATFORM != CC_PLATFORM_ANDROID)
    if (_audioEngineImpl && s_threadPool == nullptr) {
        s_threadPool = new AudioEngineThreadPool();
    }
#endif

    return true;
}

int AudioEngine::play2d(const std::string &filePath, bool loop, float volume, const AudioProfile *profile) {
   
    int ret = AudioEngine::INVALID_AUDIO_ID;

    do {
        if (!isEnabled()) {
            break;
        }

        if (!lazyInit()) {
            break;
        }

        if (!AudioFileUtils::getInstance()->isFileExist(filePath)) {
            break;
        }

        auto *profileHelper = _defaultProfileHelper;
        if (profile && profile != &profileHelper->profile) {
            CC_ASSERT(!profile->name.empty());
            profileHelper = &_audioPathProfileHelperMap[profile->name];
            profileHelper->profile = *profile;
        }

        if (_audioIDInfoMap.size() >= _maxInstances) {
            ALOGE("Fail to play %s cause by limited max instance of AudioEngine", filePath.c_str());
            break;
        }
        if (profileHelper) {
            if (profileHelper->profile.maxInstances != 0 && profileHelper->audioIDs.size() >= profileHelper->profile.maxInstances) {
                ALOGI("Fail to play %s cause by limited max instance of AudioProfile", filePath.c_str());
                break;
            }
            if (profileHelper->profile.minDelay > TIME_DELAY_PRECISION) {
                auto currTime = std::chrono::high_resolution_clock::now();
                auto delay = static_cast<float>(std::chrono::duration_cast<std::chrono::microseconds>(currTime - profileHelper->lastPlayTime).count()) / 1000000.0;
                if (profileHelper->lastPlayTime.time_since_epoch().count() != 0 && delay <= profileHelper->profile.minDelay) {
                    ALOGI("Fail to play %s cause by limited minimum delay", filePath.c_str());
                    break;
                }
            }
        }

        if (volume < 0.0F) {
            volume = 0.0F;
        } else if (volume > 1.0F) {
            volume = 1.0F;
        }

        ret = _audioEngineImpl->play2d(filePath, loop, volume);
        if (ret != INVALID_AUDIO_ID) {
            _audioPathIDMap[filePath].push_back(ret);
            auto it = _audioPathIDMap.find(filePath);

            auto &audioRef = _audioIDInfoMap[ret];
            audioRef.volume = volume;
            audioRef.loop = loop;
            audioRef.filePath = &it->first;
            audioRef.state = AudioState::PLAYING;

            if (profileHelper) {
                profileHelper->lastPlayTime = std::chrono::high_resolution_clock::now();
                profileHelper->audioIDs.push_back(ret);
            }
            audioRef.profileHelper = profileHelper;
        }
    } while (false);

    return ret;
}

void AudioEngine::setLoop(int audioID, bool loop) {
    auto it = _audioIDInfoMap.find(audioID);
    if (it != _audioIDInfoMap.end() && it->second.loop != loop) {
        _audioEngineImpl->setLoop(audioID, loop);
        it->second.loop = loop;
    }
}

void AudioEngine::setVolume(int audioID, float volume) {
    auto it = _audioIDInfoMap.find(audioID);
    if (it != _audioIDInfoMap.end()) {
        if (volume < 0.0F) {
            volume = 0.0F;
        } else if (volume > 1.0F) {
            volume = 1.0F;
        }

        if (it->second.volume != volume) {
            _audioEngineImpl->setVolume(audioID, volume);
            it->second.volume = volume;
        }
    }
}

//void AudioEngine::setVolumeFactor(float factor) {
//    if (factor > 1.0F) {
//        factor = 1.0F;
//    }
//    if (factor < 0) {
//        factor = 0.0F;
//    }
//    sVolumeFactor = factor;
//    for (auto &item : _audioIDInfoMap) {
//        _audioEngineImpl->setVolume(item.first, item.second.volume * sVolumeFactor);
//    }
//}

void AudioEngine::pause(int audioID) {
    auto it = _audioIDInfoMap.find(audioID);
    if (it != _audioIDInfoMap.end() && it->second.state == AudioState::PLAYING) {
        _audioEngineImpl->pause(audioID);
        it->second.state = AudioState::PAUSED;
    }
}

void AudioEngine::pauseAll() {
    auto itEnd = _audioIDInfoMap.end();
    for (auto it = _audioIDInfoMap.begin(); it != itEnd; ++it) {
        if (it->second.state == AudioState::PLAYING) {
            _audioEngineImpl->pause(it->first);
            it->second.state = AudioState::PAUSED;
        }
    }
}

void AudioEngine::resume(int audioID) {
    auto it = _audioIDInfoMap.find(audioID);
    if (it != _audioIDInfoMap.end() && it->second.state == AudioState::PAUSED) {
        _audioEngineImpl->resume(audioID);
        it->second.state = AudioState::PLAYING;
    }
}

void AudioEngine::resumeAll() {
    auto itEnd = _audioIDInfoMap.end();
    for (auto it = _audioIDInfoMap.begin(); it != itEnd; ++it) {
        if (it->second.state == AudioState::PAUSED) {
            _audioEngineImpl->resume(it->first);
            it->second.state = AudioState::PLAYING;
        }
    }
}

//void AudioEngine::onEnterBackground() {
//    auto itEnd = _audioIDInfoMap.end();
//    for (auto it = _audioIDInfoMap.begin(); it != itEnd; ++it) {
//        if (it->second.state == AudioState::PLAYING) {
//            _audioEngineImpl->pause(it->first);
//            it->second.state = AudioState::PAUSED;
//            sBreakAudioID.push_back(it->first);
//        }
//    }
//}

//void AudioEngine::onEnterForeground() {
//    auto itEnd = sBreakAudioID.end();
//    for (auto it = sBreakAudioID.begin(); it != itEnd; ++it) {
//        auto iter = _audioIDInfoMap.find(*it);
//        if (iter != _audioIDInfoMap.end() && iter->second.state == AudioState::PAUSED) {
//            _audioEngineImpl->resume(*it);
//            iter->second.state = AudioState::PLAYING;
//        }
//    }
//    sBreakAudioID.clear();
//
//#if CC_PLATFORM == CC_PLATFORM_ANDROID
//    if (_audioEngineImpl) {
//        _audioEngineImpl->onResume();
//    }
//#endif
//}

void AudioEngine::stop(int audioID) {
    auto it = _audioIDInfoMap.find(audioID);
    if (it != _audioIDInfoMap.end()) {
        _audioEngineImpl->pause(audioID);
        _audioEngineImpl->stop(audioID);
        ALOGI("stop %d finished!", audioID);

        remove(audioID);
    }
}

void AudioEngine::remove(int audioID) {
    auto it = _audioIDInfoMap.find(audioID);
    if (it != _audioIDInfoMap.end()) {
        if (it->second.profileHelper) {
            it->second.profileHelper->audioIDs.remove(audioID);
        }
        _audioPathIDMap[*it->second.filePath].remove(audioID);
        _audioIDInfoMap.erase(audioID);
    }
}

void AudioEngine::stopAll() {
    if (!_audioEngineImpl) {
        return;
    }
    _audioEngineImpl->stopAll();
    auto itEnd = _audioIDInfoMap.end();
    for (auto it = _audioIDInfoMap.begin(); it != itEnd; ++it) {
        if (it->second.profileHelper) {
            it->second.profileHelper->audioIDs.remove(it->first);
        }
    }
    _audioPathIDMap.clear();
    _audioIDInfoMap.clear();
}

void AudioEngine::uncache(const std::string &filePath) {
    auto audioIDsIter = _audioPathIDMap.find(filePath);
    if (audioIDsIter != _audioPathIDMap.end()) {
        //@Note: For safely iterating elements from the audioID list, we need to copy the list
        // since 'AudioEngine::remove' may be invoked in '_audioEngineImpl->stop' synchronously.
        // If this happens, it will break the iteration, and crash will appear on some devices.
        std::list<int> copiedIDs(audioIDsIter->second);

        for (int audioID : copiedIDs) {
            _audioEngineImpl->stop(audioID);

            auto itInfo = _audioIDInfoMap.find(audioID);
            if (itInfo != _audioIDInfoMap.end()) {
                if (itInfo->second.profileHelper) {
                    itInfo->second.profileHelper->audioIDs.remove(audioID);
                }
                _audioIDInfoMap.erase(audioID);
            }
        }
        _audioPathIDMap.erase(filePath);
    }

    if (_audioEngineImpl) {
        _audioEngineImpl->uncache(filePath);
    }
}

void AudioEngine::uncacheAll() {
    if (!_audioEngineImpl) {
        return;
    }
    stopAll();
    _audioEngineImpl->uncacheAll();
}

float AudioEngine::getDuration(int audioID) {
    auto it = _audioIDInfoMap.find(audioID);
    if (it != _audioIDInfoMap.end() && it->second.state != AudioState::INITIALIZING) {
        if (it->second.duration == TIME_UNKNOWN) {
            it->second.duration = _audioEngineImpl->getDuration(audioID);
        }
        return it->second.duration;
    }

    return TIME_UNKNOWN;
}

//float AudioEngine::getDurationFromFile(const std::string &filePath) {
//    lazyInit();
//
//    if (_audioEngineImpl) {
//        return _audioEngineImpl->getDurationFromFile(filePath);
//    }
//
//    return TIME_UNKNOWN;
//}

bool AudioEngine::setCurrentTime(int audioID, float time) {
    auto it = _audioIDInfoMap.find(audioID);
    if (it != _audioIDInfoMap.end() && it->second.state != AudioState::INITIALIZING) {
        return _audioEngineImpl->setCurrentTime(audioID, time);
    }

    return false;
}

float AudioEngine::getCurrentTime(int audioID) {
    auto it = _audioIDInfoMap.find(audioID);
    if (it != _audioIDInfoMap.end() && it->second.state != AudioState::INITIALIZING) {
        return _audioEngineImpl->getCurrentTime(audioID);
    }
    return 0.0F;
}

void AudioEngine::setFinishCallback(int audioID, const std::function<void(int, const std::string &)> &callback) {
    auto it = _audioIDInfoMap.find(audioID);
    if (it != _audioIDInfoMap.end()) {
        _audioEngineImpl->setFinishCallback(audioID, callback);
    }
}

bool AudioEngine::setMaxAudioInstance(int maxInstances) {
    if (maxInstances > 0 && maxInstances <= MAX_AUDIOINSTANCES) {
        _maxInstances = maxInstances;
        return true;
    }

    return false;
}

bool AudioEngine::isLoop(int audioID) {
    auto tmpIterator = _audioIDInfoMap.find(audioID);
    if (tmpIterator != _audioIDInfoMap.end()) {
        return tmpIterator->second.loop;
    }

    ALOGI("AudioEngine::isLoop-->The audio instance %d is non-existent", audioID);
    return false;
}

float AudioEngine::getVolume(int audioID) {
    auto tmpIterator = _audioIDInfoMap.find(audioID);
    if (tmpIterator != _audioIDInfoMap.end()) {
        return tmpIterator->second.volume;
    }

    ALOGI("AudioEngine::getVolume-->The audio instance %d is non-existent", audioID);
    return 0.0F;
}

AudioEngine::AudioState AudioEngine::getState(int audioID) {
    auto tmpIterator = _audioIDInfoMap.find(audioID);
    if (tmpIterator != _audioIDInfoMap.end()) {
        return tmpIterator->second.state;
    }

    return AudioState::ERROR;
}

AudioProfile *AudioEngine::getProfile(int audioID) {
    auto it = _audioIDInfoMap.find(audioID);
    if (it != _audioIDInfoMap.end()) {
        return &it->second.profileHelper->profile;
    }

    return nullptr;
}

AudioProfile *AudioEngine::getDefaultProfile() {
    if (_defaultProfileHelper == nullptr) {
        _defaultProfileHelper = new ProfileHelper();
    }

    return &_defaultProfileHelper->profile;
}

AudioProfile *AudioEngine::getProfile(const std::string &name) {
    auto it = _audioPathProfileHelperMap.find(name);
    if (it != _audioPathProfileHelperMap.end()) {
        return &it->second.profile;
    }
    return nullptr;
}

void AudioEngine::preload(const std::string &filePath, std::function<void(bool isSuccess)> callback) {
    if (!isEnabled()) {
        callback(false);
        return;
    }

    lazyInit();

    if (_audioEngineImpl) {
        if (!AudioFileUtils::getInstance()->isFileExist(filePath)) {
            if (callback) {
                callback(false);
            }
            return;
        }

        _audioEngineImpl->preload(filePath, callback);
    }
}

void AudioEngine::addTask(const std::function<void()> &task) {
    lazyInit();

    if (_audioEngineImpl && s_threadPool) {
        s_threadPool->addTask(task);
    }
}

int AudioEngine::getPlayingAudioCount() {
    return static_cast<int>(_audioIDInfoMap.size());
}

void AudioEngine::setEnabled(bool isEnabled) {
    if (_isEnabled != isEnabled) {
        _isEnabled = isEnabled;

        if (!_isEnabled) {
            stopAll();
        }
    }
}

bool AudioEngine::isEnabled() {
    return _isEnabled;
}

//PCMHeader AudioEngine::getPCMHeader(const char *url) {
//    lazyInit();
//    return _audioEngineImpl->getPCMHeader(url);
//}
//std::vector<uint8_t> AudioEngine::getOriginalPCMBuffer(const char *url, uint32_t channelID) {
//    lazyInit();
//    return _audioEngineImpl->getOriginalPCMBuffer(url, channelID);
//}
}} // namespace cc
