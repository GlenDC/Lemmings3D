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

class FlatColorMaterial;
class ModelComponent;
class BoxColliderComponent;
class RigidBodyComponent;

class Peddle: public GameObject
{
public:
	Peddle(float width, float height, float depth);
	~Peddle(void);

	virtual void Initialize();

private:

	D3DXVECTOR3 m_Dimensions;
	
	ModelComponent* m_pPeddleModelComp;
	BoxColliderComponent* m_pBoxCollider;
	RigidBodyComponent* m_pRigidBody;
	FlatColorMaterial * m_pPeddleMaterial;

};

