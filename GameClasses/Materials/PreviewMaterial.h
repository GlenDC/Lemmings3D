#pragma once

//====================== #INCLUDES ===================================
#include "helpers/stdafx.h"
#include "helpers/d3dutil.h"
#include "helpers/generalstructs.h"
#include "Graphics/Material.h"
#include <memory>
//====================================================================

//====================== PreviewMaterial Class =========================
// Description:
//		Material for the preview of objectss
// Last Modification: 30/05/2013
// Copyright Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class PreviewMaterial : public Material
{
public:
	explicit PreviewMaterial();
	virtual ~PreviewMaterial(void);

	void SetTexture(const tstring & path);

	ID3D10ShaderResourceView * GetTexture() const { return m_pTextureView; }

	void SetPosition(const D3DXVECTOR3 & pos) { m_PreviewPosition = pos; }

protected:

	virtual void LoadEffectVariables();
	virtual void UpdateEffectVariables(ModelComponent* modelComponent);

private:
	ID3D10ShaderResourceView * m_pTextureView;
	ID3D10EffectVectorVariable * m_pPositionVariable;
	ID3D10EffectShaderResourceVariable * m_pShaderTexture;

	D3DXVECTOR3 m_PreviewPosition;

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	PreviewMaterial(const PreviewMaterial& yRef);									
	PreviewMaterial& operator=(const PreviewMaterial& yRef);
};