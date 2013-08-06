#pragma once

//====================== #INCLUDES ===================================
#include "UIElement.h"
#include <memory>
//====================================================================

//====================== UITextField Class ===========================
// Description:
//		Textfield used in a zone of the Userinterface
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class UITextField : public UIElement
{
public:
	UITextField(const int x, const int y, const int width, const tstring & name, const UIDockInterface * pParrent,
		const tstring & text, shared_ptr<SpriteFont> pFont, const D3DXCOLOR & color = D3DXCOLOR(0.8f,0.8f,0.8f,1));
	virtual ~UITextField();

	virtual void Draw(const GameContext & context) const;
	void SetTextColor(const D3DXCOLOR & color) { m_TextColor = color; }
	void SetText(const tstring & text) { m_Text = text; }

protected:
    D3DXCOLOR m_TextColor;
    tstring m_Text;
	shared_ptr<SpriteFont> m_pFont;

private:
	UITextField(const UITextField& yRef);									
	UITextField& operator=(const UITextField& yRef);
};