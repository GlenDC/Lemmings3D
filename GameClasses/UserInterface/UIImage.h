#pragma once

//====================== #INCLUDES ===================================
#include "UIElement.h"
//====================================================================

//====================== UIImage Class ==============================
// Description:
//		A normal texture to be used as an image within a dock of the userinterface
// Last Modification: 20/05/2013
// Copyright Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class UIImage : public UIElement
{
public:
	UIImage(int x, int y, tstring name, UIDockInterface * pParrent, tstring asset_file);
	virtual ~UIImage(); //default destructor

	virtual void Draw(const GameContext &context) const;
	virtual void Update(const GameContext &context);

protected:
	ID3D10ShaderResourceView *m_pTexture;
	SpriteInfo m_ImageSprite;

private:
	UIImage(const UIImage& yRef);									
	UIImage& operator=(const UIImage& yRef);
};