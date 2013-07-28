//====================== #INCLUDES ===================================
#include "BaseScreen.h"
#include "../GameObjects/GameEntity.h"
#include "Managers/PhysicsManager.h"
#include "../Managers/ScreenManager.h"
#include "Helpers/DebugRenderer.h"
#include "Diagnostics/Logger.h"
#include "Prefabs/FreeCamera.h"
#include "../Lib/GlobalParameters.h"
//====================================================================

BaseScreen::BaseScreen(wstring name, tstring windowName, bool physicsEnabled)
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
	GameScene::Update(context);
}

void BaseScreen::Draw(const GameContext& context)
{
	GameScene::Draw(context);
}