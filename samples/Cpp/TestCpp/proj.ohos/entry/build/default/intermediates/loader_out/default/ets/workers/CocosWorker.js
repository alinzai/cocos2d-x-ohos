var _db1e3f18b39670795846b2d01fcc4338;
/******/ (() => { // webpackBootstrap
/******/ 	var __webpack_modules__ = ({

/***/ "D:\\work\\cocos2d-x-ohos\\cocos2dx\\platform\\ohos\\libcocos2dx\\src\\main\\ets\\components\\audio\\AudioEngine.ts":
/*!**************************************************************************************************************!*\
  !*** D:\work\cocos2d-x-ohos\cocos2dx\platform\ohos\libcocos2dx\src\main\ets\components\audio\AudioEngine.ts ***!
  \**************************************************************************************************************/
/***/ (function(__unused_webpack_module, exports, __webpack_require__) {

"use strict";

var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", ({ value: true }));
const CC2dxMusic_1 = __importDefault(__webpack_require__(/*! ./CC2dxMusic */ "D:\\work\\cocos2d-x-ohos\\cocos2dx\\platform\\ohos\\libcocos2dx\\src\\main\\ets\\components\\audio\\CC2dxMusic.ts"));
const CC2dxSound_1 = __importDefault(__webpack_require__(/*! ./CC2dxSound */ "D:\\work\\cocos2d-x-ohos\\cocos2dx\\platform\\ohos\\libcocos2dx\\src\\main\\ets\\components\\audio\\CC2dxSound.ts"));
let backgroundMusicModel = new CC2dxMusic_1.default();
backgroundMusicModel.setLoop(true);
function preloadBackgroundMusic(uri) {
    return backgroundMusicModel.preload(uri);
}
function playBackgroundMusic(uri, seek, startplay) {
    return backgroundMusicModel.play(uri, seek, startplay);
}
function stopBackgroundMusic() {
    return backgroundMusicModel.stop();
}
function setBackgroundVolume(volume) {
    return backgroundMusicModel.setVolume(volume);
}
function getBackgroundVolume() {
    return backgroundMusicModel.getVolume();
}
function pauseBackgroundMusic() {
    return backgroundMusicModel.pause();
}
function resumeBackgroundMusic() {
    return backgroundMusicModel.resume();
}
function seekBackgroundMusic(seek) {
    return backgroundMusicModel.seek(seek);
}
function releaseBackgroundMusic() {
    backgroundMusicModel.release();
    backgroundMusicModel = new CC2dxMusic_1.default();
    return 0;
}
globalThis.ccCpp2Js = {};
globalThis.ccCpp2Js.preloadBackgroundMusic = preloadBackgroundMusic;
globalThis.ccCpp2Js.playBackgroundMusic = playBackgroundMusic;
globalThis.ccCpp2Js.stopBackgroundMusic = stopBackgroundMusic;
globalThis.ccCpp2Js.setBackgroundVolume = setBackgroundVolume;
globalThis.ccCpp2Js.getBackgroundVolume = getBackgroundVolume;
globalThis.ccCpp2Js.pauseBackgroundMusic = pauseBackgroundMusic;
globalThis.ccCpp2Js.resumeBackgroundMusic = resumeBackgroundMusic;
globalThis.ccCpp2Js.seekBackgroundMusic = seekBackgroundMusic;
globalThis.ccCpp2Js.releaseBackgroundMusic = releaseBackgroundMusic;
globalThis.ccCpp2Js.getEffectsVolume = CC2dxSound_1.default.getInstance().getVolume;
globalThis.ccCpp2Js.setEffectsVolume = CC2dxSound_1.default.getInstance().setVolume;
globalThis.ccCpp2Js.playEffect = CC2dxSound_1.default.getInstance().play;
globalThis.ccCpp2Js.pauseEffect = CC2dxSound_1.default.getInstance().pause;
globalThis.ccCpp2Js.pauseAllEffects = CC2dxSound_1.default.getInstance().pauseAll;
globalThis.ccCpp2Js.resumeEffect = CC2dxSound_1.default.getInstance().resume;
globalThis.ccCpp2Js.resumeAllEffects = CC2dxSound_1.default.getInstance().resumeAll;
globalThis.ccCpp2Js.stopEffect = CC2dxSound_1.default.getInstance().stop;
globalThis.ccCpp2Js.stopAllEffects = CC2dxSound_1.default.getInstance().stopAll;
globalThis.ccCpp2Js.preloadEffect = CC2dxSound_1.default.getInstance().preload;
globalThis.ccCpp2Js.isEffectPreloaded = CC2dxSound_1.default.getInstance().isEffectPreloaded;
globalThis.ccCpp2Js.unloadEffect = CC2dxSound_1.default.getInstance().unload;


/***/ }),

/***/ "D:\\work\\cocos2d-x-ohos\\cocos2dx\\platform\\ohos\\libcocos2dx\\src\\main\\ets\\components\\audio\\CC2dxMusic.ts":
/*!*************************************************************************************************************!*\
  !*** D:\work\cocos2d-x-ohos\cocos2dx\platform\ohos\libcocos2dx\src\main\ets\components\audio\CC2dxMusic.ts ***!
  \*************************************************************************************************************/
/***/ (function(__unused_webpack_module, exports, __webpack_require__) {

"use strict";

var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", ({ value: true }));
exports.PlayResult = void 0;
var _ohos_multimedia_media_1  = globalThis.requireNapi('multimedia.media') || (isSystemplugin('multimedia.media', 'ohos') ? globalThis.ohosplugin.multimedia.media : isSystemplugin('multimedia.media', 'system') ? globalThis.systemplugin.multimedia.media : undefined);
__webpack_require__(/*! @ohos.resourceManager */ "../../api/@ohos.resourceManager.d.ts");
var _ohos_fileio_1  = globalThis.requireNapi('fileio') || (isSystemplugin('fileio', 'ohos') ? globalThis.ohosplugin.fileio : isSystemplugin('fileio', 'system') ? globalThis.systemplugin.fileio : undefined);
var PlayResult;
(function (PlayResult) {
    PlayResult[PlayResult["failed"] = 0] = "failed";
    PlayResult[PlayResult["success"] = 1] = "success";
})(PlayResult = exports.PlayResult || (exports.PlayResult = {}));
;
class CC2dxMusicModel {
    constructor() {
        this.isPlaying = false;
        this.volume = 0.5;
        this.player = _ohos_multimedia_media_1.createAudioPlayer();
        this.player.setVolume(0.5);
    }
    preloadAndPlay(fileUri, needPlay) {
        this.uri = fileUri;
        if (fileUri.startsWith('/')) {
            _ohos_fileio_1.open(this.uri, (err, fdNumber) => {
                let fdPath = 'fd://';
                let source = fdPath + fdNumber;
                let self = this;
                if (source === this.player.src && this.player.state != 'idle' && this.player.state != 'stopped') {
                    console.info('MusicPlayer[PlayerModel] preLoad finished. src not changed');
                    //                callback();
                }
                else if (this.player.state === 'idle') {
                    this.player.on('dataLoad', () => {
                        console.info('MusicPlayer[PlayerModel] dataLoad callback, state=' + self.player.state);
                        //                    callback();
                    });
                    console.info('MusicPlayer[PlayerModel] player.src=' + source);
                    this.player.src = source;
                }
                else {
                    //                this.notifyPlayingStatus(false);
                    //                this.cancelTimer();
                    console.info('MusicPlayer[PlayerModel] player.reset');
                    self.player.reset();
                    console.info('MusicPlayer[PlayerModel] player.reset done, state=' + self.player.state);
                    self.player.on('dataLoad', () => {
                        console.info('MusicPlayer[PlayerModel] dataLoad callback, state=' + self.player.state);
                        //                    callback();
                    });
                    console.info('MusicPlayer[PlayerModel] player.src=' + source);
                    self.player.src = source;
                }
                console.info('MusicPlayer[PlayerModel] preLoad ' + source + ' end');
                if (needPlay) {
                    this.play(fileUri, -1, true);
                }
            });
            return PlayResult.success;
        }
        let mgr = globalThis.abilityContext.resourceManager;
        mgr.getRawFileDescriptor(fileUri).then(value => {
            let rawFile = value;
            let fdPath = 'fd://';
            let source = fdPath + rawFile.fd;
            if (typeof (source) === 'undefined') {
                console.error('MusicPlayer[PlayerModel] preLoad ignored, source=' + source);
                return;
            }
            let self = this;
            if (source === this.player.src && this.player.state != 'idle' && this.player.state != 'stopped') {
                console.info('MusicPlayer[PlayerModel] preLoad finished. src not changed');
            }
            else if (this.player.state === 'idle') {
                this.player.on('dataLoad', () => {
                    console.info('MusicPlayer[PlayerModel] dataLoad callback, state=' + self.player.state);
                });
                console.info('MusicPlayer[PlayerModel] player.src=' + source);
                this.player.src = source;
            }
            else {
                console.info('MusicPlayer[PlayerModel] player.reset');
                self.player.reset();
                console.info('MusicPlayer[PlayerModel] player.reset done, state=' + self.player.state);
                self.player.on('dataLoad', () => {
                    console.info('MusicPlayer[PlayerModel] dataLoad callback, state=' + self.player.state);
                });
                console.info('MusicPlayer[PlayerModel] player.src=' + source);
                self.player.src = source;
            }
            console.info('MusicPlayer[PlayerModel] preLoad ' + source + ' end');
            if (needPlay) {
                this.play(fileUri, -1, true);
            }
        }).catch(error => {
            console.log("getRawFileContent promise error is " + error);
        });
        return PlayResult.success;
    }
    preload(fileUri) {
        return this.preloadAndPlay(fileUri, false);
    }
    play(uri, seekTo, startPlay) {
        if (uri != this.uri) {
            // 沒有預加載的，需要預加載並播放
            return this.preloadAndPlay(uri, true);
        }
        console.info('MusicPlayer[PlayerModel] play seekTo=' + seekTo + ', startPlay=' + startPlay);
        if (startPlay) {
            if (seekTo < 0 && this.currentTimeMs > 0) {
                console.info('MusicPlayer[PlayerModel] pop seekTo=' + this.currentTimeMs);
                seekTo = this.currentTimeMs;
            }
            let self = this;
            this.player.on('play', () => {
                console.log('MusicPlayer[PlayerModel] play() callback entered, player.state=' + self.player.state);
                if (seekTo > 0) {
                    self.seek(seekTo);
                }
            });
            console.info('MusicPlayer[PlayerModel] call player.play');
            this.player.play();
            this.isPlaying = true;
            console.info('MusicPlayer[PlayerModel] player.play called player.state=' + this.player.state);
        }
        else if (seekTo > 0) {
            this.currentTimeMs = seekTo;
            console.info('MusicPlayer[PlayerModel] stash seekTo=' + this.currentTimeMs);
        }
        return PlayResult.success;
    }
    pause() {
        if (!this.isPlaying) {
            console.info('MusicPlayer[PlayerModel] pause ignored, isPlaying=' + this.isPlaying);
            return;
        }
        this.isPlaying = false;
        console.info('MusicPlayer[PlayerModel] call player.pause');
        this.player.pause();
        console.info('MusicPlayer[PlayerModel] player.pause called, player.state=' + this.player.state);
        return PlayResult.success;
    }
    resume() {
        if (this.isPlaying) {
            console.info('MusicPlayer[PlayerModel] resume ignored, isPlaying=' + this.isPlaying);
            return;
        }
        this.isPlaying = true;
        console.info('MusicPlayer[PlayerModel] call player.play');
        this.player.play();
        console.info('MusicPlayer[PlayerModel] player.pause called, player.state=' + this.player.state);
        return PlayResult.success;
    }
    seek(ms) {
        this.currentTimeMs = ms;
        this.player.seek(ms);
        return PlayResult.success;
    }
    stop() {
        if (!this.isPlaying) {
            console.info('MusicPlayer[PlayerModel] stop ignored, isPlaying=' + this.isPlaying);
            return;
        }
        console.info('MusicPlayer[PlayerModel] call player.stop');
        this.player.stop();
        console.info('MusicPlayer[PlayerModel] player.stop called, player.state=' + this.player.state);
        this.isPlaying = false;
        this.uri = "";
        return PlayResult.success;
    }
    setVolume(volume) {
        if (volume > 1.0) {
            this.volume = 1.0;
        }
        else if (volume < 0) {
            this.volume = 0;
        }
        else {
            this.volume = volume;
        }
        this.player.setVolume(this.volume);
        return PlayResult.success;
    }
    getVolume() {
        return this.volume;
    }
    release() {
        if (typeof (this.player) != 'undefined') {
            console.info('MusicPlayer[PlayerModel] player.release begin');
            this.player.release();
            console.info('MusicPlayer[PlayerModel] player.release end');
            this.player = undefined;
        }
    }
    setLoop(isLoop) {
        this.player.loop = isLoop;
    }
}
exports["default"] = CC2dxMusicModel;


/***/ }),

/***/ "D:\\work\\cocos2d-x-ohos\\cocos2dx\\platform\\ohos\\libcocos2dx\\src\\main\\ets\\components\\audio\\CC2dxSound.ts":
/*!*************************************************************************************************************!*\
  !*** D:\work\cocos2d-x-ohos\cocos2dx\platform\ohos\libcocos2dx\src\main\ets\components\audio\CC2dxSound.ts ***!
  \*************************************************************************************************************/
/***/ (function(__unused_webpack_module, exports, __webpack_require__) {

"use strict";

var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", ({ value: true }));
const CC2dxMusic_1 = __importDefault(__webpack_require__(/*! ./CC2dxMusic */ "D:\\work\\cocos2d-x-ohos\\cocos2dx\\platform\\ohos\\libcocos2dx\\src\\main\\ets\\components\\audio\\CC2dxMusic.ts"));
class CC2dxSoundPool {
    static getInstance() {
        return CC2dxSoundPool.instance;
    }
    preload(uri) {
        var model;
        var soundId;
        if (CC2dxSoundPool.uriPool.has(uri)) {
            soundId = CC2dxSoundPool.uriPool.get(uri);
            model = CC2dxSoundPool.modelPool.get(soundId);
        }
        else {
            soundId = ++CC2dxSoundPool.soundIdIndex;
            model = new CC2dxMusic_1.default();
            CC2dxSoundPool.modelPool.set(soundId, model);
            CC2dxSoundPool.uriPool.set(uri, soundId);
        }
        model.preload(uri);
        return soundId;
    }
    play(uri, loop) {
        if (!CC2dxSoundPool.uriPool.has(uri)) {
            let model;
            let soundId;
            soundId = ++CC2dxSoundPool.soundIdIndex;
            model = new CC2dxMusic_1.default();
            CC2dxSoundPool.modelPool.set(soundId, model);
            CC2dxSoundPool.uriPool.set(uri, soundId);
            model.setLoop(loop);
            model.preloadAndPlay(uri, true);
            return soundId;
        }
        var soundId = CC2dxSoundPool.uriPool.get(uri);
        var model = CC2dxSoundPool.modelPool.get(soundId);
        model.setLoop(loop);
        model.play(uri, -1, true);
        return soundId;
    }
    stop(soundId) {
        if (!CC2dxSoundPool.modelPool.has(soundId)) {
            // TBD 补充日志
            return;
        }
        var model = CC2dxSoundPool.modelPool.get(soundId);
        model.stop();
    }
    stopAll() {
        CC2dxSoundPool.uriPool.forEach((soundId, key, map) => {
            CC2dxSoundPool.getInstance().stop(soundId);
        });
        return 0;
    }
    resume(soundId) {
        if (!CC2dxSoundPool.modelPool.has(soundId)) {
            // TBD 补充日志
            return;
        }
        var model = CC2dxSoundPool.modelPool.get(soundId);
        model.resume();
    }
    resumeAll() {
        CC2dxSoundPool.uriPool.forEach((soundId, key, map) => {
            CC2dxSoundPool.getInstance().resume(soundId);
        });
        return 0;
    }
    pause(soundId) {
        if (!CC2dxSoundPool.modelPool.has(soundId)) {
            // TBD 补充日志
            return;
        }
        var model = CC2dxSoundPool.modelPool.get(soundId);
        model.pause();
    }
    pauseAll() {
        CC2dxSoundPool.uriPool.forEach((soundId, key, map) => {
            CC2dxSoundPool.getInstance().pause(soundId);
        });
        return 0;
    }
    getVolume() {
        return CC2dxSoundPool.volume;
    }
    setVolume(volume) {
        if (volume > 1.0) {
            CC2dxSoundPool.volume = 1.0;
        }
        else if (volume < 0) {
            CC2dxSoundPool.volume = 0;
        }
        else {
            CC2dxSoundPool.volume = volume;
        }
        CC2dxSoundPool.modelPool.forEach((model, key, map) => {
            model.setVolume(CC2dxSoundPool.volume);
        });
    }
    unload(uri) {
        if (!CC2dxSoundPool.uriPool.has(uri)) {
            // TBD 补充日志
            return;
        }
        var soundId = CC2dxSoundPool.uriPool.get(uri);
        var model = CC2dxSoundPool.modelPool.get(soundId);
        model.release();
        CC2dxSoundPool.modelPool.delete(soundId);
        CC2dxSoundPool.uriPool.delete(uri);
    }
    isEffectPreloaded(uri) {
        return CC2dxSoundPool.uriPool.has(uri);
    }
}
exports["default"] = CC2dxSoundPool;
CC2dxSoundPool.soundIdIndex = 0;
CC2dxSoundPool.instance = new CC2dxSoundPool();
CC2dxSoundPool.modelPool = new Map();
CC2dxSoundPool.uriPool = new Map();
CC2dxSoundPool.volume = 0.5;


/***/ }),

/***/ "D:\\work\\cocos2d-x-ohos\\cocos2dx\\platform\\ohos\\libcocos2dx\\src\\main\\ets\\components\\dialog\\CCDialogWorkerUtils.ts":
/*!***********************************************************************************************************************!*\
  !*** D:\work\cocos2d-x-ohos\cocos2dx\platform\ohos\libcocos2dx\src\main\ets\components\dialog\CCDialogWorkerUtils.ts ***!
  \***********************************************************************************************************************/
/***/ (function(__unused_webpack_module, exports) {

"use strict";

var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", ({ value: true }));
var _ohos_hilog_1  = globalThis.requireNapi('hilog') || (isSystemplugin('hilog', 'ohos') ? globalThis.ohosplugin.hilog : isSystemplugin('hilog', 'system') ? globalThis.systemplugin.hilog : undefined);
class CCDialogUtils {
    static init(parentPort) {
        CCDialogUtils.parentPort = parentPort;
    }
    static showDialogPostToMainThread(message, title) {
        _ohos_hilog_1.debug(0x0000, 'testTag', 'CCDialogUtils showDialogPostToMainThread!');
        CCDialogUtils.parentPort.postMessage({ 'function': 'showDialog', 'title': title, 'message': message });
    }
}
exports["default"] = CCDialogUtils;
globalThis.ccDialogUtils = {};
globalThis.ccDialogUtils.showDialog = CCDialogUtils.showDialogPostToMainThread;


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

/***/ "D:\\work\\cocos2d-x-ohos\\samples\\Cpp\\TestCpp\\proj.ohos\\entry\\src\\main\\ets\\workers\\CocosWorker.ts":
/*!******************************************************************************************************!*\
  !*** D:\work\cocos2d-x-ohos\samples\Cpp\TestCpp\proj.ohos\entry\src\main\ets\workers\CocosWorker.ts ***!
  \******************************************************************************************************/
/***/ (function(__unused_webpack_module, exports, __webpack_require__) {

"use strict";

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
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", ({ value: true }));
var _ohos_worker_1  = globalThis.requireNapi('worker') || (isSystemplugin('worker', 'ohos') ? globalThis.ohosplugin.worker : isSystemplugin('worker', 'system') ? globalThis.systemplugin.worker : undefined);
var nativerender = globalThis.requireNapi("nativerender", true, "ohos.samples.etsxcomponent/entry");
;
const Constants_1 = __webpack_require__(/*! ../common/Constants */ "D:\\work\\cocos2d-x-ohos\\samples\\Cpp\\TestCpp\\proj.ohos\\entry\\src\\main\\ets\\common\\Constants.ts");
__webpack_require__(/*! @ohos/libcocos2dx/src/main/ets/components/audio/AudioEngine */ "D:\\work\\cocos2d-x-ohos\\cocos2dx\\platform\\ohos\\libcocos2dx\\src\\main\\ets\\components\\audio\\AudioEngine.ts");
const CCDialogWorkerUtils_1 = __importDefault(__webpack_require__(/*! @ohos/libcocos2dx/src/main/ets/components/dialog/CCDialogWorkerUtils */ "D:\\work\\cocos2d-x-ohos\\cocos2dx\\platform\\ohos\\libcocos2dx\\src\\main\\ets\\components\\dialog\\CCDialogWorkerUtils.ts"));
console.log("[cocos] native render workerInit =-------> ");
const nativeContext = nativerender.getContext(Constants_1.ContextType.WORKER_INIT);
nativeContext.workerInit();
const parentPort = _ohos_worker_1.parentPort;
parentPort.onmessage = function (e) {
    var data = e.data;
    switch (data.type) {
        case "onXCLoad":
            console.log("[cocos] onXCLoad Callback");
            const renderContext = nativerender.getContext(Constants_1.ContextType.NATIVE_RENDER_API);
            renderContext.nativeEngineStart();
            CCDialogWorkerUtils_1.default.init(parentPort);
            break;
        case "audioInit":
            globalThis.abilityContext = data.data;
            break;
        default:
            console.error("cocos worker: message type unknown");
    }
};


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
/******/ 	var __webpack_exports__ = __webpack_require__("D:\\work\\cocos2d-x-ohos\\samples\\Cpp\\TestCpp\\proj.ohos\\entry\\src\\main\\ets\\workers\\CocosWorker.ts");
/******/ 	_db1e3f18b39670795846b2d01fcc4338 = __webpack_exports__;
/******/ 	
/******/ })()
;
//# sourceMappingURL=CocosWorker.js.map