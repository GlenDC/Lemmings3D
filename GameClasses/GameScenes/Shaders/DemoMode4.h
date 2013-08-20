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

class GameEntity;

//====================== DemoMode4 Class ====================
// Description:
//		Mode Class for Expirement 4
// Last Modification: August 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class SpriteFont;
class UIDockInterface;
class GameScene;

class DemoMode4 : public DemoModeBase
{
public:
	DemoMode4(GameScene * scene);
	virtual ~DemoMode4(void);

	virtual void Initialize(void);
	virtual void Update(const GameContext& context);
	virtual void Draw(const GameContext& context);
	virtual void Draw2D(const GameContext& context);

	virtual void Activate();
	virtual void Deactivate();

private:

	// Disabling default copy constructor and default assignment operator.
	DemoMode4(const DemoMode4& yRef);									
	DemoMode4& operator=(const DemoMode4& yRef);
};

