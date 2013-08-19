#pragma once

//====================== #INCLUDES ===================================
#include "Graphics/Material.h"
//====================================================================

//====================== SkyBoxMaterial Class =========================
// Description:
//		skybox/cubemap material
// Last Modification: August 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class GraphicsDevice;
class ModelComponent;

class SkyBoxMaterial : public Material
{
public:
	explicit SkyBoxMaterial();
	~SkyBoxMaterial(void);

	void SetCubeMap(const tstring & path);
	void Update(const GameContext & context);

	void SetPosition(const D3DXVECTOR3 & pos);

protected:
	virtual void LoadEffectVariables();
	virtual void UpdateEffectVariables(ModelComponent* modelComponent);

private:
	ID3D10ShaderResourceView	*m_pCubemapResourceView;
	D3DXVECTOR3 m_PreviewPosition;
	D3DXMATRIX m_WorldMatrix;

	ID3D10EffectShaderResourceVariable* m_pCubeMapVariabele;

	SkyBoxMaterial(const SkyBoxMaterial& yRef);									
	SkyBoxMaterial& operator=(const SkyBoxMaterial& yRef);
};