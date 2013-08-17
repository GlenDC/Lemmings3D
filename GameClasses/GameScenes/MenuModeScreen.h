#pragma once

//====================== #INCLUDES ===================================
#include "BaseModeScreen.h"
//====================================================================

class UIDockInterface;
class SpriteFont;

//====================== MenuModeScreen Class =========================
// Description:
//		Screen State for the game menu logic
// Last Modification: August 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class MenuModeScreen : public BaseModeScreen
{
public:
	MenuModeScreen(GameScreen * parent, InputManager * inputManager);
	virtual ~MenuModeScreen(void);

	virtual void Initialize();
	virtual void Update(const GameContext& context);
	virtual void Draw(const GameContext& context);
	virtual void Draw2D(const GameContext& context);

	virtual void Activate();
	virtual void Deactivate();

	virtual void Save();
	
private:
	shared_ptr<SpriteFont> m_pSpriteFont;
	UIDockInterface * m_MainMenuDock;

	// Disabling default copy constructor and default assignment operator.
	MenuModeScreen(const MenuModeScreen& yRef);									
	MenuModeScreen& operator=(const MenuModeScreen& yRef);
};

