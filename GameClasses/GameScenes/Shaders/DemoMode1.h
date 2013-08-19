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

//====================== DemoMode1 Class ====================
// Description:
//		Mode Class for Expirement 1
// Last Modification: August 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class SpriteFont;
class UIDockInterface;

class DemoMode1 : public DemoModeBase
{
public:
	DemoMode1();
	virtual ~DemoMode1(void);

	virtual void Initialize(void);
	virtual void Update(const GameContext& context);
	virtual void Draw(const GameContext& context);
	virtual void Draw2D(const GameContext& context);

	virtual void Activate();
	virtual void Deactivate();

private:
	// Disabling default copy constructor and default assignment operator.
	DemoMode1(const DemoMode1& yRef);									
	DemoMode1& operator=(const DemoMode1& yRef);
};

