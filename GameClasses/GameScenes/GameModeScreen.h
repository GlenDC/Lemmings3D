#pragma once

//====================== #INCLUDES ===================================
#include "BaseModeScreen.h"
//====================================================================

class EditorCamera;

//====================== GameModeScreen Class =========================
// Description:
//		Screen State for the game logic
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class GameModeScreen : public BaseModeScreen
{
public:
	GameModeScreen(GameScreen * parent, InputManager * inputManager);
	virtual ~GameModeScreen(void);

	virtual void Initialize();
	virtual void Update(const GameContext& context);
	virtual void Draw(const GameContext& context);
	virtual void Draw2D(const GameContext& context);

	virtual void Activate();
	virtual void Deactivate();
	
private:
	EditorCamera *m_pCamera;

	// Disabling default copy constructor and default assignment operator.
	GameModeScreen(const GameModeScreen& yRef);									
	GameModeScreen& operator=(const GameModeScreen& yRef);
};

