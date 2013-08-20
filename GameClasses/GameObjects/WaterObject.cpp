//=============================== INCLUDES ====================================
#include "WaterObject.h"
//-----------------------------------------------------------------------------
#include "OverlordComponents.h"
#include "Scenegraph/GameScene.h"
//-----------------------------------------------------------------------------
//=============================================================================

WaterObject::WaterObject()
	: m_pFluid(nullptr)
	, m_FluidDesc()
	, m_ParticleData()
	, m_NumParticles(100)
	, m_BufferParticles(m_NumParticles)
{
}

WaterObject::~WaterObject()
{

}

void WaterObject::Initialize()
{
	//Set structure to pass particles, and receive them after every simulation step 
	m_ParticleData.numParticlesPtr = &m_NumParticles;
	m_ParticleData.bufferPos = &m_BufferParticles[0].x;
	m_ParticleData.bufferPosByteStride = sizeof(NxVec3);

	m_FluidDesc.kernelRadiusMultiplier = 2.3f;
	m_FluidDesc.restParticlesPerMeter = 10.0f;
	m_FluidDesc.stiffness = 200.0f;
	m_FluidDesc.viscosity = 22.0f;
	m_FluidDesc.restDensity = 1000.0f;
	m_FluidDesc.damping = 0.0f;
	m_FluidDesc.simulationMethod = NX_F_SPH;
	m_FluidDesc.initialParticleData = m_ParticleData;
	m_FluidDesc.particlesWriteData = m_ParticleData;

	m_pFluid = dynamic_cast<NxFluid*>(m_pScene->GetPhysicsScene()->createFluid(m_FluidDesc));
}

void WaterObject::Update(const GameContext & context)
{
}

void WaterObject::SetNumParticles(UINT particles)
{
	m_NumParticles = particles;
	m_BufferParticles.reserve(m_NumParticles);
}