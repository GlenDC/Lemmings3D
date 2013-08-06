//====================== #INCLUDES ===================================
#include "UIToggleButton.h"
//--------------------------------------------------------------------
#include "../Lib/GlobalParameters.h"
#include "../Lib/LemmingsHelpers.h"
//--------------------------------------------------------------------
#include "Managers/ContentManager.h"
//====================================================================

UIToggleButton::UIToggleButton(const int x, const int y, const tstring & name, 
							   const UIDockInterface * pParrent, const tstring & asset_file)
    :UIElement(x, y, 0, 0, name, pParrent)
{
	m_pTexture = ContentManager::Load<ID3D10ShaderResourceView>(asset_file);
	
	UINT width(0), height(0);
	LemmingsHelpers::GetTextureDimensions(m_pTexture, width, height);
	//LemmingsHelpers::SetTextureDimensions(m_pTexture, width, height / 2);
	//Spritesheet with 5 rows => idle, hover, click, toggle, disable
	SetDimensions(width, height / 2);

	m_ButtonSprite.pTexture = m_pTexture;
	m_ButtonSprite.Color = D3DXCOLOR(1,1,1,m_AlphaValue);
}

UIToggleButton::~UIToggleButton()
{
	SafeRelease(m_pTexture);
}

void UIToggleButton::Draw(const GameContext &context) const
{
	if (m_IsVisible)
    {
       SpriteBatch::Draw(m_ButtonSprite);
	   UIElement::Draw(context);
    }
}

void UIToggleButton::Update(const GameContext &context)
{
	m_ButtonSprite.Color.a = m_AlphaValue;
	m_ButtonSprite.OffsetY = m_IsOffline ? 0.0f : 1.0f;
	m_ButtonSprite.OffsetX = 0;
	LemmingsHelpers::Rect zone(GetRealElementZone());
	m_ButtonSprite.Transform = LemmingsHelpers::MatrixScale(1.0f,0.5f,0) * LemmingsHelpers::MatrixTranslation((float)zone.X, (float)zone.Y,  0.02f);
	UIElement::Update(context);
}

void UIToggleButton::Select()
{
	m_IsOffline = !m_IsOffline;
	UIElement::Select();
}

void UIToggleButton::SetOnline(const bool is_on)
{
	m_IsOffline = !is_on;
}