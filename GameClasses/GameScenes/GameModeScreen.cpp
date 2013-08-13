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
#include "../Entities/RisingWater.h"
#include "../GameObjects/GameEntity.h"
#include "../GameObjects/ColissionEntity.h"
#include "../GameObjects/LemmingCharacter.h"
#include "../GameObjects/PhysicsCube.h"
#include "../GameObjects/EditorCamera.h"
#include "../Managers/ScreenManager.h"
#include "../Managers/Stopwatch.h"
#include "../Managers/ColissionCollector.h"
//====================================================================

GameModeScreen::GameModeScreen(GameScreen * parent, InputManager *inputManager)
	: BaseModeScreen(parent, inputManager)
	, m_pCamera(nullptr)
	,m_pLemmingsCharacter(nullptr)
	,m_pLemmingsCharacter1(nullptr)
	,m_pLemmingsCharacter2(nullptr)
	,m_pRisingWater(nullptr)
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

	//m_pRisingWater = new RisingWater(m_pLevel->GetMinDepth(), m_pLevel->GetMaxDepth());
	/*D3DXVECTOR3 offset = m_pLevel->Getoffset();
	float size = GlobalParameters::GetParameters()->GetParameter<float>(_T("GRID_SIZE"));
	for(UINT row = 0 ; row < m_pLevel->GetHeight() ; row += 30)
	{
		for(UINT col = 0 ; col < m_pLevel->Getwidth() ; col += 30)
		{
			D3DXVECTOR3 pos(col * size, 0, row * size);
			pos += offset;
			LemmingsHelpers::SnapPositionXYZ(pos, size);
			pos.x -= 0.25f;
			pos.z -= 0.25f;
			pos.y -= 15 * size;
			m_pRisingWater->AddInstance(pos);
		}
	}
	m_pRisingWater->Initialize();*/
}

void GameModeScreen::Update(const GameContext& context)
{
	if(context.Input->IsActionTriggered((int)InputControls::KB_ESCAPE_PRESSED))
	{
		m_pParentScreen->SetState(_T("menu"));
	}
	m_pParentScreen->GetPlayer()->Update(context);
	m_pParentScreen->GetPlayer()->UpdateMenu(context);
	//m_pRisingWater->Update(context);
	ColissionCollector::GetInstance()->Update(const_cast<GameContext&>(context));
}

void GameModeScreen::Draw(const GameContext& context)
{
	//m_pRisingWater->Draw(context);
}

void GameModeScreen::Draw2D(const GameContext& context)
{
	m_pParentScreen->GetPlayer()->DrawMenu(context);
	//m_pRisingWater->Draw2D(context);
}

void GameModeScreen::Activate()
{
	m_pCamera->GetComponent<CameraComponent>()->SetActive();
	m_pParentScreen->SetActiveCamera(m_pCamera);
}

void GameModeScreen::Deactivate()
{
}