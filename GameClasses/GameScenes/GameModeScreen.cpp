//====================== #INCLUDES ===================================
#include "GameModeScreen.h"
//--------------------------------------------------------------------
#include "GameScreen.h"
#include "Graphics/GraphicsDevice.h"
#include "Helpers/D3DUtil.h"
#include "Helpers/GeneralStructs.h"
#include "OverlordComponents.h"
#include "Scenegraph/GameObject.h"
//--------------------------------------------------------------------
#include "../Entities/ParameterClass.h"
#include "../GameObjects/GameEntity.h"
#include "../GameObjects/ColissionEntity.h"
#include "../Managers/ScreenManager.h"
#include "../Managers/Stopwatch.h"
//====================================================================

GameModeScreen::GameModeScreen(GameScreen * parent, InputManager *inputManager)
	:BaseModeScreen(parent, inputManager)
{
}


GameModeScreen::~GameModeScreen(void)
{
}

void GameModeScreen::Initialize()
{
}

void GameModeScreen::Update(const GameContext& context)
{
}

void GameModeScreen::Draw(const GameContext& context)
{
}