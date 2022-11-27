/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef THIRD_PARTY_LIBJPEG_TURBO_JCONFIGINT_H
#define THIRD_PARTY_LIBJPEG_TURBO_JCONFIGINT_H

/* libjpeg-turbo build number */
#define BUILD  "20220811"

/* Compiler's inline keyword */
#undef inline

/* How to obtain function inlining. */
#ifdef _MSC_VER
#define INLINE __forceinline
#else
#define INLINE  __inline__ __attribute__((always_inline))
#endif

/* How to obtain thread-local storage */
#define THREAD_LOCAL

/* Define to the full name of this package. */
#define PACKAGE_NAME  "libjpeg-turbo"

/* Version number of package */
#define VERSION  "2.0.5"

/* The size of `size_t', as computed by sizeof. */
#ifdef __SIZEOF_SIZE_T__
#define SIZEOF_SIZE_T __SIZEOF_SIZE_T__
#elif __WORDSIZE==64 || defined(_WIN64)
#define SIZEOF_SIZE_T 8
#else
#define SIZEOF_SIZE_T 4
#endif

/* Define if your compiler has __builtin_ctzl() and sizeof(unsigned long) == sizeof(size_t). */
#define HAVE_BUILTIN_CTZL

/* Define to 1 if you have the <intrin.h> header file. */
/* #undef HAVE_INTRIN_H */

#if defined(_MSC_VER) && defined(HAVE_INTRIN_H)
#if (SIZEOF_SIZE_T == 8)
#define HAVE_BITSCANFORWARD64
#elif (SIZEOF_SIZE_T == 4)
#define HAVE_BITSCANFORWARD
#endif
#endif

#endif