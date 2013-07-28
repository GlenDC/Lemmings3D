#include "Bone.h" 
#include "../../../Materials/FlatColorMaterial.h"

const float BoneObject::BONE_STRETCH_VALUE = 1.25f;

BoneObject::BoneObject(int boneId, float length)
	:m_BoneId(boneId)
	,m_Length(length)
	,m_pMesh(nullptr)
	,m_pMaterial(nullptr)
	,m_pBone(nullptr)
{

}

BoneObject::~BoneObject(void)
{
	SafeDelete(m_pMaterial);
}

void BoneObject::Initialize()
{
	m_pMaterial = new FlatColorMaterial();

	m_pBone = new GameObject();

	m_pMesh = new ModelComponent(L"./Resources/Bone.ovm");
	m_pMesh->SetMaterial(m_pMaterial);
	m_pBone->AddComponent(m_pMesh);
	AddChild(m_pBone);


	auto transform = m_pBone->GetComponent<TransformComponent>();

	transform->Scale(m_Length,m_Length,m_Length);
	//GetComponent<TransformComponent>()->Translate(0,0,m_Length);

	GameObject::Initialize();
}

void BoneObject::Update(const GameContext& context)
{
	GameObject::Update(context);
}

void BoneObject::AddBone(BoneObject* bone)
{
	AddChild(bone);
	bone->GetComponent<TransformComponent>()->Translate(0,0,m_Length);
}

void BoneObject::CalculateBindPose()
{
	auto childBones = GetChildren<BoneObject>();
	D3DXMatrixInverse(&m_BindPose, NULL, &GetComponent<TransformComponent>()->GetWorldMatrix());
	for(auto childBone:childBones)
		childBone->CalculateBindPose();
}