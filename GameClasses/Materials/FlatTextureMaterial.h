#pragma once

//====================== #INCLUDES ===================================
#include "Graphics/Material.h"
//====================================================================

//====================== FlatTextureMaterial Class =========================
// Description:
//		Simple material with a diffuse texture
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class GraphicsDevice;
class ModelComponent;

class FlatTextureMaterial:public Material
{
public:
	FlatTextureMaterial(void);
	~FlatTextureMaterial(void);

	void SetLightDirection(const D3DXVECTOR3 & lightDirection){ m_vecLightDirection = lightDirection; }
	void SetDiffuse(const tstring & path);

protected:
	virtual void LoadEffectVariables();
	virtual void UpdateEffectVariables(ModelComponent* modelComponent);

private:

	D3DXVECTOR3 m_vecLightDirection;
	ID3D10ShaderResourceView	*m_pDiffuseResourceView;

	ID3D10EffectVectorVariable* m_pLightDirVariable;
	ID3D10EffectShaderResourceVariable* m_pDiffuseMapVariabele;

	FlatTextureMaterial(const FlatTextureMaterial& yRef);									
	FlatTextureMaterial& operator=(const FlatTextureMaterial& yRef);
};

