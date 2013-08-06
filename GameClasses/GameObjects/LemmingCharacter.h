#pragma once
//====================== #INCLUDES ===================================
#include "Scenegraph/GameObject.h"
#include "../Interfaces/IColissionUser.h"
//====================================================================
class ControllerComponent;
class SkinnedMaterial;
class ModelComponent;

//====================== LemmingCharacter Class =====================
// Description:
//		Character object (ai)
// Last Modification: 10/06/2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class LemmingCharacter : public GameObject, public IColissionUser
{
public:
	explicit LemmingCharacter(const D3DXVECTOR3 & startPos);
	virtual ~LemmingCharacter();

	virtual void Initialize();
	virtual void Draw(const GameContext & context);
	virtual void Update(const GameContext & context);

    virtual const D3DXVECTOR3 & GetCUPosition() const;
    virtual float GetCURange() const;

	void AddToInventory(const int itemID);
	bool HasItem(const int itemID);

private:
	static const int CURANGE = 20;
	D3DXVECTOR3 m_Position;

	ControllerComponent* m_pController;
	ModelComponent *m_pModelComponent;
	SkinnedMaterial *m_pSkinnedMaterial;

	D3DXVECTOR3 m_Velocity;
	vector<int> m_Inventory;

	float m_TotalPitch, m_TotalYaw;
	float m_MoveSpeed, m_RotationSpeed;
	float m_Width, m_Height;

	float m_MaxRunVelocity, m_TerminalVelocity,
		  m_Gravity, m_RunAccelerationTime, 
		  m_JumpAccelerationTime, m_RunAcceleration,
		  m_JumpAcceleration, m_RunVelocity,
		  m_JumpVelocity;
	
	bool HasContact(const D3DXVECTOR3 & position);
	void UpdatePhysics(const GameContext & context);

	// Disabling default copy constructor and default assignment operator.
	LemmingCharacter(const LemmingCharacter& yRef);									
	LemmingCharacter& operator=(const LemmingCharacter& yRef);
};