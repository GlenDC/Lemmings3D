//====================== #INCLUDES ===================================
#include "ThirdPersonCamera.h"
//--------------------------------------------------------------------
#include "OverlordComponents.h"
#include "../GameScenes/GameScreen.h"
#include "../Entities/Level.h"
#include "../GameObjects/GameEntity.h"
#include "../Lib/GlobalParameters.h"
//--------------------------------------------------------------------
#include "Helpers/GeneralStructs.h"
#include "../Lib/LemmingsHelpers.h"
//====================================================================

ThirdPersonCamera::ThirdPersonCamera()
	: BaseCamera()
	, m_pTarget(nullptr)
	, m_ZoomOffset(0)
	, m_MinZoom(GlobalParameters::GetParameters()->GetParameter<float>(_T("GRID_SIZE")) * 2.5f)
	, m_MaxZoom(GlobalParameters::GetParameters()->GetParameter<float>(_T("GRID_SIZE")) * 5.0f)
{
}


ThirdPersonCamera::~ThirdPersonCamera(void)
{
}

void ThirdPersonCamera::SetTarget(GameEntity * target)
{
	m_pTarget = target;
}

void ThirdPersonCamera::Initialize()
{
	BaseCamera::Initialize();
}

void ThirdPersonCamera::Update(const GameContext& context)
{
	if(m_pCamera->IsActive() && m_pTarget)
	{
		D3DXVECTOR3 pos = m_pTarget->GetCameraTargetPosition();

		float offsetTranslation(0);
		if(context.Input->IsMouseButtonDown(VK_MBUTTON)
			&& context.Input->GetMouseMovement().y != 0)
		{
			offsetTranslation = context.Input->GetMouseMovement().y > 0 ? 1.0f : -1.0f;
		}

		m_ZoomOffset += offsetTranslation * context.GameTime.ElapsedSeconds() * GetMoveSpeed();
		m_ZoomOffset = max(m_MinZoom, min(m_ZoomOffset, m_MaxZoom));
		//CALCULATE TRANSFORMS
		auto transform = GetComponent<TransformComponent>();

		if(m_CanMove)
		{
			pos -= m_ZoomOffset * GetTransform()->GetForward();
			transform->Translate(pos);
		}
	}

	BaseCamera::Update(context);
}