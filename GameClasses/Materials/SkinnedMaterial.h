#pragma once

//====================== #INCLUDES ===================================
#include "Graphics/Material.h"
//====================================================================

//====================== SkinnedMaterial Class =========================
// Description:
//		Material for skinned materials
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class GraphicsDevice;
class ModelComponent;

class SkinnedMaterial:public Material
{
public:
	SkinnedMaterial(void);
	~SkinnedMaterial(void);

	void SetLightDirection(const D3DXVECTOR3 & lightDirection){m_vecLightDirection = lightDirection;}
	void SetDiffuse(const tstring & path);
	void SetBoneTransformations(const std::vector<D3DXMATRIX> & boneTransformations);

protected:
	virtual void LoadEffectVariables();
	virtual void UpdateEffectVariables(ModelComponent* modelComponent);

private:
	D3DXVECTOR3 m_vecLightDirection;
	ID3D10ShaderResourceView	*m_pDiffuseResourceView;
	std::vector<D3DXMATRIX> m_BoneTransformations;

	ID3D10EffectVectorVariable* m_pLightDirVariable;
	ID3D10EffectShaderResourceVariable* m_pDiffuseMapVariabele;
	ID3D10EffectVariable*				m_pBoneTransformationsVariable;

	SkinnedMaterial(const SkinnedMaterial& yRef);									
	SkinnedMaterial& operator=(const SkinnedMaterial& yRef);
};

