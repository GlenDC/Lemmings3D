//====================== #INCLUDES ===================================
#include "BaseCamera.h"
//--------------------------------------------------------------------
#include "OverlordComponents.h"
//--------------------------------------------------------------------
#include "Helpers/GeneralStructs.h"
//====================================================================

BaseCamera::BaseCamera(void)
	: m_MoveSpeed(30)
	, m_RotationSpeed(1.0f)
	, m_TotalPitch(0)
	, m_TotalYaw(0)
	, m_pCamera(nullptr)
	, m_CanMove(true)
{
}


BaseCamera::~BaseCamera(void)
{
}

void BaseCamera::Initialize()
{
	//Camera Component
	m_pCamera = new CameraComponent();
	AddComponent(m_pCamera);

	GameObject::Initialize();

	m_pCamera->SetActive();
}

void BaseCamera::Update(const GameContext& context)
{
	GameObject::Update(context);
}

void BaseCamera::IncreaseSpeed()
{
	m_MoveSpeed += 10;
	if(m_MoveSpeed > 400)
		m_MoveSpeed = 400;
}

void BaseCamera::DecreaseSpeed()
{
	m_MoveSpeed -= 10;
	if(m_MoveSpeed < 10)
		m_MoveSpeed = 10;
}

void BaseCamera::IncreaseRotSpeed()
{
	m_RotationSpeed += 0.5f;
	if(m_RotationSpeed > 3.14f)
		m_RotationSpeed = 3.14f;
}

void BaseCamera::DecreaseRotSpeed()
{
	m_RotationSpeed -= 0.5f;
	if(m_RotationSpeed < 0.5f)
		m_RotationSpeed = 0.5f;
}

void BaseCamera::ResetTransformation()
{
	auto transform = GetComponent<TransformComponent>();
	transform->Translate(0,0,0);
	transform->Rotate(0,0,0);
	m_TotalYaw = 0;
	m_TotalPitch = 0;
}

void BaseCamera::SetInformation(const D3DXVECTOR3 & pos, float yaw, float pitch, float speed, float rotSpeed)
{
	auto transform = GetComponent<TransformComponent>();
	transform->Translate(pos.x, pos.y, pos.z);
	m_TotalPitch = pitch;
	m_TotalYaw = yaw;
	m_MoveSpeed = speed;
	m_RotationSpeed = rotSpeed;
}