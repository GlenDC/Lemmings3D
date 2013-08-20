//============================ INCLUDES ==========================================
#include "SkyBoxMaterial.h"
//--------------------------------------------------------------------------------
#include "Graphics/GraphicsDevice.h"
#include "Components/ModelComponent.h"
#include "Managers/ContentManager.h"
#include "../Lib/LemmingsHelpers.h"
//--------------------------------------------------------------------------------


SkyBoxMaterial::SkyBoxMaterial():
	Material(_T("./Resources/Lemmings3D/shaders/SkyBox.fx")),
	m_pCubemapResourceView(nullptr),
	m_PreviewPosition(),
	m_WorldMatrix(),
	m_pCubeMapVariabele(nullptr)
{
}


SkyBoxMaterial::~SkyBoxMaterial(void)
{
}

void SkyBoxMaterial::LoadEffectVariables()
{
	m_pCubeMapVariabele = m_pEffect->GetVariableByName("m_CubeMap")->AsShaderResource();
}

void SkyBoxMaterial::UpdateEffectVariables(ModelComponent* modelComponent)
{
	m_pCubeMapVariabele->SetResource(m_pCubemapResourceView);
}

void SkyBoxMaterial::SetCubeMap(const tstring & path)
{
	tstringstream strstr;
	strstr << _T("./Resources/Lemmings3D/textures/") << path;
	m_pCubemapResourceView = ContentManager::Load<ID3D10ShaderResourceView>(strstr.str()); 
}

void SkyBoxMaterial::Update(const GameContext & context)
{
	SetEffectVariables(context, m_WorldMatrix);
}

void SkyBoxMaterial::SetPosition(const D3DXVECTOR3 & pos)
{ 
	m_PreviewPosition = pos;
	m_WorldMatrix = LemmingsHelpers::MatrixScale(500,500,500) * LemmingsHelpers::MatrixTranslation(pos);
}