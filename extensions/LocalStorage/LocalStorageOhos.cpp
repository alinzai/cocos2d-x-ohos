#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_OHOS)

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string>

#include "napi/modules/JniHelper.h"

USING_NS_CC;
static int _initialized = 0;

static void splitFilename (std::string& str)
{

}

void localStorageInit( const char *fullpath)
{

}

void localStorageFree()
{

}

/** sets an item in the LS */
void localStorageSetItem( const char *key, const char *value)
{

}

/** gets an item from the LS */
const char* localStorageGetItem( const char *key )
{
    return NULL;
}

/** removes an item from the LS */
void localStorageRemoveItem( const char *key )
{

}

#endif // #if (CC_TARGET_PLATFORM == CC_PLATFORM_OHOS)
