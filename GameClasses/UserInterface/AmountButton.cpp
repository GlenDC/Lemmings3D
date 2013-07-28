//====================== #INCLUDES ===================================
#include "AmountButton.h"
#include "UIDockInterface.h"
//====================================================================

AmountButton::AmountButton(int x, int y, const tstring & name, UIDockInterface * pParrent, const tstring & asset_file, int amount, SpriteFont * pFont)
	: UIButton(x, y, name, pParrent, asset_file)
	, m_pFont(pFont)
	, m_Amount(amount)
{
}

AmountButton::~AmountButton() {}


void AmountButton::Draw(const GameContext & context) const
{
	UIButton::Draw(context);

	LemmingsHelpers::Rect realElementZone(GetScreenZone());
	tstring text(_T("0"));
	text = XMLConverter::ConvertToTString<int>(m_Amount / 10);
	SpriteBatch::DrawTextW(m_pFont, text, 
		D3DXVECTOR2(realElementZone.X + 5 * m_pParrentDock->m_ScreenScale.x, 
		realElementZone.Y + 5 * m_pParrentDock->m_ScreenScale.y),
		D3DXCOLOR(1,0,0,1));
	text = XMLConverter::ConvertToTString<int>(m_Amount % 10);
	SpriteBatch::DrawTextW(m_pFont, text, 
		D3DXVECTOR2(realElementZone.X + 25 * m_pParrentDock->m_ScreenScale.x, 
		realElementZone.Y + 5 * m_pParrentDock->m_ScreenScale.y),
		D3DXCOLOR(1,0,0,1));
}

void AmountButton::SetAmount(int amount)
{
	m_Amount = amount;
}

const int & AmountButton::GetAmount() const
{
	return m_Amount;
}

bool AmountButton::SubstractAmount()
{
	--m_Amount;
	if(m_Amount < 0)
	{
		m_Amount = 0;
		return false;
	}
	return true;
}