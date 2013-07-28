//--------------------------------------------------------------------------------------
//   _____     _______ ____  _     ___  ____  ____    _____ _   _  ____ ___ _   _ _____ 
//  / _ \ \   / / ____|  _ \| |   / _ \|  _ \|  _ \  | ____| \ | |/ ___|_ _| \ | | ____|
// | | | \ \ / /|  _| | |_) | |  | | | | |_) | | | | |  _| |  \| | |  _ | ||  \| |  _|  
// | |_| |\ V / | |___|  _ <| |__| |_| |  _ <| |_| | | |___| |\  | |_| || || |\  | |___ 
//  \___/  \_/  |_____|_| \_\_____\___/|_| \_\____/  |_____|_| \_|\____|___|_| \_|_____|
//
// Overlord Engine v0.44
// Copyright Overlord Brecht Kets & Overlord Thomas Goussaert
// http://www.digitalartsandentertainment.com/
//--------------------------------------------------------------------------------------

#pragma once

#include "Helpers/stdafx.h"
#include "Helpers/D3DUtil.h"
#include "Helpers/GeneralStructs.h"
#include "Components/CameraComponent.h"
#include "Managers/InputManager.h"
#include <vector>
#include "../UserInterface/UIDockInterface.h"

class BaseModeScreen;
class ColissionEntity;
class GameScreen;
class SpriteFont;

class BaseModeScreen
{
public:
	BaseModeScreen(GameScreen * parent, InputManager * inputManager);
	virtual ~BaseModeScreen(void);

	virtual void Initialize();
	virtual void Update(const GameContext& context);
	virtual void Draw(const GameContext& context);

	void SetMainTitle(const tstring & title);

protected:
	InputManager *m_pInputManager;
	GameScreen *m_pParentScreen;
	//UIZone *m_pDeveloperZone, *m_pDebugZone;
	SpriteFont *m_pDefaultFont;

private:
	// Disabling default copy constructor and default assignment operator.
	BaseModeScreen(const BaseModeScreen& yRef);									
	BaseModeScreen& operator=(const BaseModeScreen& yRef);
};

