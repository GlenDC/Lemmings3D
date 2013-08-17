//====================== #INCLUDES ===================================
#include "GameCamera.h"
//--------------------------------------------------------------------
#include "OverlordComponents.h"
#include "../GameScenes/GameScreen.h"
#include "../Entities/Level.h"
//--------------------------------------------------------------------
#include "Helpers/GeneralStructs.h"
//====================================================================

GameCamera::GameCamera(GameScreen * screen)
	: BaseCamera()
	, m_pGame(screen)
	, m_ZoomOffset(0)
	, m_CameraPosition(0,0,0)
{
}


GameCamera::~GameCamera(void)
{
}

void GameCamera::Initialize()
{
	D3DXVECTOR3 pos = m_pGame->GetLevel()->GetCenter();
	pos.y = m_pGame->GetLevel()->GetMaxDepth();
	GetComponent<TransformComponent>()->Translate(pos);
	m_CameraPosition = pos;
	BaseCamera::Initialize();
}

void GameCamera::Update(const GameContext& context)
{
	if(m_pCamera->IsActive())
	{
		D3DXVECTOR3 pos = m_CameraPosition;
		D3DXVECTOR3 center = m_pGame->GetLevel()->GetCenter();
		pos.x = center.x;
		pos.z = center.z;
		//HANDLE INPUT
		float moveY(0);
		moveY = context.Input->IsKeyboardKeyDown('W')?1.0f:0.0f;
		if(moveY == 0) moveY = -(context.Input->IsKeyboardKeyDown('S')?1.0f:0.0f);
		if(moveY == 0) moveY = context.Input->GetThumbstickPosition().y;

		float offsetTranslation(0);
		if(context.Input->IsKeyboardKeyDown('A'))
		{
			offsetTranslation = -1.0f;
		}
		else if(context.Input->IsKeyboardKeyDown('D'))
		{
			offsetTranslation = 1.0f;
		}

		m_ZoomOffset += offsetTranslation * context.GameTime.ElapsedSeconds() * GetMoveSpeed();
		float min_check(m_pGame->GetLevel()->GetMaxDepth() / 2.0f);
		if(m_ZoomOffset < 0)
		{
			m_ZoomOffset = 0;
		}
		if(m_ZoomOffset > min_check)
		{
			m_ZoomOffset = min_check;
		}

		pos.y += moveY * m_MoveSpeed * context.GameTime.ElapsedSeconds();
		if(pos.y < min_check)
		{
			pos.y = min_check;
		}

		m_CameraPosition = pos;

		D3DXVECTOR2 look = D3DXVECTOR2(0,0);
		if(context.Input->IsMouseButtonDown(VK_LBUTTON))
		{
			auto mouseMove = context.Input->GetMouseMovement();
			look = D3DXVECTOR2(static_cast<float>(mouseMove.x),static_cast<float>(mouseMove.y));
		}
		if(look.x == 0 && look.y == 0)
		{
			look = context.Input->GetThumbstickPosition(false);
			look.y *= -1;
		}

		//CALCULATE TRANSFORMS
		auto transform = GetComponent<TransformComponent>();

		m_TotalYaw += look.x * m_RotationSpeed * context.GameTime.ElapsedSeconds();
		m_TotalPitch += look.y * m_RotationSpeed * context.GameTime.ElapsedSeconds();

		D3DXMATRIX yawRotationMat, pitchRotationMat, finalRotMat;
		D3DXVECTOR3 transformedRight;
		D3DXMatrixRotationAxis(&yawRotationMat, &D3DXVECTOR3(0,1,0), m_TotalYaw);
		D3DXVec3TransformCoord(&transformedRight,&D3DXVECTOR3(1,0,0),&yawRotationMat);
		D3DXMatrixRotationAxis(&pitchRotationMat, &transformedRight, m_TotalPitch);
		finalRotMat = yawRotationMat * pitchRotationMat;

		D3DXQUATERNION finalQuat;
		D3DXQuaternionRotationMatrix(&finalQuat, &finalRotMat);

		if(m_CanMove)
		{
			transform->Rotate(finalQuat);
			pos += m_ZoomOffset * transform->GetForward();
			transform->Translate(pos);
		}
	}

	BaseCamera::Update(context);
}