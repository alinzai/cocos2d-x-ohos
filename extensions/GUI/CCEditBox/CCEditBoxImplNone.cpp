#include "CCEditBox.h"

#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID ) && (CC_TARGET_PLATFORM != CC_PLATFORM_IOS ) && \
    (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32) && (CC_TARGET_PLATFORM != CC_PLATFORM_MAC) && \
    (CC_TARGET_PLATFORM != CC_PLATFORM_TIZEN) && (CC_TARGET_PLATFORM != CC_PLATFORM_OHOS)

NS_CC_EXT_BEGIN

CCEditBoxImpl* __createSystemEditBox(CCEditBox* pEditBox)
{
    return NULL;
}

NS_CC_EXT_END

#endif /* #if (..) */
