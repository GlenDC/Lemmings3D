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
		if(context.Input->IsKeyboardKeyDown('A'))
		{
			offsetTranslation = -1.0f;
		}
		else if(context.Input->IsKeyboardKeyDown('D'))
		{
			offsetTranslation = 1.0f;
		}
		if(context.Input->IsMouseButtonDown(VK_MBUTTON) && offsetTranslation == 0
			&& context.Input->GetMouseMovement().y != 0)
		{
			offsetTranslation = context.Input->GetMouseMovement().y > 0 ? 1.0f : -1.0f;
		}

		m_ZoomOffset += offsetTranslation * context.GameTime.ElapsedSeconds() * GetMoveSpeed();
		m_ZoomOffset = max(m_MinZoom, min(m_ZoomOffset, m_MaxZoom));
		//CALCULATE TRANSFORMS
		auto transform = GetComponent<TransformComponent>();

		if(context.Input->IsMouseButtonDown(VK_RBUTTON))
		{
			D3DXVECTOR2 look = D3DXVECTOR2(0,0);
			if(context.Input->IsMouseButtonDown(VK_RBUTTON))
			{
				auto mouseMove = context.Input->GetMouseMovement();
				look = D3DXVECTOR2(static_cast<float>(mouseMove.x),static_cast<float>(mouseMove.y));
			}
			m_TotalYaw += look.x * m_RotationSpeed * context.GameTime.ElapsedSeconds();
			m_TotalPitch += look.y * m_RotationSpeed * context.GameTime.ElapsedSeconds();
		}
		D3DXMATRIX yawRotationMat, pitchRotationMat, finalRotMat;
		D3DXVECTOR3 transformedRight;
		D3DXMatrixRotationAxis(&yawRotationMat, &D3DXVECTOR3(0,1,0), m_TotalYaw + LemmingsHelpers::GetYaw(m_pTarget->GetRotation()));
		D3DXVec3TransformCoord(&transformedRight,&D3DXVECTOR3(1,0,0),&yawRotationMat);
		D3DXMatrixRotationAxis(&pitchRotationMat, &transformedRight, m_TotalPitch);
		finalRotMat = yawRotationMat * pitchRotationMat;

		D3DXQUATERNION finalQuat;
		D3DXQuaternionRotationMatrix(&finalQuat, &finalRotMat);

		if(m_CanMove)
		{
			transform->Rotate(finalQuat);
			pos -= m_ZoomOffset * GetTransform()->GetForward();
			transform->Translate(pos);
		}
	}

	BaseCamera::Update(context);
}