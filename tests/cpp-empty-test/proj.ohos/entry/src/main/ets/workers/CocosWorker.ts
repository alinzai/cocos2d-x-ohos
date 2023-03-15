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

import worker from '@ohos.worker';
import nativerender from "libnativerender.so";
import { ContextType } from "../common/Constants"
import "../../../../../../../../cocos/platform/ohos/libcocos2dx/src/main/ets/components/audio/AudioEngine"
import  CCDialogUtils from "../../../../../../../../cocos/platform/ohos/libcocos2dx/src/main/ets/components/dialog/CCDialogWorkerUtils"


console.log("[cocos] native render workerInit =-------> ");
const nativeContext = nativerender.getContext(ContextType.WORKER_INIT);
nativeContext.workerInit()

const parentPort = worker.parentPort;

parentPort.onmessage = function(e) {
    var data = e.data;
    switch(data.type) {
        case "onXCLoad":
            console.log("[cocos] onXCLoad Callback");
            const renderContext = nativerender.getContext(ContextType.NATIVE_RENDER_API);
            renderContext.nativeEngineStart();
            CCDialogUtils.init(parentPort);
            break;
        case "audioInit":
            globalThis.abilityContext = data.data;
            break;
        default:
            console.error("cocos worker: message type unknown")
    }
}


