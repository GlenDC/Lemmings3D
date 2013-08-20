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

//====================== DemoModeNXFluid Class ====================
// Description:
//		Mode Class to test the NXFluid Implementation
// Last Modification: August 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class SpriteFont;
class UIDockInterface;
class GameScene;
class WaterObject;

class DemoModeNXFluid : public DemoModeBase
{
public:
	DemoModeNXFluid(GameScene * scene);
	virtual ~DemoModeNXFluid(void);

	virtual void Initialize(void);
	virtual void Update(const GameContext& context);
	virtual void Draw(const GameContext& context);
	virtual void Draw2D(const GameContext& context);

	virtual void Activate();
	virtual void Deactivate();

private:
	WaterObject * m_pFluids;

	// Disabling default copy constructor and default assignment operator.
	DemoModeNXFluid(const DemoModeNXFluid& yRef);									
	DemoModeNXFluid& operator=(const DemoModeNXFluid& yRef);
};

