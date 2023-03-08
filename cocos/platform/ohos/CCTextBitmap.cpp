//
// Created on 2022/11/16.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "CCTextBitmap.h"
#include "platform/CCPlatformMacros.h"
#include "platform/CCCommon.h"
#include <native_drawing/drawing_font_collection.h>




NS_CC_BEGIN

CCTextBitmap* CCTextBitmap::createCCTextBitmap(const char *text, const char *pFontName, const Device::TextAlign eAlignMask, int width_, int height_, double fontSize)
{
    

    return createCCTextBitmap(text, pFontName, 
        fontSize, 1, 1, 1, eAlignMask,
        width_, height_, 
        false, 1, 1, 1, 
        false, 1, 1, 1, 1);
}

int CCTextBitmap::calxStartPosition(int pAlignment, int layoutWidth, int realWidth, int textWidth)
{
    if (pAlignment == TEXT_ALIGN_LEFT)
    {
        return 0;
    }
    if (pAlignment == TEXT_ALIGN_CENTER)
    {
        // 先移动到文字的最左边，再补充文字与实际渲染位置的边距。注意，起绘制的内容往左边移动使用-位置，向右移动使用+位置
        return (-(layoutWidth - realWidth) / 2) + ((textWidth - realWidth) / 2);
    }    
    
    if (pAlignment == TEXT_ALIGN_RIGHT)
    {
        return -(layoutWidth - textWidth);
    }
    return 0;
}
int CCTextBitmap::calyStartPosition(int pAlignment, int realHeight, int textHeight)
{
    const int pVerticalAlignment = (pAlignment >> 4) & 0x0F;
    int y = 0;
        switch (pVerticalAlignment) {
			case VERTICALALIGN_TOP:
				y = 0;
				break;
			case VERTICALALIGN_CENTER:
				y = (textHeight - realHeight) / 2;
				break;
			case VERTICALALIGN_BOTTOM:
				y = textHeight - realHeight;
				break;
			default:
				break;
			}
    
    return y;
}
int CCTextBitmap::processTextAlign(int pAlignment)
{
    const int horizontalAlignment = pAlignment & 0x0F;
    int align = TEXT_ALIGN_LEFT;
    switch (horizontalAlignment) {
        case HORIZONTALALIGN_CENTER:
            align = TEXT_ALIGN_CENTER;
            break;
		case HORIZONTALALIGN_RIGHT:
            align = TEXT_ALIGN_RIGHT;
			break;
		case HORIZONTALALIGN_LEFT:
		default:
			align = TEXT_ALIGN_LEFT;
			break;
    }
    return align;
}

