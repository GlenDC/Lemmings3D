#pragma once

//====================== #INCLUDES ===================================
#include "UIElement.h"
//====================================================================

//====================== UIToggleButton Class ==============================
// Description:
//		A on/off button. Other examples are checkboxes
// Last Modification: 20/05/2013
// Copyright Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class UIToggleButton : public UIElement
{
public:
	UIToggleButton(int x, int y, tstring name, UIDockInterface * pParrent, tstring asset_file);
	virtual ~UIToggleButton(); //default destructor

	virtual void Draw(const GameContext &context) const;
	virtual void Update(const GameContext &context);
	virtual void Select();

	void SetOnline(bool is_on);

protected:
	ID3D10ShaderResourceView *m_pTexture;
	SpriteInfo m_ButtonSprite;

private:
	UIToggleButton(const UIToggleButton& yRef);									
	UIToggleButton& operator=(const UIToggleButton& yRef);
};