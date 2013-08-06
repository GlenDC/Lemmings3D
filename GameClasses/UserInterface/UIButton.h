#pragma once

//====================== #INCLUDES ===================================
#include "UIElement.h"
#include <memory>
//====================================================================

//====================== UIButton Class ==============================
// Description:
//		Button used in the userinterface
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class UIButton : public UIElement
{
public:
	UIButton(const int x, const int y, const tstring & name, 
		const UIDockInterface * pParrent, 
		const tstring & asset_file);
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