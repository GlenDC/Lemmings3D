#pragma once

//====================== #INCLUDES ===================================
#include "Helpers/stdafx.h"
#include "Scenegraph/GameObject.h"
#include "Helpers/d3dutil.h"
//====================================================================

//====================== BaseCamera Class =========================
// Description:
//		Camera for the LevelEditor 
// Last Modification: August 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

struct GameContext;
class CameraComponent;

class BaseCamera : public GameObject
{
public:
	BaseCamera(void);
	~BaseCamera(void);

	void IncreaseSpeed();
	void DecreaseSpeed();
	void IncreaseRotSpeed();
	void DecreaseRotSpeed();

	void ResetTransformation();

	int GetMoveSpeed() const { return (int)m_MoveSpeed; }
	const float & GetRotSpeed() const { return m_RotationSpeed; }

	void AllowCameraControls(const bool allow) { m_CanMove = allow; }

	const float & GetYaw() const { return m_TotalYaw; }
	const float & GetPitch() const { return m_TotalPitch; }

	void SetInformation(const D3DXVECTOR3 & pos, const float yaw, const float pitch, const float speed, const float rotSpeed);

protected:

	virtual void Initialize();
	virtual void Update(const GameContext& context);

	float m_TotalPitch, m_TotalYaw;
	float m_MoveSpeed, m_RotationSpeed;
	CameraComponent *m_pCamera;
	bool m_CanMove;

private:

	// Disabling default copy constructor and default assignment operator.
	BaseCamera(const BaseCamera& yRef);									
	BaseCamera& operator=(const BaseCamera& yRef);
};

