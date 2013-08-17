#pragma once

//====================== #INCLUDES ===================================
#include "Graphics/Material.h"
//====================================================================

//====================== BaseModelMaterial Class =========================
// Description:
//		Simple material with a diffuse texture
// Last Modification: August 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class GraphicsDevice;
class ModelComponent;

class BaseModelMaterial:public Material
{
public:
	BaseModelMaterial(void);
	~BaseModelMaterial(void);

	void SetLightDirection(const D3DXVECTOR3 & lightDirection){ m_vecLightDirection = lightDirection; }
	void SetDiffuse(const tstring & path);
	inline void SetAlpha(const float alpha) { m_Alpha = alpha; }

protected:
	virtual void LoadEffectVariables();
	virtual void UpdateEffectVariables(ModelComponent* modelComponent);

private:
	float m_Alpha;
	D3DXVECTOR3 m_vecLightDirection;
	ID3D10ShaderResourceView	*m_pDiffuseResourceView;

	ID3D10EffectVectorVariable* m_pLightDirVariable;
	ID3D10EffectScalarVariable * m_pAlphaVariable;
	ID3D10EffectShaderResourceVariable* m_pDiffuseMapVariabele;

	BaseModelMaterial(const BaseModelMaterial& yRef);									
	BaseModelMaterial& operator=(const BaseModelMaterial& yRef);
};

