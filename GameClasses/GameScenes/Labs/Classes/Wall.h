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
#include "Helpers/D3DUtil.h"
#include "Scenegraph/GameObject.h"

class BoxColliderComponent;
class RigidBodyComponent;
class PhysicsMaterial;
enum TriggerAction;

class Wall: public GameObject
{
public:
	Wall(float width, float height, float depth, bool isTrigger = false);
	~Wall(void);

	virtual void Initialize();
	void OnTrigger(RigidBodyComponent* triggerobject, RigidBodyComponent* otherobject, TriggerAction action);

	bool IsTriggered() const { return m_WasTriggered; }
	void Reset(){ m_WasTriggered = false; }

private:

	D3DXVECTOR3 m_Dimensions;
	bool m_IsTrigger;
	bool m_WasTriggered;

	BoxColliderComponent* m_pBoxCollider;
	RigidBodyComponent* m_pRigidBody;
};

void Triggered(RigidBodyComponent * pA,RigidBodyComponent * pB,TriggerAction action);