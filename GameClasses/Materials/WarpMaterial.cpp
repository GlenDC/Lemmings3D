//========================== INCLUDES =======================================
#include "WarpMaterial.h"
//---------------------------------------------------------------------------
#include "Graphics/GraphicsDevice.h"
#include "Components/ModelComponent.h"
#include "Managers/ContentManager.h"
//===========================================================================

WarpMaterial::WarpMaterial():
	Material(_T("./Resources/Lemmings3D/shaders/WarpShader.fx")),
	m_pMaskResourceView(nullptr),
	m_pColorMaskResourceView(nullptr),
	m_Color(1,1,1),
	m_Time(0),
	m_pMaskMapVariabele(nullptr),
	m_pColorMaskMapVariabele(nullptr),
	m_pColorVariable(nullptr),
	m_pTimeVariable(nullptr)
{
}


WarpMaterial::~WarpMaterial(void)
{
}

void WarpMaterial::LoadEffectVariables()
{
	m_pColorVariable = m_pEffect->GetVariableByName("m_PortalColor")->AsVector();
	m_pColorMaskMapVariabele = m_pEffect->GetVariableByName("m_ColorMask")->AsShaderResource();
	m_pMaskMapVariabele = m_pEffect->GetVariableByName("m_Mask")->AsShaderResource();
	m_pTimeVariable = m_pEffect->GetVariableByName("m_Time")->AsScalar();
}

void WarpMaterial::UpdateEffectVariables(ModelComponent* modelComponent)
{
	m_pColorVariable->SetFloatVector(m_Color);
	m_pColorMaskMapVariabele->SetResource(m_pColorMaskResourceView);
	m_pMaskMapVariabele->SetResource(m_pMaskResourceView);
	m_pTimeVariable->SetFloat(m_Time);
}

void WarpMaterial::SetMask(const tstring & path)
{
	m_pMaskResourceView = ContentManager::Load<ID3D10ShaderResourceView>(path); 
}

void WarpMaterial::SetColorMask(const tstring & path)
{
	m_pColorMaskResourceView = ContentManager::Load<ID3D10ShaderResourceView>(path); 
}

void WarpMaterial::SetColor(const D3DXVECTOR3 & color)
{
	m_Color = color;
}
void WarpMaterial::SetTime(float time)
{
	m_Time = time;
}