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

class SpikeyMaterial:public Material
{
public:
	SpikeyMaterial(void);
	virtual ~SpikeyMaterial(void);

	void SetLightDirection(D3DXVECTOR3 lightDirection){m_vecLightDirection = lightDirection;}
	void SetColor(D3DXCOLOR color){m_Color = color;}

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

