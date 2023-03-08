/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _PLUGIN_MANAGER_H_
#define _PLUGIN_MANAGER_H_

#include <string>
#include <unordered_map>

#include <ace/xcomponent/native_interface_xcomponent.h>
#include <napi/native_api.h>
#include <uv.h>

#include "common/native_common.h"
#include "WorkerMessageQueue.h"
#include "render/plugin_render.h"

class NapiManager {
public:
    ~NapiManager() {}

    static NapiManager* GetInstance()
    {
        return &NapiManager::manager_;
    }

    static napi_value GetContext(napi_env env, napi_callback_info info);

    /******************************APP Lifecycle******************************/
    static napi_value NapiOnCreate(napi_env env, napi_callback_info info);
    static napi_value NapiOnShow(napi_env env, napi_callback_info info);
    static napi_value NapiOnHide(napi_env env, napi_callback_info info);
    static napi_value NapiOnDestroy(napi_env env, napi_callback_info info);
    /*********************************************************************/

    /******************************声明式范式******************************/
    /**                      JS Page : Lifecycle                        **/
    static napi_value NapiOnPageShow(napi_env env, napi_callback_info info);
    static napi_value NapiOnPageHide(napi_env env, napi_callback_info info);
    void OnPageShowNative();
    void OnPageHideNative();
    /*************************************************************************/

    // Worker Func
    static napi_value napiWorkerInit(napi_env env, napi_callback_info info);
    static napi_value napiNativeEngineStart(napi_env env, napi_callback_info info);

    OH_NativeXComponent* GetNativeXComponent();
    void SetNativeXComponent(OH_NativeXComponent* nativeXComponent);

public:
    // Napi export
    bool Export(napi_env env, napi_value exports);
private:
    static void MainOnMessage(const uv_async_t* req);
    static NapiManager manager_;

    OH_NativeXComponent* nativeXComponent_ = nullptr;

public:
    napi_env mainEnv_ = nullptr;
    uv_loop_t* mainLoop_ = nullptr;
    uv_async_t mainOnMessageSignal_ {};
};

#endif // _PLUGIN_MANAGER_H_