#include "math/CCGeometry.h"
#include "platform/ohos/CCAccelerometer.h"
#include "../CCEGLView.h"
#include "JniHelper.h"
// #include <jni.h>
#include "CCDirector.h"
#include "CCLogOhos.h"

using namespace cocos2d;

extern "C" {
     void Java_org_cocos2dx_lib_Cocos2dxAccelerometer_onSensorChanged() {
        // CCDirector* pDirector = CCDirector::sharedDirector();
        // pDirector->getAccelerometer()->update(x, y, z, timeStamp);
        OHOS_LOGE("Java_org_cocos2dx_lib_Cocos2dxAccelerometer_onSensorChanged");
    }    
}
