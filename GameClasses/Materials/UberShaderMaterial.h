#pragma once

//====================== #INCLUDES ===================================
#include "Graphics/Material.h"
//====================================================================

//====================== UberShaderMaterial Class =========================
// Description:
//		Simple material with a diffuse texture
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class GraphicsDevice;
class ModelComponent;

class UberShaderMaterial:public Material
{
public:
	enum SpecularModel : byte
	{
		Blinn = 0,
		Phong,
		CookTorrance, 
		Lyon
	};

	UberShaderMaterial(void);
	~UberShaderMaterial(void);

	//Global Setting Set/Get
	void SetLightDirection(const D3DXVECTOR3 & direction);
	void SetWorldMatrix(const D3DMATRIX & matWorld);
	void SetCamera(const D3DMATRIX & matCamera);
	void EnableMultipleLights(bool enable);

	//Diffuse Setting Set/Get
	void SetDiffuseTexture(const tstring & filename);
	void SetDiffuseColor(const D3DXVECTOR3 & color);
	void SetDiffuseLerpControl(float lerpControl);
	void EnableDiffuseTexture(bool enable);
	void EnableHalfLambert(bool enable);
	void SetLambertPower(float power);

	//Specular Setting Set/Get
	void SetSpecularTexture(const tstring & filename);
	void SetSpecularColor(const D3DXVECTOR3 & color);
	void SetShininess(int s);
	void EnableSpecularTexture(bool enable);

	//Ambient Setting Set/Get
	void SetAmbientColor(const D3DXVECTOR3 & color);
	void SetAmbientIntensity(float intensity);
	void SetAmbientLerpControl(float lerpControl);

	//Normal Setting Set/Get
	void SetNormalTexture(const tstring & filename);
	void SetFlipGreenChannel(bool flipGreenChannel);
	bool GetFlipGreenChannel();
	void EnableNormalTexture(bool enable);
	bool GetStateNormalTexture();

	//Environment Setting Set/Get
	void SetEnvironmentTexture(const tstring & filename);
	void EnableEnvironmentMapping(bool enable);
	void EnableRefraction(bool enable);
	void SetReflectionStrength(float strength);
	void SetRefractionStrength(float strength);
	void SetRefractionLerpControl(float lerpControl);
	void SetRefractionIndex(float refractionIndex);

	//Specular Models Setting Set/Get
	void SetSpecularModel(SpecularModel spec);
	void SetSpecularModel(SpecularModel spec, float lerpControl);
	void ForceSpecularModel(SpecularModel spec);
	void SetRoughnessMaterial(float roughnessMaterial);
	void SetFresnelStrength(float strength);

	//Fresnel Setting Set/Get
	void EnableFresnelFaloff(bool enable);
	void SetFresnelPower(float power);
	void SetFresnelMultiplier(float multiplier);
	void SetFresnelHardness(float hardness);
	void SetFresnelLerpControl(float lerpControl);
	void SetFresnelMaskDirection(const D3DXVECTOR3 & maskDirection);
	void SetFresnelColor(const D3DXVECTOR3 & color);

	//Opacity Setting Set/Get
	void SetOpacity(float opacity);
	void SetOpacityTexture(const tstring & filename);
	void EnableOpacityTexture(bool enable);

	//Panning Set
	void CreatePanning(float panSpeed, const tstring & alphaMask);
	void CreatePanning(float panSpeed1, float panSpeed2, const tstring & alphaMask1, const tstring & alphaMask2);
	void UpdatePanning1(float speed);
	void UpdatePanning2(float speed);

	static void EnableGlobalSpecular(bool enable);
	static void EnableGlobalNormal(bool enable);
	static void EnableGlobalEnvironment(bool enable);
	static void EnableGlobalOpacity(bool enable);
	static void EnableGlobalHalfLambert(bool enable);
	static void EnableGlobalFresnelFallof(bool enable);

	static bool IsGlobalSpecularEnabled() { return ENABLE_SPECULAR; }
	static bool IsGlobalNormalEnabled() { return ENABLE_NORMAL; }
	static bool IsGlobalEnvironmentEnabled() { return ENABLE_ENVIRONMENT; }
	static bool IsGlobalOpacityEnabled() { return ENABLE_OPACITY; }
	static bool IsGlobalHalfLambertEnabled() { return ENABLE_HALF_LAMBERT; }
	static bool IsGlobalFresnelFallofEnabled() { return ENABLE_FRESNEL_FALLOF; }

protected:
	virtual void LoadEffectVariables();
	virtual void UpdateEffectVariables(ModelComponent* modelComponent);

private:
	static bool		ENABLE_SPECULAR,
					ENABLE_NORMAL,
					ENABLE_ENVIRONMENT,
					ENABLE_OPACITY,
					ENABLE_HALF_LAMBERT,
					ENABLE_FRESNEL_FALLOF;

	//UpdateTimer
	void UpdateTime(float time);

	bool m_bMultipleLights;

	D3DXVECTOR3	m_LightDirection;

	//Effect Variables
	ID3D10EffectVectorVariable*			m_pLightDirVariable;
	ID3D10EffectScalarVariable			*m_pLightsEnableVariable;

