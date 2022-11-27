/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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
#include "CCFileUtilsOhos.h"
#include "support/zip_support/ZipUtils.h"
#include "platform/CCCommon.h"
#include "napi/modules//Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include "RawFileUtils.h"
using namespace std;

NS_CC_BEGIN

// record the zip on the resource path
static ZipFile *s_pZipFile = NULL;

CCFileUtils* CCFileUtils::sharedFileUtils()
{
    if (s_sharedFileUtils == NULL)
    {
        s_sharedFileUtils = new CCFileUtilsOhos();
        s_sharedFileUtils->init();
        std::string resourcePath = getApkPath();
        s_pZipFile = new ZipFile(resourcePath, "/data/storage/el2/base/haps/entry/files/");
    }
    return s_sharedFileUtils;
}

CCFileUtilsOhos::CCFileUtilsOhos()
{
}

CCFileUtilsOhos::~CCFileUtilsOhos()
{
    CC_SAFE_DELETE(s_pZipFile);
}

bool CCFileUtilsOhos::init()
{
    // m_strDefaultResRootPath = "/data/storage/el2/base/haps/entry/files/";
    m_strDefaultResRootPath = "";
    return CCFileUtils::init();
}

bool CCFileUtilsOhos::isFileExist(const std::string& strFilePath)
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
        bFound = true;
        RawFileUtils::GetInstance().Close(fp);
    }
    return bFound;
}

bool CCFileUtilsOhos::isAbsolutePath(const std::string& strPath)
{
    // On Android, there are two situations for full path.
    // 1) Files in APK, e.g. /data/cocos/path/path/file.png
    // 2) Files not in APK, e.g. /data/data/org.cocos2dx.hellocpp/cache/path/path/file.png, or /sdcard/path/path/file.png.
    // So these two situations need to be checked on Android.
    if (strPath[0] == '/')
    {
        return true;
    }
    return false;
}


unsigned char* CCFileUtilsOhos::getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize)
{    
    return doGetFileData(pszFileName, pszMode, pSize, false);
}

unsigned char* CCFileUtilsOhos::getFileDataForAsync(const char* pszFileName, const char* pszMode, unsigned long * pSize)
{
    return doGetFileData(pszFileName, pszMode, pSize, true);
}

unsigned char* CCFileUtilsOhos::doGetFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize, bool forAsync)
{
    unsigned char * pData = 0;
    
    if ((! pszFileName) || (! pszMode) || 0 == strlen(pszFileName))
    {
        return 0;
    }
    
    do
    {
        RawFile *fp = RawFileUtils::GetInstance().Open(pszFileName);//fopen(strFilePath.c_str(), "r");
        CCLOG("===================> doGetFileData %s", pszFileName);
        CC_BREAK_IF(!fp);
        long size = RawFileUtils::GetInstance().GetSize(fp);
        pData = new unsigned char[size];
        size = RawFileUtils::GetInstance().Read(fp, pData, size);
        RawFileUtils::GetInstance().Close(fp);
        CCLOG("===================> doGetFileData %d", size);
        if (pSize)
        {
            *pSize = size;
        }
    } while (0);
    
    
    if (! pData)
    {
        std::string msg = "Get data from file(";
        msg.append(pszFileName).append(") failed!");
        CCLOG("%s", msg.c_str());
    }
    
    return pData;
}

string CCFileUtilsOhos::getWritablePath()
{
    // Fix for Nexus 10 (Android 4.2 multi-user environment)
    // the path is retrieved through Java Context.getCacheDir() method
    string dir("");
    string tmp = getFileDirectoryJNI();

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
