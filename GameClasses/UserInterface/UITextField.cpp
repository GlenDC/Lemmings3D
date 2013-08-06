//====================== #INCLUDES ===================================
#include "UITextField.h" 
//====================================================================

UITextField::UITextField(const int x, const int y, const int width, const tstring & name, const UIDockInterface * pParrent,
		const tstring & text, shared_ptr<SpriteFont> pFont, const D3DXCOLOR & color)
    : UIElement(x, y, width, 0, name, pParrent)
	,m_pFont(pFont)
	,m_Text(text)
	,m_TextColor(color)
{
}

UITextField::~UITextField() //default destructor
{
	// nothing to destroy
}

void UITextField::Draw(const GameContext & context) const
{
	LemmingsHelpers::Rect realZone(GetScreenZone());
	SpriteBatch::DrawTextW(m_pFont.get(), m_Text, D3DXVECTOR2((float)realZone.X, (float)realZone.Y), m_TextColor);
	UIElement::Draw(context);
}