#include "Player.h"
#include "Helpers/GeneralStructs.h"
#include "OverlordComponents.h"
#include "../UserInterface/UIDockInterface.h"
#include "Scenegraph/GameScene.h"
#include "../Managers/ScreenManager.h"
#include "Managers/ContentManager.h"
#include "Scenegraph/GameObject.h"
#include "../GameObjects/LemmingCharacter.h"
#include "Helpers/SpriteFont.h"
#include "../Managers/SpritefontManager.h"

Player::Player(const tstring & name, GameScene *pScene)
	: m_Name(name)
	, m_pSettings(nullptr)
	, m_pSelectedObject(nullptr)
	, m_pPlayerObject(nullptr)
	, m_pPickComponent(nullptr)
	, m_pSelectionMenu(nullptr)
{
	m_pSettings = new UserSettings(this);

	m_pPlayerObject = new GameObject();
	pScene->AddSceneObject(m_pPlayerObject);

	m_pPickComponent = new PickComponent();
	m_pPlayerObject->AddComponent(m_pPickComponent);

	m_pPlayerObject->Initialize();

	m_pSelectionMenu = new UIDockInterface(60, 0, 300, 60, nullptr, nullptr);
	m_pSelectionMenu->AddImage(0,0,_T("Asel_Avatar"), _T("Selection_Avatar.png"));
	auto pFont35 = SpritefontManager::GetInstance()->CreateOrGet(_T("GameOver"), 35);
	m_pSelectionMenu->AddTextField(50,-3,50,35,_T("Asel_Name"), _T("Lemming"), D3DXCOLOR(0.85f, 0.85f, 0.85f, 1.0f),pFont35);
	m_pSelectionMenu->Initialize();
}

Player::~Player()
{
	delete m_pSettings;
}

void Player::Update(const GameContext & context)
{
	if(context.Input->IsActionTriggered((int)InputControls::MOUSE_LEFT_PRESSED))
	{
		m_pSelectedObject = m_pPickComponent->Pick(context, context.Input->GetMousePosition(), D3DXVECTOR2(1280,720));
		if(m_pSelectedObject != nullptr)
		{
			m_pSelectedObject = dynamic_cast<LemmingCharacter*>(m_pSelectedObject);
		}
	}
}

void Player::UpdateMenu(const GameContext & context)
{
	if(m_pSelectedObject != nullptr)
	{
		m_pSelectionMenu->Update(context);
	}
}

void Player::DrawMenu(const GameContext & context)
{
	if(m_pSelectedObject != nullptr)
	{
		m_pSelectionMenu->Draw(context);
	}
}

void Player::Save()
{
	m_pSettings->SaveSettings();
}