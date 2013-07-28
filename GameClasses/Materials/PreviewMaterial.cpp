#include "PreviewMaterial.h"
#include "Managers/ContentManager.h"

PreviewMaterial::PreviewMaterial()
	: Material(_T("./Resources/Lemmings3D/shaders/PreviewObjectShader.fx"))
	, m_pTextureView(nullptr)
	, m_pShaderTexture(nullptr)
	, m_PreviewPosition(0,0,0)
{
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
	m_pShaderTexture = GetEffectShaderResource("Texture", m_pEffect);
	m_pPositionVariable = GetEffectVector("PreviewPosition", m_pEffect);
}

void PreviewMaterial::UpdateEffectVariables(ModelComponent* modelComponent)
{
	if(m_pTextureView != nullptr)
	{
		m_pShaderTexture->SetResource(m_pTextureView);
	}
	m_pPositionVariable->SetFloatVector(m_PreviewPosition);
}