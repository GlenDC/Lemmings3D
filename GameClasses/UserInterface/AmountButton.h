#pragma once

//====================== #INCLUDES ===================================
#include "UIButton.h"
#include "../Lib/LemmingsHelpers.h"
#include <memory>
//====================================================================

//====================== AmountButton Class ==============================
// Description:
//		A button with an amount counter on top of it (max 99)
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class AmountButton : public UIButton
{
public:
	AmountButton(int x, int y, const tstring & name, const UIDockInterface * pParrent, const tstring & asset_file, int amount, shared_ptr<SpriteFont> pFont);
	~AmountButton(); // default destructor
	//change text of textfield in this ButtonWT
	void SetText(const tstring & text);
	
	virtual void Draw(const GameContext & context) const;

	void SetAmount(int amount);
	const int & GetAmount() const;

	bool SubstractAmount();

protected:
	//Text to be shown on top off the button
	int m_Amount;
	//font to be used (shared pointer)
	shared_ptr<SpriteFont> m_pFont;

private:
	AmountButton(const AmountButton& yRef);									
	AmountButton& operator=(const AmountButton& yRef);
};