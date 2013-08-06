#pragma once

//====================== #INCLUDES ===================================
#include "Helpers/stdafx.h"
#include "Helpers/generalstructs.h"
#include "Helpers/D3DUtil.h"
//====================================================================

//====================== RenderContext Class =======================
// Description:
//		RenderContext class
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class RenderContext
{
public:
	explicit RenderContext(const tstring & effect_file);
	virtual ~RenderContext(void);
  
	// Begin the render context and make its render state active
	void BeginDraw(void);
	// End the render context and restore previous render state,
	// if necessary
	void EndDraw(void);

private:
	// Any description of the current render state and pixel
	// and vertex shaders. ID3D10Effect framework is particularly useful.
	ID3D10Effect * m_pEffect;

	// Disabling default copy constructor and default assignment operator.
	RenderContext(const RenderContext& yRef);									
	RenderContext& operator=(const RenderContext& yRef);
};