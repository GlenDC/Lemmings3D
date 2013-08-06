#pragma once

//====================== #INCLUDES ===================================
#include "UIElement.h"
#include <memory>
//====================================================================

//====================== UIToggleButton Class ==============================
// Description:
//		A on/off button. Other examples are checkboxes
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class UIToggleButton : public UIElement
{
public:
	UIToggleButton(const int x, const int y, const tstring & name, 
		const UIDockInterface * pParrent, const tstring & asset_file);
	virtual ~UIToggleButton(); //default destructor

	virtual void Draw(const GameContext &context) const;
	virtual void Update(const GameContext &context);
	virtual void Select();

	void SetOnline(const bool is_on);

protected:
	ID3D10ShaderResourceView *m_pTexture;
	SpriteInfo m_ButtonSprite;

private:
	UIToggleButton(const UIToggleButton& yRef);									
	UIToggleButton& operator=(const UIToggleButton& yRef);
};