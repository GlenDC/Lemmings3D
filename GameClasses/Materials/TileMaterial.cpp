//============================ INCLUDES ==========================================
#include "TileMaterial.h"
//--------------------------------------------------------------------------------
#include "Graphics/GraphicsDevice.h"
#include "Components/ModelComponent.h"
#include "Managers/ContentManager.h"
//--------------------------------------------------------------------------------


TileMaterial::TileMaterial(const D3DXVECTOR2 & uv_tile, const D3DXVECTOR2 & uv_scale):
	Material(_T("./Resources/Lemmings3D/shaders/TileTex.fx")),
	m_UVTile(uv_tile),
	m_UVScale(uv_scale),
	m_pDiffuseResourceView(nullptr),
	m_pUVTileVariable(nullptr),
	m_pUVScaleVariable(nullptr),
	m_pDiffuseMapVariabele(nullptr)
{
}


TileMaterial::~TileMaterial(void)
{
}

void TileMaterial::LoadEffectVariables()
{
	m_pUVTileVariable = m_pEffect->GetVariableByName("UVTile")->AsVector();
	m_pUVScaleVariable = m_pEffect->GetVariableByName("UVScale")->AsVector();
	m_pDiffuseMapVariabele = m_pEffect->GetVariableByName("m_Texture")->AsShaderResource();
}

void TileMaterial::UpdateEffectVariables(ModelComponent* modelComponent)
{
	m_pUVTileVariable->SetFloatVector(m_UVTile);
	m_pUVScaleVariable->SetFloatVector(m_UVScale);
	m_pDiffuseMapVariabele->SetResource(m_pDiffuseResourceView);
}

void TileMaterial::SetDiffuse(const tstring & path)
{
	tstringstream strstr;
	strstr << _T("./Resources/Lemmings3D/textures/") << path;
	m_pDiffuseResourceView = ContentManager::Load<ID3D10ShaderResourceView>(strstr.str()); 
}