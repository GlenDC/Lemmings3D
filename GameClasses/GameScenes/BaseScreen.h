#pragma once
//====================== #INCLUDES ===================================
#include "Scenegraph/GameScene.h"
//====================================================================

//====================== BaseScreen Class =================================
// Description:
//		BaseScreen based on GameScreen of the overlord engine.
//		Reason to do this is to allow options like 2 scenes at 
//		the same time to be open.
// Last Modification: 04/03/2013
// Copyright Glen De Cauwsemaecker
// www.glendc.com
//====================================================================
class GameEntity;
class FreeCamera;

class BaseScreen : public GameScene
{
public:
	BaseScreen(tstring name, tstring windowName, bool physicsEnabled);
	virtual ~BaseScreen(void);

	virtual void Initialize();
	virtual void Update(const GameContext& context);
	virtual void Draw(const GameContext& context);

	tstring GetWindowName() { return m_WindowName; }
	bool IsPhysicsEnabled() { return m_PhysicsEnabled; }

protected:
	bool m_PhysicsEnabled;
	tstring m_WindowName;

private:
	friend class ScreenManager;

private:
	// Disabling default copy constructor and default 
	// assignment operator.
	BaseScreen(const BaseScreen& t);
	BaseScreen& operator=(const BaseScreen& t);
};