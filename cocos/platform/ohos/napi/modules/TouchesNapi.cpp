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
#include "deprecated/CCSet.h"
#include "base/CCDirector.h"
//#include "keypad_dispatcher/CCKeypadDispatcher.h"
#include "base/CCTouch.h"
#include "platform/CCGLView.h"
//#include "touch_dispatcher/CCTouchDispatcher.h"

#include "platform/ohos/CCLogOhos.h"
// #include <jni.h>

using namespace cocos2d;

extern "C" {
    void Cocos2dxRenderer_nativeTouchesBegin(intptr_t id, float x, float y) {
        cocos2d::Director::sharedDirector()->getOpenGLView()->handleTouchesBegin(1, &id, &x, &y);
    }

    void Cocos2dxRenderer_nativeTouchesEnd(intptr_t id, float x, float y) {
        cocos2d::Director::sharedDirector()->getOpenGLView()->handleTouchesEnd(1, &id, &x, &y);
    }

    void Cocos2dxRenderer_nativeTouchesMove(intptr_t id, float x, float y) {
       cocos2d::Director::sharedDirector()->getOpenGLView()->handleTouchesMove(1, &id, &x, &y);
    }

    void Cocos2dxRenderer_nativeTouchesCancel(intptr_t id, float x, float y) {
       cocos2d::Director::sharedDirector()->getOpenGLView()->handleTouchesCancel(1, &id, &x, &y);
    }

    #define KEYCODE_BACK 0x04
    #define KEYCODE_MENU 0x52

    bool Cocos2dxRenderer_nativeKeyDown(int keyCode) {
       Director* pDirector = Director::sharedDirector();
       switch (keyCode) {
           case KEYCODE_BACK:
                    // TBD need fixed 
//                 if (pDirector->getKeypadDispatcher()->dispatchKeypadMSG(kTypeBackClicked))
                   return true;
               break;
           case KEYCODE_MENU:
//               if (pDirector->getKeypadDispatcher()->dispatchKeypadMSG(kTypeMenuClicked))
                   return true;
               break;
           default:
               return false;
       }
        return 0;
    }
}
