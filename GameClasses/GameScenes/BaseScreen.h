#pragma once
//====================== #INCLUDES ===================================
#include "Scenegraph/GameScene.h"
//====================================================================

//====================== BaseScreen Class =================================
// Description:
//		BaseScreen based on GameScreen of the overlord engine.
//		Reason to do this is to allow options like 2 scenes at 
//		the same time to be open.
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================
class GameEntity;
class FreeCamera;

// base class
class BaseScreen : public GameScene
{
public:
	BaseScreen(const tstring & name, const tstring & windowName, const bool physicsEnabled);
	virtual ~BaseScreen(void);

	virtual void Initialize();
	virtual void Update(const GameContext& context);
	virtual void Draw(const GameContext& context);

	virtual void BeginControl() = 0;
	virtual void EndControl() = 0;

	virtual void Activated() = 0;
	virtual void Deactivated() = 0;

	const tstring & GetWindowName() const { return m_WindowName; }
	const bool IsPhysicsEnabled() const { return m_PhysicsEnabled; }

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