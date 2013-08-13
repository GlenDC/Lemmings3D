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
#include "../Entities/Player.h"
#include "../Lib/GlobalParameters.h"
#include "../Lib/LemmingsHelpers.h"
#include "../Entities/EditorBuilder.h"
#include "../GameObjects/GameEntity.h"
#include "../GameObjects/ColissionEntity.h"
#include "../GameObjects/PhysicsCube.h"
#include "../GameObjects/EditorCamera.h"
#include "../Managers/ScreenManager.h"
#include "../Managers/Stopwatch.h"
#include "../Managers/ColissionCollector.h"
//====================================================================

GameModeScreen::GameModeScreen(GameScreen * parent, InputManager *inputManager)
	: BaseModeScreen(parent, inputManager)
	, m_pCamera(nullptr)
{

}


GameModeScreen::~GameModeScreen(void)
{
}

void GameModeScreen::Initialize()
{
	m_pCamera = new EditorCamera();
	m_pParentScreen->AddSceneObject(m_pCamera);
	m_pCamera->GetComponent<CameraComponent>()->SetFieldOfView(LemmingsHelpers::ToRad(m_pParentScreen->GetPlayer()->GetSetting<float>(_T("EDITOR_CAMERA_FOV"))));
	m_pCamera->SetInformation(m_pParentScreen->GetPlayer()->GetSetting<D3DXVECTOR3>(_T("EDITOR_CAMERA_POS")),
									m_pParentScreen->GetPlayer()->GetSetting<float>(_T("EDITOR_CAMERA_YAW")),
									m_pParentScreen->GetPlayer()->GetSetting<float>(_T("EDITOR_CAMERA_PITCH")),
									m_pParentScreen->GetPlayer()->GetSetting<float>(_T("EDITOR_CAMERA_SPEED")),
									m_pParentScreen->GetPlayer()->GetSetting<float>(_T("EDITOR_CAMERA_ROT_SPEED")));
}

void GameModeScreen::Update(const GameContext& context)
{
	m_pParentScreen->GetPlayer()->Update(context);
	m_pParentScreen->GetPlayer()->UpdateMenu(context);
	//m_pRisingWater->Update(context);
	ColissionCollector::GetInstance()->Update(const_cast<GameContext&>(context));
}

void GameModeScreen::Draw(const GameContext& context)
{
}

void GameModeScreen::Draw2D(const GameContext& context)
{
	m_pParentScreen->GetPlayer()->DrawMenu(context);
}

void GameModeScreen::Activate()
{
	m_pCamera->GetComponent<CameraComponent>()->SetActive();
}

void GameModeScreen::Deactivate()
{
}