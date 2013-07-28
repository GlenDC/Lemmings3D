#pragma once
//====================== #INCLUDES ===================================
#include "Scenegraph/GameObject.h"
//====================================================================

//====================== GameEntity Class =============================
// Description:
//		Visual entity used as the base class for all visual objects
//		in the game or editor.
// Last Modification: 04/03/2013
// Copyright Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class Material;
class ModelComponent;
class BaseScreen;

enum MaterialType
{
	MatFlatColor,
	MatFlatTexture,
	MatSpikey
};

class GameEntity : public GameObject
{
public:
	GameEntity(MaterialType material = MaterialType::MatFlatColor);
	GameEntity(tstring visualModelPath, MaterialType material = MaterialType::MatFlatColor);
	virtual ~GameEntity();

	virtual void Initialize();

protected:
	ModelComponent* m_pVisualModel;
	Material *m_pVisualMaterial;

	BaseScreen *m_pScreen;
	tstring m_VisualResourcePath;
	MaterialType m_MaterialName;

private:
	// Disabling default copy constructor and default assignment operator.
	GameEntity(const GameEntity& yRef);									
	GameEntity& operator=(const GameEntity& yRef);

private:
	friend class BaseScreen;
};