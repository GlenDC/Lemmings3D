//====================== #INCLUDES ===================================
#include "UISpritesheet.h"
//--------------------------------------------------------------------
#include "Managers/ContentManager.h"
//--------------------------------------------------------------------
#include "../Lib/GlobalParameters.h"
#include "../Lib/LemmingsHelpers.h"
//====================================================================

UISpritesheet::UISpritesheet(const int x, const int y, const tstring & name, const UIDockInterface * pParrent, 
		const tstring & asset_file, const UINT frames_x, const UINT frames_y, const float animation_speed)
    : UIImage(x, y, name, pParrent, asset_file)
	, m_FramesX(frames_x)
	, m_FramesY(frames_y)
	, m_CurrentFrame(0)
	, m_AnimationSpeed(animation_speed)
{
	m_ImageSprite.UVX = 1.0f / float(frames_x);
	m_ImageSprite.UVY = 1.0f / float(frames_y);
	m_Scale.x = m_ImageSprite.UVX;
	m_Scale.y = m_ImageSprite.UVY;
}

UISpritesheet::~UISpritesheet()
{
}

void UISpritesheet::Update(const GameContext &context)
{
	m_CurrentFrame += context.GameTime.ElapsedSeconds() * 30.0f * m_AnimationSpeed;
	float maxFrames = float(m_FramesX * m_FramesY);
	if(m_CurrentFrame > maxFrames)
	{
		m_CurrentFrame -= maxFrames;
	}
	UINT frameX = UINT(m_CurrentFrame) % m_FramesX;
	UINT frameY = UINT(m_CurrentFrame) / m_FramesX;
	m_ImageSprite.OffsetX = m_ImageSprite.UVX * frameX;
	m_ImageSprite.OffsetY = m_ImageSprite.UVY * frameY;
	UIImage::Update(context);
}