#pragma once

//====================== #INCLUDES ===================================
#include "BaseCamera.h"
//====================================================================

//====================== GameCamera Class =========================
// Description:
//		Main camera to play the game as a player
// Last Modification: August 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

struct GameContext;
class CameraComponent;
class GameScreen;

class GameCamera : public BaseCamera
{
public:
	explicit GameCamera(GameScreen * screen);
	~GameCamera(void);
protected:
	virtual void Initialize();
	virtual void Update(const GameContext& context);

	GameScreen * m_pGame;
	float m_ZoomOffset;
	D3DXVECTOR3 m_CameraPosition;

private:
	// Disabling default copy constructor and default assignment operator.
	GameCamera(const GameCamera& yRef);									
	GameCamera& operator=(const GameCamera& yRef);
};

