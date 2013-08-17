#pragma once

//====================== #INCLUDES ===================================
#include "Scenegraph/GameObject.h"
#include <D3DX10.h>
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
class TransformComponent;

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
	explicit GameEntity(Material * material);
	GameEntity(MaterialType material = MaterialType::MatFlatColor);
	GameEntity(const tstring & visualModelPath, MaterialType material = MaterialType::MatFlatColor);
	GameEntity(const tstring & visualModelPath, Material * material);
	virtual ~GameEntity();

	virtual void Initialize();
	virtual void Draw(const GameContext & context);
	void SetMaterial(Material * material);
	Material * GetMaterial() const { return m_pVisualMaterial; }

	bool IsVisible() const { m_IsVisible; }
	void SetIsVisible(bool is_visible) { m_IsVisible = is_visible; }

	TransformComponent * GetTransform() const;
	void Translate(float x, float y, float z);
	void Translate(const D3DXVECTOR3 & vector);
	void Scale(float x, float y, float z);
	void Scale(const D3DXVECTOR3 & vector);
	void Rotate(float x, float y, float z);
	void Rotate(const D3DXVECTOR3 & vector);
	void Rotate(const D3DXQUATERNION & rotation);

	const D3DXVECTOR3 & GetTranslation() const;
	const D3DXVECTOR3 & GetScale() const;
	const D3DXQUATERNION & GetRotation() const;
	const D3DXMATRIX & GetWorldMatrix() const;

	float GetCameraHeight() const { return m_CameraHeight; }
	D3DXVECTOR3 GetCameraTargetPosition() const;

protected:
	ModelComponent* m_pVisualModel;
	Material *m_pVisualMaterial;

	BaseScreen *m_pScreen;
	tstring m_VisualResourcePath;
	MaterialType m_MaterialName;
	bool m_IsVisible;
	float m_CameraHeight;

private:
	friend class BaseScreen;

	// Disabling default copy constructor and default assignment operator.
	GameEntity(const GameEntity& yRef);									
	GameEntity& operator=(const GameEntity& yRef);
};