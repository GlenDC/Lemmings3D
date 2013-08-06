#pragma once

//====================== #INCLUDES ===================================
#include "BaseModeScreen.h"
//====================================================================

//====================== EditModeScreen Class =========================
// Description:
//		Screen for the editor
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class GameEntity;
class ColissionEntity;

class EditModeScreen : public BaseModeScreen
{
public:
	EditModeScreen(GameScreen * parent, InputManager * inputManager);
	virtual ~EditModeScreen(void);

	virtual void Initialize();
	virtual void Update(const GameContext& context);
	virtual void Draw(const GameContext& context);
	
private:
	// Disabling default copy constructor and default assignment operator.
	EditModeScreen(const EditModeScreen& yRef);									
	EditModeScreen& operator=(const EditModeScreen& yRef);
};