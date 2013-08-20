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

//====================== DemoModeNXJoint Class ====================
// Description:
//		Mode Class for nx joint tests
// Last Modification: August 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class SpriteFont;
class UIDockInterface;
class GameScene;
class ColissionEntity;

class DemoModeNXJoint : public DemoModeBase
{
public:
	DemoModeNXJoint(GameScene * scene);
	virtual ~DemoModeNXJoint(void);

	virtual void Initialize(void);
	virtual void Update(const GameContext& context);
	virtual void Draw(const GameContext& context);
	virtual void Draw2D(const GameContext& context);

	virtual void Activate();
	virtual void Deactivate();

private:
	void ShootCube();

	ColissionEntity * m_pActorA, *m_pActorB, *m_pActorC, *m_pActorD, *m_pActorE;

	std::vector<ColissionEntity*> m_Ammo;

	// Disabling default copy constructor and default assignment operator.
	DemoModeNXJoint(const DemoModeNXJoint& yRef);									
	DemoModeNXJoint& operator=(const DemoModeNXJoint& yRef);
};

