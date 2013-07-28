//--------------------------------------------------------------------------------------
//   _____     _______ ____  _     ___  ____  ____    _____ _   _  ____ ___ _   _ _____ 
//  / _ \ \   / / ____|  _ \| |   / _ \|  _ \|  _ \  | ____| \ | |/ ___|_ _| \ | | ____|
// | | | \ \ / /|  _| | |_) | |  | | | | |_) | | | | |  _| |  \| | |  _ | ||  \| |  _|  
// | |_| |\ V / | |___|  _ <| |__| |_| |  _ <| |_| | | |___| |\  | |_| || || |\  | |___ 
//  \___/  \_/  |_____|_| \_\_____\___/|_| \_\____/  |_____|_| \_|\____|___|_| \_|_____|
//
// Overlord Engine v0.44
// Copyright Overlord Brecht Kets & Overlord Thomas Goussaert
// http://www.digitalartsandentertainment.com/
//--------------------------------------------------------------------------------------

#include "SpikeyMaterial.h"
#include "Graphics/GraphicsDevice.h"
#include "Components/ModelComponent.h"
#include "Managers/ContentManager.h"

SpikeyMaterial::SpikeyMaterial():
	Material(_T("./Resources/SpikeyShader.fx")),
	m_vecLightDirection(D3DXVECTOR3(-0.5f, -0.5f, 0.5f)),
	m_pLightDirVariable(0),
	m_Color(D3DXCOLOR(1,1,1,1)),
	m_TargetColor(D3DXCOLOR(1,1,1,1)),
	m_pColorVariable(0),
	m_pSpikeHeightVariable(0),
	m_SpikeHeight(5.0f),
	m_TargetSpikeHeight(0),
	m_CurrentTime(0),
	m_pDiffuseResourceView(nullptr),
	m_pDiffuseMapVariabele(nullptr),
	m_pNegativeVariable(nullptr)
{
}


SpikeyMaterial::~SpikeyMaterial(void)
{
}

void SpikeyMaterial::LoadEffectVariables()
{
	m_pLightDirVariable = m_pEffect->GetVariableByName("m_LightDir")->AsVector();
	m_pColorVariable = m_pEffect->GetVariableByName("m_Color")->AsVector();
	m_pSpikeHeightVariable = m_pEffect->GetVariableByName("m_SpikeHeight")->AsScalar();
	m_pNegativeVariable = m_pEffect->GetVariableByName("m_Negative")->AsScalar();
	m_pDiffuseMapVariabele = m_pEffect->GetVariableByName("m_TextureDiffuse")->AsShaderResource();
	m_pDiffuseResourceView = ContentManager::Load<ID3D10ShaderResourceView>(_T("./Resources/Checker.jpg")); 
}

void SpikeyMaterial::UpdateEffectVariables(ModelComponent* modelComponent)
{
	m_pLightDirVariable->SetFloatVector(m_vecLightDirection);
	m_CurrentTime += 0.01f;
	if(m_CurrentTime > 0.5f)
	{
		m_CurrentTime -= 0.5f;
		m_Color = D3DXCOLOR((float)(rand()%90+5)/100.0f,(float)(rand()%90+5)/100.0f,(float)(rand()%90+5)/100.0f,1);
		m_SpikeHeight = (float)(rand()%8+2);
	}
	m_TargetColor -= (m_TargetColor - m_Color) *0.05f;
	m_TargetSpikeHeight -= (m_TargetSpikeHeight - m_SpikeHeight)*0.05f;
	m_Negative = (float)(rand()%1);
	m_pSpikeHeightVariable->SetFloat(m_TargetSpikeHeight);
	m_pColorVariable->SetFloatVector(m_TargetColor);
	m_pDiffuseMapVariabele->SetResource(m_pDiffuseResourceView);
	m_pNegativeVariable->SetFloat(m_Negative);
}
