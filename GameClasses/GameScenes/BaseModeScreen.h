#pragma once

//====================== #INCLUDES ===================================
#include "Helpers/stdafx.h"
#include "Helpers/D3DUtil.h"
#include "Helpers/GeneralStructs.h"
#include "Components/CameraComponent.h"
#include "Managers/InputManager.h"
#include <vector>
#include <memory>
//====================================================================

//====================== ColissionCollector Class ====================
// Description:
//		Base Class for all screens in this game.
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class BaseModeScreen;
class ColissionEntity;
class GameScreen;
class SpriteFont;

class BaseModeScreen
{
public:
	BaseModeScreen(const GameScreen * parent, const InputManager * inputManager);
	virtual ~BaseModeScreen(void);

	virtual void Initialize(void);
	virtual void Update(const GameContext& context);
	virtual void Draw(const GameContext& context);

	void SetMainTitle(const tstring & title);

protected:
	const InputManager *m_pInputManager;
	const GameScreen *m_pParentScreen;
	// Default font will be used by many objects, which makes it safer
	// to use a shared pointer in this case.
	std::shared_ptr<SpriteFont> m_pDefaultFont;

private:
	// Disabling default copy constructor and default assignment operator.
	BaseModeScreen(const BaseModeScreen& yRef);									
	BaseModeScreen& operator=(const BaseModeScreen& yRef);
};

