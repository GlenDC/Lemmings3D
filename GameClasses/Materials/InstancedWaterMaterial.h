#pragma once

//====================== #INCLUDES ===================================
#include "helpers/stdafx.h"
#include "helpers/d3dutil.h"
#include "helpers/generalstructs.h"
#include "Graphics/Material.h"
#include <memory>
//====================================================================

//====================== InstancedWaterMaterial Class =========================
// Description:
//		Material for the Instanced Water
// Last Modification: 09/06/2013
// Copyright Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class InstancedWaterMaterial : public Material
{
public:
	explicit InstancedWaterMaterial();
	virtual ~InstancedWaterMaterial(void);

	void SetTexture(const tstring & path);

	ID3D10ShaderResourceView * GetTexture() const { return m_pTextureView; }

	void SetWaterLevel(float waterLevel);
	void SetWaterAlpha(float waterAlpha);

protected:

	virtual void LoadEffectVariables();
	virtual void UpdateEffectVariables(ModelComponent* modelComponent);

private:
	ID3D10ShaderResourceView * m_pTextureView;
	ID3D10EffectShaderResourceVariable * m_pShaderTexture;
	ID3D10EffectScalarVariable *m_pWaterLevelVariable;
	ID3D10EffectScalarVariable *m_pWaterAlphaVariable;

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	InstancedWaterMaterial(const InstancedWaterMaterial& yRef);									
	InstancedWaterMaterial& operator=(const InstancedWaterMaterial& yRef);
};