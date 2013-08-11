//====================== #INCLUDES ===================================
#include "BaseScreen.h"

#include "Diagnostics/Logger.h"
#include "Helpers/DebugRenderer.h"
#include "Managers/PhysicsManager.h"
#include "Prefabs/FreeCamera.h"
#include "../GameObjects/GameEntity.h"
#include "../Managers/ScreenManager.h"
#include "../Lib/GlobalParameters.h"
//====================================================================

BaseScreen::BaseScreen(const tstring & name, const tstring & windowName, const bool physicsEnabled)
	: GameScene(name)
	, m_WindowName(windowName)
	, m_PhysicsEnabled(physicsEnabled)
{
}

BaseScreen::~BaseScreen(void)
{

}

void BaseScreen::Initialize()
{
	ScreenManager::GetInstance()->m_pInputManager->AddInputAction(InputAction((int)InputControls::KB_F12_PRESSED, Pressed, VK_F12));
	GameScene::Initialize();
}

void BaseScreen::Update(const GameContext& context)
{
	if(ScreenManager::GetInstance()->m_pInputManager->IsActionTriggered((int)InputControls::KB_F12_PRESSED))
	{
		ScreenManager::GetInstance()->TogglePhysicsDisable();
	}
}

void BaseScreen::Draw(const GameContext& context)
{
}