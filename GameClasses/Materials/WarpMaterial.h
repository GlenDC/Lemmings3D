#pragma once

//====================== #INCLUDES ===================================
#include "Graphics/Material.h"
//====================================================================

//====================== WarpMaterial Class =========================
// Description:
//		Special material for the warp center of the portal object
// Last Modification: August 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class GraphicsDevice;
class ModelComponent;

class WarpMaterial:public Material
{
public:
	WarpMaterial(void);
	~WarpMaterial(void);

	void SetMask(const tstring & path);
	void SetColorMask(const tstring & path);
	void SetColor(const D3DXVECTOR3 & color);
	void SetTime(float time);

protected:
	virtual void LoadEffectVariables();
	virtual void UpdateEffectVariables(ModelComponent* modelComponent);

private:
	ID3D10ShaderResourceView	*m_pMaskResourceView;
	ID3D10ShaderResourceView	*m_pColorMaskResourceView;
	D3DXVECTOR3					m_Color;
	float m_Time;

	ID3D10EffectShaderResourceVariable* m_pMaskMapVariabele;
	ID3D10EffectShaderResourceVariable* m_pColorMaskMapVariabele;
	ID3D10EffectVectorVariable	*m_pColorVariable;
	ID3D10EffectScalarVariable	*m_pTimeVariable;

	WarpMaterial(const WarpMaterial& yRef);									
	WarpMaterial& operator=(const WarpMaterial& yRef);
};