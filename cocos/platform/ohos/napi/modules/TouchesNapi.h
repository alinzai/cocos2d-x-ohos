#ifndef __TouchesNapi_H__
#define __TouchesNapi_H__

#include "deprecated/CCSet.h"
#include "base/CCDirector.h"
//#include "keypad_dispatcher/CCKeypadDispatcher.h"
#include "base/CCTouch.h"
#include "platform/CCGLView.h"
//#include "touch_dispatcher/CCTouchDispatcher.h"

#include "platform/ohos/CCLogOhos.h"

using namespace cocos2d;

extern "C" {
    void Cocos2dxRenderer_nativeTouchesBegin(int id, float x, float y);
    void Cocos2dxRenderer_nativeTouchesEnd(int id, float x, float y);
    void Cocos2dxRenderer_nativeTouchesMove(int id, float x, float y);
    void Cocos2dxRenderer_nativeTouchesCancel(int id, float x, float y);
    bool Cocos2dxRenderer_nativeKeyDown(int keyCode);
}

#endif