import prompt from '@system.prompt'
import hilog from '@ohos.hilog';

export default class CCDialogUtils {
    static readonly SUCCESS = 0;

    static showDialogInUiThread(eventData) : number {
        let dialogTitle = eventData.title;
        let dialogMessage = eventData.message;
        return this.showDialog(dialogTitle, dialogMessage);
    }

    static showDialog(dialogTitle, dialogMessage) : number {
        prompt.showDialog({
            title: dialogTitle,
            message: dialogMessage,
            buttons: [
                {
                    text: 'OK',
                    color: '#000000'
                },
            ],
            success: function(data) {
                hilog.debug(0x0000, 'testTag', "handling callback", data);
            }
        });
        return CCDialogUtils.SUCCESS;
    }
}