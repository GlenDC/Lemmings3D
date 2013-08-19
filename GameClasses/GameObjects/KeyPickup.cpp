//================================ INCLUDES =========================
#include "KeyPickup.h"
#include "OverlordComponents.h"
#include "../Managers/ParameterManager.h"
#include "../Entities/ParameterClass.h"
#include "../XML/XMLConverter.h"
#include "../Materials/BaseModelMaterial.h"
#include "../Lib/GlobalParameters.h"
#include "../GameObjects/ColissionEntity.h"
//===================================================================

KeyPickup::KeyPickup()
	: GameEntity (
	MaterialType::MatCustom)
	, m_pOwner(nullptr)
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
}

KeyPickup::~KeyPickup()
{

}

void KeyPickup::Initialize()
{
	GameEntity::Initialize();
}

void KeyPickup::Update(const GameContext & context)
{
	GameEntity::Update(context);

	float size = GlobalParameters::GetParameters()->GetParameter<float>(_T("GRID_SIZE"));


	D3DXVECTOR3 pos = m_OriginalPosition;
	if(m_pOwner != nullptr)
	{
		pos = m_pOwner->GetCameraTargetPosition();
		pos.y -= size / 4;
		m_Rotation += context.GameTime.ElapsedSeconds() * 50;
		Rotate(0,m_Rotation,0);
	}
	else if(pos.y == 0)
	{
		m_OriginalPosition = GetTransform()->GetWorldPosition();
		pos = m_OriginalPosition;
	}

	m_Height += m_Direction * context.GameTime.ElapsedSeconds() * 2.0f;
	if(abs(m_Height) > size / 8.0f)
	{
		m_Height = m_Direction * size / 8.0f;
		m_Direction *= -1;
	}

	pos.y += m_Height;
	Translate(pos);
}