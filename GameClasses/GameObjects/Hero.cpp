//============================= INCLUDES ==========================
#include "Hero.h"
#include "Helpers\GeneralStructs.h"
#include "../Lib/GlobalParameters.h"
#include "ThirdPersonCamera.h"
#include "Scenegraph/GameObject.h"
#include "Scenegraph/GameScene.h"
//=================================================================

Hero::Hero()
	: Lemming ( _T("player_d.png"))
	, m_Controlled(false)
	, m_pCamera(nullptr)
{
	float speed(GlobalParameters::GetParameters()->GetParameter<float>(_T("HERO_SPEED")));

	m_Name = _T("Player");
}

 Hero::~Hero()
 {

 }

 void Hero::Initialize()
 {
	 m_pCamera = new ThirdPersonCamera();
	 m_pCamera->SetTarget(this);
	 m_pScene->AddSceneObject(m_pCamera);

	 Lemming::Initialize();
 }

 void Hero::Update(const GameContext & context)
 {
	 if(m_Controlled)
	 {
		 m_Actions[Forward] = context.Input->IsKeyboardKeyDown('W');
		 m_Actions[Backward] = context.Input->IsKeyboardKeyDown('S');
		 m_Actions[Left] = context.Input->IsKeyboardKeyDown('A');
		 m_Actions[Right] = context.Input->IsKeyboardKeyDown('D');
		 m_Actions[Jump] = context.Input->IsKeyboardKeyDown(VK_SPACE);
	 }
	 Lemming::Update(context);
 }
 
 void Hero::UpdateControl(const GameContext & context)
 {
	 Lemming::UpdateControl(context);
 }

 void Hero::SetControlled(bool control_character)
 {
	 m_Controlled = control_character;
	 if(m_Controlled)
	 {
		 m_pCamera->GetComponent<CameraComponent>()->SetActive();
	 }
 }