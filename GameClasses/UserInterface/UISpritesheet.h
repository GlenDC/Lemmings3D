#pragma once

//====================== #INCLUDES ===================================
#include "UIImage.h"
#include <memory>
//====================================================================

//====================== UISpritesheet Class ==============================
// Description:
//		A normal texture to be used as an image within a dock of the userinterface
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class UISpritesheet : public UIImage
{
public:
	UISpritesheet(const int x, const int y, const tstring & name, const UIDockInterface * pParrent, 
		const tstring & asset_file, const UINT frames_x, const UINT frames_y, const float animation_speed);
	virtual ~UISpritesheet(); //default destructor

	virtual void Update(const GameContext &context);

protected:
	UINT m_FramesX, m_FramesY;
	float m_CurrentFrame, m_AnimationSpeed;

private:
	UISpritesheet(const UISpritesheet& yRef);									
	UISpritesheet& operator=(const UISpritesheet& yRef);
};