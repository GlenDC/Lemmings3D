//====================== #INCLUDES ===================================
#include "LemmingCharacter.h"
//--------------------------------------------------------------------
#include "OverlordComponents.h"
#include "Managers/PhysicsManager.h"
//--------------------------------------------------------------------
#include "../Materials/SkinnedMaterial.h"
#include "../Managers/ColissionCollector.h"
//====================================================================

LemmingCharacter::LemmingCharacter(const D3DXVECTOR3 & startPos)
	: m_Position(startPos)
	, m_pController(nullptr)
	, m_pModelComponent(nullptr)
	, m_pSkinnedMaterial(nullptr)
	, m_Velocity(0,0,0)
	, m_Inventory(0)
	, m_TotalPitch(0)
	, m_TotalYaw(0)
	, m_MoveSpeed(0)
	, m_RotationSpeed(static_cast<float>(D3DX_PI/2))
	, m_Width(3)
	, m_Height(7)
	, m_MaxRunVelocity(50.0f)
	, m_TerminalVelocity(60.0f)
	, m_Gravity(9.81f)
	, m_RunAccelerationTime(0.3f)
	, m_JumpAccelerationTime(0.3f)
	, m_RunAcceleration(m_MaxRunVelocity/m_RunAccelerationTime)
	, m_JumpVelocity(m_Gravity/m_JumpAccelerationTime)
{
	ColissionCollector::GetInstance()->AddUser(this);
}

LemmingCharacter::~LemmingCharacter()
{
	ColissionCollector::GetInstance()->RemoveUser(this);
	delete m_pSkinnedMaterial;
}

void LemmingCharacter::Initialize()
{
	auto transform = GetComponent<TransformComponent>();
	transform->Translate(m_Position);
	transform->Scale(0.2f, 0.2f, 0.2f);

	m_pController = new ControllerComponent(m_Width, m_Height);
	AddComponent(m_pController);

	m_pSkinnedMaterial = new SkinnedMaterial();
	m_pSkinnedMaterial->SetDiffuse(_T("./Resources/Lemmings3D/models/Vampire_Diffuse.dds"));

	m_pModelComponent = new ModelComponent(_T("./Resources/Lemmings3D/models/HeroTest.ovm"));
	m_pModelComponent->SetMaterial(m_pSkinnedMaterial);

	AddComponent(m_pModelComponent);

	GameObject::Initialize();
}

void LemmingCharacter::Draw(const GameContext & context)
{
	GameObject::Draw(context);
}

void LemmingCharacter::Update(const GameContext & context)
{
	//m_pSkinnedMaterial->SetEffectVariables(context, m_pModelComponent);
	m_pSkinnedMaterial->SetBoneTransformations(m_pModelComponent->GetBoneTransformations());
	UpdatePhysics(context);
	/*auto transform = GetComponent<TransformComponent>();
	D3DXVECTOR3 pos = m_pController->GetTranslation();
	transform->Translate(pos);*/
	GameObject::Update(context);
}

const D3DXVECTOR3 & LemmingCharacter::GetCUPosition() const
{
	return m_Position;
}

float LemmingCharacter::GetCURange() const
{
	return (float)CURANGE;
}

void LemmingCharacter::AddToInventory(const int itemID)
{
	m_Inventory.push_back(itemID);
}

bool LemmingCharacter::HasItem(const int itemID)
{
	for(UINT i = 0 ; i < m_Inventory.size() ; ++i)
	{
		if(m_Inventory[i] == itemID)
		{
			return true;
		}
	}
	return false;
}

bool LemmingCharacter::HasContact(const D3DXVECTOR3 & position)
{
	NxVec3 start(position.x, position.y, position.z);
    NxVec3 direction(0,-1,0);
    NxRay ray(start,direction);

	NxShape* shape = PhysicsManager::GetInstance()->GetClosestShape(GetGameScene()->GetPhysicsScene()
		,ray,NxShapesType::NX_STATIC_SHAPES, m_Height);

    return shape != NULL;
}
void LemmingCharacter::UpdatePhysics(const GameContext & context)
{
	//Handle Input
		/*auto diff = D3DXVECTOR2(0,0);
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
		}*/

		auto transform = GetComponent<TransformComponent>();
		auto currPos = m_pController->GetTranslation();

		//Camera Rotation
	/*	m_TotalYaw += look.x * m_RotationSpeed * context.GameTime.ElapsedSeconds();
		m_TotalPitch += look.y * m_RotationSpeed * context.GameTime.ElapsedSeconds();

		D3DXMATRIX yawRotationMatrix, pitchRotationMatrix, finalRotMat;
		D3DXVECTOR3 transformedRight;

		D3DXMatrixRotationAxis(&yawRotationMatrix, &D3DXVECTOR3(0,1,0), m_TotalYaw);
		D3DXVec3TransformCoord(&transformedRight, &D3DXVECTOR3(1,0,0), &yawRotationMatrix);
		D3DXMatrixRotationAxis(&pitchRotationMatrix, &transformedRight, m_TotalPitch);

		finalRotMat = yawRotationMatrix * pitchRotationMatrix;

		D3DXQUATERNION finalQuat;
		D3DXQuaternionRotationMatrix(&finalQuat, &finalRotMat);
		
		transform->Rotate(finalQuat);*/

		//translation
	/*	D3DXVECTOR3 currDirection = (transform->GetForward() * diff.y) +
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
*/
		//gravity / jump
		if(!HasContact(currPos))
		{
			m_JumpVelocity -= m_JumpAcceleration * context.GameTime.ElapsedSpeedGameTime;
			if(m_JumpVelocity < -m_TerminalVelocity) m_JumpVelocity = -m_TerminalVelocity;
		}
		/*else if(input->IsKeyboardKeyDown(m_JumpKeyCode))
		{
			m_JumpVelocity = 0;
			m_Velocity.y = 80;
		}*/
		else
		{
			m_Velocity.y = 0;
		}

		m_Velocity.y += m_JumpVelocity;

		m_pController->Move(m_Velocity * context.GameTime.ElapsedSpeedGameTime);
}