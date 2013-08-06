#pragma once

//====================== #INCLUDES ===================================
#include "Helpers/stdafx.h"
#include "Helpers/generalstructs.h"
#include "Helpers/D3DUtil.h"

#include "../Entities//RenderContext.h"
//====================================================================

//====================== GeometryBatch Interface ============================
// Description:
//		interface for a class designed to draw an instanced object!
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class IGeometryBatch
{
public:
	// destructor
    virtual ~IGeometryBatch() {}
	// Remove all instances from the geometry batch
	virtual void ClearInstances(void) = 0;
	// Add an instance to the collection and return its ID.
	// Return -1 if it can't accept more instances.
	virtual int AddInstance(const D3DXMATRIX & world, int instance_id) = 0;
	// Remove an instance by its world matrix and return its ID
	// return -1 if it can't find the instance
	virtual int RemoveInstance(const D3DXMATRIX & world) = 0;
	// Remove an instance by its id and return its world matrix
	// return an identy matrix if instance cant be found
	virtual D3DXMATRIX RemoveInstance(int id) = 0;
	// Commit all instances, to be called once before the
	// render loop begins and after every change to the instances collection
	virtual unsigned int Commit(void) = 0;
	// Update the geometry batch, eventually prepare GPU-specific
	// data ready to be submitted to the driver, fill vertex and
	// index buffers as necessary, to be called once per frame
	virtual void Update(const GameContext & context) = 0;
	// Submit the batch to the driver, typically implemented
	// with a call to DrawIndexedPrimitive
	virtual void Draw(const GameContext & context) = 0;

protected:
	RenderContext *m_pRenderContext;
};