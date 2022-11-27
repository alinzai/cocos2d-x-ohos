#include "CCEditBoxImplOhos.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_OHOS)

#include "CCEditBox.h"
#include "napi/modules/Java_org_cocos2dx_lib_Cocos2dxBitmap.cpp"
#include "napi/modules/Java_org_cocos2dx_lib_Cocos2dxHelper.cpp"


NS_CC_EXT_BEGIN

CCEditBoxImpl* __createSystemEditBox(CCEditBox* pEditBox)
{
    return 0;
}

CCEditBoxImplOhos::CCEditBoxImplOhos(CCEditBox* pEditText)
: CCEditBoxImpl(pEditText)
, m_pLabel(NULL)
, m_pLabelPlaceHolder(NULL)
, m_eEditBoxInputMode(kEditBoxInputModeSingleLine)
, m_eEditBoxInputFlag(kEditBoxInputFlagInitialCapsAllCharacters)
, m_eKeyboardReturnType(kKeyboardReturnTypeDefault)
, m_colText(ccWHITE)
, m_colPlaceHolder(ccGRAY)
, m_nMaxLength(-1)
{
    
}

CCEditBoxImplOhos::~CCEditBoxImplOhos()
{
	
}

void CCEditBoxImplOhos::doAnimationWhenKeyboardMove(float duration, float distance)
{ // don't need to be implemented on android platform.
	
}


bool CCEditBoxImplOhos::initWithSize(const CCSize& size)
{
    return 0;
}

void CCEditBoxImplOhos::setFont(const char* pFontName, int fontSize)
{
	
}

void CCEditBoxImplOhos::setFontColor(const ccColor3B& color)
{
    
}

void CCEditBoxImplOhos::setPlaceholderFont(const char* pFontName, int fontSize)
{

}

void CCEditBoxImplOhos::setPlaceholderFontColor(const ccColor3B& color)
{
    
}

void CCEditBoxImplOhos::setInputMode(EditBoxInputMode inputMode)
{
    
}

void CCEditBoxImplOhos::setMaxLength(int maxLength)
{
    
}

int CCEditBoxImplOhos::getMaxLength()
{
    return 0;
}

void CCEditBoxImplOhos::setInputFlag(EditBoxInputFlag inputFlag)
{
    
}

void CCEditBoxImplOhos::setReturnType(KeyboardReturnType returnType)
{
    
}

bool CCEditBoxImplOhos::isEditing()
{
    return 0;
}

void CCEditBoxImplOhos::setText(const char* pText)
{
    
}

const char*  CCEditBoxImplOhos::getText(void)
{
    return 0;
}

void CCEditBoxImplOhos::setPlaceHolder(const char* pText)
{

}

void CCEditBoxImplOhos::setPosition(const CCPoint& pos)
{ // don't need to be implemented on android platform.
	
}

void CCEditBoxImplOhos::setVisible(bool visible)
{ // don't need to be implemented on android platform.

}

void CCEditBoxImplOhos::setContentSize(const CCSize& size)
{ // don't need to be implemented on android platform.
	
}

void CCEditBoxImplOhos::setAnchorPoint(const CCPoint& anchorPoint)
{ // don't need to be implemented on android platform.
	
}

void CCEditBoxImplOhos::visit(void)
{ // don't need to be implemented on android platform.
    
}

void CCEditBoxImplOhos::onEnter(void)
{ // don't need to be implemented on android platform.
    
}

static void editBoxCallbackFunc(const char* pText, void* ctx)
{
    
}

void CCEditBoxImplOhos::openKeyboard()
{
	
}

void CCEditBoxImplOhos::closeKeyboard()
{
	
}

NS_CC_EXT_END

#endif /* #if (CC_TARGET_PLATFORM == CC_PLATFORM_OHOS) */

