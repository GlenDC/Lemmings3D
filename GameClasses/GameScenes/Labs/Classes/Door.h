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

class ModelComponent;
class SphereColliderComponent;
class FlatTextureMaterial;
class Character;

class Door:public GameObject
{
public:
	Door(Character * pCharacter);
	~Door(void);

	virtual void Initialize();
	virtual void Update(const GameContext& context);

private:
	FlatTextureMaterial *m_pVisualMaterial;
	Character *m_pTriggerCharacter;
	ModelComponent *m_Model;

	bool m_Open; 
};

