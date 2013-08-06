//====================== #INCLUDES ===================================
#include "InstancedBlockMaterial.h"
#include "Managers/ContentManager.h"
//====================================================================

InstancedBlockMaterial::InstancedBlockMaterial()
	: Material(_T("./Resources/Lemmings3D/shaders/InstancedObjectShader.fx"))
	, m_pTextureView(nullptr)
	, m_pShaderTexture(nullptr)
{
	m_pElementDescVec.push_back(D3D10_INPUT_PER_VERTEX_DATA);
	m_pElementDescVec.push_back(D3D10_INPUT_PER_VERTEX_DATA);
	m_pElementDescVec.push_back(D3D10_INPUT_PER_VERTEX_DATA);
	m_pElementDescVec.push_back(D3D10_INPUT_PER_INSTANCE_DATA);
	m_pElementDescVec.push_back(D3D10_INPUT_PER_INSTANCE_DATA);

	m_InstanceDataStepRateVec.push_back(0);
	m_InstanceDataStepRateVec.push_back(0);
	m_InstanceDataStepRateVec.push_back(0);
	m_InstanceDataStepRateVec.push_back(1);
	m_InstanceDataStepRateVec.push_back(1);

	m_InputSloteVec.push_back(0);
	m_InputSloteVec.push_back(0);
	m_InputSloteVec.push_back(0);
	m_InputSloteVec.push_back(1);
	m_InputSloteVec.push_back(1);
}

InstancedBlockMaterial::~InstancedBlockMaterial(void)
{
}

void InstancedBlockMaterial::SetTexture(const tstring & path)
{
	m_pTextureView = ContentManager::Load<ID3D10ShaderResourceView>(path); 
	m_pShaderTexture->SetResource(m_pTextureView);
}

void InstancedBlockMaterial::LoadEffectVariables()
{
	//load texture (view)
	// ...

	//Get texture shader resource
	m_pShaderTexture = GetEffectShaderResource(_T("Texture"), m_pEffect);
}

void InstancedBlockMaterial::UpdateEffectVariables(ModelComponent* modelComponent)
{
}