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

#include "../include/SimpleAudioEngine.h"



#include <string>
#include "../include/SimpleAudioEngine.h"
#include "JsAudioEngine.h"
#include "CCFileUtilsOhos.h"


namespace CocosDenshion {

static  int _lastBackGroundAudioID;
static  char* _lastBackGroundFilename;
static  int _lastEffectAudioID;
static  char* _lastEffectFilename;
static bool useJsFunc = true;

static std::string getFullPathWithoutAssetsPrefix(const char* pszFilename)
{
    std::string fullPath = cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(pszFilename);
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

SimpleAudioEngine* SimpleAudioEngine::sharedEngine()
{
    if (! s_pEngine)
    {
        s_pEngine = new SimpleAudioEngine();
    }
    
    return s_pEngine;
}

void SimpleAudioEngine::end()
{
    // TBD 待补充
}

void SimpleAudioEngine::preloadBackgroundMusic(const char* pszFilePath)
{
    std::string uri(getFullPathWithoutAssetsPrefix(pszFilePath));
    cocos2d::JsAudioEngine::preLoadBackgroundMusic(uri);
}

void SimpleAudioEngine::playBackgroundMusic(const char* pszFilePath, bool bLoop)
{
    std::string uri(getFullPathWithoutAssetsPrefix(pszFilePath));
    // TBD 这里音量大小待确认
    cocos2d::JsAudioEngine::playBackgroundMusic(uri);
}

void SimpleAudioEngine::stopBackgroundMusic(bool bReleaseData)
{
    std::string uri = "hello";
    cocos2d::JsAudioEngine::stopBackgroundMusic(uri);

}

void SimpleAudioEngine::pauseBackgroundMusic()
{
    cocos2d::JsAudioEngine::pauseBackgroundMusic();
}

void SimpleAudioEngine::resumeBackgroundMusic()
{
    cocos2d::JsAudioEngine::resumeBackgroundMusic();
}

void SimpleAudioEngine::rewindBackgroundMusic()
{
    cocos2d::JsAudioEngine::rewindBackgroundMusic();
}

bool SimpleAudioEngine::willPlayBackgroundMusic()
{
    return true;
}

bool SimpleAudioEngine::isBackgroundMusicPlaying()
{
    // TBD 待补充
}

float SimpleAudioEngine::getBackgroundMusicVolume()
{
    return cocos2d::JsAudioEngine::getBackgroundMusicVolume();
}

void SimpleAudioEngine::setBackgroundMusicVolume(float volume)
{
    return cocos2d::JsAudioEngine::setBackgroundMusicVolume(volume);
}

float SimpleAudioEngine::getEffectsVolume()
{
    return cocos2d::JsAudioEngine::getEffectsVolume();
}

void SimpleAudioEngine::setEffectsVolume(float volume)
{
    cocos2d::JsAudioEngine::setEffectsVolume(volume);
}

unsigned int SimpleAudioEngine::playEffect(const char* pszFilePath, bool bLoop)
{
    std::string uri(getFullPathWithoutAssetsPrefix(pszFilePath));
    return cocos2d::JsAudioEngine::playEffect(uri.c_str(), bLoop);
}


void SimpleAudioEngine::stopEffect(unsigned int nSoundId)
{
    cocos2d::JsAudioEngine::stopEffect(nSoundId);
}

void SimpleAudioEngine::preloadEffect(const char* pszFilePath)
{
    std::string uri(getFullPathWithoutAssetsPrefix(pszFilePath));
    cocos2d::JsAudioEngine::preloadEffect(uri.c_str());
}

void SimpleAudioEngine::unloadEffect(const char* pszFilePath)
{
    std::string uri(getFullPathWithoutAssetsPrefix(pszFilePath));
    cocos2d::JsAudioEngine::unloadEffect(uri.c_str());
}

void SimpleAudioEngine::pauseEffect(unsigned int nSoundId)
{
    cocos2d::JsAudioEngine::pauseEffect(nSoundId);
}

void SimpleAudioEngine::pauseAllEffects()
{
    cocos2d::JsAudioEngine::pauseAllEffects();
}

void SimpleAudioEngine::resumeEffect(unsigned int nSoundId)
{
    cocos2d::JsAudioEngine::resumeEffect(nSoundId);
}

void SimpleAudioEngine::resumeAllEffects()
{
    cocos2d::JsAudioEngine::resumeAllEffects();
}

void SimpleAudioEngine::stopAllEffects()
{
    cocos2d::JsAudioEngine::stopAllEffects();
}

}
