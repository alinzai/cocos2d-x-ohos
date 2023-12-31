#include "AppDelegate.h"
#include "cocos2d.h"
#include "CCEventType.h"
#include "platform/ohos/napi/modules/JniHelper.h"
#include "CCLogOhos.h"

using namespace cocos2d;

extern "C"
{  

void Cocos2dxRenderer_nativeInit(int w, int h)
{
    OHOS_LOGE("Cocos2dxRenderer_nativeInit() - window width:[%d], height:[%d]", w, h);
    if (!CCDirector::sharedDirector()->getOpenGLView())
    {
        CCEGLView *view = CCEGLView::sharedOpenGLView();
        view->setFrameSize(w, h);

        AppDelegate *pAppDelegate = new AppDelegate();
        CCApplication::sharedApplication()->run();
    }
    else
    {
        ccGLInvalidateStateCache();
        CCShaderCache::sharedShaderCache()->reloadDefaultShaders();
        ccDrawInit();
        CCTextureCache::reloadAllTextures();
        CCNotificationCenter::sharedNotificationCenter()->postNotification(EVENT_COME_TO_FOREGROUND, NULL);
        CCDirector::sharedDirector()->setGLDefaultValues(); 
    }
}

}