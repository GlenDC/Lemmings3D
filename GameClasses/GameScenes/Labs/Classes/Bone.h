#pragma once
#include "Scenegraph/GameObject.h"
#include "Helpers/stdafx.h"
#include "OverlordComponents.h"

#include <vector>

class FlatColorMaterial;

class BoneObject: public GameObject
{
public:
	BoneObject(int boneId, float length = 5.0f);
	virtual ~BoneObject(void);

	virtual void Initialize();
	virtual void Update(const GameContext& context);

	void AddBone(BoneObject* bone);

	D3DXMATRIX GetBindPose() { return m_BindPose; }
	void CalculateBindPose();

private:
	static const float BONE_STRETCH_VALUE;

	GameObject * m_pBone;

	float m_Length;
	int m_BoneId;
	ModelComponent* m_pMesh;
	FlatColorMaterial* m_pMaterial;
	D3DXMATRIX m_BindPose;

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	BoneObject(const BoneObject& t);
	BoneObject& operator=(const BoneObject& t);
};
