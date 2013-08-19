//====================== #INCLUDES ===================================
#include "UIButton.h"
//--------------------------------------------------------------------
#include "../Lib/GlobalParameters.h"
#include "../Lib/LemmingsHelpers.h"
//--------------------------------------------------------------------
#include "Managers/ContentManager.h"
//====================================================================

UIButton::UIButton(const int x, const int y, const tstring & name, 
				   const UIDockInterface * pParrent, const tstring & asset_file)
    :UIElement(x, y, 0, 0, name, pParrent)
{
	m_pTexture = ContentManager::Load<ID3D10ShaderResourceView>(asset_file);
	UINT width(0), height(0);
	LemmingsHelpers::GetTextureDimensions(m_pTexture, width, height);
	//LemmingsHelpers::SetTextureDimensions(m_pTexture, width, height / 5);
	//Spritesheet with 5 rows => idle, hover, click, toggle, disable
	SetDimensions(width,(UINT)(height / MAX_ELEMENT_STATES * 1.5f));

	m_ButtonSprite.pTexture = m_pTexture;
	m_ButtonSprite.Color = D3DXCOLOR(1,1,1,m_AlphaValue);
	m_ButtonSprite.UVY = 1.0f / (float)MAX_ELEMENT_STATES;
}

UIButton::~UIButton()
{
}

void UIButton::Draw(const GameContext &context) const
{
	if (m_IsVisible)
    {
       SpriteBatch::Draw(m_ButtonSprite);
	   UIElement::Draw(context);
    }
}

void UIButton::Update(const GameContext &context)
{
	m_ButtonSprite.Color.a = m_AlphaValue;
	m_ButtonSprite.OffsetY = m_ButtonSprite.UVY * (float)m_State;
	if(m_IsToggled)
	{
		m_ButtonSprite.OffsetY = m_ButtonSprite.UVY * (float)ElementStates::TOGGLE;
	}
	m_ButtonSprite.OffsetX = 0;
	LemmingsHelpers::Rect zone(GetScreenZone());
	m_ButtonSprite.Transform = LemmingsHelpers::MatrixScale(1.0f,0.2f,0) * LemmingsHelpers::MatrixTranslation((float)zone.X, (float)zone.Y,  0.02f);
	UIElement::Update(context);
}