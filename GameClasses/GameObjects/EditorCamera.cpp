#include "EditorCamera.h"
#include "OverlordComponents.h"
#include "Helpers/GeneralStructs.h"

EditorCamera::EditorCamera(void)
	: m_MoveSpeed(30)
	, m_RotationSpeed(1.0f)
	, m_TotalPitch(0)
	, m_TotalYaw(0)
	, m_pCamera(nullptr)
	, m_CanMove(true)
{
}


EditorCamera::~EditorCamera(void)
{
}

void EditorCamera::Initialize()
{

	//Camera Component
	m_pCamera = new CameraComponent();
	AddComponent(m_pCamera);

	GameObject::Initialize();

	m_pCamera->SetActive();
}

void EditorCamera::Update(const GameContext& context)
{
	if(m_pCamera->IsActive())
	{
		//HANDLE INPUT
		D3DXVECTOR2 move = D3DXVECTOR2(0,0);
		move.y = context.Input->IsKeyboardKeyDown('W')?1.0f:0.0f;
		if(move.y == 0) move.y = -(context.Input->IsKeyboardKeyDown('S')?1.0f:0.0f);
		if(move.y == 0) move.y = context.Input->GetThumbstickPosition().y;

		move.x = context.Input->IsKeyboardKeyDown('D')?1.0f:0.0f;
		if(move.x == 0) move.x = -(context.Input->IsKeyboardKeyDown('A')?1.0f:0.0f);
		if(move.x == 0) move.x = context.Input->GetThumbstickPosition().x;

		D3DXVECTOR2 look = D3DXVECTOR2(0,0);
		if(context.Input->IsMouseButtonDown(VK_LBUTTON))
		{
			auto mouseMove = context.Input->GetMouseMovement();
			look = D3DXVECTOR2(static_cast<float>(mouseMove.x),static_cast<float>(mouseMove.y));
		}
		if(look.x == 0 && look.y == 0)
		{
			look = context.Input->GetThumbstickPosition(false);
			look.y *= -1;
		}

		//CALCULATE TRANSFORMS
		auto transform = GetComponent<TransformComponent>();
		auto currPos = transform->GetWorldPosition();

		currPos += transform->GetForward() * move.y * m_MoveSpeed*context.GameTime.ElapsedSeconds();
		currPos += transform->GetRight() * move.x * m_MoveSpeed*context.GameTime.ElapsedSeconds();

		m_TotalYaw += look.x * m_RotationSpeed * context.GameTime.ElapsedSeconds();
		m_TotalPitch += look.y * m_RotationSpeed * context.GameTime.ElapsedSeconds();

		D3DXMATRIX yawRotationMat, pitchRotationMat, finalRotMat;
		D3DXVECTOR3 transformedRight;
		D3DXMatrixRotationAxis(&yawRotationMat, &D3DXVECTOR3(0,1,0), m_TotalYaw);
		D3DXVec3TransformCoord(&transformedRight,&D3DXVECTOR3(1,0,0),&yawRotationMat);
		D3DXMatrixRotationAxis(&pitchRotationMat, &transformedRight, m_TotalPitch);
		finalRotMat = yawRotationMat * pitchRotationMat;

		D3DXQUATERNION finalQuat;
		D3DXQuaternionRotationMatrix(&finalQuat, &finalRotMat);

		if(m_CanMove)
		{
			transform->Rotate(finalQuat);
		}
		transform->Translate(currPos);
	}

	GameObject::Update(context);
}

void EditorCamera::IncreaseSpeed()
{
	m_MoveSpeed += 10;
	if(m_MoveSpeed > 400)
		m_MoveSpeed = 400;
}

void EditorCamera::DecreaseSpeed()
{
	m_MoveSpeed -= 10;
	if(m_MoveSpeed < 10)
		m_MoveSpeed = 10;
}

void EditorCamera::IncreaseRotSpeed()
{
	m_RotationSpeed += 0.5f;
	if(m_RotationSpeed > 3.14f)
		m_RotationSpeed = 3.14f;
}

void EditorCamera::DecreaseRotSpeed()
{
	m_RotationSpeed -= 0.5f;
	if(m_RotationSpeed < 0.5f)
		m_RotationSpeed = 0.5f;
}

void EditorCamera::ResetTransformation()
{
	auto transform = GetComponent<TransformComponent>();
	transform->Translate(0,0,0);
	transform->Rotate(0,0,0);
	m_TotalYaw = 0;
	m_TotalPitch = 0;
}

void EditorCamera::SetInformation(const D3DXVECTOR3 & pos, float yaw, float pitch, float speed, float rotSpeed)
{
	auto transform = GetComponent<TransformComponent>();
	transform->Translate(pos.x, pos.y, pos.z);
	m_TotalPitch = pitch;
	m_TotalYaw = yaw;
	m_MoveSpeed = speed;
	m_RotationSpeed = rotSpeed;
}