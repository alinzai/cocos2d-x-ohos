#include <stdint.h>
#include <string>
#include <stdio.h>

#include <ace/xcomponent/native_interface_xcomponent.h>

#include "platform/ohos/napi/plugin_manager.h"
#include "../common/plugin_common.h"

#include <js_native_api_types.h>
#include "RawFileUtils.h"


NativeResourceManager* RawFileUtils::nativeResourceManager_ = nullptr;

bool RawFileUtils::InitResourceManager(napi_env env, napi_value param) {
    nativeResourceManager_ = OH_ResourceManager_InitNativeResourceManager(env, param);
    LOGD("cocos qgh  initResourceManager %{public}p", nativeResourceManager_);
    return true;
}
