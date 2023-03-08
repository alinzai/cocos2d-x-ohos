var _db1e3f18b39670795846b2d01fcc4338;
/******/ (() => { // webpackBootstrap
/******/ 	var __webpack_modules__ = ({

/***/ "D:\\work\\cocos2d-x-ohos\\samples\\Cpp\\TestCpp\\proj.ohos\\entry\\src\\main\\ets\\MainAbility\\MainAbility.ts?entry":
/*!****************************************************************************************************************!*\
  !*** D:\work\cocos2d-x-ohos\samples\Cpp\TestCpp\proj.ohos\entry\src\main\ets\MainAbility\MainAbility.ts?entry ***!
  \****************************************************************************************************************/
/***/ (function(__unused_webpack_module, exports, __webpack_require__) {

"use strict";

var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", ({ value: true }));
// @ts-nocheck
var nativerender = globalThis.requireNapi("nativerender", true, "ohos.samples.etsxcomponent/entry");
;
var _ohos_application_Ability_1  = globalThis.requireNapi('application.Ability') || (isSystemplugin('application.Ability', 'ohos') ? globalThis.ohosplugin.application.Ability : isSystemplugin('application.Ability', 'system') ? globalThis.systemplugin.application.Ability : undefined);
const Constants_1 = __webpack_require__(/*! ../common/Constants */ "D:\\work\\cocos2d-x-ohos\\samples\\Cpp\\TestCpp\\proj.ohos\\entry\\src\\main\\ets\\common\\Constants.ts");
__webpack_require__(/*! @ohos.resourceManager */ "../../api/@ohos.resourceManager.d.ts");
const nativeAppLifecycle = nativerender.getContext(Constants_1.ContextType.APP_LIFECYCLE);
const rawFileUtils = nativerender.getContext(Constants_1.ContextType.RAW_FILE_UTILS);
class MainAbility extends _ohos_application_Ability_1 {
    onCreate(want, launchParam) {
        nativeAppLifecycle.onCreate();
        globalThis.abilityContext = this.context;
        console.info('[LIFECYCLE-App] onCreate');
    }
    onDestroy() {
        nativeAppLifecycle.onDestroy();
        console.info('[LIFECYCLE-App] onDestroy');
    }
    onWindowStageCreate(windowStage) {
        // Main window is created, set main page for this ability
        windowStage.loadContent('pages/Index', (err, data) => {
            if (err.code) {
                return;
            }
            rawFileUtils.nativeResourceManagerInit(this.context.resourceManager);
        });
    }
    onWindowStageDestroy() {
        // Main window is destroyed, release UI related resources
    }
    onForeground() {
        // Ability has brought to foreground
        console.info('[LIFECYCLE-App] onShow');
        nativeAppLifecycle.onShow();
    }
    onBackground() {
        // Ability has back to background
        console.info('[LIFECYCLE-App] onDestroy');
        nativeAppLifecycle.onHide();
    }
}
globalThis.exports.default = MainAbility;
;


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

/***/ "../../api/@ohos.resourceManager.d.ts":
/*!********************************************!*\
  !*** ../../api/@ohos.resourceManager.d.ts ***!
  \********************************************/
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
/******/ 	var __webpack_exports__ = __webpack_require__("D:\\work\\cocos2d-x-ohos\\samples\\Cpp\\TestCpp\\proj.ohos\\entry\\src\\main\\ets\\MainAbility\\MainAbility.ts?entry");
/******/ 	_db1e3f18b39670795846b2d01fcc4338 = __webpack_exports__;
/******/ 	
/******/ })()
;
//# sourceMappingURL=MainAbility.js.map