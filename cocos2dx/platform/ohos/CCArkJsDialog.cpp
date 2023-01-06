#include "CCArkJsDialog.h"
#include "platform/CCPlatformMacros.h"
#include "plugin_common.h"

#include <vector>
#include <js_native_api.h>
#include <js_native_api_types.h>
NS_CC_BEGIN
napi_env CCArkJsDialog::_env = nullptr;
napi_value CCArkJsDialog::initCCArkJsDialog(napi_env env, napi_value exports)
{
    LOGD("initCCArkJsDialog start!");
    _env = env;
    return 0;
}

void CCArkJsDialog::showDialog(std::string& pszMsg, std::string& pszTitle)
{
    LOGD("CCArkJsDialog showDialog start!");
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        LOGE("CCArkJsDialog::showDialog get global failed! status:%d", status);
        return;
    }
    napi_value preloadMusicFunc = getEngineFunc("showDialog");
    if (preloadMusicFunc == nullptr) {
        return;
    }

    std::vector<napi_value> args;
    napi_value argMsg;
    napi_create_string_utf8(_env, pszMsg.data(), pszMsg.length() ,&argMsg);
    args.push_back(argMsg);
    napi_value argTitle;
    napi_create_string_utf8(_env, pszTitle.data(), pszTitle.length() ,&argTitle);
    args.push_back(argTitle);

    napi_value return_val;
    status = napi_call_function(_env, global, preloadMusicFunc, args.size(), args.data(), &return_val);
    if (status != napi_ok) {
        LOGE("CCArkJsDialog::showDialog napi_call_function failed! status:%d", status);
        return;
    }    
}

napi_value CCArkJsDialog::getEngineFunc(const char* funcName)
{
    // Get the function named "AddTwo" on the global object
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        LOGE("%s get global failed!", funcName);
        return nullptr;
    }
    
    napi_value cocosNs;
    status = napi_get_named_property(_env, global, "ccDialogUtils", &cocosNs);
    if (status != napi_ok) {
        LOGE("%s get cocosNs failed!", funcName);
        return nullptr;
    }        
    
    napi_value func;
    status = napi_get_named_property(_env, cocosNs, funcName, &func);
    if (status != napi_ok) {
        LOGE("%s get func failed!", funcName);
        return nullptr;
    }
    
    napi_valuetype functype;
    napi_typeof(_env, func, &functype);
    if (functype != napi_function) {
        LOGE("%s get func but is not a function", funcName);
        return nullptr;
    }    
    return func;
}
NS_CC_END