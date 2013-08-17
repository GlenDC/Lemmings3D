#pragma once

//====================== #INCLUDES ===================================
#include "BaseCamera.h"
//====================================================================

//====================== ThirdPersonCamera Class =========================
// Description:
//		ThirdPerson Cmaera. Player can zoom in and out
// Last Modification: August 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

struct GameContext;
class CameraComponent;
class GameEntity;

class ThirdPersonCamera : public BaseCamera
{
public:
	ThirdPersonCamera();
	~ThirdPersonCamera(void);

	void SetTarget(GameEntity * target);
protected:
	virtual void Initialize();
	virtual void Update(const GameContext& context);

	GameEntity * m_pTarget;
	float m_ZoomOffset;
	const float m_MinZoom, m_MaxZoom;

private:
	// Disabling default copy constructor and default assignment operator.
	ThirdPersonCamera(const ThirdPersonCamera& yRef);									
	ThirdPersonCamera& operator=(const ThirdPersonCamera& yRef);
};

