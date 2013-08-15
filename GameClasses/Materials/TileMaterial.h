#pragma once

//====================== #INCLUDES ===================================
#include "Graphics/Material.h"
//====================================================================

//====================== TileMaterial Class =========================
// Description:
//		material with diffuse texture that can tile
// Last Modification: August 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class GraphicsDevice;
class ModelComponent;

class TileMaterial:public Material
{
public:
	explicit TileMaterial(const D3DXVECTOR2 & uv);
	~TileMaterial(void);

	void SetDiffuse(const tstring & path);
	void SetUVTile(const D3DXVECTOR2 & uv) { m_UVTile = uv; }

protected:
	virtual void LoadEffectVariables();
	virtual void UpdateEffectVariables(ModelComponent* modelComponent);

private:
	D3DXVECTOR2 m_UVTile;
	ID3D10ShaderResourceView	*m_pDiffuseResourceView;

	ID3D10EffectVectorVariable* m_pUVTileVariable;
	ID3D10EffectShaderResourceVariable* m_pDiffuseMapVariabele;

	TileMaterial(const TileMaterial& yRef);									
	TileMaterial& operator=(const TileMaterial& yRef);
};

