#include <map>
#include <string>
#include <stdio.h>
#include <unistd.h>

#include "SimpleAudioEngine.h"
#include "platform/ohos/napi/modules/JniHelper.h"
#include "cocos2d.h"
#include "CCLogOhos.h"

USING_NS_CC;

namespace CocosDenshion {

static std::string getFullPathWithoutAssetsPrefix(const char* pszFilename)
{
    return 0;
}

SimpleAudioEngine::SimpleAudioEngine()
{

}

SimpleAudioEngine::~SimpleAudioEngine()
{
    
}

SimpleAudioEngine* SimpleAudioEngine::sharedEngine()
{
    return 0;
}

void SimpleAudioEngine::end()
{
    
}

void SimpleAudioEngine::preloadBackgroundMusic(const char* pszFilePath)
{
    
}

void SimpleAudioEngine::playBackgroundMusic(const char* pszFilePath, bool bLoop)
{
    
}

void SimpleAudioEngine::stopBackgroundMusic(bool bReleaseData)
{
    
}

void SimpleAudioEngine::pauseBackgroundMusic()
{
    
}

void SimpleAudioEngine::resumeBackgroundMusic()
{
    
}

void SimpleAudioEngine::rewindBackgroundMusic()
{
    
}

bool SimpleAudioEngine::willPlayBackgroundMusic()
{
    return 0;
}

bool SimpleAudioEngine::isBackgroundMusicPlaying()
{
    return 0;
}

float SimpleAudioEngine::getBackgroundMusicVolume()
{
    return 0;
}

void SimpleAudioEngine::setBackgroundMusicVolume(float volume)
{
    
}

float SimpleAudioEngine::getEffectsVolume()
{
    return 0;
}

void SimpleAudioEngine::setEffectsVolume(float volume)
{
    
}

unsigned int SimpleAudioEngine::playEffect(const char* pszFilePath, bool bLoop)
{
    return 0;
}

void SimpleAudioEngine::stopEffect(unsigned int nSoundId)
{
    
}

void SimpleAudioEngine::preloadEffect(const char* pszFilePath)
{
    
}

void SimpleAudioEngine::unloadEffect(const char* pszFilePath)
{
    
}

void SimpleAudioEngine::pauseEffect(unsigned int nSoundId)
{
    
}

void SimpleAudioEngine::pauseAllEffects()
{
    
}

void SimpleAudioEngine::resumeEffect(unsigned int nSoundId)
{
    
}

void SimpleAudioEngine::resumeAllEffects()
{
    
}

void SimpleAudioEngine::stopAllEffects()
{
    
}

}