	//Diffuse Variables
	bool								m_bDiffuseTexture
		,m_bHalfLambert;
	D3DXVECTOR4							m_v4ColorDiffuse;
	ID3D10ShaderResourceView			*m_pDiffuseResourceView;
	float								m_DiffuseLerpControl,
		m_LambertPower;

	ID3D10EffectShaderResourceVariable	*m_pDiffuseMapVariabele;
	ID3D10EffectScalarVariable			*m_pDiffuseTextureVariable,
		*m_pDiffuseLerpControlVariable,
		*m_pLambertPowerVariable,
		*m_pHalfLambertVariable;
	ID3D10EffectVectorVariable			*m_pColorDiffuseVectorVariable;

	//Specular Variables
	bool								m_bSpecularLevelTexture;
	D3DXVECTOR4							m_v4ColorSpecular;
	ID3D10ShaderResourceView			*m_pSpecularResourceView;
	int									m_Shininess;

	ID3D10EffectShaderResourceVariable	*m_pSpecularMapVariable;
	ID3D10EffectScalarVariable			*m_pSpecularLevelTextureVariable,
		*m_pShininessVariable;
	ID3D10EffectVectorVariable			*m_SpecularVectorVariable;


	//Ambient Variables
	D3DXVECTOR4							m_v4ColorAmbient;
	float								m_AmbientIntensity,
		m_AmbientLerpControl;

	ID3D10EffectScalarVariable			*m_pAmbientIntensityVariable,
		*m_pAmbientLerpControlVariable;
	ID3D10EffectVectorVariable			*m_pAmbientVectorVariable;

	//Normal Mapping
	bool								m_bFlipGreenChannel,
		m_bNormalMapping;
	ID3D10ShaderResourceView			*m_pNormalResourceView;

	ID3D10EffectShaderResourceVariable	*m_pNormalMapVariable;
	ID3D10EffectScalarVariable			*m_pFlipGreenChannelVariable,
		*m_pNormalMappingVariable;

	//Environment Mapping
	bool								m_bEnvironmentMapping,
		m_bRefraction;
	ID3D10EffectShaderResourceVariable	*m_pEnvironmentMapCubeVariable;
	float								m_ReflectionStrength,
		m_RefractionStrength,
		m_RefractionLerpControl,
		m_RefractionIndex;

	ID3D10ShaderResourceView			*m_pEnvironmentResourceView;
	ID3D10EffectScalarVariable			*m_pEnvironmentVariable,
		*m_pRefractionVariable,
		*m_pReflectionStrengthVariable,
		*m_pRefractionStrengthVariable,
		*m_pRefractionLerpControlVariable,
		*m_pRefractionIndexVariable;

	//Specular Models
	bool								m_bSpecularBlinn,
		m_bSpecularPhong,
		m_bSpecularCookTorrance,
		m_bSpecularLyon;
	float								m_CookTorranceLerpControl,
		m_PhongLerpControl,
		m_RoughnessMaterial,
		m_FresnelStrength,
		m_LyonLerpControl;

	ID3D10EffectScalarVariable			*m_pSpecularBlinnVariable,
		*m_pSpecularPhongVariable,
		*m_pSpecularLyonVariable,
		*m_pSpecularCookTorranceVariable,
		*m_pCookTorranceLerpControlVariable,
		*m_pPhongLerpControlVariable,
		*m_pLyonLerpControlVariable,
		*m_pRoughnessMaterialVariable,
		*m_pFresnelStrengthVariable;

	//Fresnell Fallof
	bool								m_bFresnelFaloff;
	float								m_FresnelPower,
		m_FresnelMultiplier,
		m_FresnelHardness,
		m_FresnelFaloffEnvLerpControl;
	D3DXVECTOR3							m_FresnelMaskDirection,
		m_ColorFresnel;

	ID3D10EffectScalarVariable			*m_pFresnelFalloffVariable,
		*m_pFresnelPowerVariable,
		*m_pFresnelMultiplierVariable,
		*m_pFresnelHardnessVariable,
		*m_pFresnelFalloffEnvLerpControlVariable;
	ID3D10EffectVectorVariable			*m_pFresnelMaskDirectionVectorVariable,
		*m_pColorFresnelVectorVariable;

	//Opacity Mapping
	bool								m_bOpacityMap;
	float								m_Opacity;
	ID3D10EffectShaderResourceVariable	*m_pOpacityTextureMapVariable;

	ID3D10ShaderResourceView			*m_pOpacityResourceView;
	ID3D10EffectScalarVariable			*m_pOpacityMapVariable,
		*m_pOpacityVariable;

	//Panning
	bool								m_bUsePanning;
	float								m_PanningSpeed1, m_PanningSpeed2;
	ID3D10EffectShaderResourceVariable *m_pPanningAlpha1, *m_pPanningAlpha2;

	ID3D10ShaderResourceView			*m_pPanningAlpha1RV, *m_pPanningAlpha2RV;
	ID3D10EffectScalarVariable			*m_pPanningSpeed1Variable, *m_pPanningSpeed2Variable,
		*m_pUsePanningVariable;

	//Time 
	float								m_TimeValue;
	ID3D10EffectScalarVariable			*m_pTimeValueVariable;

	UberShaderMaterial(const UberShaderMaterial& yRef);									
	UberShaderMaterial& operator=(const UberShaderMaterial& yRef);
};

