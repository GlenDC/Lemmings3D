//====================== #INCLUDES ===================================
#include "UIIMage.h"
//--------------------------------------------------------------------
#include "Managers/ContentManager.h"
//--------------------------------------------------------------------
#include "../Lib/GlobalParameters.h"
#include "../Lib/LemmingsHelpers.h"
//====================================================================

UIImage::UIImage(const int x, const int y, const tstring & name, const UIDockInterface * pParrent, const tstring & asset_file)
    :UIElement(x, y, 0, 0, name, pParrent)
	,m_pTexture(nullptr)
	,m_ImageSprite()
	,m_Scale(1.0f,1.0f)
{
	m_pTexture = ContentManager::Load<ID3D10ShaderResourceView>(asset_file);
	
	UINT width(0), height(0);
	LemmingsHelpers::GetTextureDimensions(m_pTexture, width, height);
	//Spritesheet with 5 rows => idle, hover, click, toggle, disable
	SetDimensions(width, height);

	m_ImageSprite.pTexture = m_pTexture;
	m_ImageSprite.OffsetY = 0;
	m_ImageSprite.OffsetX = 0;
	m_ImageSprite.Color = D3DXCOLOR(1,1,1,m_AlphaValue);
}

UIImage::~UIImage()
{
	SafeRelease(m_pTexture);
}

void UIImage::Draw(const GameContext &context) const
{
	if (m_IsVisible)
    {
       SpriteBatch::Draw(m_ImageSprite);
	   UIElement::Draw(context);
    }
}

void UIImage::Update(const GameContext &context)
{
	m_ImageSprite.Color.a = m_AlphaValue;
	LemmingsHelpers::Rect zone(GetScreenZone());
	m_ImageSprite.Transform = LemmingsHelpers::MatrixScale(m_Scale.x, m_Scale.y, m_Scale.y);
	m_ImageSprite.Transform *= LemmingsHelpers::MatrixTranslation(float(zone.X), float(zone.Y), 0.08f);
	UIElement::Update(context);
}