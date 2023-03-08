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

#ifndef _PLUGIN_RENDER_H_
#define _PLUGIN_RENDER_H_

#include <string>
#include <unordered_map>
#include <uv.h>

#include <ace/xcomponent/native_interface_xcomponent.h>
#include <napi/native_api.h>

#include "egl_core.h"
#include "../WorkerMessageQueue.h"

class PluginRender {
public:
    PluginRender();
    static PluginRender* GetInstance();
    static OH_NativeXComponent_Callback* GetNXComponentCallback();

    static void onMessageCallback(const uv_async_t* req);
    static void timerCb(uv_timer_t* handle);

    void SetNativeXComponent(OH_NativeXComponent* component);

    void workerInit(napi_env env, uv_loop_t* loop);

    void sendMsgToWorker(const MessageType& type, OH_NativeXComponent* component, void* window); 
    void enqueue(const WorkerMessageData& data);
    bool dequeue(WorkerMessageData* data);
    void triggerMessageSignal();
    void run();

public:
    // NAPI interface
    napi_value Export(napi_env env, napi_value exports);

    // Exposed to JS developers by NAPI
    static napi_value NapiChangeShape(napi_env env, napi_callback_info info);
    static napi_value NapiDrawTriangle(napi_env env, napi_callback_info info);
    static napi_value NapiChangeColor(napi_env env, napi_callback_info info);
    static napi_value NapiChangeColorWorker(napi_env env, napi_callback_info info);

    // Callback, called by ACE XComponent
    void OnSurfaceCreated(OH_NativeXComponent* component, void* window);

    void OnSurfaceChanged(OH_NativeXComponent* component, void* window);

    void OnSurfaceDestroyed(OH_NativeXComponent* component, void* window);

    void DispatchTouchEvent(OH_NativeXComponent* component, void* window);

    void OnCreateNative(napi_env env, uv_loop_t* loop);
    void OnShowNative();
    void OnHideNative();
    void OnDestroyNative();

public:
    static PluginRender* instance_;
    static OH_NativeXComponent_Callback callback_;
    static std::queue<OH_NativeXComponent_TouchEvent*> touchEventQueue_;

    OH_NativeXComponent* component_{nullptr};
    uv_timer_t timerHandle_;
    bool timerInited_{false};
    uv_loop_t* workerLoop_{nullptr};
    uv_async_t messageSignal_{};
    WorkerMessageQueue messageQueue_;
    EGLCore* eglCore_{nullptr};

    uint64_t width_;
    uint64_t height_;

    double x_;
    double y_;
};

#endif // _PLUGIN_RENDER_H_
