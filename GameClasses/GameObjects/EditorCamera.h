#pragma once

//====================== #INCLUDES ===================================
#include "Helpers/stdafx.h"
#include "Scenegraph/GameObject.h"
#include "Helpers/d3dutil.h"
//====================================================================

//====================== EditorCamera Class =========================
// Description:
//		Camera for the LevelEditor 
// Last Modification: 29/05/2013
// Copyright Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

struct GameContext;
class CameraComponent;

class EditorCamera : public GameObject
{
public:
	EditorCamera(void);
	~EditorCamera(void);

	void IncreaseSpeed();
	void DecreaseSpeed();
	void IncreaseRotSpeed();
	void DecreaseRotSpeed();

	void ResetTransformation();

	int GetMoveSpeed() const { return (int)m_MoveSpeed; }
	const float & GetRotSpeed() const { return m_RotationSpeed; }

	void AllowCameraControls(bool allow) { m_CanMove = allow; }

	const float & GetYaw() const { return m_TotalYaw; }
	const float & GetPitch() const { return m_TotalPitch; }

	void SetInformation(const D3DXVECTOR3 & pos, float yaw, float pitch, float speed, float rotSpeed);

protected:

	virtual void Initialize();
	virtual void Update(const GameContext& context);

private:
	float m_TotalPitch, m_TotalYaw;
	float m_MoveSpeed, m_RotationSpeed;
	CameraComponent *m_pCamera;

	bool m_CanMove;

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	EditorCamera(const EditorCamera& yRef);									
	EditorCamera& operator=(const EditorCamera& yRef);
};

