//================================ INCLUDES =========================
#include "PortalEnter.h"
#include "OverlordComponents.h"
#include "../Managers/ParameterManager.h"
#include "../Entities/ParameterClass.h"
#include "../XML/XMLConverter.h"
#include "../Materials/BaseModelMaterial.h"
#include "../Lib/GlobalParameters.h"
#include "../GameObjects/ColissionEntity.h"
#include "../Managers/Stopwatch.h"
#include "../Managers/LemmingManager.h"
//===================================================================

PortalEnter::PortalEnter()
	: GameEntity (
	MaterialType::MatCustom)
	, m_CanSpawn(true)
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

PortalEnter::~PortalEnter()
{

}

void PortalEnter::Initialize()
{
	GameEntity::Initialize();
	LemmingManager::GetInstance()->Initialize();
	LemmingManager::GetInstance()->SetGameScene(GetTransform()->GetGameScene());
}

void PortalEnter::Update(const GameContext & context)
{
	GameEntity::Update(context);

	if(m_CanSpawn)
	{
		m_CanSpawn = false;
		float spawn_delay = GlobalParameters::GetParameters()->GetParameter<float>(_T("AI_SPAWN_DELAY"));
		LemmingManager::GetInstance()->CreateLemming(GetTranslation());
		Stopwatch::GetInstance()->CreateTimer(_T("ai_spawner"), spawn_delay, true, false, [&] ()
		{
			m_CanSpawn = true;
		});
	}

	LemmingManager::GetInstance()->Update(const_cast<GameContext&>(context));
}