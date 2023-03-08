import worker from '@ohos.worker';
import hilog from '@ohos.hilog';
import DialogUtils from '../dialog/DialogUtils'

export default class ThreadUtils {

    static recvWorkerThreadMessage(event) {
        var eventData = event.data;
        hilog.debug(0x0000, 'cocos', 'mainThread recv:' + eventData.function);
        switch (eventData.function) {
          case "showDialog":
            let title = eventData.title;
            let message = eventData.message;
            DialogUtils.showDialog(title, message);
            break;
        }
    }

}
