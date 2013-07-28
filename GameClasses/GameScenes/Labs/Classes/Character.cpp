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

#include "Character.h"
#include "OverlordComponents.h"
#include "Managers/PhysicsManager.h"
#include "Helpers/GeneralStructs.h"
#include "Scenegraph/GameScene.h"

Character::Character(float width, float height, float moveSpeed, int forwardKeyCode, 
				int backwardKeyCode, int leftKeyCode, int rightKeyCode, 
				int rotationMouseButtonCode, int jumpKeyCode)
				:m_pCamera(nullptr)
				,m_pController(nullptr)
				,m_TotalPitch(0)
				,m_TotalYaw(0)
				,m_MoveSpeed(moveSpeed)
				,m_RotationSpeed(static_cast<float>(D3DX_PI/2))
				,m_Width(width)
				,m_Height(height)
				//,m_PreviousPosition(0,0,0)
				,m_ForwardKeyCode(forwardKeyCode)
				,m_BackwardKeyCode(backwardKeyCode)
				,m_LeftKeyCode(leftKeyCode)
				,m_RightKeyCode(rightKeyCode)
				,m_RotationMouseButtonCode(rotationMouseButtonCode)
				,m_JumpKeyCode(jumpKeyCode)
				,m_Velocity(0,0,0)
				,m_MaxRunVelocity(50.0f)
				,m_Gravity(9.81f)
				,m_RunAccelerationTime(0.3f)
				,m_JumpAccelerationTime(0.3f)
				,m_RunAcceleration(m_MaxRunVelocity/m_RunAccelerationTime)
				,m_JumpAcceleration(m_Gravity/m_JumpAccelerationTime)
				,m_RunVelocity(0)
				,m_JumpVelocity(0)
				,m_TerminalVelocity(60)
{
}

Character::~Character(void)
{
}

void Character::Initialize()
{
	//Add code here
	//m_PreviousPosition = GetComponent<TransformComponent>()->GetWorldPosition();

	m_pController = new ControllerComponent();
	AddComponent(m_pController);

	m_pCamera = new CameraComponent();
	AddComponent(m_pCamera);
	m_pCamera->SetActive();

	GameObject::Initialize();
}

