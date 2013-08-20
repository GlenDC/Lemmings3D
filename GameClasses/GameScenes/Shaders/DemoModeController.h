#pragma once
//====================== #INCLUDES ===================================
#include "Helpers/stdafx.h"
#include "Helpers/D3DUtil.h"
#include "Helpers/GeneralStructs.h"
#include "Components/CameraComponent.h"
#include "Managers/InputManager.h"
#include "DemoModeBase.h" 
#include <vector>
#include <memory>
//====================================================================

//====================== DemoModeController Class ====================
// Description:
//		Mode Class for testing the character controller ( + animations )
// Last Modification: August 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class SpriteFont;
class UIDockInterface;
class GameScene;
class GameObject;
class Hero;

class DemoModeController : public DemoModeBase
{
public:
	DemoModeController(GameScene * scene);
	virtual ~DemoModeController(void);

	virtual void Initialize(void);
	virtual void Update(const GameContext& context);
	virtual void Draw(const GameContext& context);
	virtual void Draw2D(const GameContext& context);

	virtual void Activate();
	virtual void Deactivate();

private:
	GameObject *m_pFloor;
	Hero * m_pPlayer;

	// Disabling default copy constructor and default assignment operator.
	DemoModeController(const DemoModeController& yRef);									
	DemoModeController& operator=(const DemoModeController& yRef);
};

