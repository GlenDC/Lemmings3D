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
//===================================================================

PortalExit::PortalExit()
	: ColissionEntity (
	MaterialType::MatCustom)
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
			Logger::Log(_T("Lemming reached portal!!"), LogLevel::Warning);
		}
	});
	m_pRigidBody->SetStatic(true);
}