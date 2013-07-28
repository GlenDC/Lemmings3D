#include "UITextField.h" 

UITextField::UITextField(int x, int y, int width, tstring name, UIDockInterface * pParrent,
		tstring text, SpriteFont * pFont, D3DXCOLOR color)
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
	SpriteBatch::DrawTextW(m_pFont, m_Text, D3DXVECTOR2((float)realZone.X, (float)realZone.Y), m_TextColor);
	UIElement::Draw(context);
}