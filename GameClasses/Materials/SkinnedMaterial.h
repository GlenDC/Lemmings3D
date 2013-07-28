//--------------------------------------------------------------------------------------
//   _____     _______ ____  _     ___  ____  ____    _____ _   _  ____ ___ _   _ _____ 
//  / _ \ \   / / ____|  _ \| |   / _ \|  _ \|  _ \  | ____| \ | |/ ___|_ _| \ | | ____|
// | | | \ \ / /|  _| | |_) | |  | | | | |_) | | | | |  _| |  \| | |  _ | ||  \| |  _|  
// | |_| |\ V / | |___|  _ <| |__| |_| |  _ <| |_| | | |___| |\  | |_| || || |\  | |___ 
//  \___/  \_/  |_____|_| \_\_____\___/|_| \_\____/  |_____|_| \_|\____|___|_| \_|_____|
//
// Overlord Engine v0.44
// Copyright Overlord Brecht Kets & Overlord Thomas Goussaert
// http://www.digitalartsandentertainment.com/
//--------------------------------------------------------------------------------------

#pragma once
#include "Graphics/Material.h"

class GraphicsDevice;
class ModelComponent;

class SkinnedMaterial:public Material
{
public:
	SkinnedMaterial(void);
	~SkinnedMaterial(void);

	void SetLightDirection(D3DXVECTOR3 lightDirection){m_vecLightDirection = lightDirection;}
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

