#pragma once
//====================== #INCLUDES ===================================
#include "ColissionEntity.h"
#include <map>
//====================================================================

//====================== Lemming Class =============================
// Description:
//		Lemming Object, base for both AI and Player
// Last Modification: August 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class ControllerComponent;
class KeyObject;
class KeyPickup;

class Lemming : public GameEntity
{
public:
	explicit Lemming(const tstring & diff_texture);
	virtual ~Lemming();

	virtual void Initialize();
	virtual void Update(const GameContext & context);

	void GiveKey(KeyObject * pKey);

protected:
	enum ControlActions
	{
		Forward = 0,
		Backward,
		Left,
		Right,
		Jump
	};
	KeyPickup  *m_pKey;
	KeyObject *m_pOriginalKey;
	ControllerComponent * m_pController;
	D3DXVECTOR3 m_Velocity;

	float m_MoveSpeed, m_RotationSpeed;
	float m_Width, m_Height;
	float m_MaxRunVelocity, m_TerminalVelocity,
		m_Gravity, m_RunAccelerationTime, 
		m_JumpAccelerationTime, m_RunAcceleration,
		m_JumpAcceleration, m_RunVelocity,
		m_JumpVelocity;

	map<ControlActions, bool> m_Actions;

	bool HasContact(const D3DXVECTOR3 & position);
	void UpdatePhysics(const GameContext & context);

private:
	// Disabling default copy constructor and default assignment operator.
	Lemming(const Lemming& yRef);									
	Lemming& operator=(const Lemming& yRef);
};