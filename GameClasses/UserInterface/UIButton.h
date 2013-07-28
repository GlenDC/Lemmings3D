#pragma once

//====================== #INCLUDES ===================================
#include "UIElement.h"
//====================================================================

//====================== UIButton Class ==============================
// Description:
//		Button used in the userinterface
// Last Modification: 20/05/2013
// Copyright Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class UIButton : public UIElement
{
public:
	UIButton(int x, int y, const tstring & name, UIDockInterface * pParrent, const tstring & asset_file);
	virtual ~UIButton(); //default destructor

	virtual void Draw(const GameContext &context) const;
	virtual void Update(const GameContext &context);

protected:
	ID3D10ShaderResourceView *m_pTexture;
	SpriteInfo m_ButtonSprite;

private:
	UIButton(const UIButton& yRef);									
	UIButton& operator=(const UIButton& yRef);
};