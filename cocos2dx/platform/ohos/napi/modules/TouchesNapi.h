#ifndef __TouchesNapi_H__
#define __TouchesNapi_H__

#include "cocoa/CCSet.h"
#include "CCDirector.h"
#include "keypad_dispatcher/CCKeypadDispatcher.h"
#include "touch_dispatcher/CCTouch.h"
#include "../CCEGLView.h"
#include "touch_dispatcher/CCTouchDispatcher.h"

#include "CCLogOhos.h"

using namespace cocos2d;

extern "C" {
    void Cocos2dxRenderer_nativeTouchesBegin(int id, float x, float y);
    void Cocos2dxRenderer_nativeTouchesEnd(int id, float x, float y);
    void Cocos2dxRenderer_nativeTouchesMove(int id, float x, float y);
    void Cocos2dxRenderer_nativeTouchesCancel(int id, float x, float y);
    bool Cocos2dxRenderer_nativeKeyDown(int keyCode);
}

#endif