//====================== #INCLUDES ===================================
#include "EditModeScreen.h"
//--------------------------------------------------------------------
#include "OverlordComponents.h"
#include "GameScreen.h"
#include "Graphics/GraphicsDevice.h"
#include "Helpers/GeneralStructs.h"
#include "Helpers/D3DUtil.h"
#include "Scenegraph/GameObject.h"
#include "OverlordComponents.h"
//--------------------------------------------------------------------
#include "../Entities/ParameterClass.h"
#include "../GameObjects/ColissionEntity.h"
#include "../GameObjects/GameEntity.h"
#include "../Managers/ScreenManager.h"
#include "../Managers/Stopwatch.h"
//====================================================================

EditModeScreen::EditModeScreen(GameScreen * parent, InputManager *inputManager)
	:BaseModeScreen(parent, inputManager)
{
}

EditModeScreen::~EditModeScreen(void)
{
}

void EditModeScreen::Initialize()
{
}

void EditModeScreen::Update(const GameContext& context)
{
}

void EditModeScreen::Draw(const GameContext& context)
{
}