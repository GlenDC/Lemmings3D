//======================================= INCLUDES =====================================
#include "Decal.h"
//--------------------------------------------------------------------------------------
#include "../Managers/ParameterManager.h"
#include "../XML/XMLConverter.h"
#include "../Entities/ParameterClass.h"
#include "../Materials/TileMaterial.h"
//======================================================================================

Decal::Decal(UINT id)
	: GameEntity(MaterialType::MatCustom)
{
	auto & container = ParameterManager::GetInstance()->CreateOrGet(_T("Models"));
	UINT real_id(max(3u,id));
	tstring name = XMLConverter::ConvertToTString(real_id + 2);

	tstringstream strstr;
	strstr << _T("./Resources/Lemmings3D/models/") << container.GetChildParameter<tstring>(name, _T("MODEL"));
	m_VisualResourcePath = strstr.str();
	strstr.str(_T(""));
	strstr << container.GetChildParameter<tstring>(name, _T("TEXTURE"));
	tstring texture_path = strstr.str();

	TileMaterial * pMaterial = new TileMaterial(
		D3DXVECTOR2((float)(real_id % 2), (float)(real_id / 2)),
		D3DXVECTOR2(0.5f, 0.5f)
		);
	pMaterial->SetDiffuse(texture_path);
	m_pVisualMaterial = pMaterial;	
}

Decal::~Decal()
{

}