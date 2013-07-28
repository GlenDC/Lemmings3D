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

#include "Week1.h"
#include "OverlordComponents.h"
#include "Scenegraph/GameObject.h"
#include "Graphics/GraphicsDevice.h"
#include "OverlordComponents.h"
#include "Helpers/GeneralStructs.h"
#include "../../GameObjects/GameEntity.h"
#include "../../GameObjects/ColissionEntity.h"
#include "../../Managers/ScreenManager.h"
#include "../../Managers/Stopwatch.h"
#include "helpers/D3DUtil.h"
#include "Classes/Peddle.h"
#include "Classes/Wall.h"
#include "Classes/Ball.h"

enum PongInput
{
	RightPeddle_UP = 0,
	RightPeddle_DOWN = 1,
	LeftPeddle_UP = 2,
	LeftPeddle_DOWN = 3,
	LaunchBall = 4,
	FullScreen = 5
};


Week1::Week1(void)
	:BaseScreen(_T("Week1"), _T("Labo Week1: Pong2.5D"), true)
	,m_pCamera(nullptr)
	,m_pBall(nullptr)
	,m_pLeftPeddle(nullptr)
	,m_pRightPeddle(nullptr)
	,m_pWallTop(nullptr)
	,m_pWallBottom(nullptr)
	,m_pWallLeft(nullptr)
	,m_pWallRight(nullptr)
	,m_BallLaunched(false)
{
}


Week1::~Week1(void)
{
}

void Week1::Initialize()
{
	//Create InputActions
	InputAction rightPaddleUp(RightPeddle_UP,Down,VK_UP);
	InputAction rightPaddleDown(RightPeddle_DOWN,Down,VK_DOWN);
	InputAction leftPaddleUp(LeftPeddle_UP,Down,'W');
	InputAction leftPaddleDown(LeftPeddle_DOWN,Down,'S');
	InputAction launchBall(LaunchBall,Down,VK_SPACE);
	InputAction fullScreen(FullScreen,Pressed,'F');

	/*m_pInputManager->AddInputAction(rightPaddleUp);
	m_pInputManager->AddInputAction(rightPaddleDown);
	m_pInputManager->AddInputAction(leftPaddleUp);
	m_pInputManager->AddInputAction(leftPaddleDown);
	m_pInputManager->AddInputAction(launchBall);
	m_pInputManager->AddInputAction(fullScreen);
	m_pInputManager->AddInputAction(InputAction(-1, Pressed, 'N'));
	m_pInputManager->AddInputAction(InputAction(-2, Pressed, 'P'));*/

	// if inputmanager=>IsActionTriggered(id)

	//Create Camera (Orthographic)
	m_pCamera = new GameObject();
	AddSceneObject(m_pCamera);
	auto cameraComponent = new CameraComponent();
	m_pCamera->AddComponent(cameraComponent);
	cameraComponent->UseOrthographicProjection();
	cameraComponent->SetOrthoSize(-1);
	cameraComponent->SetFieldOfView((float)D3DX_PI/4.0f);
	
	cameraComponent->SetActive();
	// OR => // SetActiveCamera(cameraComponent);

	m_pCamera->GetComponent<TransformComponent>()->Translate(0,100,0);
	m_pCamera->GetComponent<TransformComponent>()->Rotate(90,0,0);

	//Add Pong objects
	//Create Ball
	m_pBall = new Ball(40.0f);
	AddSceneObject(m_pBall);
	//Left Peddle
	m_pLeftPeddle  = new Peddle(40,40,160);
	AddSceneObject(m_pLeftPeddle);
	m_pLeftPeddle->GetComponent<TransformComponent>()->Translate(-600,0,0);
	//Right Peddle
	m_pRightPeddle  = new Peddle(40,40,160);
	AddSceneObject(m_pRightPeddle);
	m_pRightPeddle->GetComponent<TransformComponent>()->Translate(600,0,0);
	//Top Wall
	m_pWallTop = new Wall(1280,40,20);
	m_pWallTop->GetComponent<TransformComponent>()->Translate(0,0,360);
	AddSceneObject(m_pWallTop);
	//Bottom Wall
	m_pWallBottom = new Wall(1280,40,20);
	m_pWallBottom->GetComponent<TransformComponent>()->Translate(0,0,-360);
	AddSceneObject(m_pWallBottom);
	//Left Wall
	m_pWallLeft = new Wall(20,40,690, true);
	m_pWallLeft->GetComponent<TransformComponent>()->Translate(-640,0,0);
	AddSceneObject(m_pWallLeft);
	//Right Wall
	m_pWallRight = new Wall(20,40,690, true);
	m_pWallRight->GetComponent<TransformComponent>()->Translate(640,0,0);
	AddSceneObject(m_pWallRight);

	BaseScreen::Initialize();
}

