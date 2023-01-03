// @ts-nocheck
import nativerender from "libnativerender.so";
import { ContextType } from "../common/Constants"
import { WorkerManager } from "../workers/WorkerManager"
import window from '@ohos.window'

const nativePageLifecycle = nativerender.getContext(ContextType.JSPAGE_LIFECYCLE);
const rawFileUtils = nativerender.getContext(ContextType.RAW_FILE_UTILS);

@Entry
@Component
struct Index {
  private context = null;
  cocosWorker = WorkerManager.getInstance().getWorker();

  onPageShow() {
    console.log('[LIFECYCLE-Page] onPageShow');
    nativePageLifecycle.onPageShow();
  }

  onPageHide() {
    console.log('[LIFECYCLE-Page] onPageHide');
    nativePageLifecycle.onPageHide();
  }
  
  build() {
    Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Center, justifyContent: FlexAlign.Center }) {
      XComponent({ id: 'xcomponentId', type: 'surface', libraryname: 'nativerender'})
        .onLoad((context) => {
          console.log('[cocos] XComponent.onLoad Callback');
          this.context = context;
          this.cocosWorker.postMessage({type: "onXCLoad", data: "XComponent"});
          this.cocosWorker.postMessage({type: "audioInit", data: globalThis.abilityContext});

        })
        .onDestroy(() => {
        })
    }
    .width('100%')
    .height('100%')
  }
}
