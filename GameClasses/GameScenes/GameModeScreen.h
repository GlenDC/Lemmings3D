#pragma once

//====================== #INCLUDES ===================================
#include "BaseModeScreen.h"
//====================================================================

//====================== GameModeScreen Class =========================
// Description:
//		Screen for the game
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class GameEntity;
class ColissionEntity;

class GameModeScreen : public BaseModeScreen
{
public:
	GameModeScreen(GameScreen * parent, InputManager * inputManager);
	virtual ~GameModeScreen(void);

	virtual void Initialize();
	virtual void Update(const GameContext& context);
	virtual void Draw(const GameContext& context);
	
private:
	// Disabling default copy constructor and default assignment operator.
	GameModeScreen(const GameModeScreen& yRef);									
	GameModeScreen& operator=(const GameModeScreen& yRef);
};

