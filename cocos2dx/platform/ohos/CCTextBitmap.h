//
// Created on 2022/11/16.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef XComponent_CCTextBitmap_H
#define XComponent_CCTextBitmap_H

#include "platform/CCPlatformMacros.h"
#include "platform/CCImage.h"

#define DEFAULT_FONTSIZE 20

NS_CC_BEGIN
class CCTextBitmap
{
    public:
        static const int HORIZONTALALIGN_LEFT = 1;
        static const int HORIZONTALALIGN_RIGHT = 2;
        static const int HORIZONTALALIGN_CENTER = 3;
    
    	static const int VERTICALALIGN_TOP = 1;
    	static const int VERTICALALIGN_BOTTOM = 2;
    	static const int VERTICALALIGN_CENTER = 3;
        static CCTextBitmap* createCCTextBitmap(const char *text, const char *pFontName, const CCImage::ETextAlign eAlignMask, int width_, int height_, double fontSize);
        static CCTextBitmap* createCCTextBitmap(const char *text,  const char *pFontName, const int pFontSize,
            const float fontTintR, const float fontTintG, const float fontTintB,
            const CCImage::ETextAlign eAlignMask, const int pWidth, const int pHeight, const bool shadow,
            const float shadowDX, const float shadowDY, const float shadowBlur, const bool stroke,
            const float strokeR, const float strokeG, const float strokeB, const float strokeSize);
        void* getPixelAddr();
        int GetWidth() { return width; }
        int GetHeight() { return height; }
    private:

        /**
        * 计算x绘制的起点
        * @param pAlignment 文字的靠边设置
        * @param layoutWidth 文字测量时的宽度
        * @param realWidth 文字实际的宽度
        * @param textWidth text控件最后呈现的宽度，即bitmap的宽度
        * @return x 绘制的起始点
         */
        static int calxStartPosition(int pAlignment, int layoutWidth, int realWidth, int textWidth);
        
        /**
        * 计算y绘制的起点
        * @param pAlignment 文字的靠边设置
        * @param realWidth 文字实际的宽度
        * @param textWidth text控件最后呈现的宽度，即bitmap的宽度
        * @return x 绘制的起始点
         */        
        static int calyStartPosition(int pAlignment, int realHeight, int textHeight);

        static int processTextAlign(int pAlignment);
        void* pixelAddr = nullptr;
        int width = 0;
        int height = 0;

};
NS_CC_END
#endif 
