//====================== #INCLUDES ===================================
#include "GameEntity.h"
#include "../Materials/FlatColorMaterial.h"
#include "../Materials/FlatTextureMaterial.h"
#include "../Materials/SpikeyMaterial.h"
#include "../GameScenes/BaseScreen.h"
//--------------------------------------------------------------------
#include "OverlordComponents.h"
//====================================================================

GameEntity::GameEntity(Material * material)
	:GameObject()
	,m_pVisualModel(nullptr)
	,m_pVisualMaterial(material)
	,m_pScreen(nullptr)
	,m_VisualResourcePath(_T("./Resources/Sphere.ovm"))
	,m_MaterialName(MaterialType::MatCustom)
	,m_IsVisible(true)
{

}

GameEntity::GameEntity(MaterialType material)
	:GameObject()
	,m_pVisualModel(nullptr)
	,m_pVisualMaterial(nullptr)
	,m_pScreen(nullptr)
	,m_VisualResourcePath(_T("./Resources/Sphere.ovm"))
	,m_MaterialName(material)
	,m_IsVisible(true)
{
}

GameEntity::GameEntity(const tstring & visualModelPath, MaterialType material)
	:GameObject()
	,m_pVisualModel(nullptr)
	,m_pVisualMaterial(nullptr)
	,m_pScreen(nullptr)
	,m_VisualResourcePath(visualModelPath)
	,m_MaterialName(material)
	,m_IsVisible(true)
{
}

GameEntity::GameEntity(const tstring & visualModelPath, Material * material) 
	:GameObject()
	,m_pVisualModel(nullptr)
	,m_pVisualMaterial(material)
	,m_pScreen(nullptr)
	,m_VisualResourcePath(visualModelPath)
	,m_MaterialName(MaterialType::MatCustom)
	,m_IsVisible(true)
{
}

GameEntity::~GameEntity() //Default Destructor
{
	SafeDelete(m_pVisualMaterial);
}

void GameEntity::Initialize()
{
	if(m_MaterialName != MaterialType::MatCustom)
	{
		switch(m_MaterialName)
		{
		case MaterialType::MatSpikey:
			m_pVisualMaterial = new SpikeyMaterial();
			break;
		case MaterialType::MatFlatTexture:
			m_pVisualMaterial = new FlatTextureMaterial();
		default:
			m_pVisualMaterial = new FlatColorMaterial();
			break;
		}
	}

	m_pVisualModel = new ModelComponent(m_VisualResourcePath);
	m_pVisualModel->SetMaterial(m_pVisualMaterial);
	AddComponent(m_pVisualModel);

	GameObject::Initialize();
}

void GameEntity::Draw(const GameContext & context)
{
	if(m_IsVisible)
	{
		GameObject::Draw(context);
	}
}

void GameEntity::SetMaterial(Material * material)
{
	m_pVisualMaterial = material;
	if(m_pVisualModel != nullptr)
	{
		m_pVisualModel->SetMaterial(material);
	}
}

TransformComponent * GameEntity::GetTransform() const
{
	return GetComponent<TransformComponent>();
}

void GameEntity::Translate(float x, float y, float z)
{
	auto transform = GetTransform();
	transform->Translate(x, y, z);
}

void GameEntity::Translate(const D3DXVECTOR3 & vector)
{
	auto transform = GetTransform();
	transform->Translate(vector);
}

void GameEntity::Scale(float x, float y, float z)
{
	auto transform = GetTransform();
	transform->Scale(x, y, z);
}

void GameEntity::Scale(const D3DXVECTOR3 & vector)
{
	auto transform = GetTransform();
	transform->Scale(vector);
}

void GameEntity::Rotate(float x, float y, float z)
{
	auto transform = GetTransform();
	transform->Rotate(x, y, z);
}

void GameEntity::Rotate(const D3DXVECTOR3 & vector)
{
	Rotate(vector.x, vector.y, vector.z);
}

void GameEntity::Rotate(const D3DXQUATERNION & rotation)
{
	auto transform = GetTransform();
	transform->Rotate(rotation);
}

const D3DXVECTOR3 & GameEntity::GetTranslation() const
{
	return GetTransform()->GetWorldPosition();
}

const D3DXVECTOR3 & GameEntity::GetScale() const
{
	return GetTransform()->GetWorldScale();
}

const D3DXQUATERNION & GameEntity::GetRotation() const
{
	return GetTransform()->GetWorldRotation();
}
	
const D3DXMATRIX & GameEntity::GetWorldMatrix() const
{
	return GetTransform()->GetWorldMatrix();
}