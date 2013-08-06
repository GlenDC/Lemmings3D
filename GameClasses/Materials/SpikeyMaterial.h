#pragma once

//====================== #INCLUDES ===================================
#include "Graphics/Material.h"
//====================================================================

//====================== SpikeyMaterial Class =========================
// Description:
//		Testmaterial, for a spiky lab!
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class GraphicsDevice;
class ModelComponent;

class SpikeyMaterial:public Material
{
public:
	SpikeyMaterial(void);
	virtual ~SpikeyMaterial(void);

	void SetLightDirection(const D3DXVECTOR3 & lightDirection){m_vecLightDirection = lightDirection;}
	void SetColor(const D3DXCOLOR & color){m_Color = color;}

protected:
	virtual void LoadEffectVariables();
	virtual void UpdateEffectVariables(ModelComponent* modelComponent);

private:

	D3DXVECTOR3 m_vecLightDirection;
	D3DXCOLOR m_Color, m_TargetColor;
	float m_SpikeHeight;
	float m_TargetSpikeHeight;
	float m_CurrentTime;
	float m_Negative;
	ID3D10ShaderResourceView	*m_pDiffuseResourceView;
	D3DXVECTOR3 m_Target;

	ID3D10EffectVectorVariable* m_pLightDirVariable;
	ID3D10EffectVectorVariable* m_pColorVariable;
	ID3D10EffectScalarVariable* m_pSpikeHeightVariable;
	ID3D10EffectScalarVariable* m_pNegativeVariable;
	ID3D10EffectShaderResourceVariable* m_pDiffuseMapVariabele;

	SpikeyMaterial(const SpikeyMaterial& yRef);									
	SpikeyMaterial& operator=(const SpikeyMaterial& yRef);
};

