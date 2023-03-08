/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef COCOS_LIB_UTILS_COMPAT_H
#define COCOS_LIB_UTILS_COMPAT_H

#include <SLES/OpenSLES_OpenHarmony.h>
#include <SLES/OpenSLES_Platform.h>

#define ZD      "%zd"
#define ZD_TYPE ssize_t


/*
 * Needed for cases where something should be constexpr if possible, but not
 * being constexpr is fine if in pre-C++11 code (such as a const static float
 * member variable).
 */
#if __cplusplus >= 201103L
    #define CONSTEXPR constexpr
#else
    #define CONSTEXPR
#endif

/*
 * TEMP_FAILURE_RETRY is defined by some, but not all, versions of
 * <unistd.h>. (Alas, it is not as standard as we'd hoped!) So, if it's
 * not already defined, then define it here.
 */
#ifndef TEMP_FAILURE_RETRY
    /* Used to retry syscalls that can return EINTR. */
    #define TEMP_FAILURE_RETRY(exp) ({         \
    typeof (exp) _rc;                      \
    do {                                   \
        _rc = (exp);                       \
    } while (_rc == -1 && errno == EINTR); \
    _rc; })
#endif

#if defined(_WIN32)
    #define OS_PATH_SEPARATOR '\\'
#else
    #define OS_PATH_SEPARATOR '/'
#endif


typedef SLOHBufferQueueItf CCSLBufferQueueItf;
#define CC_SL_IDD_BUFFER_QUEUE SL_IID_OH_BUFFERQUEUE
#define __unused


#endif /* COCOS_LIB_UTILS_COMPAT_H */
