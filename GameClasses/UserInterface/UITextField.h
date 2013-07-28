#pragma once

//====================== #INCLUDES ===================================
#include "UIElement.h"
#include <memory>
//====================================================================

//====================== UITextField Class ===========================
// Description:
//		Textfield used in a zone of the Userinterface
// Last Modification: 23/03/2013
// Copyright Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class UITextField : public UIElement
{
public:
	UITextField(int x, int y, int width, tstring name, UIDockInterface * pParrent,
		tstring text, SpriteFont * pFont, D3DXCOLOR color = D3DXCOLOR(0.8f,0.8f,0.8f,1));
	virtual ~UITextField();

	virtual void Draw(const GameContext & context) const;
	void SetTextColor(D3DXCOLOR color) { m_TextColor = color; }
	void SetText(tstring text) { m_Text = text; }

protected:
    D3DXCOLOR m_TextColor;
    tstring m_Text;
	SpriteFont * m_pFont;

private:
	UITextField(const UITextField& yRef);									
	UITextField& operator=(const UITextField& yRef);
};