CCTextBitmap* CCTextBitmap::createCCTextBitmap(const char *text,  const char *pFontName, const int fontSize,
            const float fontTintR, const float fontTintG, const float fontTintB,
            const Device::TextAlign eAlignMask, const int pWidth, const int pHeight, const bool shadow,
            const float shadowDX, const float shadowDY, const float shadowBlur, const bool stroke,
            const float strokeR, const float strokeG, const float strokeB, const float strokeSize)
{
    CCTextBitmap *cCTextBitmap = new CCTextBitmap();
    
    cCTextBitmap->_typographyStyle = OH_Drawing_CreateTypographyStyle();
    OH_Drawing_SetTypographyTextDirection(cCTextBitmap->_typographyStyle, TEXT_DIRECTION_LTR);

    int align = processTextAlign((int)eAlignMask);
    OH_Drawing_SetTypographyTextAlign(cCTextBitmap->_typographyStyle, align);
    
    cCTextBitmap->_fontCollection = OH_Drawing_CreateFontCollection();
    cCTextBitmap->_typographyCreate = OH_Drawing_CreateTypographyHandler(cCTextBitmap->_typographyStyle,
		cCTextBitmap->_fontCollection);
    
    cCTextBitmap->_textStyle = OH_Drawing_CreateTextStyle();
    // 设置文字颜色    
    OH_Drawing_SetTextStyleColor(cCTextBitmap->_textStyle, OH_Drawing_ColorSetArgb(0xFF, 0xFF* fontTintR, 0xFF* fontTintR, 0xFF* fontTintR));
    
    // 设置文字大小
    OH_Drawing_SetTextStyleFontSize(cCTextBitmap->_textStyle, fontSize == 0 ? DEFAULT_FONTSIZE : fontSize/2) ;
    
    OH_Drawing_SetTextStyleFontWeight(cCTextBitmap->_textStyle, FONT_WEIGHT_400);
    OH_Drawing_SetTextStyleBaseLine(cCTextBitmap->_textStyle, TEXT_BASELINE_ALPHABETIC);
    OH_Drawing_SetTextStyleFontHeight(cCTextBitmap->_textStyle, 1);
    const char *fontFamilies[] = {pFontName};
    OH_Drawing_SetTextStyleFontFamilies(cCTextBitmap->_textStyle, 1, fontFamilies);
    OH_Drawing_SetTextStyleFontStyle(cCTextBitmap->_textStyle, FONT_STYLE_NORMAL);
    OH_Drawing_SetTextStyleLocale(cCTextBitmap->_textStyle, "en");
    
    OH_Drawing_TypographyHandlerPushTextStyle(cCTextBitmap->_typographyCreate, cCTextBitmap->_textStyle);
    OH_Drawing_TypographyHandlerAddText(cCTextBitmap->_typographyCreate, text);
    OH_Drawing_TypographyHandlerPopTextStyle(cCTextBitmap->_typographyCreate);

    cCTextBitmap->_typography = OH_Drawing_CreateTypography(cCTextBitmap->_typographyCreate);
 
    // layout 之后才可以获取文字的高宽
    int layoutWidth = pWidth != 0 ? std::min(pWidth, 720) : 720;
    OH_Drawing_TypographyLayout(cCTextBitmap->_typography, layoutWidth);
    
    int realWidth = OH_Drawing_TypographyGetMaxIntrinsicWidth(cCTextBitmap->_typography);
    int realHeight = OH_Drawing_TypographyGetHeight(cCTextBitmap->_typography);
    int textWidth = pWidth != 0 ? pWidth : realWidth;
    int textHeight = pHeight != 0 ? pHeight : realHeight;

    
    cCTextBitmap->_bitmap = OH_Drawing_BitmapCreate();
    OH_Drawing_BitmapFormat cFormat = {COLOR_FORMAT_RGBA_8888, ALPHA_FORMAT_OPAQUE};
        
    OH_Drawing_BitmapBuild(cCTextBitmap->_bitmap, textWidth, textHeight , &cFormat);
        
    cCTextBitmap->_canvas = OH_Drawing_CanvasCreate();
    OH_Drawing_CanvasBind(cCTextBitmap->_canvas, cCTextBitmap->_bitmap);
        
    int xStart = calxStartPosition(align, layoutWidth, realWidth, textWidth);
    int yStart = calyStartPosition((int)eAlignMask, realHeight, textHeight);
    double position[2] = {xStart, yStart};
    OH_Drawing_CanvasClear(cCTextBitmap->_canvas, OH_Drawing_ColorSetArgb(0x00, 0xFF, 0x00, 0x00));            
    OH_Drawing_TypographyPaint(cCTextBitmap->_typography, cCTextBitmap->_canvas, position[0], position[1]);
    
    constexpr uint32_t stride = 4;
    int32_t addrSize = pWidth * pHeight * stride;
    cCTextBitmap->pixelAddr = OH_Drawing_BitmapGetPixels(cCTextBitmap->_bitmap);
    cCTextBitmap->width = textWidth;
    cCTextBitmap->height = textHeight;
    return cCTextBitmap;
}

void* CCTextBitmap::getPixelAddr()
{
    return pixelAddr;
}

CCTextBitmap::~CCTextBitmap()
{
  OH_Drawing_CanvasDestroy(_canvas);
//  OH_Drawing_BitmapDestroy(_bitmap);
  OH_Drawing_DestroyTypographyStyle(_typographyStyle);
  OH_Drawing_DestroyTextStyle(_textStyle);
  OH_Drawing_DestroyTypographyHandler(_typographyCreate);
  OH_Drawing_DestroyTypography(_typography);
  OH_Drawing_DestroyFontCollection(_fontCollection);  

  pixelAddr = nullptr;
}



NS_CC_END