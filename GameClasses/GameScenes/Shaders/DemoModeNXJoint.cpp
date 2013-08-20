//=========================== INCLUDES =================================
#include "DemoModeNXJoint.h"
//----------------------------------------------------------------------
#include "OverlordComponents.h"
#include "Scenegraph/GameScene.h"
#include "../../GameObjects/ColissionEntity.h"
#include "../../Managers/ScreenManager.h"
#include "../../GameObjects/FlyCube.h"
//======================================================================

DemoModeNXJoint::DemoModeNXJoint(GameScene * scene)
	: DemoModeBase(scene, _T("NX Joint Test Zones"), _T("Testing out the different implementations of NXJoints."))
	, m_pActorA(nullptr)
	, m_pActorB(nullptr)
	, m_pActorC(nullptr)
	, m_pActorD(nullptr)
	, m_pActorE(nullptr)
	, m_Ammo(0)
{
	
}

DemoModeNXJoint::~DemoModeNXJoint(void)
{
}

void DemoModeNXJoint::Initialize()
{
	DemoModeBase::Initialize();
	m_pCamera->Enable();
}

void DemoModeNXJoint::Update(const GameContext& context)
{
	DemoModeBase::Update(context);
	if(context.Input->IsActionTriggered((int)InputControls::MOUSE_RIGHT_PRESSED))
	{
		ShootCube();
	}
}

void DemoModeNXJoint::Draw(const GameContext& context)
{

}

void DemoModeNXJoint::Draw2D(const GameContext& context)
{
	DemoModeBase::Draw2D(context);
}

void DemoModeNXJoint::Activate()
{
	// ======== BUGS:
	//	++ Start Position is wrong!!! 

	// =============== PART A ( Revolute Joint )

	D3DXVECTOR3 pos(0,0,-35);

	m_pActorA= new ColissionEntity();
	m_pScene->AddSceneObject(m_pActorA);
	m_pActorA->DisableGravity();
	m_pActorA->Translate(pos);

	m_pActorB = new ColissionEntity();
	m_pScene->AddSceneObject(m_pActorB);
	m_pActorB->DisableGravity();
	pos.x += 8;
	m_pActorB->Translate(pos);

	auto revolute_joint = new RevoluteJointComponent();
	revolute_joint->AttachActor(m_pActorB);
	revolute_joint->SetupMotor(1000, 8.0f);
	pos.x -= 4.0f;
	m_pActorA->AddComponent(revolute_joint);
	revolute_joint->SetAnchor(NxVec3(pos.x, pos.y, pos.z));

	//=========================== PART B (Spherical Joint)

	m_pActorC = new ColissionEntity();
	m_pScene->AddSceneObject(m_pActorC);
	m_pActorC->DisableGravity();
	m_pActorC->Translate(5,5,5);

	auto sphere_joint = new SphericalJointComponent();
	m_pActorC->AddComponent(sphere_joint);
	sphere_joint->SetAnchor(NxVec3(5,5,5));

	//============================ PART C (Pully Joint)

	m_pActorD = new ColissionEntity();
	m_pScene->AddSceneObject(m_pActorD);
	m_pActorD->DisableGravity();
	m_pActorD->Translate(0,-25,30);

	m_pActorE = new ColissionEntity();
	m_pScene->AddSceneObject(m_pActorE);
	m_pActorE->DisableGravity();
	m_pActorE->Translate(10,-25,30);

	auto pully_joint = new PullyJointComponent();
	pully_joint->SetDistance(20.0f);
	pully_joint->SetPullyA(NxVec3(0,-20,30));
	pully_joint->SetPullyB(NxVec3(10,-20,30));
	m_pActorD->AddComponent(pully_joint);
	pully_joint->SetAnchor(NxVec3(5,-20,30));

	//======================== Activate other stuff...

	DemoModeBase::Activate();
}

void DemoModeNXJoint::Deactivate()
{
	m_pScene->RemoveSceneObject(m_pActorA);
	m_pScene->RemoveSceneObject(m_pActorB);
	m_pScene->RemoveSceneObject(m_pActorC);
	m_pScene->RemoveSceneObject(m_pActorD);
	m_pScene->RemoveSceneObject(m_pActorE);

	for(UINT i = 0 ; i < m_Ammo.size() ;++i )
	{
		m_pScene->RemoveSceneObject(m_Ammo[i]);
	}
	m_Ammo.clear();

	DemoModeBase::Deactivate();
}

void DemoModeNXJoint::ShootCube()
{
	auto cube = new FlyCube();
	m_pScene->AddSceneObject(cube);
	cube->ShootCube(m_pCamera->GetTranslation(), m_pCamera->GetTransform()->GetForward());
	m_Ammo.push_back(cube);
}