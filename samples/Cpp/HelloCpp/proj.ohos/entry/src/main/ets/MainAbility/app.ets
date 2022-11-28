// @ts-nocheck
import nativerender from "libnativerender.so";
import { ContextType } from "./common/Constants"
import resourceManager from '@ohos.resourceManager';
const nativeAppLifecycle = nativerender.getContext(ContextType.APP_LIFECYCLE);
const rawFileUtils = nativerender.getContext(ContextType.RAW_FILE_UTILS);

export default {
  onCreate() {
    console.info('[LIFECYCLE-App] onCreate')
    nativeAppLifecycle.onCreate();
    resourceManager.getResourceManager().then(resmgr => {
      rawFileUtils.nativeResourceManagerInit(resmgr);
      console.info("test")
    });
  },
  onShow() {
    console.info('[LIFECYCLE-App] onShow')
    nativeAppLifecycle.onShow();
  },
  onHide() {
    console.info('[LIFECYCLE-App] onHide')
    nativeAppLifecycle.onHide();
  },
  onDestroy() {
    console.info('[LIFECYCLE-App] onDestroy')
    nativeAppLifecycle.onDestroy();
  },
}