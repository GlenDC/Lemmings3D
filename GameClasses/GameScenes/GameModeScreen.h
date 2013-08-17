#pragma once

//====================== #INCLUDES ===================================
#include "BaseModeScreen.h"
//====================================================================

class GameCamera;
class LemmingCharacter;
class RisingWater;

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

	virtual void Save();
	
private:
	GameCamera *m_pCamera;

	LemmingCharacter	*m_pLemmingsCharacter, 
						*m_pLemmingsCharacter1, 
						*m_pLemmingsCharacter2;

	RisingWater *m_pRisingWater;

	// Disabling default copy constructor and default assignment operator.
	GameModeScreen(const GameModeScreen& yRef);									
	GameModeScreen& operator=(const GameModeScreen& yRef);
};

