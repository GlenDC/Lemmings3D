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

#include "FlatTextureMaterial.h"
#include "Graphics/GraphicsDevice.h"
#include "Components/ModelComponent.h"
#include "Managers/ContentManager.h"


FlatTextureMaterial::FlatTextureMaterial():
	Material(_T("./Resources/PosNormTex.fx")),
	m_vecLightDirection(D3DXVECTOR3(-0.5f, -0.5f, 0.5f)),
	m_pLightDirVariable(0),
	m_pDiffuseResourceView(nullptr),
	m_pDiffuseMapVariabele(nullptr)
{
}


FlatTextureMaterial::~FlatTextureMaterial(void)
{
}

void FlatTextureMaterial::LoadEffectVariables()
{
	m_pLightDirVariable = m_pEffect->GetVariableByName("vLightDir")->AsVector();
	m_pDiffuseMapVariabele = m_pEffect->GetVariableByName("m_Texture")->AsShaderResource();
}

void FlatTextureMaterial::UpdateEffectVariables(ModelComponent* modelComponent)
{
	m_pLightDirVariable->SetFloatVector(m_vecLightDirection);
	m_pDiffuseMapVariabele->SetResource(m_pDiffuseResourceView);
}

void FlatTextureMaterial::SetDiffuse(const tstring & path)
{
	m_pDiffuseResourceView = ContentManager::Load<ID3D10ShaderResourceView>(path); 
}