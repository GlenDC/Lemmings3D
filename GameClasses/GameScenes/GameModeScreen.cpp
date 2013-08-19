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
#include "../GameObjects/Hero.h"
#include "../GameObjects/ColissionEntity.h"
#include "../GameObjects/LemmingCharacter.h"
#include "../GameObjects/PhysicsCube.h"
#include "../GameObjects/GameCamera.h"
#include "../GameObjects/FollowCamera.h"
#include "../Managers/ScreenManager.h"
#include "../Managers/Stopwatch.h"
#include "../Managers/ColissionCollector.h"
#include "../Managers/SpritefontManager.h"
//====================================================================

GameModeScreen::GameModeScreen(GameScreen * parent, InputManager *inputManager)
	: BaseModeScreen(parent, inputManager)
	, m_pFollowCamera(nullptr)
	, m_pCamera(nullptr)
	, m_pSelectedObject(nullptr)
	, m_pLemmingsCharacter(nullptr)
	, m_pLemmingsCharacter1(nullptr)
	, m_pLemmingsCharacter2(nullptr)
	, m_pHero(nullptr)
	, m_pRisingWater(nullptr)
{

}


GameModeScreen::~GameModeScreen(void)
{
	ColissionCollector::GetInstance()->RemoveUser(m_pHero);
}

void GameModeScreen::Initialize()
{
	m_pFollowCamera = new FollowCamera();
	m_pParentScreen->AddSceneObject(m_pFollowCamera);

	m_pCamera = new GameCamera(m_pParentScreen);
	m_pParentScreen->AddSceneObject(m_pCamera);
	m_pCamera->GetComponent<CameraComponent>()->SetFieldOfView(LemmingsHelpers::ToRad(m_pParentScreen->GetPlayer()->GetSetting<float>(_T("GAME_CAMERA_FOV"))));
	m_pCamera->SetInformation(m_pParentScreen->GetPlayer()->GetSetting<D3DXVECTOR3>(_T("GAME_CAMERA_POS")),
									m_pParentScreen->GetPlayer()->GetSetting<float>(_T("GAME_CAMERA_YAW")),
									m_pParentScreen->GetPlayer()->GetSetting<float>(_T("GAME_CAMERA_PITCH")),
									m_pParentScreen->GetPlayer()->GetSetting<float>(_T("GAME_CAMERA_SPEED")),
									m_pParentScreen->GetPlayer()->GetSetting<float>(_T("GAME_CAMERA_ROT_SPEED")));

	m_pHero = new Hero();
	m_pParentScreen->AddSceneObject(m_pHero);
	m_pHero->Translate(m_pParentScreen->GetLevel()->GetCenter());
	ColissionCollector::GetInstance()->AddUser(m_pHero);

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
	if(context.Input->IsMouseButtonDown(VK_RBUTTON))
	{
		auto object = m_pParentScreen->GetPlayer()->GetPickComponent()->Pick(context,  context.Input->GetMousePosition(), D3DXVECTOR2(1280,720));
		GameEntity * pEntity(nullptr);
		if(object != nullptr)
		{
			pEntity = dynamic_cast<GameEntity*>(object);
		}
		m_pSelectedObject = pEntity;
		m_pFollowCamera->SetTarget(pEntity);
	}
	if(m_pSelectedObject && context.Input->IsKeyboardKeyDown(VK_SPACE))
	{
		m_pFollowCamera->GetComponent<CameraComponent>()->SetActive();
		if(m_pCamera->GetComponent<CameraComponent>()->IsActive())
		{
			m_pFollowCamera->SetRotation(m_pCamera->GetComponent<TransformComponent>()->GetWorldRotation());
		}
		m_pParentScreen->SetActiveCamera(m_pFollowCamera);
	}
	else
	{
		m_pCamera->GetComponent<CameraComponent>()->SetActive();
		m_pParentScreen->SetActiveCamera(m_pCamera);
	}
	m_pParentScreen->GetPlayer()->Update(context);
	m_pParentScreen->GetPlayer()->UpdateMenu(context);
	//m_pRisingWater->Update(context);
	if(m_pSelectedObject != nullptr)
	{
		m_pSelectedObject->UpdateControl(context);
	}
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

	if(m_pSelectedObject != nullptr)
	{
		auto pFont = SpritefontManager::GetInstance()->CreateOrGet(_T("GameOver"));
		tstringstream strstr;
		strstr << _T("selected: ") << m_pSelectedObject->GetName();
		SpriteBatch::DrawTextW(pFont.get(), strstr.str(), D3DXVECTOR2(120, 5), D3DXCOLOR(0.184f,0.565f,0.22f,1));
	}
}

void GameModeScreen::Activate()
{
	m_pCamera->GetComponent<CameraComponent>()->SetActive();
	m_pParentScreen->SetActiveCamera(m_pCamera);
	m_pParentScreen->SetGameUIDisabled(false);

	BaseModeScreen::Activate();
}

void GameModeScreen::Deactivate()
{
	m_pParentScreen->SetGameUIDisabled(true);

	BaseModeScreen::Deactivate();
}

void GameModeScreen::Save()
{
	auto transform = m_pCamera->GetComponent<TransformComponent>();
	m_pParentScreen->GetPlayer()->SetSetting<D3DXVECTOR3>(_T("GAME_CAMERA_POS"), transform->GetWorldPosition());
	m_pParentScreen->GetPlayer()->SetSetting<float>(_T("GAME_CAMERA_YAW"), m_pCamera->GetYaw());
	m_pParentScreen->GetPlayer()->SetSetting<float>(_T("GAME_CAMERA_PITCH"), m_pCamera->GetPitch());
	m_pParentScreen->GetPlayer()->SetSetting<float>(_T("GAME_CAMERA_FOV"), m_pParentScreen->GetCameraFOV());
	m_pParentScreen->GetPlayer()->SetSetting<int>(_T("GAME_CAMERA_SPEED"), m_pCamera->GetMoveSpeed());
	m_pParentScreen->GetPlayer()->SetSetting<float>(_T("GAME_CAMERA_ROT_SPEED"), m_pCamera->GetRotSpeed());
	m_pParentScreen->GetPlayer()->Save(); 
}