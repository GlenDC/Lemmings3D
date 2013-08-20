//================================ INCLUDES =========================
#include "PortalExit.h"
#include "OverlordComponents.h"
#include "../Managers/ParameterManager.h"
#include "../Entities/ParameterClass.h"
#include "../XML/XMLConverter.h"
#include "../Materials/BaseModelMaterial.h"
#include "../Lib/GlobalParameters.h"
#include "../GameObjects/ColissionEntity.h"
#include "../GameObjects/Lemming.h"
#include "../../../OverlordEngine/Diagnostics/Logger.h"
#include "../GameScenes/GameScreen.h"
#include "LemmingAI.h"
#include "../Managers/LemmingManager.h"
#include "../Materials/UberShaderMaterial.h"
#include "../Materials/WarpMaterial.h"
//===================================================================

PortalExit::PortalExit()
	: ColissionEntity (
	MaterialType::MatCustom)
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

	m_pWarpMaterial = new WarpMaterial();
	m_pWarpMaterial->SetColor(D3DXVECTOR3(1,0,0));

	/*m_pWarp = new GameEntity(_T("plane_warp.ovm"), m_pWarpMaterial);
	AddChild(m_pWarp);
	m_pWarp->Translate(0,5,-4);*/

	strstr.str(_T(""));
	strstr << _T("./Resources/Lemmings3D/models/") << container.GetChildParameter<tstring>(name, _T("CONVEX"));
	tstring collission_path = strstr.str();

	AddMeshCollider(collission_path, true, false, true);

	m_Name = _T("Portal");
}

PortalExit::~PortalExit()
{

}

void PortalExit::Initialize()
{
	ColissionEntity::Initialize();
}

void PortalExit::InitializeRigidBody()
{
	ColissionEntity::InitializeRigidBody();
	m_pRigidBody->SetOnTriggerCallBack([this](RigidBodyComponent* trigger, RigidBodyComponent* receiver, TriggerAction action)
	{
		if(action == TriggerAction::ENTER)
		{
			auto ai = dynamic_cast<LemmingAI*>(receiver->GetParentObject());
			if(ai != nullptr)
			{
				dynamic_cast<GameScreen*>(m_pScene)->SaveLemming();
				LemmingManager::GetInstance()->DeleteLemming(ai);
			}
		}
	});
	m_pRigidBody->SetStatic(true);
}

void PortalExit::Update(const GameContext & context)
{
	ColissionEntity::Update(context);

	m_pWarpMaterial->SetTime(context.GameTime.TotalSpeedGameTime);
}