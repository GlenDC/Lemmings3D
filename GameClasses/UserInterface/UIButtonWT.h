#pragma once

//====================== #INCLUDES ===================================
#include "UIButton.h"
#include "../Lib/LemmingsHelpers.h"
//====================================================================

//====================== UIButtonWT Class ==============================
// Description:
//		A button with a textfield on top of it. 
// Last Modification: 20/05/2013
// Copyright Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class UIButtonWT : public UIButton
{
public:
	UIButtonWT(int x, int y, const tstring & name, UIDockInterface * pParrent, const tstring & asset_file,
		UINT textX, UINT textY, const tstring & text, SpriteFont * pFont, const D3DXCOLOR & color_idle,
		const D3DXCOLOR & color_hover, const D3DXCOLOR & color_click, const D3DXCOLOR & color_disabled = D3DXCOLOR(1,0,0,1));
	~UIButtonWT(); // default destructor
	//change text of textfield in this ButtonWT
	void SetText(const tstring & text);
	
	virtual void Draw(const GameContext & context);

protected:
	//Text to be shown on top off the button
	tstring m_Text;
	//2D offset, adding this to the button position gives us the text position
	LemmingsHelpers::Position m_TextOffset;
	//Text State Colors;
	D3DXCOLOR m_TextColors[sizeof(ElementStates)];
	//font to be used (shared pointer)
	SpriteFont * m_pFont;

private:
	UIButtonWT(const UIButtonWT& yRef);									
	UIButtonWT& operator=(const UIButtonWT& yRef);
};