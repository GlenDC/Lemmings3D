//====================== #INCLUDES ===================================
#include "GameEntity.h"
#include "../Materials/FlatColorMaterial.h"
#include "../Materials/FlatTextureMaterial.h"
#include "../Materials/SpikeyMaterial.h"
#include "../GameScenes/BaseScreen.h"
#include "../Lib/GlobalParameters.h"
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
	,m_CameraHeight(GlobalParameters::GetParameters()->GetParameter<float>(_T("GRID_SIZE")) * 1.5f)
	,m_MaterialAndModelCreated(false)
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
	,m_CameraHeight(GlobalParameters::GetParameters()->GetParameter<float>(_T("GRID_SIZE")) * 1.5f)
	,m_MaterialAndModelCreated(false)
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
	,m_CameraHeight(GlobalParameters::GetParameters()->GetParameter<float>(_T("GRID_SIZE")) * 1.5f)
	,m_MaterialAndModelCreated(false)
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
	,m_CameraHeight(GlobalParameters::GetParameters()->GetParameter<float>(_T("GRID_SIZE")) * 1.5f)
	,m_MaterialAndModelCreated(false)
{
}

GameEntity::~GameEntity() //Default Destructor
{
	SafeDelete(m_pVisualMaterial);
}

void GameEntity::Initialize()
{
	CreateModelAndMaterial();

	GameObject::Initialize();
}

void GameEntity::CreateModelAndMaterial()
{
	if(m_MaterialAndModelCreated == false)
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

		m_MaterialAndModelCreated = true;
	}
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

D3DXVECTOR3 GameEntity::GetCameraTargetPosition() const
{
	D3DXVECTOR3 pos = GetTranslation();
	pos.y += GetCameraHeight();
	return pos;
}