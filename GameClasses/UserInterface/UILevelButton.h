#pragma once

//====================== #INCLUDES ===================================
#include "UIElement.h"
#include <memory>
#include <functional>
//====================================================================

class UIDockInterface;

//====================== UILevelButton Class ===========================
// Description:
//		Textfield used in a zone of the Userinterface
// Last Modification: August 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class UILevelButton : public UIElement
{
public:
	UILevelButton(const int x, const int y, const tstring & name, const UIDockInterface * pParrent,
		const tstring & level_name, const tstring & button_image, const UINT level_id, const UINT highscore, const UINT best_time, function<void()> select_function);
	virtual ~UILevelButton();

	virtual void Draw(const GameContext & context) const;
	virtual void Update(const GameContext &context);

	virtual void SetDisabled(bool disabled);

protected:
	tstring m_LevelName;
	UINT m_LevelID, 
		 m_Highscore,
		 m_BestTime;
	shared_ptr<SpriteFont> m_pFont;
	UIDockInterface * m_pDock;

private:
	UILevelButton(const UILevelButton& yRef);									
	UILevelButton& operator=(const UILevelButton& yRef);
};