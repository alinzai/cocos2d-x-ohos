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


#include <native_drawing/drawing_color.h>
#include <native_drawing/drawing_text_declaration.h>
#include <native_drawing/drawing_types.h>
#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_OHOS

#include "platform/CCDevice.h"
#include "napi/modules/DPIJni.h"
#include "base/ccTypes.h"
#include "CCTextBitmap.h"

NS_CC_BEGIN

int Device::getDPI()
{
    static int dpi = -1;
    if (dpi == -1)
    {
        dpi = (int)getDPIJNI();
    }
    return dpi;
}

void Device::setAccelerometerEnabled(bool isEnabled)
{
    if (isEnabled)
    {
        // TBD need fixed JniHelper::callStaticVoidMethod(helperClassName, "enableAccelerometer");
    }
    else
    {
        // TBD need fixed JniHelper::callStaticVoidMethod(helperClassName, "disableAccelerometer");
    }
}

void Device::setAccelerometerInterval(float interval)
{
    // TBD need fixed JniHelper::callStaticVoidMethod(helperClassName, "setAccelerometerInterval", interval);
}

class BitmapDC
{
public:

    BitmapDC()
    : m_nWidth(0)
    , m_nHeight(0)
    , m_pData(NULL)
    {
    }

    ~BitmapDC(void)
    {
        if (m_pData)
        {
            delete [] m_pData;
        }
    }
   
    bool getBitmapFromJavaShadowStroke(	const char *text,
    									int nWidth,
    									int nHeight,
    									Device::TextAlign eAlignMask,
										const FontDefinition& textDefinition)
    {
                                                            
        CCTextBitmap* cCtextBitmap = CCTextBitmap::createCCTextBitmap(text, textDefinition._fontName.data(), eAlignMask, nWidth, nHeight, textDefinition._fontSize);
        void* pixels = cCtextBitmap->getPixelAddr();
        cocos2d::BitmapDC& bitmapDC = sharedBitmapDC();
        bitmapDC.m_nWidth = cCtextBitmap->GetWidth();
        bitmapDC.m_nHeight = cCtextBitmap->GetHeight();
        bitmapDC.m_pData = (unsigned char*)pixels;
        
        unsigned int *tempPtr = (unsigned int*)bitmapDC.m_pData;
        unsigned int tempdata = 0;
        for (int i = 0; i < cCtextBitmap->GetHeight(); ++i)
        {
            for (int j = 0; j < cCtextBitmap->GetWidth(); ++j)
            {
                tempdata = *tempPtr;
                *tempPtr++ = bitmapDC.swapAlpha(tempdata);
            }
        }
           
        return true;
    }

public:
    int m_nWidth;
    int m_nHeight;
    unsigned char *m_pData;


    
    static BitmapDC& sharedBitmapDC()
    {
        static BitmapDC s_BmpDC;
        return s_BmpDC;
    }
	
    bool getBitmapFromJava(const char *text, int nWidth, int nHeight, Device::TextAlign eAlignMask, const char * pFontName, float fontSize)
    {
        FontDefinition textDefinition; // TBD need fixed
    	return  getBitmapFromJavaShadowStroke(	text, nWidth, nHeight, eAlignMask, textDefinition);
    }

    // ARGB -> RGBA
    inline unsigned int swapAlpha(unsigned int value)
    {
        return ((value << 8 & 0xffffff00) | (value >> 24 & 0x000000ff));
    }
	
};

Data Device::getTextureDataForText(const char * text, const FontDefinition& textDefinition, TextAlign align, int &width, int &height, bool& hasPremultipliedAlpha)
{
    Data ret;
    do 
    {
        BitmapDC &dc = BitmapDC::sharedBitmapDC();

        if(! dc.getBitmapFromJavaShadowStroke(text, 
            (int)textDefinition._dimensions.width, 
            (int)textDefinition._dimensions.height, 
            align, textDefinition )) { break;};

        width = dc.m_nWidth;
        height = dc.m_nHeight;
        ret.fastSet(dc.m_pData,width * height * 4);
        hasPremultipliedAlpha = true;
    } while (0);

    return ret;
}	


void Device::setKeepScreenOn(bool value)
{
    // TBD need fixed JniHelper::callStaticVoidMethod(helperClassName, "setKeepScreenOn", value);
}

void Device::vibrate(float duration)
{
    // TBD need fixed JniHelper::callStaticVoidMethod(helperClassName, "vibrate", duration);
}
NS_CC_END
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_OHOS
