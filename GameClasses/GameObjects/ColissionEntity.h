#pragma once
//====================== #INCLUDES ===================================
#include "GameEntity.h"
//====================================================================

//====================== ColissionEntity Class =============================
// Description:
//		All visual entities with a colission. 
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class RigidBodyComponent;
class PhysicsMaterial;
class BaseColliderComponent;
class KeyPickup;

class ColissionEntity : public GameEntity
{
private:

public:
	explicit ColissionEntity(Material * material);
	ColissionEntity(MaterialType material = MaterialType::MatFlatColor);
	ColissionEntity(const tstring & visualModelPath, MaterialType material = MaterialType::MatFlatColor);
	ColissionEntity(const tstring & visualModelPath, Material * material);

	virtual ~ColissionEntity();
	
	virtual void Initialize();

	virtual void Enable();
	virtual void Disable();

	void GiveKey(ColissionEntity * original_key);

	void SetIsStatic(bool is_static);
	bool IsStatic() const;

	//Set the material settings. otherwise the default physics material will be used.
	void SetPhysicsMaterial(float restituation = 1.0f, NxCombineMode restituationCombineMode = NX_CM_MAX,
		float dynamicFriction = 0, float staticFriction = 0, NxCombineMode frictionCombineMode = NX_CM_MIN);

	//Add box collider compontent, if none user-defined collider is added a defaul box collider will be used.
	void AddBoxCollider(float width, float height, float depth, bool useMaterial = true, bool isTrigger = false);
	//Add mesh collider  compontent, if none user-defined collider is added a defaul box collider will be used.
	void AddMeshCollider(const tstring & path, bool isConvex, bool useMaterial = true, bool isTrigger = false);
	//Add sphere collider compontent, if none user-defined collider is added a defaul box collider will be used.
	void AddSphereCollider(float radius, bool useMaterial = true, bool isTrigger = false);
	//Add plane collider compontent, if none user-defined collider is added a defaul box collider will be used.
	void AddPlaneCollider(float distance, const NxVec3 & normal, bool useMaterial = true, bool isTrigger = false);
	//Add capsule collider compontent, if none user-defined collider is added a defaul box collider will be used.
	void AddCapsuleCollider(float height, float radius, bool useMaterial = true, bool isTrigger = false);

	void ClearColliders();
	void RemoveRigidBody();

	void DisableGravity();

	float GetCollectionRange() const { return m_CollectionRange; }
protected:
	virtual void InitializeRigidBody();

	PhysicsMaterial * m_pPhysicsMaterial;
	RigidBodyComponent *m_pRigidBody;
	std::vector<BaseColliderComponent*> m_ColliderComponents;
	bool m_IsStatic;
	float m_CollectionRange;
	KeyPickup *m_pPickup;
	ColissionEntity * m_pOriginalKey;

private:

	// Disabling default copy constructor and default assignment operator.
	ColissionEntity(const ColissionEntity& yRef);									
	ColissionEntity& operator=(const ColissionEntity& yRef);
};