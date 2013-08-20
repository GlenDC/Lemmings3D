#pragma once

//====================== #INCLUDES ===================================
#include "Scenegraph/GameObject.h"
#include <D3DX10.h>
//====================================================================

//====================== WaterObject Class =============================
// Description:
//		fluid implementation
// Last Modification: August 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class BaseScreen;

class WaterObject : public GameObject
{
public:
	WaterObject();
	virtual ~WaterObject();

	virtual void Initialize();
	virtual void Update(const GameContext & context);

	void SetNumParticles(UINT particles);

protected:
	NxFluid * m_pFluid;
	NxFluidDesc m_FluidDesc;
	NxParticleData m_ParticleData;

	UINT m_NumParticles;
	std::vector<NxVec3> m_BufferParticles;

private:
	friend class BaseScreen;

	// Disabling default copy constructor and default assignment operator.
	WaterObject(const WaterObject& yRef);									
	WaterObject& operator=(const WaterObject& yRef);
};
