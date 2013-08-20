#pragma once
//====================== #INCLUDES ===================================
#include "Helpers/stdafx.h"
#include "Helpers/D3DUtil.h"
#include "Helpers/GeneralStructs.h"
#include "Components/CameraComponent.h"
#include "Managers/InputManager.h"
#include "../../Entities/State.h" 
#include <vector>
#include <memory>
//====================================================================

//====================== DemoModeBase Class ====================
// Description:
//		Base Class foor all Demo states
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class SpriteFont;
class UIDockInterface;
class GameScene;
class GameEntity;
class GameObject;

class DemoModeBase : public State
{
public:
	virtual ~DemoModeBase(void);

	virtual void Initialize(void);
	virtual void Update(const GameContext& context);
	virtual void Draw(const GameContext& context) = 0;
	virtual void Draw2D(const GameContext& context);

	virtual void Activate();
	virtual void Deactivate();

protected:
	DemoModeBase(GameScene * scene, const tstring & title, const tstring & description = _T("Enter description here..."));
	UIDockInterface * m_pDescriptionDock;
	std::shared_ptr<SpriteFont> m_pDefaultFont;
	GameScene * m_pScene;
	bool m_ContentActive;

	GameEntity * m_pDemoObject;
	static const float ROTATION_SPEED;

	GameObject *m_pCamera;

private:
	// Disabling default copy constructor and default assignment operator.
	DemoModeBase(const DemoModeBase& yRef);									
	DemoModeBase& operator=(const DemoModeBase& yRef);
};

