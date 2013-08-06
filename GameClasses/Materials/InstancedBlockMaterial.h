#pragma once

//====================== #INCLUDES ===================================
#include "helpers/stdafx.h"
#include "helpers/d3dutil.h"
#include "helpers/generalstructs.h"
#include "Graphics/Material.h"
#include <memory>
//====================================================================

//====================== InstancedBlockMaterial Class =========================
// Description:
//		Material for the Instanced Blocks
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class InstancedBlockMaterial : public Material
{
public:
	explicit InstancedBlockMaterial();
	virtual ~InstancedBlockMaterial(void);

	void SetTexture(const tstring & path);

	ID3D10ShaderResourceView * GetTexture() const { return m_pTextureView; }

protected:

	virtual void LoadEffectVariables();
	virtual void UpdateEffectVariables(ModelComponent* modelComponent);

private:
	ID3D10ShaderResourceView * m_pTextureView;
	ID3D10EffectShaderResourceVariable * m_pShaderTexture;

	// Disabling default copy constructor and default assignment operator.
	InstancedBlockMaterial(const InstancedBlockMaterial& yRef);									
	InstancedBlockMaterial& operator=(const InstancedBlockMaterial& yRef);
};