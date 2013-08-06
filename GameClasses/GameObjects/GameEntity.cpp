//====================== #INCLUDES ===================================
#include "GameEntity.h"
#include "../Materials/FlatColorMaterial.h"
#include "../Materials/FlatTextureMaterial.h"
#include "../Materials/SpikeyMaterial.h"
#include "../GameScenes/BaseScreen.h"
//--------------------------------------------------------------------
#include "OverlordComponents.h"
//====================================================================

GameEntity::GameEntity(MaterialType material) //Default Constructor
	:GameObject()
	,m_pVisualModel(nullptr)
	,m_pVisualMaterial(nullptr)
	,m_pScreen(nullptr)
	,m_VisualResourcePath(_T("./Resources/Sphere.ovm"))
	,m_MaterialName(material)
{
}

GameEntity::GameEntity(const tstring & visualModelPath, MaterialType material) //Default Constructor
	:GameObject()
	,m_pVisualModel(nullptr)
	,m_pVisualMaterial(nullptr)
	,m_pScreen(nullptr)
	,m_VisualResourcePath(visualModelPath)
	,m_MaterialName(material)
{
}

GameEntity::~GameEntity() //Default Destructor
{
	SafeDelete(m_pVisualMaterial);
}

void GameEntity::Initialize()
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

	m_pVisualModel = new ModelComponent(m_VisualResourcePath);
	m_pVisualModel->SetMaterial(m_pVisualMaterial);
	AddComponent(m_pVisualModel);

	GameObject::Initialize();
}