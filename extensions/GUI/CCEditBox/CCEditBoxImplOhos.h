#ifndef __CCEDITBOXIMPLOHOS_H__
#define __CCEDITBOXIMPLOHOS_H__

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_OHOS)

#include "ExtensionMacros.h"
#include "CCEditBoxImpl.h"

NS_CC_EXT_BEGIN

class CCEditBox;

class CCEditBoxImplOhos : public CCEditBoxImpl
{
public:
    CCEditBoxImplOhos(CCEditBox* pEditText);
    virtual ~CCEditBoxImplOhos();
    
    virtual bool initWithSize(const CCSize& size);
    virtual void setFont(const char* pFontName, int fontSize);
    virtual void setFontColor(const ccColor3B& color);
    virtual void setPlaceholderFont(const char* pFontName, int fontSize);
    virtual void setPlaceholderFontColor(const ccColor3B& color);
    virtual void setInputMode(EditBoxInputMode inputMode);
    virtual void setInputFlag(EditBoxInputFlag inputFlag);
    virtual void setMaxLength(int maxLength);
    virtual int  getMaxLength();
    virtual void setReturnType(KeyboardReturnType returnType);
    virtual bool isEditing();
    
    virtual void setText(const char* pText);
    virtual const char* getText(void);
    virtual void setPlaceHolder(const char* pText);
    virtual void setPosition(const CCPoint& pos);
    virtual void setVisible(bool visible);
    virtual void setContentSize(const CCSize& size);
	virtual void setAnchorPoint(const CCPoint& anchorPoint);

    virtual void visit(void);
	virtual void onEnter(void);
    virtual void doAnimationWhenKeyboardMove(float duration, float distance);
    virtual void openKeyboard();
    virtual void closeKeyboard();
    
private:
    CCLabelTTF* m_pLabel;
    CCLabelTTF* m_pLabelPlaceHolder;
    EditBoxInputMode    m_eEditBoxInputMode;
    EditBoxInputFlag    m_eEditBoxInputFlag;
    KeyboardReturnType  m_eKeyboardReturnType;
    
    std::string m_strText;
    std::string m_strPlaceHolder;
    
    ccColor3B m_colText;
    ccColor3B m_colPlaceHolder;

    int   m_nMaxLength;
    CCSize m_EditSize;
};


NS_CC_EXT_END

#endif /* #if (CC_TARGET_PLATFORM == CC_PLATFORM_OHOS) */

#endif /* __CCEDITBOXIMPLOHOS_H__ */