//================================ INCLUDES =========================
#include "Lemming.h"
#include "OverlordComponents.h"
#include "../Managers/ParameterManager.h"
#include "../Entities/ParameterClass.h"
#include "../XML/XMLConverter.h"
#include "../Materials/UberShaderMaterial.h"
#include "../Lib/GlobalParameters.h"
#include "Managers/PhysicsManager.h"
#include "KeyObject.h"
#include "KeyPickup.h"
#include "../../../OverlordEngine/Diagnostics/Logger.h"
//===================================================================

Lemming::Lemming(const tstring & diff_texture)
	: GameEntity ( MaterialType::MatCustom)
	, m_pKey(nullptr)
	, m_pOriginalKey(nullptr)
	, m_pController(nullptr)
	, m_Velocity(0,0,0)
	, m_MoveSpeed(0)
	, m_RotationSpeed(static_cast<float>(D3DX_PI/2))
	, m_Width(4)
	, m_Height(5)
	, m_RunVelocity(0)
	, m_MaxRunVelocity(50.0f)
	, m_TerminalVelocity(60.0f)
	, m_Gravity(9.81f)
	, m_RunAccelerationTime(0.3f)
	, m_JumpAccelerationTime(0.3f)
	, m_RunAcceleration(m_MaxRunVelocity/m_RunAccelerationTime)
	, m_JumpVelocity(0)
	, m_Actions()
{
	m_VisualResourcePath = _T("./Resources/Lemmings3D/models/LemmingsCharacter.ovm");
	tstring specular_path = _T("lemmings_s.png");
	tstring normal_path = _T("lemmings_n.png");
	tstring env_path = _T("grassenvmap1024.dds");

	UberShaderMaterial * pMaterial = new UberShaderMaterial();
	pMaterial->SetDiffuseTexture(diff_texture);
	pMaterial->SetSpecularTexture(specular_path);
	pMaterial->SetNormalTexture(normal_path);
	pMaterial->SetEnvironmentTexture(env_path);
	pMaterial->EnableHalfLambert(true);
	m_pVisualMaterial = pMaterial;	

	m_pController = new ControllerComponent(m_Width, m_Height);
	AddComponent(m_pController);

	m_Name = _T("Lemming");

	m_Actions[Forward] = false;
	m_Actions[Backward] = false;
	m_Actions[Left] = false;
	m_Actions[Right] = false;
	m_Actions[Jump] = false;
}

Lemming::~Lemming()
{
}

void Lemming::Initialize()
{
	GameEntity::Initialize();
}

void Lemming::Update(const GameContext & context)
{;
	//...bone update!
	UpdatePhysics(context);

	m_Actions[Forward] = false;
	m_Actions[Backward] = false;
	m_Actions[Left] = false;
	m_Actions[Right] = false;
	m_Actions[Jump] = false;

	GameEntity::Update(context);
}

void Lemming::GiveKey(KeyObject * pKey)
{
	m_pKey = new KeyPickup();
	m_pScene->AddSceneObject(m_pKey);
	m_pOriginalKey = pKey;
	m_pKey->SetOwner(this);
}

bool Lemming::HasContact(const D3DXVECTOR3 & position)
{
	NxVec3 start(position.x, position.y, position.z);
    NxVec3 direction(0,-1,0);
    NxRay ray(start,direction);

	NxShape* shape = PhysicsManager::GetInstance()->GetClosestShape(GetGameScene()->GetPhysicsScene()
		,ray,NxShapesType::NX_STATIC_SHAPES, m_Height);

    return shape != NULL;
}

void Lemming::UpdatePhysics(const GameContext & context)
{
	//Handle Input
	auto diff = D3DXVECTOR2(0,0);
	auto input = context.Input;

	diff.y += m_Actions[Forward]?1.0f:0.0f;
	diff.y += m_Actions[Backward]?-1.0f:0.0f;

	diff.x += m_Actions[Right]?1.0f:0.0f;
	diff.x += m_Actions[Left]?-1.0f:0.0f;

	auto transform = GetComponent<TransformComponent>();
	auto currPos = m_pController->GetTranslation();

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

	bool has_contact(HasContact(currPos));
	//gravity / jump
	if(!has_contact)
	{
		Logger::Log(_T("falling...."), LogLevel::Info);
		m_JumpVelocity -= m_JumpAcceleration * context.GameTime.ElapsedSeconds();
		if(m_JumpVelocity < -m_TerminalVelocity) m_JumpVelocity = -m_TerminalVelocity;
	}
	else if(m_Actions[Jump])
	{
		Logger::Log(_T("jumping...."), LogLevel::Info);
		m_JumpVelocity = 5;
	}
	else
	{
		Logger::Log(_T("chilling...."), LogLevel::Info);
		m_Velocity.y = 0;
		m_JumpVelocity = 0;
	}

	m_Velocity.y += m_JumpVelocity;

	m_pController->Move(m_Velocity * context.GameTime.ElapsedSeconds());
}