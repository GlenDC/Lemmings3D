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

#include "Week6_picking.h"
#include "OverlordComponents.h"
#include "Scenegraph/GameObject.h"
#include "Graphics/GraphicsDevice.h"
#include "OverlordComponents.h"
#include "Helpers/GeneralStructs.h"
#include "../../GameObjects/ColissionEntity.h"
#include "../../Managers/ScreenManager.h"
#include "Managers/ContentManager.h"
#include "helpers/SpriteFont.h"
#include "helpers/D3DUtil.h"


Week6_picking::Week6_picking(void)
	:BaseScreen(_T("Week6_picking"), _T("Lab Week6_picking: Picking some objects"), true)
	,m_pSpriteFont(nullptr)
	,m_SelectedObjectName(_T("none"))
	,m_pEntity1(nullptr)
	,m_pEntity2(nullptr)
	,m_pEntity3(nullptr)
{
}


Week6_picking::~Week6_picking(void)
{
}

void Week6_picking::Initialize()
{
	m_pSpriteFont = ContentManager::Load<SpriteFont>(_T("./Resources/Verdana_12.fnt"));

	m_pEntity1 = new ColissionEntity();
	m_pEntity2 = new ColissionEntity();
	m_pEntity3 = new ColissionEntity();

	AddSceneObject(m_pEntity1);
	AddSceneObject(m_pEntity2);
	AddSceneObject(m_pEntity3);

	auto pickComponent = new PickComponent();
	m_pActiveCamera->GetParentObject()->AddComponent(pickComponent);

	BaseScreen::Initialize();

	m_pEntity1->GetComponent<TransformComponent>()->Translate(-10,0,0);
	m_pEntity2->GetComponent<TransformComponent>()->Translate(0,0,0);
	m_pEntity3->GetComponent<TransformComponent>()->Translate(10,0,0);

	m_pEntity1->GetComponent<RigidBodyComponent>()->AddConstraints(Constraints::DISABLE_GRAVITY);
	m_pEntity2->GetComponent<RigidBodyComponent>()->AddConstraints(Constraints::DISABLE_GRAVITY);
	m_pEntity3->GetComponent<RigidBodyComponent>()->AddConstraints(Constraints::DISABLE_GRAVITY);

	//ScreenManager::GetInstance()->m_pInputManager->AddInputAction(InputAction(1, Pressed, VK_SPACE, VK_LBUTTON));
}

void Week6_picking::Update(const GameContext& context)
{
	if(context.Input->IsActionTriggered(1))
	{
		GameObject * returnObject = m_pActiveCamera->GetParentObject()->GetComponent<PickComponent>()->Pick(context.Input->GetMousePosition(), GraphicsDevice::GetInstance()->GetWindowDimensions());
		if(returnObject == nullptr)
		{
			m_SelectedObjectName = _T("none");
		}
		else if(returnObject == m_pEntity1)
		{
			m_SelectedObjectName = _T("left");
		}
		else if(returnObject == m_pEntity2)
		{
			m_SelectedObjectName = _T("middle");
		}
		else if(returnObject == m_pEntity3)
		{
			m_SelectedObjectName = _T("right");
		}
	}

	BaseScreen::Update(context);
}

void Week6_picking::Draw(const GameContext& context)
{
	GraphicsDevice::GetInstance()->Clear(D3DXCOLOR(0,0,0,1));
	SpriteBatch::DrawTextW(m_pSpriteFont, _T("SelectedObject: ") + m_SelectedObjectName, D3DXVECTOR2(5,5));
	BaseScreen::Draw(context);
}