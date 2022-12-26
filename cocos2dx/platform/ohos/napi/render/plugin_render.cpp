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

#include <stdint.h>

#include "plugin_render.h"
#include "plugin_common.h"
#include "plugin_manager.h"

#include "../modules/TouchesNapi.h"

// #include "AppDelegate.h"
#include "CCLogOhos.h"
#include "cocos2d.h"
using namespace cocos2d;

#ifdef __cplusplus
extern "C" {
#endif

PluginRender* PluginRender::instance_ = nullptr;
OH_NativeXComponent_Callback PluginRender::callback_;
std::queue<OH_NativeXComponent_TouchEvent*> PluginRender::touchEventQueue_;

void OnSurfaceCreatedCB(OH_NativeXComponent* component, void* window)
{
    LOGD("OnSurfaceCreatedCB");
    PluginRender::GetInstance()->sendMsgToWorker(MessageType::WM_XCOMPONENT_SURFACE_CREATED, component, window);
}

void OnSurfaceChangedCB(OH_NativeXComponent* component, void* window)
{
    LOGD("OnSurfaceChangedCB");
    PluginRender::GetInstance()->sendMsgToWorker(MessageType::WM_XCOMPONENT_SURFACE_CHANGED, component, window);
}

void OnSurfaceDestroyedCB(OH_NativeXComponent* component, void* window)
{
    LOGD("OnSurfaceDestroyedCB");
    PluginRender::GetInstance()->sendMsgToWorker(MessageType::WM_XCOMPONENT_SURFACE_DESTROY, component, window);
}

void DispatchTouchEventCB(OH_NativeXComponent* component, void* window)
{
    LOGD("DispatchTouchEventCB");
    OH_NativeXComponent_TouchEvent* touchEvent = new(std::nothrow) OH_NativeXComponent_TouchEvent();
    if (!touchEvent) {
        LOGE("DispatchTouchEventCB::touchEvent alloc failed");
        return;
    }
    int32_t ret = OH_NativeXComponent_GetTouchEvent(component, window, touchEvent);
    if (ret == OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        PluginRender::touchEventQueue_.push(touchEvent);
    }
    PluginRender::GetInstance()->sendMsgToWorker(MessageType::WM_XCOMPONENT_TOUCH_EVENT, component, window);
}

PluginRender::PluginRender() : component_(nullptr)
{
    auto renderCallback = PluginRender::GetNXComponentCallback();
    renderCallback->OnSurfaceCreated = OnSurfaceCreatedCB;
    renderCallback->OnSurfaceChanged = OnSurfaceChangedCB;
    renderCallback->OnSurfaceDestroyed = OnSurfaceDestroyedCB;
    renderCallback->DispatchTouchEvent = DispatchTouchEventCB;
}

PluginRender* PluginRender::GetInstance()
{
    if (instance_ == nullptr) {
        instance_ = new PluginRender();
    }
    return instance_;
}

OH_NativeXComponent_Callback* PluginRender::GetNXComponentCallback()
{
    return &PluginRender::callback_;
}

// static
void PluginRender::onMessageCallback(const uv_async_t* /* req */) {
    // LOGD("PluginRender::onMessageCallback");
    void* window = nullptr;
    WorkerMessageData msgData;
    PluginRender* render = PluginRender::GetInstance();

    while (true) {
        //loop until all msg dispatch
        if (!render->dequeue(reinterpret_cast<WorkerMessageData*>(&msgData))) {
            // Queue has no data
            break;
        }

        if ((msgData.type >= MessageType::WM_XCOMPONENT_SURFACE_CREATED) && (msgData.type <= MessageType::WM_XCOMPONENT_SURFACE_DESTROY)) {
            OH_NativeXComponent* nativexcomponet = reinterpret_cast<OH_NativeXComponent*>(msgData.data);
            CC_ASSERT(nativexcomponet != nullptr);

            if (msgData.type == MessageType::WM_XCOMPONENT_SURFACE_CREATED) {
                render->OnSurfaceCreated(nativexcomponet, msgData.window);
            } else if (msgData.type == MessageType::WM_XCOMPONENT_TOUCH_EVENT) {
                render->DispatchTouchEvent(nativexcomponet, msgData.window);
            } else if (msgData.type == MessageType::WM_XCOMPONENT_SURFACE_CHANGED) {
                render->OnSurfaceChanged(nativexcomponet, msgData.window);
            } else if (msgData.type == MessageType::WM_XCOMPONENT_SURFACE_DESTROY) {
                render->OnSurfaceDestroyed(nativexcomponet, msgData.window);
            } else {
                CC_ASSERT(false);
            }
            continue;
        }

        if (msgData.type == MessageType::WM_APP_SHOW) {
            render->OnShowNative();
        } else if (msgData.type == MessageType::WM_APP_HIDE) {
            render->OnHideNative();
        } else if (msgData.type == MessageType::WM_APP_DESTROY) {
            render->OnDestroyNative();
        }
        if(msgData.type == MessageType::WM_VSYNC) {
            // render->runTask();
        }
    }
}

// static
void PluginRender::timerCb(uv_timer_t* handle)
{
    // LOGD("PluginRender::timerCb");
    if (PluginRender::GetInstance()->eglCore_ != nullptr) {
        cocos2d::CCDirector::sharedDirector()->mainLoop();
        PluginRender::GetInstance()->eglCore_->Update();
    }
}

void PluginRender::SetNativeXComponent(OH_NativeXComponent* component)
{
    component_ = component;
    OH_NativeXComponent_RegisterCallback(component_, &PluginRender::callback_);
}

void PluginRender::workerInit(napi_env env, uv_loop_t* loop) {
    LOGD("PluginRender::workerInit");
    workerLoop_ = loop;
    if (workerLoop_) {
        uv_async_init(workerLoop_, &messageSignal_, reinterpret_cast<uv_async_cb>(PluginRender::onMessageCallback));
        if (!messageQueue_.empty()) {
            triggerMessageSignal(); // trigger the signal to handle the pending message
        }
    }
}

void PluginRender::sendMsgToWorker(const MessageType& type, OH_NativeXComponent* component, void* window) {
    WorkerMessageData data{type, static_cast<void*>(component), window};
    enqueue(data);
}

void PluginRender::enqueue(const WorkerMessageData& msg) {
    messageQueue_.enqueue(msg);
    triggerMessageSignal();
}

bool PluginRender::dequeue(WorkerMessageData* msg) {
    return messageQueue_.dequeue(msg);
}

void PluginRender::triggerMessageSignal() {
    if(workerLoop_ != nullptr) {
        // It is possible that when the message is sent, the worker thread has not yet started.
        uv_async_send(&messageSignal_);
    }
}

void PluginRender::run() {
    LOGD("PluginRender::run");
    if (workerLoop_) {
    // Todo: Starting the timer in this way is inaccurate and will be fixed later.
        uv_timer_init(workerLoop_, &timerHandle_);
        timerInited_ = true;
    // 1s = 1000ms = 60fps;
    // 1000ms / 60fps = 16 ms/fps
        uv_timer_start(&timerHandle_, &PluginRender::timerCb, 16, true);
    }
}

void Cocos2dxRenderer_nativeInit(int w, int h);
void PluginRender::OnSurfaceCreated(OH_NativeXComponent* component, void* window)
{
    LOGD("PluginRender::OnSurfaceCreated");
    eglCore_ = new EGLCore();
    int32_t ret = OH_NativeXComponent_GetXComponentSize(component, window, &width_, &height_);
    if (ret == OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        eglCore_->GLContextInit(window, width_, height_);
        Cocos2dxRenderer_nativeInit(width_, height_);
    }
}

void PluginRender::OnSurfaceChanged(OH_NativeXComponent* component, void* window)
{
}

void PluginRender::OnSurfaceDestroyed(OH_NativeXComponent* component, void* window)
{
}

void PluginRender::DispatchTouchEvent(OH_NativeXComponent* component, void* window)
{
    OH_NativeXComponent_TouchEvent* touchEvent;
    while(!touchEventQueue_.empty()) {
        touchEvent = touchEventQueue_.front();
        touchEventQueue_.pop();

        LOGD("Touch Info : x = %{public}f, y = %{public}f screenx = %{public}f, screeny = %{public}f", touchEvent->x, touchEvent->y, touchEvent->screenX, touchEvent->screenY);
        for (int i = 0; i < touchEvent->numPoints; i++) {
            LOGD("Touch Info : dots[%{public}d] id %{public}d x = %{public}f, y = %{public}f", i, touchEvent->touchPoints[i].id, touchEvent->touchPoints[i].x, touchEvent->touchPoints[i].y);
            LOGD("Touch Info : screenx = %{public}f, screeny = %{public}f", touchEvent->touchPoints[i].screenX, touchEvent->touchPoints[i].screenY);
            LOGD("vtimeStamp = %{public}llu, isPressed = %{public}d", touchEvent->touchPoints[i].timeStamp, touchEvent->touchPoints[i].isPressed);
            switch (touchEvent->touchPoints[i].type) {
                case OH_NATIVEXCOMPONENT_DOWN:
                    Cocos2dxRenderer_nativeTouchesBegin(touchEvent->touchPoints[i].id, touchEvent->touchPoints[i].x, touchEvent->touchPoints[i].y);
                    LOGD("Touch Info : OH_NATIVEXCOMPONENT_DOWN");
                    break;
                case OH_NATIVEXCOMPONENT_UP:
                    Cocos2dxRenderer_nativeTouchesEnd(touchEvent->touchPoints[i].id, touchEvent->touchPoints[i].x, touchEvent->touchPoints[i].y);
                    LOGD("Touch Info : OH_NATIVEXCOMPONENT_UP");
                    break;
                case OH_NATIVEXCOMPONENT_MOVE:
                    Cocos2dxRenderer_nativeTouchesMove(touchEvent->touchPoints[i].id, touchEvent->touchPoints[i].x, touchEvent->touchPoints[i].y);
                    LOGD("Touch Info : OH_NATIVEXCOMPONENT_MOVE");
                    break;
                case OH_NATIVEXCOMPONENT_CANCEL:
                    Cocos2dxRenderer_nativeTouchesCancel(touchEvent->touchPoints[i].id, touchEvent->touchPoints[i].x, touchEvent->touchPoints[i].y);
                    LOGD("Touch Info : OH_NATIVEXCOMPONENT_CANCEL");
                    break;
                case OH_NATIVEXCOMPONENT_UNKNOWN:
                    LOGD("Touch Info : OH_NATIVEXCOMPONENT_UNKNOWN");
                    break;
                default:
                    LOGD("Touch Info : default");
                    break;
            }
        }
        free(touchEvent);
    }
}

void PluginRender::OnCreateNative(napi_env env, uv_loop_t* loop) {
    LOGD("PluginRender::OnCreateNative");
}

void PluginRender::OnShowNative() {
    LOGD("PluginRender::OnShowNative");
    if (timerInited_) {
        uv_timer_start(&timerHandle_, &PluginRender::timerCb, 16, true);
    }
}

void PluginRender::OnHideNative() {
    LOGD("PluginRender::OnHideNative");
    if (timerInited_) {
        uv_timer_stop(&timerHandle_);
    }
}

void PluginRender::OnDestroyNative() {
    LOGD("PluginRender::OnDestoryNative");
    if (timerInited_) {
        uv_timer_stop(&timerHandle_);
    }
}

napi_value PluginRender::Export(napi_env env, napi_value exports)
{
    LOGE("PluginRender::Export");
    // Register JS API
    napi_property_descriptor desc[] = {
        DECLARE_NAPI_FUNCTION("changeShape", PluginRender::NapiChangeShape),
        DECLARE_NAPI_FUNCTION("drawTriangle", PluginRender::NapiDrawTriangle),
        DECLARE_NAPI_FUNCTION("changeColor", PluginRender::NapiChangeColor),
    };
    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc));
    return exports;
}

napi_value PluginRender::NapiChangeShape(napi_env env, napi_callback_info info)
{
    LOGD("PluginRender::NapiChangeShape");
    PluginRender* instance = PluginRender::GetInstance();
    if (instance) {
        CCDirector::sharedDirector()->mainLoop();
        instance->eglCore_->Update();
    }
    return nullptr;
}

napi_value PluginRender::NapiDrawTriangle(napi_env env, napi_callback_info info)
{
    LOGD("NapiDrawTriangle");
    return nullptr;
}

napi_value PluginRender::NapiChangeColor(napi_env env, napi_callback_info info)
{
    LOGD("NapiChangeColor");
    return nullptr;
}

#ifdef __cplusplus
}
#endif