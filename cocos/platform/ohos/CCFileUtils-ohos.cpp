/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_OHOS

#include "platform/ohos/CCFileUtils-ohos.h"
#include "platform/CCCommon.h"
#include "base/ZipUtils.h"
#include "napi/common/plugin_common.h"

#include <stdlib.h>
#include <sys/stat.h>

using namespace std;

#define DECLARE_GUARD std::lock_guard<std::recursive_mutex> mutexGuard(_mutex)

NS_CC_BEGIN
NativeResourceManager* FileUtilsOhos::nativeResourceManager_ = nullptr;
ZipFile* FileUtilsOhos::obbfile = nullptr;

void FileUtilsOhos::setassetmanager(NativeResourceManager* a) {
    if (nullptr == a) {
        LOGD("setassetmanager : received unexpected nullptr parameter");
        return;
    }

    cocos2d::FileUtilsOhos::nativeResourceManager_ = a;
}

FileUtils* FileUtils::getInstance()
{
    LOGD("FileUtils::getInstance()");
    if (s_sharedFileUtils == nullptr)
    {
        s_sharedFileUtils = new FileUtilsOhos();
        s_sharedFileUtils->init();
        std::string resourcePath("");
        FileUtilsOhos::obbfile = new ZipFile(resourcePath, "/data/storage/el2/base/haps/entry/files/");
    }
    return s_sharedFileUtils;
}

FileUtilsOhos::FileUtilsOhos()
{
}

FileUtilsOhos::~FileUtilsOhos()
{
    CC_SAFE_DELETE(obbfile);
}

bool FileUtilsOhos::init()
{
    DECLARE_GUARD;
    
    LOGD("FileUtilsOhos::init()");
    
    std::string assetsPath("");//getApkPath());
    if (assetsPath.find("/obb/") != std::string::npos)
    {
        obbfile = new ZipFile(assetsPath);
    }

    return FileUtils::init();
}

bool FileUtilsOhos::isFileExistInternal(const std::string& strFilePath) const
{
    
    if (0 == strFilePath.length())
    {
        return false;
    }

    bool bFound = false;
    RawFile *fp = RawFileUtils::GetInstance().Open(strFilePath.c_str());//fopen(strFilePath.c_str(), "r");
    CCLOG("===================> open %s", strFilePath.c_str());
    if(fp)
    {
        CCLOG("FileUtilsOhos::isFileExistInternal() - open success");
        bFound = true;
        RawFileUtils::GetInstance().Close(fp);
    }
    return bFound;
}

bool FileUtilsOhos::isDirectoryExistInternal(const std::string& dirPath) const
{
    if (dirPath.empty())
    {
        return false;
    }
    return false;
}

bool FileUtilsOhos::isAbsolutePath(const std::string& strPath) const
{
    DECLARE_GUARD;
    // On Android, there are two situations for full path.
    // 1) Files in APK, e.g. assets/path/path/file.png
    // 2) Files not in APK, e.g. /data/data/org.cocos2dx.hellocpp/cache/path/path/file.png, or /sdcard/path/path/file.png.
    // So these two situations need to be checked on Android.
    if (strPath[0] == '/')
    {
        return true;
    }
    return false;
}

long FileUtilsOhos::getFileSize(const std::string& filepath) const
{
    DECLARE_GUARD;
    LOGD("FileUtilsOhos::getFileSize()");

    RawFile *fp = RawFileUtils::GetInstance().Open(filepath.c_str());//fopen(strFilePath.c_str(), "r");
    CCLOG("FileUtilsOhos::getFileSize ===================> doGetFileData %s", filepath.c_str());
    long size = RawFileUtils::GetInstance().GetSize(fp);
    RawFileUtils::GetInstance().Close(fp);
    if (size != -1) {
        return size;
    }
    return size;
}

std::vector<std::string> FileUtilsOhos::listFiles(const std::string& dirPath) const
{

    if(!dirPath.empty() && dirPath[0] == '/') return FileUtils::listFiles(dirPath);

    std::vector<std::string> fileList;
    return fileList;
}

FileUtils::Status FileUtilsOhos::getContents(const std::string& filename, ResizableBuffer* buffer) const
{
    if (filename.empty()) {
        LOGD("FileUtilsOhos::getContents() - filename is empty");
        return FileUtils::Status::NotExists;
    }

    string fullPath = fullPathForFilename(filename);

    if (fullPath[0] == '/') {
        LOGD("FileUtilsOhos::getContents() - fullPath[0] == '/'");
        return FileUtils::getContents(fullPath, buffer);
    }

    RawFile *fp = RawFileUtils::GetInstance().Open(filename.c_str());//fopen(strFilePath.c_str(), "r");
    CCLOG("FileUtilsOhos::getContents() ===================> doGetFileData %s", filename.c_str());
    if (!fp) {
        LOGD("FileUtilsOhos::fp is nullptr");
        return FileUtils::Status::NotInitialized;
    }
    auto size = RawFileUtils::GetInstance().GetSize(fp);
    buffer->resize(size);

    int readsize = RawFileUtils::GetInstance().Read(fp, buffer->buffer(), size);
    RawFileUtils::GetInstance().Close(fp);

    if (readsize < size) {
        if (readsize >= 0)
           buffer->resize(readsize);
           LOGD("FileUtilsOhos::getContents() - readsize < size");
        return FileUtils::Status::ReadFailed;
    }

    if (!buffer->buffer())
    {
        std::string msg = "Get data from file(";
        msg.append(filename).append(") failed!");
        CCLOG("%s", msg.c_str());
    }

    return FileUtils::Status::OK;
}

string FileUtilsOhos::getWritablePath() const
{
    // Fix for Nexus 10 (Android 4.2 multi-user environment)
    // the path is retrieved through Java Context.getCacheDir() method
    string dir("");
    string tmp = "";//JniHelper::callStaticStringMethod("org.cocos2dx.lib.Cocos2dxHelper", "getCocos2dxWritablePath");

    if (tmp.length() > 0)
    {
        dir.append(tmp).append("/");

        return dir;
    }
    else
    {
        return "";
    }
}

NS_CC_END

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_OHOS
