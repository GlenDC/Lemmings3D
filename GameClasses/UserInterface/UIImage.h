#pragma once

//====================== #INCLUDES ===================================
#include "UIElement.h"
#include <memory>
//====================================================================

//====================== UIImage Class ==============================
// Description:
//		A normal texture to be used as an image within a dock of the userinterface
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class UIImage : public UIElement
{
public:
	UIImage(const int x, const int y, const tstring & name, const UIDockInterface * pParrent, const tstring & asset_file);
	virtual ~UIImage(); //default destructor

	virtual void Draw(const GameContext &context) const;
	virtual void Update(const GameContext &context);

protected:
	ID3D10ShaderResourceView *m_pTexture;
	SpriteInfo m_ImageSprite;
	D3DXVECTOR2 m_Scale;

private:
	UIImage(const UIImage& yRef);									
	UIImage& operator=(const UIImage& yRef);
};