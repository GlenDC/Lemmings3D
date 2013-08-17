//====================== #INCLUDES ===================================
#include "PreviewMaterial.h"
#include "Managers/ContentManager.h"
//====================================================================

PreviewMaterial::PreviewMaterial()
	: Material(_T("./Resources/Lemmings3D/shaders/PreviewObjectShader.fx"))
	, m_pTextureView(nullptr)
	, m_pShaderTexture(nullptr)
	, m_PreviewPosition(0,0,0)
{
	m_pElementDescVec.push_back(D3D10_INPUT_PER_VERTEX_DATA);
	m_pElementDescVec.push_back(D3D10_INPUT_PER_VERTEX_DATA);
	m_pElementDescVec.push_back(D3D10_INPUT_PER_VERTEX_DATA);
	m_InstanceDataStepRateVec.push_back(0);
	m_InstanceDataStepRateVec.push_back(0);
	m_InstanceDataStepRateVec.push_back(0);
	m_InputSloteVec.push_back(0);
	m_InputSloteVec.push_back(0);
	m_InputSloteVec.push_back(0);
}

PreviewMaterial::~PreviewMaterial(void)
{
}

void PreviewMaterial::SetTexture(const tstring & path)
{
	m_pTextureView = ContentManager::Load<ID3D10ShaderResourceView>(path); 
}

void PreviewMaterial::LoadEffectVariables()
{
	//load texture (view)
	// ...

	//Get texture shader resource
	m_pShaderTexture = GetEffectShaderResource(_T("Texture"), m_pEffect);
	m_pPositionVariable = GetEffectVector(_T("PreviewPosition"), m_pEffect);
}

void PreviewMaterial::UpdateEffectVariables(ModelComponent* modelComponent)
{
	if(m_pTextureView != nullptr)
	{
		m_pShaderTexture->SetResource(m_pTextureView);
	}
	m_pPositionVariable->SetFloatVector(m_PreviewPosition);
}