void Week1::Update(const GameContext& context)
{
	//handle special stuff
	if(context.Input->IsActionTriggered(-1))
	{
		ScreenManager::GetInstance()->RemoveActiveScreen(_T("Week1"));
		ScreenManager::GetInstance()->AddActiveScreen(_T("Week2"));
		ScreenManager::GetInstance()->SetControlScreen(_T("Week2"));
	}
	else if(context.Input->IsActionTriggered(-2))
	{
		ScreenManager::GetInstance()->RemoveActiveScreen(_T("Week1"));
		ScreenManager::GetInstance()->AddActiveScreen(_T("Week6"));
		ScreenManager::GetInstance()->SetControlScreen(_T("Week6"));
	}

	//Handle Peddle Interaction
	if(context.Input->IsActionTriggered(FullScreen))
		GraphicsDevice::GetInstance()->ToggleFullScreen();

	auto leftPeddlePos = m_pLeftPeddle->GetComponent<TransformComponent>()->GetWorldPosition();

	if(context.Input->IsActionTriggered(LeftPeddle_UP))
		leftPeddlePos.z += PEDDLE_SPEED*context.GameTime.ElapsedSeconds();
	if(context.Input->IsActionTriggered(LeftPeddle_DOWN))
		leftPeddlePos.z -= PEDDLE_SPEED*context.GameTime.ElapsedSeconds();

	leftPeddlePos.z = Clamp<float>(leftPeddlePos.z, -270.0f, 270.0f);
	m_pLeftPeddle->GetComponent<TransformComponent>()->Translate(leftPeddlePos);

	leftPeddlePos.z = Clamp<float>(leftPeddlePos.z, -270.0f, 270.0f);
	m_pLeftPeddle->GetComponent<TransformComponent>()->Translate(leftPeddlePos);

	auto rightPeddlePos = m_pRightPeddle->GetComponent<TransformComponent>()->GetWorldPosition();
	if(context.Input->IsActionTriggered(RightPeddle_UP))
		rightPeddlePos.z += PEDDLE_SPEED*context.GameTime.ElapsedSeconds();
	if(context.Input->IsActionTriggered(RightPeddle_DOWN))
		rightPeddlePos.z -= PEDDLE_SPEED*context.GameTime.ElapsedSeconds();

	rightPeddlePos.z = Clamp<float>(rightPeddlePos.z, -270.0f, 270.0f);
	m_pRightPeddle->GetComponent<TransformComponent>()->Translate(rightPeddlePos);

	if(!m_BallLaunched && context.Input->IsActionTriggered(LaunchBall))
	{
		m_BallLaunched = true;
		//m_pBall->GetComponent<RigidBodyComponent>()->AddForce(NxVec3(3000.0f,0,3000.0f));
		m_pBall->GetComponent<RigidBodyComponent>()->AddForce(NxVec3(0.7f,0,0.3f)*500,NxForceMode::NX_IMPULSE);
	}

	if(m_pWallLeft->IsTriggered() || m_pWallRight->IsTriggered())
	{
		m_pRightPeddle->GetComponent<TransformComponent>()->Translate(600,0,0);
		m_pLeftPeddle->GetComponent<TransformComponent>()->Translate(-600,0,0);

		m_pWallLeft->Reset();
		m_pWallLeft->Reset();
	
		m_pBall->GetComponent<TransformComponent>()->Translate(0,0,0);
		m_pBall->GetComponent<RigidBodyComponent>()->PutToSleep();

		m_BallLaunched = false;
	}

	BaseScreen::Update(context);
}

void Week1::Draw(const GameContext& context)
{
	GraphicsDevice::GetInstance()->Clear(D3DXCOLOR(0.6f,0.81f,0.92f,1.0f));

	BaseScreen::Draw(context);
}

void Week1::CheckColissionBall(Wall * wall)
{
	SphereColliderComponent * bCollider = m_pBall->GetComponent<SphereColliderComponent>();
	D3DXVECTOR3 vecBall = m_pBall->GetComponent<TransformComponent>()->GetWorldPosition();
	BoxColliderComponent * wCollider = wall->GetComponent<BoxColliderComponent>();
	D3DXVECTOR3 vecWall = wall->GetComponent<TransformComponent>()->GetWorldPosition();
	D3DXVECTOR3 vec(0,0,0.5f);
	if((vecBall.x < vecWall.x || vecBall.x > vecWall.x) && wall->IsTriggered())
	{
		
	}
}
