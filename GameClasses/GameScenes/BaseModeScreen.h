#pragma once

//====================== #INCLUDES ===================================
#include "Helpers/stdafx.h"
#include "Helpers/D3DUtil.h"
#include "Helpers/GeneralStructs.h"
#include "Components/CameraComponent.h"
#include "Managers/InputManager.h"
#include "../Entities/State.h" 
#include <vector>
#include <memory>
//====================================================================

//====================== BaseModeScreen Class ====================
// Description:
//		Base Class for all screens in this game.
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class ColissionEntity;
class GameScreen;
class SpriteFont;

class BaseModeScreen : public State
{
public:
	virtual ~BaseModeScreen(void) {}

	virtual void Initialize(void) = 0;
	virtual void Update(const GameContext& context) = 0;
	virtual void Draw(const GameContext& context) = 0;
	virtual void Draw2D(const GameContext& context) = 0;

	virtual void Activate() { State::Activate(); }
	virtual void Deactivate() { State::Deactivate(); }

	void SetMainTitle(const tstring & title);

protected:
	BaseModeScreen(GameScreen * parent, const InputManager * inputManager);
	const InputManager *m_pInputManager;
	GameScreen *m_pParentScreen;
	// Default font will be used by many objects, which makes it safer
	// to use a shared pointer in this case.
	std::shared_ptr<SpriteFont> m_pDefaultFont;

private:
	// Disabling default copy constructor and default assignment operator.
	BaseModeScreen(const BaseModeScreen& yRef);									
	BaseModeScreen& operator=(const BaseModeScreen& yRef);
};

