//====================== #INCLUDES ===================================
#include "SkinnedMaterial.h"
#include "Graphics/GraphicsDevice.h"
#include "Components/ModelComponent.h"
#include "Managers/ContentManager.h"
//====================================================================

SkinnedMaterial::SkinnedMaterial():
	Material(_T("./Resources/SkinnedEffect.fx")),
	m_vecLightDirection(D3DXVECTOR3(-0.5f, -0.5f, 0.5f)),
	m_pLightDirVariable(0),
	m_pDiffuseResourceView(nullptr),
	m_pDiffuseMapVariabele(nullptr),
	m_pBoneTransformationsVariable(nullptr)
{
}

SkinnedMaterial::~SkinnedMaterial(void)
{
}

void SkinnedMaterial::LoadEffectVariables()
{
	m_pLightDirVariable = m_pEffect->GetVariableByName("vLightDir")->AsVector();
	m_pDiffuseMapVariabele = m_pEffect->GetVariableByName("m_Texture")->AsShaderResource();
	m_pBoneTransformationsVariable = m_pEffect->GetVariableByName("matBones");
}

void SkinnedMaterial::UpdateEffectVariables(ModelComponent* modelComponent)
{
	m_pLightDirVariable->SetFloatVector(m_vecLightDirection);
	m_pDiffuseMapVariabele->SetResource(m_pDiffuseResourceView);
	if(m_BoneTransformations.size() > 0)
	{
		m_pBoneTransformationsVariable->SetRawValue(m_BoneTransformations[0], 0, 
			m_BoneTransformations.size() * sizeof(D3DXMATRIX));
	}
}

void SkinnedMaterial::SetDiffuse(const tstring & path)
{
	m_pDiffuseResourceView = ContentManager::Load<ID3D10ShaderResourceView>(path); 
}

void SkinnedMaterial::SetBoneTransformations(const std::vector<D3DXMATRIX> & boneTransformations)
{
	m_BoneTransformations = boneTransformations;
}