#pragma once

//====================== #INCLUDES ===================================
#include "Graphics/Material.h"
//====================================================================

//====================== FlatColorMaterial Class =========================
// Description:
//		Simple material, with a diffuse color
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class GraphicsDevice;
class ModelComponent;

class FlatColorMaterial:public Material
{
public:
	FlatColorMaterial(void);
	~FlatColorMaterial(void);

	void SetLightDirection(const D3DXVECTOR3 & lightDirection){m_vecLightDirection = lightDirection;}
	void SetColor(const D3DXCOLOR & color){m_Color = color;}

protected:
	virtual void LoadEffectVariables();
	virtual void UpdateEffectVariables(ModelComponent* modelComponent);

private:

	D3DXVECTOR3 m_vecLightDirection;
	D3DXCOLOR m_Color;

	ID3D10EffectVectorVariable* m_pLightDirVariable;
	ID3D10EffectVectorVariable* m_pColorVariable;

	FlatColorMaterial(const FlatColorMaterial& yRef);									
	FlatColorMaterial& operator=(const FlatColorMaterial& yRef);
};

