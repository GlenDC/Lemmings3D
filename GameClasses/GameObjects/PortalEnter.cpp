//================================ INCLUDES =========================
#include "PortalEnter.h"
#include "OverlordComponents.h"
#include "../Managers/ParameterManager.h"
#include "../Entities/ParameterClass.h"
#include "../XML/XMLConverter.h"
#include "../Lib/GlobalParameters.h"
#include "../GameObjects/ColissionEntity.h"
#include "../Managers/Stopwatch.h"
#include "../Managers/LemmingManager.h"
#include "../Materials/UberShaderMaterial.h"
#include "../Materials/WarpMaterial.h"
//===================================================================

PortalEnter::PortalEnter()
	: GameEntity (
	MaterialType::MatCustom)
	, m_CanSpawn(true)
	, m_pWarp(nullptr)
	, m_pWarpMaterial(nullptr)
{
	auto & container = ParameterManager::GetInstance()->CreateOrGet(_T("Models"));

	tstring name = XMLConverter::ConvertToTString(MODEL_ID);

	tstringstream strstr;
	strstr << _T("./Resources/Lemmings3D/models/") << container.GetChildParameter<tstring>(name, _T("MODEL"));
	m_VisualResourcePath = strstr.str();

	UberShaderMaterial * pMaterial = new UberShaderMaterial();
	pMaterial->SetDiffuseTexture(container.GetChildParameter<tstring>(name, _T("TEXTURE")));
	pMaterial->SetSpecularTexture(container.GetChildParameter<tstring>(name, _T("SPECULAR")));
	pMaterial->SetNormalTexture(container.GetChildParameter<tstring>(name, _T("NORMAL")));
	pMaterial->SetEnvironmentTexture(container.GetChildParameter<tstring>(name, _T("CUBREMAP")));
	pMaterial->EnableHalfLambert(true);
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

	m_pWarpMaterial = new WarpMaterial();
	m_pWarpMaterial->SetColor(D3DXVECTOR3(0,1,0));

	/*m_pWarp = new GameEntity(_T("plane_warp.ovm"), m_pWarpMaterial);
	AddChild(m_pWarp);
	m_pWarp->Translate(0,5,4);*/
}

void PortalEnter::Update(const GameContext & context)
{
	GameEntity::Update(context);

	/*m_pWarpMaterial->SetTime(context.GameTime.TotalSpeedGameTime);

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

	LemmingManager::GetInstance()->Update(const_cast<GameContext&>(context));*/
}