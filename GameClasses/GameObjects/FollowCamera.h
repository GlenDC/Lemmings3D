#pragma once

//====================== #INCLUDES ===================================
#include "BaseCamera.h"
//====================================================================

//====================== FollowCamera Class =========================
// Description:
//		Camera that follows a target. Free rotation by player!
// Last Modification: August 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

struct GameContext;
class CameraComponent;
class GameEntity;

class FollowCamera : public BaseCamera
{
public:
	FollowCamera();
	~FollowCamera(void);

	void SetTarget(GameEntity * target);
	void SetRotation(const D3DXQUATERNION & rotation);
protected:
	virtual void Initialize();
	virtual void Update(const GameContext& context);

	GameEntity * m_pTarget;
	float m_ZoomOffset;
	const float m_MinZoom, m_MaxZoom;

private:
	// Disabling default copy constructor and default assignment operator.
	FollowCamera(const FollowCamera& yRef);									
	FollowCamera& operator=(const FollowCamera& yRef);
};

