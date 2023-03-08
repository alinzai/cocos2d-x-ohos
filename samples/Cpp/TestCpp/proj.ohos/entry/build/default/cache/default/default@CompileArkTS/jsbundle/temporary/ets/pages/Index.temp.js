var _db1e3f18b39670795846b2d01fcc4338;
/******/ (() => { // webpackBootstrap
/******/ 	var __webpack_modules__ = ({

/***/ "D:\\work\\cocos2d-x-ohos\\cocos2dx\\platform\\ohos\\libcocos2dx\\src\\main\\ets\\components\\dialog\\DialogUtils.ts":
/*!***************************************************************************************************************!*\
  !*** D:\work\cocos2d-x-ohos\cocos2dx\platform\ohos\libcocos2dx\src\main\ets\components\dialog\DialogUtils.ts ***!
  \***************************************************************************************************************/
/***/ (function(__unused_webpack_module, exports) {

"use strict";

var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", ({ value: true }));
var _system_prompt_1  = isSystemplugin('prompt', 'system') ? globalThis.systemplugin.prompt : globalThis.requireNapi('prompt');
var _ohos_hilog_1  = globalThis.requireNapi('hilog') || (isSystemplugin('hilog', 'ohos') ? globalThis.ohosplugin.hilog : isSystemplugin('hilog', 'system') ? globalThis.systemplugin.hilog : undefined);
class CCDialogUtils {
    static showDialogInUiThread(eventData) {
        let dialogTitle = eventData.title;
        let dialogMessage = eventData.message;
        return this.showDialog(dialogTitle, dialogMessage);
    }
    static showDialog(dialogTitle, dialogMessage) {
        _system_prompt_1.showDialog({
            title: dialogTitle,
            message: dialogMessage,
            buttons: [
                {
                    text: 'OK',
                    color: '#000000'
                },
            ],
            success: function (data) {
                _ohos_hilog_1.debug(0x0000, 'testTag', "handling callback", data);
            }
        });
        return CCDialogUtils.SUCCESS;
    }
}
exports["default"] = CCDialogUtils;
CCDialogUtils.SUCCESS = 0;


/***/ }),

/***/ "D:\\work\\cocos2d-x-ohos\\cocos2dx\\platform\\ohos\\libcocos2dx\\src\\main\\ets\\components\\thread\\ThreadUtils.ts":
/*!***************************************************************************************************************!*\
  !*** D:\work\cocos2d-x-ohos\cocos2dx\platform\ohos\libcocos2dx\src\main\ets\components\thread\ThreadUtils.ts ***!
  \***************************************************************************************************************/
/***/ (function(__unused_webpack_module, exports, __webpack_require__) {

"use strict";

var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", ({ value: true }));
__webpack_require__(/*! @ohos.worker */ "../../api/@ohos.worker.d.ts");
var _ohos_hilog_1  = globalThis.requireNapi('hilog') || (isSystemplugin('hilog', 'ohos') ? globalThis.ohosplugin.hilog : isSystemplugin('hilog', 'system') ? globalThis.systemplugin.hilog : undefined);
const DialogUtils_1 = __importDefault(__webpack_require__(/*! ../dialog/DialogUtils */ "D:\\work\\cocos2d-x-ohos\\cocos2dx\\platform\\ohos\\libcocos2dx\\src\\main\\ets\\components\\dialog\\DialogUtils.ts"));
class ThreadUtils {
    static recvWorkerThreadMessage(event) {
        var eventData = event.data;
        _ohos_hilog_1.debug(0x0000, 'cocos', 'mainThread recv:' + eventData.function);
        switch (eventData.function) {
            case "showDialog":
                let title = eventData.title;
                let message = eventData.message;
                DialogUtils_1.default.showDialog(title, message);
                break;
        }
    }
}
exports["default"] = ThreadUtils;


/***/ }),

/***/ "D:\\work\\cocos2d-x-ohos\\samples\\Cpp\\TestCpp\\proj.ohos\\entry\\src\\main\\ets\\common\\Constants.ts":
/*!***************************************************************************************************!*\
  !*** D:\work\cocos2d-x-ohos\samples\Cpp\TestCpp\proj.ohos\entry\src\main\ets\common\Constants.ts ***!
  \***************************************************************************************************/
/***/ ((__unused_webpack_module, exports) => {

"use strict";

Object.defineProperty(exports, "__esModule", ({ value: true }));
exports.Constants = exports.ContextType = void 0;
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
var ContextType;
(function (ContextType) {
    ContextType[ContextType["APP_LIFECYCLE"] = 0] = "APP_LIFECYCLE";
    ContextType[ContextType["JSPAGE_LIFECYCLE"] = 1] = "JSPAGE_LIFECYCLE";
    ContextType[ContextType["RAW_FILE_UTILS"] = 2] = "RAW_FILE_UTILS";
    ContextType[ContextType["WORKER_INIT"] = 3] = "WORKER_INIT";
    ContextType[ContextType["NATIVE_RENDER_API"] = 4] = "NATIVE_RENDER_API";
})(ContextType = exports.ContextType || (exports.ContextType = {}));
class Constants {
}
exports.Constants = Constants;
Constants.APP_KEY_WORKER_MANAGER = "app_key_worker_manager";


/***/ }),

/***/ "D:\\work\\cocos2d-x-ohos\\samples\\Cpp\\TestCpp\\proj.ohos\\entry\\src\\main\\ets\\pages\\Index.ets?entry":
/*!*****************************************************************************************************!*\
  !*** D:\work\cocos2d-x-ohos\samples\Cpp\TestCpp\proj.ohos\entry\src\main\ets\pages\Index.ets?entry ***!
  \*****************************************************************************************************/
/***/ (function(__unused_webpack_module, exports, __webpack_require__) {

"use strict";

var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", ({ value: true }));
let __generate__Id = 0;
function generateId() {
    return "Index_" + ++__generate__Id;
}
// @ts-nocheck
var nativerender = globalThis.requireNapi("nativerender", true, "ohos.samples.etsxcomponent/entry");
;
const Constants_1 = __webpack_require__(/*! ../common/Constants */ "D:\\work\\cocos2d-x-ohos\\samples\\Cpp\\TestCpp\\proj.ohos\\entry\\src\\main\\ets\\common\\Constants.ts");
const WorkerManager_1 = __webpack_require__(/*! ../workers/WorkerManager */ "D:\\work\\cocos2d-x-ohos\\samples\\Cpp\\TestCpp\\proj.ohos\\entry\\src\\main\\ets\\workers\\WorkerManager.ets");
const ThreadUtils_1 = __importDefault(__webpack_require__(/*! @ohos/libcocos2dx/src/main/ets/components/thread/ThreadUtils */ "D:\\work\\cocos2d-x-ohos\\cocos2dx\\platform\\ohos\\libcocos2dx\\src\\main\\ets\\components\\thread\\ThreadUtils.ts"));
__webpack_require__(/*! @ohos.window */ "../../api/@ohos.window.d.ts");
const nativePageLifecycle = nativerender.getContext(Constants_1.ContextType.JSPAGE_LIFECYCLE);
const rawFileUtils = nativerender.getContext(Constants_1.ContextType.RAW_FILE_UTILS);
class Index extends View {
    constructor(compilerAssignedUniqueChildId, parent, params) {
        super(compilerAssignedUniqueChildId, parent);
        this.context = null;
        this.cocosWorker = WorkerManager_1.WorkerManager.getInstance().getWorker();
        this.updateWithValueParams(params);
    }
    updateWithValueParams(params) {
        if (params.context !== undefined) {
            this.context = params.context;
        }
        if (params.cocosWorker !== undefined) {
            this.cocosWorker = params.cocosWorker;
        }
    }
    aboutToBeDeleted() {
        SubscriberManager.Get().delete(this.id());
    }
    onPageShow() {
        console.log('[LIFECYCLE-Page] onPageShow');
        nativePageLifecycle.onPageShow();
    }
    onPageHide() {
        console.log('[LIFECYCLE-Page] onPageHide');
        nativePageLifecycle.onPageHide();
    }
    render() {
        Flex.create({ direction: FlexDirection.Column, alignItems: ItemAlign.Center, justifyContent: FlexAlign.Center });
        Flex.width('100%');
        Flex.height('100%');
        XComponent.create({ id: 'xcomponentId', type: 'surface', libraryname: 'nativerender' }, "ohos.samples.etsxcomponent/entry");
        XComponent.onLoad((context) => {
            console.log('[cocos] XComponent.onLoad Callback');
            this.context = context;
            this.cocosWorker.postMessage({ type: "onXCLoad", data: "XComponent" });
            this.cocosWorker.postMessage({ type: "audioInit", data: globalThis.abilityContext });
            this.cocosWorker.onmessage = ThreadUtils_1.default.recvWorkerThreadMessage;
        });
        XComponent.onDestroy(() => {
        });
        Flex.pop();
    }
}
loadDocument(new Index("1", undefined, {}));


/***/ }),

/***/ "D:\\work\\cocos2d-x-ohos\\samples\\Cpp\\TestCpp\\proj.ohos\\entry\\src\\main\\ets\\workers\\WorkerManager.ets":
/*!*********************************************************************************************************!*\
  !*** D:\work\cocos2d-x-ohos\samples\Cpp\TestCpp\proj.ohos\entry\src\main\ets\workers\WorkerManager.ets ***!
  \*********************************************************************************************************/
/***/ (function(__unused_webpack_module, exports, __webpack_require__) {

"use strict";

var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", ({ value: true }));
exports.WorkerManager = void 0;
let __generate__Id = 0;
function generateId() {
    return "WorkerManager_" + ++__generate__Id;
}
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
var _ohos_worker_1  = globalThis.requireNapi('worker') || (isSystemplugin('worker', 'ohos') ? globalThis.ohosplugin.worker : isSystemplugin('worker', 'system') ? globalThis.systemplugin.worker : undefined);
const Constants_1 = __webpack_require__(/*! common/Constants */ "D:\\work\\cocos2d-x-ohos\\samples\\Cpp\\TestCpp\\proj.ohos\\entry\\src\\main\\ets\\common\\Constants.ts");
class WorkerManager {
    constructor() {
        console.log("LIFESTYLE 1111111");
        this.cocosWorker = new _ohos_worker_1.Worker("/entry/ets/workers/CocosWorker.js", { type: "classic", name: "CocosWorker" });
        console.log("LIFESTYLE 222222");
        this.cocosWorker.onerror = function (e) {
            var msg = e.message;
            var filename = e.filename;
            var lineno = e.lineno;
            var colno = e.colno;
            console.error(`on Error ${msg} ${filename} ${lineno} ${colno}`);
        };
    }
    static getInstance() {
        if (AppStorage.Get(Constants_1.Constants.APP_KEY_WORKER_MANAGER) == null) {
            AppStorage.SetOrCreate(Constants_1.Constants.APP_KEY_WORKER_MANAGER, new WorkerManager);
        }
        return AppStorage.Get(Constants_1.Constants.APP_KEY_WORKER_MANAGER);
    }
    getWorker() {
        return this.cocosWorker;
    }
}
exports.WorkerManager = WorkerManager;


/***/ }),

/***/ "../../api/@ohos.window.d.ts":
/*!***********************************!*\
  !*** ../../api/@ohos.window.d.ts ***!
  \***********************************/
/***/ (() => {



/***/ }),

/***/ "../../api/@ohos.worker.d.ts":
/*!***********************************!*\
  !*** ../../api/@ohos.worker.d.ts ***!
  \***********************************/
/***/ (() => {



/***/ })

/******/ 	});
/************************************************************************/
/******/ 	// The module cache
/******/ 	var __webpack_module_cache__ = {};
/******/ 	
/******/ 	// The require function
/******/ 	function __webpack_require__(moduleId) {
/******/ 		var commonCachedModule = globalThis["__common_module_cache___db1e3f18b39670795846b2d01fcc4338"] ? globalThis["__common_module_cache___db1e3f18b39670795846b2d01fcc4338"][moduleId]: null;
/******/ 		if (commonCachedModule) { return commonCachedModule.exports; }
/******/ 		// Check if module is in cache
/******/ 		var cachedModule = __webpack_module_cache__[moduleId];
/******/ 		if (cachedModule !== undefined) {
/******/ 			return cachedModule.exports;
/******/ 		}
/******/ 		// Create a new module (and put it into the cache)
/******/ 		var module = __webpack_module_cache__[moduleId] = {
/******/ 			// no module.id needed
/******/ 			// no module.loaded needed
/******/ 			exports: {}
/******/ 		};
/******/ 	
/******/ 		function isCommonModue(moduleId) {
/******/ 		                if (globalThis["webpackChunk_db1e3f18b39670795846b2d01fcc4338"]) {
/******/ 		                  const length = globalThis["webpackChunk_db1e3f18b39670795846b2d01fcc4338"].length;
/******/ 		                  switch (length) {
/******/ 		                    case 1:
/******/ 		                      return globalThis["webpackChunk_db1e3f18b39670795846b2d01fcc4338"][0][1][moduleId];
/******/ 		                    case 2:
/******/ 		                      return globalThis["webpackChunk_db1e3f18b39670795846b2d01fcc4338"][0][1][moduleId] ||
/******/ 		                      globalThis["webpackChunk_db1e3f18b39670795846b2d01fcc4338"][1][1][moduleId];
/******/ 		                  }
/******/ 		                }
/******/ 		                return undefined;
/******/ 		              }
/******/ 		if (globalThis["__common_module_cache___db1e3f18b39670795846b2d01fcc4338"] && String(moduleId).indexOf("?name=") < 0 && isCommonModue(moduleId)) {
/******/ 		  globalThis["__common_module_cache___db1e3f18b39670795846b2d01fcc4338"][moduleId] = module;
/******/ 		}
/******/ 		__webpack_modules__[moduleId].call(module.exports, module, module.exports, __webpack_require__);
/******/ 	
/******/ 		// Return the exports of the module
/******/ 		return module.exports;
/******/ 	}
/******/ 	
/************************************************************************/
/******/ 	
/******/ 	// startup
/******/ 	// Load entry module and return exports
/******/ 	// This entry module is referenced by other modules so it can't be inlined
/******/ 	var __webpack_exports__ = __webpack_require__("D:\\work\\cocos2d-x-ohos\\samples\\Cpp\\TestCpp\\proj.ohos\\entry\\src\\main\\ets\\pages\\Index.ets?entry");
/******/ 	_db1e3f18b39670795846b2d01fcc4338 = __webpack_exports__;
/******/ 	
/******/ })()
;
//# sourceMappingURL=Index.js.map