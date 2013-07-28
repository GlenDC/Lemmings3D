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
#include "Scenegraph/GameObject.h"
#include "Helpers/stdafx.h"
#include "OverlordComponents.h"

#include <vector>

class CameraComponent;
class ControllerComponent;

class Character : public GameObject
{
public:
	//*note*: when change default parameters, you have to rebuild the file.
	//	      visual studios wont recognize the change by itself.
	Character(float width = 2, float height = 14, float moveSpeed = 100, int forwardKeyCode = 'W', 
				int backwardKeyCode = 'S', int leftKeyCode = 'A', int rightKeyCode = 'D', 
				int rotationMouseButtonCode = VK_LBUTTON, int jumpKeyCode = VK_SPACE);
	virtual ~Character(void);
	
	virtual void AddToInventory(int itemID);
	virtual wstring HashItem(int hashID);
	virtual bool HasItem(int itemID);

protected:
	virtual void Initialize();
	virtual void Update(const GameContext& context);
	//virtual float CalculateGravity(D3DXVECTOR3 currentPosition, float deltaTime);
	virtual bool HasContact(D3DXVECTOR3 position);

	CameraComponent *m_pCamera;
	ControllerComponent* m_pController;

	float m_TotalPitch, m_TotalYaw;
	float m_MoveSpeed, m_RotationSpeed;
	float m_Width, m_Height;

	float m_MaxRunVelocity, m_TerminalVelocity,
		  m_Gravity, m_RunAccelerationTime, 
		  m_JumpAccelerationTime, m_RunAcceleration,
		  m_JumpAcceleration, m_RunVelocity,
		  m_JumpVelocity;

	D3DXVECTOR3 m_Velocity;

	vector<wstring> m_Inventory;

	int m_ForwardKeyCode, m_BackwardKeyCode, m_LeftKeyCode, 
		m_RightKeyCode, m_RotationMouseButtonCode, m_JumpKeyCode;

private:
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Character(const Character& t);
	Character& operator=(const Character& t);
};
