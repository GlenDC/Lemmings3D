//====================== #INCLUDES ===================================
#include "UIButtonWT.h"
#include "UIDockInterface.h"
//====================================================================

UIButtonWT::UIButtonWT(int x, int y, const tstring & name, UIDockInterface * pParrent, const tstring & asset_file,
	UINT textX, UINT textY, const tstring & text, SpriteFont * pFont, const D3DXCOLOR & color_idle,
	const D3DXCOLOR & color_hover, const D3DXCOLOR & color_click, const D3DXCOLOR & color_disabled)
	: UIButton(x, y, name, pParrent, asset_file)
	, m_Text(text)
	, m_TextOffset(textX, textY)
	, m_pFont(pFont)
{
	m_TextColors[(UINT)ElementStates::IDLE] = color_idle;
	m_TextColors[(UINT)ElementStates::DISABLED] = color_disabled;
	m_TextColors[(UINT)ElementStates::CLICK] = color_click;
	m_TextColors[(UINT)ElementStates::TOGGLE] = color_click;
	m_TextColors[(UINT)ElementStates::HOVER] = color_hover;
}

UIButtonWT::~UIButtonWT() {}

void UIButtonWT::SetText(const tstring & text)
{
	m_Text = text;
}

void UIButtonWT::Draw(const GameContext & context)
{
	LemmingsHelpers::Rect realElementZone(GetScreenZone());
	SpriteBatch::DrawTextW(m_pFont, m_Text, 
		D3DXVECTOR2(realElementZone.X + m_TextOffset.X * m_pParrentDock->m_ScreenScale.x, 
		realElementZone.Y + m_TextOffset.Y * m_pParrentDock->m_ScreenScale.y),
		m_TextColors[(UINT)m_State]);
}