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

class FlatColorMaterial;
class ModelComponent;
class SphereColliderComponent;
class RigidBodyComponent;
class PhysicsMaterial;

class Ball:public GameObject
{
public:
	Ball(float size);
	~Ball(void);

	virtual void Initialize();

private:
	float m_Size;

	ModelComponent* m_pBallModelComp;
	SphereColliderComponent* m_pSphereCollider;
	RigidBodyComponent* m_pRigidBody;
	FlatColorMaterial *m_pBallMaterial;
	PhysicsMaterial * m_pPhysicsMaterial;
};

