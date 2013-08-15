#pragma once

//====================== #INCLUDES ===================================
#include "Scenegraph/GameObject.h"
//====================================================================

//====================== GameEntity Class =============================
// Description:
//		Visual entity used as the base class for all visual objects
//		in the game or editor.
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class Material;
class ModelComponent;
class BaseScreen;

enum MaterialType
{
	MatFlatColor,
	MatFlatTexture,
	MatSpikey,
	MatCustom
};

class GameEntity : public GameObject
{
public:
	GameEntity(Material * material);
	GameEntity(MaterialType material = MaterialType::MatFlatColor);
	GameEntity(const tstring & visualModelPath, MaterialType material = MaterialType::MatFlatColor);
	GameEntity(const tstring & visualModelPath, Material * material);
	virtual ~GameEntity();

	virtual void Initialize();
	void SetMaterial(Material * material);
	Material * GetMaterial() const { return m_pVisualMaterial; }

protected:
	ModelComponent* m_pVisualModel;
	Material *m_pVisualMaterial;

	BaseScreen *m_pScreen;
	tstring m_VisualResourcePath;
	MaterialType m_MaterialName;

private:
	friend class BaseScreen;

	// Disabling default copy constructor and default assignment operator.
	GameEntity(const GameEntity& yRef);									
	GameEntity& operator=(const GameEntity& yRef);
};