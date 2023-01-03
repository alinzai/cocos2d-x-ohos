// @ts-nocheck
import nativerender from "libnativerender.so";
import Ability from '@ohos.application.Ability';
import { ContextType } from "../common/Constants"
import resourceManager from '@ohos.resourceManager';
const nativeAppLifecycle = nativerender.getContext(ContextType.APP_LIFECYCLE);
const rawFileUtils = nativerender.getContext(ContextType.RAW_FILE_UTILS);

export default class MainAbility extends Ability {
    onCreate(want, launchParam) {
        nativeAppLifecycle.onCreate();
        globalThis.abilityContext = this.context;
        console.info('[LIFECYCLE-App] onCreate')
    }

    onDestroy() {
        nativeAppLifecycle.onDestroy();
        console.info('[LIFECYCLE-App] onDestroy')
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
        console.info('[LIFECYCLE-App] onShow')
        nativeAppLifecycle.onShow();
    }

    onBackground() {
        // Ability has back to background
        console.info('[LIFECYCLE-App] onDestroy')
        nativeAppLifecycle.onHide();
    }
};
