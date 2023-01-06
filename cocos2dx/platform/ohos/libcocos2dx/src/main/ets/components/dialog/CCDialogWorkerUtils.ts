import hilog from '@ohos.hilog';

export default class CCDialogUtils {
    static parentPort;
    static init(parentPort) {
        CCDialogUtils.parentPort = parentPort;
    }
    static showDialogPostToMainThread(message, title)  {
        hilog.debug(0x0000, 'testTag', 'CCDialogUtils showDialogPostToMainThread!');
        CCDialogUtils.parentPort.postMessage({'function': 'showDialog', 'title': title, 'message': message});
    }
}
globalThis.ccDialogUtils={};
globalThis.ccDialogUtils.showDialog=CCDialogUtils.showDialogPostToMainThread;