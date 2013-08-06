//====================== #INCLUDES ===================================
#include "FlatColorMaterial.h"
#include "Graphics/GraphicsDevice.h"
#include "Components/ModelComponent.h"
//====================================================================

FlatColorMaterial::FlatColorMaterial():
	Material((L"./Resources/PosNormCol.fx")),
	m_vecLightDirection(D3DXVECTOR3(-0.5f, -0.5f, 0.5f)),
	m_pLightDirVariable(0),
	m_Color(D3DXCOLOR(1,0,0,1)),
	m_pColorVariable(0)
{
}

FlatColorMaterial::~FlatColorMaterial(void)
{
}

void FlatColorMaterial::LoadEffectVariables()
{
	m_pLightDirVariable = m_pEffect->GetVariableByName("vLightDir")->AsVector();
	m_pColorVariable = m_pEffect->GetVariableByName("color")->AsVector();
}

void FlatColorMaterial::UpdateEffectVariables(ModelComponent* modelComponent)
{
	m_pLightDirVariable->SetFloatVector(m_vecLightDirection);
	m_pColorVariable->SetFloatVector(m_Color);
}