// In the Update, we need to calculate the delta position and new rotation.
// We will use the new rotation to rotate our transformcomponent.
// We will use the delta position to move our controller.
// Use the FreeCamera (Engine – Prefabs) as a guide to write this code.
void Character::Update(const GameContext& context)
{
	if(m_pCamera->IsActive())
	{
		//Handle Input
		auto diff = D3DXVECTOR2(0,0);
		auto input = context.Input;

		diff.y += input->IsKeyboardKeyDown(m_ForwardKeyCode)?1.0f:0.0f;
		diff.y += input->IsKeyboardKeyDown(m_BackwardKeyCode)?-1.0f:0.0f;
		if(diff.y == 0) 
			diff.y = input->GetThumbstickPosition().y;

		diff.x += input->IsKeyboardKeyDown(m_RightKeyCode)?1.0f:0.0f;
		diff.x += input->IsKeyboardKeyDown(m_LeftKeyCode)?-1.0f:0.0f;
		if(diff.x == 0) 
			diff.x = input->GetThumbstickPosition().x;

		auto look = D3DXVECTOR2(0,0);
		if(input->IsMouseButtonDown(m_RotationMouseButtonCode))
		{
			auto mouseMove = input->GetMouseMovement();
			look = D3DXVECTOR2(static_cast<float>(mouseMove.x),
				static_cast<float>(mouseMove.y));
		}
		if(look.x == 0 && look.y == 0)
		{
			look = input->GetThumbstickPosition(false)*3.0f;
			look.y *= -1;
		}

		auto transform = GetComponent<TransformComponent>();
		auto currPos = m_pController->GetTranslation();

		//Camera Rotation
		m_TotalYaw += look.x * m_RotationSpeed * context.GameTime.ElapsedSeconds();
		m_TotalPitch += look.y * m_RotationSpeed * context.GameTime.ElapsedSeconds();

		D3DXMATRIX yawRotationMatrix, pitchRotationMatrix, finalRotMat;
		D3DXVECTOR3 transformedRight;

		D3DXMatrixRotationAxis(&yawRotationMatrix, &D3DXVECTOR3(0,1,0), m_TotalYaw);
		D3DXVec3TransformCoord(&transformedRight, &D3DXVECTOR3(1,0,0), &yawRotationMatrix);
		D3DXMatrixRotationAxis(&pitchRotationMatrix, &transformedRight, m_TotalPitch);

		finalRotMat = yawRotationMatrix * pitchRotationMatrix;

		D3DXQUATERNION finalQuat;
		D3DXQuaternionRotationMatrix(&finalQuat, &finalRotMat);
		
		transform->Rotate(finalQuat);

		//translation
		D3DXVECTOR3 currDirection = (transform->GetForward() * diff.y) +
									(transform->GetRight() * diff.x);
		D3DXVec3Normalize(&currDirection, &currDirection);

		if(diff.x != 0 || diff.y != 0)
		{
			m_RunVelocity += m_RunAcceleration * context.GameTime.ElapsedSeconds();
			if(m_RunVelocity > m_MaxRunVelocity) m_RunVelocity = m_MaxRunVelocity;

			m_Velocity += currDirection * m_RunVelocity * context.GameTime.ElapsedSeconds();
		}
		else
		{
			m_Velocity.x = 0;
			m_Velocity.z = 0;
		}

		//gravity / jump
		if(!HasContact(currPos))
		{
			m_JumpVelocity -= m_JumpAcceleration * context.GameTime.ElapsedSeconds();
			if(m_JumpVelocity < -m_TerminalVelocity) m_JumpVelocity = -m_TerminalVelocity;
		}
		else if(input->IsKeyboardKeyDown(m_JumpKeyCode))
		{
			m_JumpVelocity = 0;
			m_Velocity.y = 80;
		}
		else
		{
			m_Velocity.y = 0;
		}

		m_Velocity.y += m_JumpVelocity;

		m_pController->Move(m_Velocity * context.GameTime.ElapsedSeconds());
	}

	GameObject::Update(context);

	////old Code....

	/*D3DXVECTOR2 move = D3DXVECTOR2(0,0);
	D3DXVECTOR2 look = D3DXVECTOR2(0,0);

	move.y = context.Input->IsKeyboardKeyDown(m_ForwardKeyCode)?1.0f:0.0f;
	if(move.y == 0) move.y = -(context.Input->IsKeyboardKeyDown(m_BackwardKeyCode)?1.0f:0.0f);
	if(move.y == 0) move.y = context.Input->GetThumbstickPosition().y;

	move.x = context.Input->IsKeyboardKeyDown(m_RightKeyCode)?1.0f:0.0f;
	if(move.x == 0) move.x = -(context.Input->IsKeyboardKeyDown(m_LeftKeyCode)?1.0f:0.0f);
	if(move.x == 0) move.x = context.Input->GetThumbstickPosition().x;

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
	////CALCULATE TRANSFORMS
	auto transform = GetComponent<TransformComponent>();
	auto currPos = transform->GetWorldPosition();

	//currPos += transform->GetForward() * move.y * m_MoveSpeed*context.GameTime.ElapsedSeconds();
	//currPos += transform->GetRight() * move.x * m_MoveSpeed*context.GameTime.ElapsedSeconds();

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

	//transform->Rotate(finalQuat);
	//Gravity
	D3DXVECTOR3 vecRight(transform->GetRight());
	vecRight.y = 0;
	D3DXVECTOR3 vecFoward(transform->GetForward());
	vecFoward.y = 0;

	m_pController->Move(D3DXVECTOR3(0, CalculateGravity(currPos,(float)context.GameTime.ElapsedSeconds()),0)
		+vecFoward * move.y * m_MoveSpeed * context.GameTime.ElapsedSeconds()
							+vecRight * move.x * m_MoveSpeed * context.GameTime.ElapsedSeconds());
	//GetComponent<TransformComponent>()->Translate(m_pController->GetTranslation());
	m_pCamera->GetTransform()->Rotate(m_pController->GetTransform()->GetWorldRotation());
	transform->Rotate(finalQuat);

	GameObject::Update(context);*/
}

// In the CalculateGravity method, we will calculate the delta movement along the y axis.
// We will only do this if our delta is bigger than 0.001f AND if we currently do not have contact with the level. 
// The delta y is calculated as follows
//		Delta = (CurrentPos – PreviousPos).y / deltatime + -9.82 * deltatime
//		If delta < 0 => deltaY = delta * deltatime.
//float Character::CalculateGravity(D3DXVECTOR3 currentPosition, float deltaTime)
//{
//	/*if(HasContact(currentPosition))
//		return 0;*/
//	float delta =  -9.82f * deltaTime * 10;
//	m_PreviousPosition = currentPosition;
//	/*if(delta < 0)
//		delta = delta * deltaTime;*/
//	return delta;
//}

//Character::HasContact(D3DXVECTOR3 position) Description:
// In the HasContact method, we will check if the player is currently having contact with a static object. 
// We will use the GetClosestShape method provided by the physics manager. 
// You’ll need to create a ray that starts at the position of the controller and points directly downwards. 
// The distance of the raycast needs to be equal to the height of the controller.
bool Character::HasContact(D3DXVECTOR3 position)
{    
	NxVec3 start(position.x, position.y, position.z);
    NxVec3 direction(0,-1,0);
    NxRay ray(start,direction);

	NxShape* shape = PhysicsManager::GetInstance()->GetClosestShape(GetGameScene()->GetPhysicsScene()
		,ray,NxShapesType::NX_STATIC_SHAPES, m_Height);

    return shape != NULL;
}

void Character::AddToInventory(int itemID)
{
	m_Inventory.push_back(HashItem(itemID));
}

wstring Character::HashItem(int hashID)
{
	switch(hashID)
	{
	case 1:
		return L"Key";
	}
	return L"";
}

bool Character::HasItem(int itemID)
{
	wstring value = HashItem(itemID);
	for(wstring str : m_Inventory)
	{
		if(str == value)
			return true;
	}
	return false;
}