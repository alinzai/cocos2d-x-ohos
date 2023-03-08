/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/


#include <string>
#include "../include/SimpleAudioEngine.h"
#include "platform/ohos/JsAudioEngine.h"
#include "platform/ohos/CCFileUtils-ohos.h"
#include "audio/include/AudioEngine.h"
#include "cutils/log.h"

using namespace cocos2d::experimental;

namespace CocosDenshion {

static  int _lastBackGroundAudioID = -1;
static  char* _lastBackGroundFilename;
static  int _lastEffectAudioID;
static  char* _lastEffectFilename;
static bool useJsFunc = false;
static float effectsvolume = 1.0;

static std::string getFullPathWithoutAssetsPrefix(const char* pszFilename)
{
    std::string fullPath = cocos2d::FileUtils::sharedFileUtils()->fullPathForFilename(pszFilename);
    size_t pos = fullPath.find("hap:/");
    if (pos == 0)
    {
        fullPath = fullPath.substr(strlen("hap:/"));
    }
    return fullPath;
}

static SimpleAudioEngine *s_pEngine = 0;

SimpleAudioEngine::SimpleAudioEngine()
{
}

SimpleAudioEngine::~SimpleAudioEngine()
{
}

SimpleAudioEngine* SimpleAudioEngine::getInstance()
{
    if (! s_pEngine)
    {
        s_pEngine = new SimpleAudioEngine();
    }
    
    return s_pEngine;
}

void SimpleAudioEngine::end()
{
    if (useJsFunc) {
    } else {
        cocos2d::experimental::AudioEngine::end();
    }
    
}

void SimpleAudioEngine::preloadBackgroundMusic(const char* pszFilePath)
{
    ALOGD("preloadBackgroundMusic start!");
    std::string uri(getFullPathWithoutAssetsPrefix(pszFilePath));

    cocos2d::JsAudioEngine::preLoadBackgroundMusic(uri);
}

void SimpleAudioEngine::playBackgroundMusic(const char* pszFilePath, bool bLoop)
{
    ALOGD("playBackgroundMusic: %s", pszFilePath);
    std::string uri(getFullPathWithoutAssetsPrefix(pszFilePath));
    if (useJsFunc) {
        cocos2d::JsAudioEngine::playBackgroundMusic(uri, bLoop);
    } else {
        _lastBackGroundAudioID = cocos2d::experimental::AudioEngine::play2d(uri, bLoop, 0.5);
    }
    ALOGD("playBackgroundMusic  %s  end, and id:%d", uri.c_str(), _lastBackGroundAudioID);
       
}

void SimpleAudioEngine::stopBackgroundMusic(bool bReleaseData)
{
    ALOGD("stopBackgroundMusic");

        cocos2d::experimental::AudioEngine::stop(_lastBackGroundAudioID);
        ALOGD("stopBackgroundMusic end, and id:%d", _lastBackGroundAudioID);
    
    
}

void SimpleAudioEngine::pauseBackgroundMusic()
{
    ALOGD("pauseBackgroundMusic");
    if (useJsFunc) {
        cocos2d::JsAudioEngine::pauseBackgroundMusic();
    } else {
        cocos2d::experimental::AudioEngine::pause(_lastBackGroundAudioID);
    }
    
}

void SimpleAudioEngine::resumeBackgroundMusic()
{
    ALOGD("resumeBackgroundMusic start!");
    if (useJsFunc) {
        cocos2d::JsAudioEngine::resumeBackgroundMusic();
    } else {
        cocos2d::experimental::AudioEngine::resume(_lastBackGroundAudioID);
    }
}

void SimpleAudioEngine::rewindBackgroundMusic()
{
    ALOGD("rewindBackgroundMusic");
    if (useJsFunc) {
        cocos2d::JsAudioEngine::rewindBackgroundMusic();
    } else {
        cocos2d::experimental::AudioEngine::setCurrentTime(_lastBackGroundAudioID, 0);
    }
}

bool SimpleAudioEngine::willPlayBackgroundMusic()
{
    if (useJsFunc) {
        return true;
    }
    return _lastBackGroundAudioID != -1;
}

bool SimpleAudioEngine::isBackgroundMusicPlaying()
{
    if (useJsFunc) {
        // TBD 待补充
        return false;
    } else {
  		return cocos2d::experimental::AudioEngine::getState(_lastBackGroundAudioID) == AudioEngine::AudioState::PLAYING;
    }
}

float SimpleAudioEngine::getBackgroundMusicVolume()
{
    if (useJsFunc) {
        return cocos2d::JsAudioEngine::getBackgroundMusicVolume();
    } else {
        return AudioEngine::getVolume(_lastBackGroundAudioID);
    }

    
}

void SimpleAudioEngine::setBackgroundMusicVolume(float volume)
{
    if (useJsFunc) {
        cocos2d::JsAudioEngine::setBackgroundMusicVolume(volume);
    } else {
        AudioEngine::setVolume(_lastBackGroundAudioID, volume);
    }
    
}

float SimpleAudioEngine::getEffectsVolume()
{
    if (useJsFunc) {
        return cocos2d::JsAudioEngine::getEffectsVolume();
    }
    return effectsvolume;
}

void SimpleAudioEngine::setEffectsVolume(float volume)
{
    if (useJsFunc) {
        cocos2d::JsAudioEngine::setEffectsVolume(volume);
    } else {
        effectsvolume = volume;
    }
    
}

// TBD need check pitch pan and gain
unsigned int SimpleAudioEngine::playEffect(const char* pszFilePath, bool bLoop, float pitch, float pan, float gain)
{
    std::string uri(getFullPathWithoutAssetsPrefix(pszFilePath));
    if (useJsFunc) {
        return cocos2d::JsAudioEngine::playEffect(uri.c_str(), bLoop);
    } 
    ALOGD("playEffect start! and uri:%s", uri.data());
    return  AudioEngine::play2d(uri, bLoop);
}


void SimpleAudioEngine::stopEffect(unsigned int nSoundId)
{
    if (useJsFunc) {
        cocos2d::JsAudioEngine::stopEffect(nSoundId);
    } else {
        AudioEngine::stop(nSoundId);
    }
}

void SimpleAudioEngine::preloadEffect(const char* pszFilePath)
{
    std::string uri(getFullPathWithoutAssetsPrefix(pszFilePath));
    if (useJsFunc) {
        cocos2d::JsAudioEngine::preloadEffect(uri.c_str());
    } else {
        AudioEngine::preload(uri);
    }
    
}

void SimpleAudioEngine::unloadEffect(const char* pszFilePath)
{
    std::string uri(getFullPathWithoutAssetsPrefix(pszFilePath));
    if (useJsFunc) {
        cocos2d::JsAudioEngine::unloadEffect(uri.c_str());
    } else {
        AudioEngine::uncache(uri);
    }
    
}

void SimpleAudioEngine::pauseEffect(unsigned int nSoundId)
{
    if (useJsFunc) {
        cocos2d::JsAudioEngine::pauseEffect(nSoundId);
    } else {
        AudioEngine::pause(nSoundId);
    }
    
}

void SimpleAudioEngine::pauseAllEffects()
{
    if (useJsFunc) {
        cocos2d::JsAudioEngine::pauseAllEffects();
    } else {
        AudioEngine::pauseAll();
    }
    
}

void SimpleAudioEngine::resumeEffect(unsigned int nSoundId)
{
    if (useJsFunc) {
        cocos2d::JsAudioEngine::resumeEffect(nSoundId);
    } else {
        cocos2d::experimental::AudioEngine::resume(nSoundId);
    }
    
}

void SimpleAudioEngine::resumeAllEffects()
{
    if (useJsFunc) {
        cocos2d::JsAudioEngine::resumeAllEffects();
    } else {
        cocos2d::experimental::AudioEngine::resumeAll();
    }
    
}

void SimpleAudioEngine::stopAllEffects()
{
    if (useJsFunc) {
        cocos2d::JsAudioEngine::stopAllEffects();
    } else {
        cocos2d::experimental::AudioEngine::stopAll();
    }
}

}
