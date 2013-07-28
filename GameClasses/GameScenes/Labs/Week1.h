//--------------------------------------------------------------------------------------
//   _____     _______ ____  _     ___  ____  ____    _____ _   _  ____ ___ _   _ _____ 
//  / _ \ \   / / ____|  _ \| |   / _ \|  _ \|  _ \  | ____| \ | |/ ___|_ _| \ | | ____|
// | | | \ \ / /|  _| | |_) | |  | | | | |_) | | | | |  _| |  \| | |  _ | ||  \| |  _|  
// | |_| |\ V / | |___|  _ <| |__| |_| |  _ <| |_| | | |___| |\  | |_| || || |\  | |___ 
//  \___/  \_/  |_____|_| \_\_____\___/|_| \_\____/  |_____|_| \_|\____|___|_| \_|_____|
//
// Overlord Engine v0.44
// Copyright Overlord Brecht Kets & Overlord Thomas Goussaert
// http://www.digitalartsandentertainment.com/
//--------------------------------------------------------------------------------------

#pragma once
#include "../BaseScreen.h"

class Peddle;
class Wall;
class Ball;

class Week1: public BaseScreen
{
public:
	Week1(void);
	virtual ~Week1(void);

	virtual void Initialize();
	virtual void Update(const GameContext& context);
	virtual void Draw(const GameContext& context);

private:
	GameObject * m_pCamera;
	Ball * m_pBall;
	Peddle *m_pLeftPeddle, *m_pRightPeddle;
	Wall *m_pWallTop, *m_pWallBottom, *m_pWallLeft, *m_pWallRight;

	bool m_BallLaunched;

	static const int PEDDLE_SPEED = 350;

	void CheckColissionBall(Wall * wall);
};

