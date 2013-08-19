//================================ INCLUDES =========================
#include "KeyObject.h"
#include "OverlordComponents.h"
#include "../Managers/ParameterManager.h"
#include "../Entities/ParameterClass.h"
#include "../XML/XMLConverter.h"
#include "../Materials/BaseModelMaterial.h"
#include "../Lib/GlobalParameters.h"
//===================================================================

KeyObject::KeyObject()
	: ColissionEntity (
		MaterialType::MatCustom)
	, m_OriginalPosition(0, 0, 0)
	, m_Height(0)
	, m_Rotation(0)
	, m_Direction(1)
{
	auto & container = ParameterManager::GetInstance()->CreateOrGet(_T("Models"));

	tstring name = XMLConverter::ConvertToTString(MODEL_ID);

	tstringstream strstr;
	strstr << _T("./Resources/Lemmings3D/models/") << container.GetChildParameter<tstring>(name, _T("MODEL"));
	m_VisualResourcePath = strstr.str();
	strstr.str(_T(""));
	strstr << _T("./Resources/Lemmings3D/textures/") << container.GetChildParameter<tstring>(name, _T("TEXTURE"));
	tstring texture_path = strstr.str();

	BaseModelMaterial * pMaterial = new BaseModelMaterial();
	pMaterial->SetDiffuse(texture_path);
	pMaterial->SetAlpha(1.0f);
	m_pVisualMaterial = pMaterial;	

	strstr.str(_T(""));
	strstr << _T("./Resources/Lemmings3D/models/") << container.GetChildParameter<tstring>(name, _T("CONVEX"));
	tstring collission_path = strstr.str();

	AddMeshCollider(collission_path, true, false);

	m_Name = _T("Key");
}

KeyObject::~KeyObject()
{

}

void KeyObject::Initialize()
{

	ColissionEntity::Initialize();
}

void KeyObject::Update(const GameContext & context)
{
	ColissionEntity::Update(context);

	m_Rotation += context.GameTime.ElapsedSeconds() * 50;
	Rotate(0,m_Rotation,0);

	D3DXVECTOR3 pos = m_OriginalPosition;
	if(pos.y == 0)
	{
		m_OriginalPosition = GetTransform()->GetWorldPosition();
		pos = m_OriginalPosition;
	}

	float size = GlobalParameters::GetParameters()->GetParameter<float>(_T("GRID_SIZE"));

	m_Height += m_Direction * context.GameTime.ElapsedSeconds() * 2.0f;
	if(abs(m_Height) > size / 6.0f)
	{
		m_Height = m_Direction * size / 6.0f;
		m_Direction *= -1;
	}

	pos.y += m_Height;
	Translate(pos);
}