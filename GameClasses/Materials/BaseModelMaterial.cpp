//======================= INCLUDES =====================================
#include "BaseModelMaterial.h"
//-----------------------------------------------------------------------
#include "Graphics/GraphicsDevice.h"
#include "Components/ModelComponent.h"
#include "Managers/ContentManager.h"
//=======================================================================

BaseModelMaterial::BaseModelMaterial():
	Material(_T("./Resources/Lemmings3D/shaders/BaseModelShader.fx")),
	m_vecLightDirection(D3DXVECTOR3(-0.5f, -0.5f, 0.5f)),
	m_pLightDirVariable(0),
	m_Alpha(1.0f),
	m_pDiffuseResourceView(nullptr),
	m_pAlphaVariable(nullptr),
	m_pDiffuseMapVariabele(nullptr)
{
}


BaseModelMaterial::~BaseModelMaterial(void)
{
}

void BaseModelMaterial::LoadEffectVariables()
{
	m_pLightDirVariable = m_pEffect->GetVariableByName("vLightDir")->AsVector();
	m_pAlphaVariable = m_pEffect->GetVariableByName("Alpha")->AsScalar();
	m_pDiffuseMapVariabele = m_pEffect->GetVariableByName("m_Texture")->AsShaderResource();
}

void BaseModelMaterial::UpdateEffectVariables(ModelComponent* modelComponent)
{
	m_pLightDirVariable->SetFloatVector(m_vecLightDirection);
	m_pAlphaVariable->SetFloat(m_Alpha);
	m_pDiffuseMapVariabele->SetResource(m_pDiffuseResourceView);
}

void BaseModelMaterial::SetDiffuse(const tstring & path)
{
	m_pDiffuseResourceView = ContentManager::Load<ID3D10ShaderResourceView>(path); 
}