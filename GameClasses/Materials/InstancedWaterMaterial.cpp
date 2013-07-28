#include "InstancedWaterMaterial.h"
#include "Managers/ContentManager.h"

InstancedWaterMaterial::InstancedWaterMaterial()
	: Material(_T("./Resources/Lemmings3D/shaders/InstancedWaterShader.fx"))
	, m_pTextureView(nullptr)
	, m_pShaderTexture(nullptr)
	, m_pWaterLevelVariable(nullptr)
	, m_pWaterAlphaVariable(nullptr)
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

InstancedWaterMaterial::~InstancedWaterMaterial(void)
{
}

void InstancedWaterMaterial::SetTexture(const tstring & path)
{
	m_pTextureView = ContentManager::Load<ID3D10ShaderResourceView>(path); 
}

void InstancedWaterMaterial::SetWaterLevel(float waterLevel)
{
	m_pWaterLevelVariable->SetFloat(waterLevel);
}

void InstancedWaterMaterial::SetWaterAlpha(float waterAlpha)
{
	m_pWaterAlphaVariable->SetFloat(waterAlpha);
}

void InstancedWaterMaterial::LoadEffectVariables()
{
	//load texture (view)
	// ...

	//Get texture shader resource
	m_pShaderTexture = GetEffectShaderResource("Texture", m_pEffect);
	m_pWaterLevelVariable = GetEffectScalar("WaterLevel", m_pEffect);
	m_pWaterAlphaVariable = GetEffectScalar("WaterAlpha", m_pEffect);
}

void InstancedWaterMaterial::UpdateEffectVariables(ModelComponent* modelComponent)
{
	if(m_pTextureView != nullptr)
	{
		m_pShaderTexture->SetResource(m_pTextureView);
	}
}