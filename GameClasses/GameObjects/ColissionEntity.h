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

class ColissionEntity : public GameEntity
{
private:

public:
	ColissionEntity();
	virtual ~ColissionEntity();
	
	virtual void Initialize();

	//Set the material settings. otherwise the default physics material will be used.
	void SetPhysicsMaterial(float restituation = 1.0f, NxCombineMode restituationCombineMode = NX_CM_MAX,
		float dynamicFriction = 0, float staticFriction = 0, NxCombineMode frictionCombineMode = NX_CM_MIN);

	//Add box collider compontent, if none user-defined collider is added a defaul box collider will be used.
	void AddBoxCollider(float width, float height, float depth, bool useMaterial = true);
	//Add mesh collider  compontent, if none user-defined collider is added a defaul box collider will be used.
	void AddMeshCollider(const tstring & path, bool isConvex, bool useMaterial = true);
	//Add sphere collider compontent, if none user-defined collider is added a defaul box collider will be used.
	void AddSphereCollider(float radius, bool useMaterial = true);
	//Add plane collider compontent, if none user-defined collider is added a defaul box collider will be used.
	void AddPlaneCollider(float distance, const NxVec3 & normal, bool useMaterial = true);
	//Add capsule collider compontent, if none user-defined collider is added a defaul box collider will be used.
	void AddCapsuleCollider(float height, float radius, bool useMaterial = true);
protected:
	PhysicsMaterial * m_pPhysicsMaterial;
	RigidBodyComponent *m_pRigidBody;
	std::vector<BaseColliderComponent*> m_ColliderComponents;

private:

	// Disabling default copy constructor and default assignment operator.
	ColissionEntity(const ColissionEntity& yRef);									
	ColissionEntity& operator=(const ColissionEntity& yRef);
};