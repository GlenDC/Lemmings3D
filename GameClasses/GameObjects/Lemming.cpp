//================================ INCLUDES =========================
#include "Lemming.h"
#include "OverlordComponents.h"
#include "../Managers/ParameterManager.h"
#include "../Entities/ParameterClass.h"
#include "../XML/XMLConverter.h"
#include "../Materials/UberShaderMaterial.h"
#include "../Lib/GlobalParameters.h"
//===================================================================

Lemming::Lemming(const tstring & diff_texture)
	: ColissionEntity (
	MaterialType::MatCustom)
{
	m_VisualResourcePath = _T("./Resources/Lemmings3D/models/LemmingsCharacter.ovm");
	tstring specular_path = _T("lemmings_s.png");
	tstring normal_path = _T("lemmings_n.png");
	tstring env_path = _T("grassenvmap1024.dds");

	UberShaderMaterial * pMaterial = new UberShaderMaterial();
	pMaterial->SetDiffuseTexture(diff_texture);
	pMaterial->SetSpecularTexture(specular_path);
	pMaterial->SetNormalTexture(normal_path);
	pMaterial->SetEnvironmentTexture(env_path);
	pMaterial->EnableHalfLambert(true);
	m_pVisualMaterial = pMaterial;	

	tstring collission_path = _T("./Resources/Lemmings3D/models/LemmingsCharacter_ConvexMesh.ovp");

	AddMeshCollider(collission_path, true, false);

	m_Name = _T("Player");
}

Lemming::~Lemming()
{

}

void Lemming::Initialize()
{
	ColissionEntity::Initialize();
	SetIsStatic(true);
}

void Lemming::Update(const GameContext & context)
{
	ColissionEntity::Update(context);
}