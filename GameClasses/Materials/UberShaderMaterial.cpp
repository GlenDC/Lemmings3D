//========================================= INCLUDES ======================================
#include "UberShaderMaterial.h"
//-----------------------------------------------------------------------------------------
#include "Graphics/GraphicsDevice.h"
#include "Components/ModelComponent.h"
#include "Managers/ContentManager.h"
#include "Diagnostics/Logger.h"
//==========================================================================================

UberShaderMaterial::UberShaderMaterial():
	Material(_T("./Resources/Lemmings3D/shaders/UberShader.fx"))
	,m_pLightDirVariable(nullptr)
	,m_pLightsEnableVariable(nullptr)

	,m_LightDirection(0,0,0)
	,m_bMultipleLights(false)

	//diffuse
	,m_bDiffuseTexture(false)
	,m_bHalfLambert(false)
	,m_v4ColorDiffuse(1.0f,0.0f,0.0f,1.0f)
	,m_pDiffuseMapVariabele(nullptr)
	,m_DiffuseLerpControl(0.0f)
	,m_LambertPower(0.5f)
	,m_pDiffuseResourceView(nullptr)
	,m_pDiffuseTextureVariable(nullptr)
	,m_pDiffuseLerpControlVariable(nullptr)
	,m_pColorDiffuseVectorVariable(nullptr)
	,m_pLambertPowerVariable(nullptr)
	,m_pHalfLambertVariable(nullptr)
	//specular
	,m_bSpecularLevelTexture(false)
	,m_v4ColorSpecular(1.0f,1.0f,1.0f,1.0f)
	,m_pSpecularMapVariable(nullptr)
	,m_Shininess(15)
	,m_pSpecularResourceView(nullptr)
	,m_pSpecularLevelTextureVariable(nullptr)
	,m_pShininessVariable(nullptr)
	,m_SpecularVectorVariable(nullptr)
	//ambient
	,m_v4ColorAmbient(0.1f,0.1f,1.0f,1.0f)
	,m_AmbientIntensity(0.35f)
	,m_AmbientLerpControl(0.1f)
	,m_pAmbientIntensityVariable(nullptr)
	,m_pAmbientLerpControlVariable(nullptr)
	,m_pAmbientVectorVariable(nullptr)
	//Normal mapping
	,m_bFlipGreenChannel(false)
	,m_bNormalMapping(false)
	,m_pNormalMapVariable(nullptr)
	,m_pNormalResourceView(nullptr)
	,m_pFlipGreenChannelVariable(nullptr)
	,m_pNormalMappingVariable(nullptr)
	//environment
	,m_bEnvironmentMapping(false)
	,m_bRefraction(false)
	,m_pEnvironmentMapCubeVariable(nullptr)
	,m_ReflectionStrength(0.8f)
	,m_RefractionStrength(0.1f)
	,m_RefractionLerpControl(0.6f)
	,m_RefractionIndex(0.3f)
	,m_pEnvironmentResourceView(nullptr)
	,m_pEnvironmentVariable(nullptr)
	,m_pRefractionVariable(nullptr)
	,m_pReflectionStrengthVariable(nullptr)
	,m_pRefractionLerpControlVariable(nullptr)
	,m_pRefractionIndexVariable(nullptr)
	//specular models
	,m_bSpecularBlinn(false)
	,m_bSpecularPhong(true)
	,m_bSpecularLyon(false)
	,m_bSpecularCookTorrance(false)
	,m_CookTorranceLerpControl(0.5f)
	,m_PhongLerpControl(0.5f)
	,m_LyonLerpControl(1.0f)
	,m_RoughnessMaterial(0.2f)
	,m_FresnelStrength(0.01f)
	,m_pSpecularBlinnVariable(nullptr)
	,m_pSpecularPhongVariable(nullptr)
	,m_pSpecularLyonVariable(nullptr)
	,m_pSpecularCookTorranceVariable(nullptr)
	,m_pCookTorranceLerpControlVariable(nullptr)
	,m_pPhongLerpControlVariable(nullptr)
	,m_pLyonLerpControlVariable(nullptr)
	,m_pRoughnessMaterialVariable(nullptr)
	,m_pFresnelStrengthVariable(nullptr)
	//fresnel falloff
	,m_bFresnelFaloff(false)
	,m_FresnelPower(4.2f)
	,m_FresnelMultiplier(4.30f)
	,m_FresnelHardness(3.25f)
	,m_FresnelFaloffEnvLerpControl(0.5f)
	,m_FresnelMaskDirection(0,-1.0f,0)
	,m_ColorFresnel(1,1,1)
	,m_pFresnelFalloffVariable(nullptr)
	,m_pFresnelPowerVariable(nullptr)
	,m_pFresnelMultiplierVariable(nullptr)
	,m_pFresnelHardnessVariable(nullptr)
	,m_pFresnelFalloffEnvLerpControlVariable(nullptr)
	,m_pFresnelMaskDirectionVectorVariable(nullptr)
	,m_pColorFresnelVectorVariable(nullptr)
	//opacity map
	,m_bOpacityMap(false)
	,m_Opacity(1.0f)
	,m_pOpacityTextureMapVariable(nullptr)
	,m_pOpacityResourceView(nullptr)
	,m_pOpacityMapVariable(nullptr)
	,m_pOpacityVariable(nullptr)
	//panning stuff
	,m_bUsePanning(false)
	,m_PanningSpeed1(0)
	,m_PanningSpeed2(0)
	,m_pPanningAlpha1(nullptr)
	,m_pPanningAlpha2(nullptr)
	,m_pPanningAlpha1RV(nullptr)
	,m_pPanningAlpha2RV(nullptr)
	,m_pPanningSpeed1Variable(nullptr)
	,m_pPanningSpeed2Variable(nullptr)
	,m_pUsePanningVariable(nullptr)
	//Time
	,m_TimeValue(0)
	,m_pTimeValueVariable(nullptr)
{
}


UberShaderMaterial::~UberShaderMaterial(void)
{
}

void UberShaderMaterial::LoadEffectVariables()
{
	m_pLightDirVariable = m_pEffect->GetVariableByName("m_LightDirection")->AsVector();
	if(!m_pLightDirVariable->IsValid())
	{
		Logger::Log(_T("Getting VariableByName m_LightDirection Failed"),LogLevel::Error);
	}
	m_pLightsEnableVariable = m_pEffect->GetVariableByName("m_bUseMultipleLights")->AsScalar();
	if(!m_pLightsEnableVariable->IsValid())
	{
		Logger::Log(_T("Getting VariableByName m_bUseMultipleLights Failed"),LogLevel::Error);
	}

	//get diffuse effect variables
	m_pDiffuseMapVariabele = m_pEffect->GetVariableByName("m_TextureDiffuse")->AsShaderResource();
	if(!m_pDiffuseMapVariabele->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_TextureDiffuse Failed"),LogLevel::Error);
	}
	m_pHalfLambertVariable = m_pEffect->GetVariableByName("m_bHalfLambert")->AsScalar();
	if(!m_pHalfLambertVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_bHalfLambert Failed"),LogLevel::Error);
	}
	m_pDiffuseTextureVariable = m_pEffect->GetVariableByName("m_bDiffuseTexture")->AsScalar();
	if(!m_pDiffuseTextureVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_bDiffuseTexture Failed"),LogLevel::Error);
	}
	m_pDiffuseLerpControlVariable = m_pEffect->GetVariableByName("m_DiffuseLerpControl")->AsScalar();
	if(!m_pDiffuseLerpControlVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_DiffuseLerpControl Failed"),LogLevel::Error);
	}
	m_pLambertPowerVariable = m_pEffect->GetVariableByName("m_LambertPower")->AsScalar();
	if(!m_pLambertPowerVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_LambertPower Failed"),LogLevel::Error);
	}
	m_pColorDiffuseVectorVariable = m_pEffect->GetVariableByName("m_ColorDiffuse")->AsVector();
	if(!m_pColorDiffuseVectorVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_ColorDiffuse Failed"),LogLevel::Error);
	}
	//get specular effect variables
	m_pSpecularMapVariable = m_pEffect->GetVariableByName("m_TextureSpecularLevel")->AsShaderResource();
	if(!m_pSpecularMapVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_TextureSpecularLevel Failed"),LogLevel::Error);
	}
	m_pSpecularLevelTextureVariable = m_pEffect->GetVariableByName("m_bSpecularLevelTexture")->AsScalar();
	if(!m_pSpecularLevelTextureVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_bSpecularLevelTexture Failed"),LogLevel::Error);
	}
	m_pShininessVariable = m_pEffect->GetVariableByName("m_Shininess")->AsScalar();
	if(!m_pShininessVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_Shininess Failed"),LogLevel::Error);
	}
	m_SpecularVectorVariable = m_pEffect->GetVariableByName("m_ColorSpecular")->AsVector();
	if(!m_SpecularVectorVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_ColorSpecular Failed"),LogLevel::Error);
	}
	//get ambiant effect variables
	m_pAmbientIntensityVariable = m_pEffect->GetVariableByName("m_AmbientIntensity")->AsScalar();
	if(!m_pAmbientIntensityVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_AmbientIntensity Failed"),LogLevel::Error);
	}
	m_pAmbientLerpControlVariable = m_pEffect->GetVariableByName("m_AmbientLerpControl")->AsScalar();
	if(!m_pAmbientLerpControlVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_AmbientLerpControl Failed"),LogLevel::Error);
	}
	m_pAmbientVectorVariable = m_pEffect->GetVariableByName("m_ColorAmbient")->AsVector();
	if(!m_pAmbientVectorVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_ColorAmbient Failed"),LogLevel::Error);
	}
	//get normal effect variables
	m_pNormalMapVariable = m_pEffect->GetVariableByName("m_TextureNormal")->AsShaderResource();
	if(!m_pNormalMapVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_TextureNormal Failed"),LogLevel::Error);
	}
	m_pFlipGreenChannelVariable = m_pEffect->GetVariableByName("m_FlipGreenChannel")->AsScalar();
	if(!m_pFlipGreenChannelVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_FlipGreenChannel Failed"),LogLevel::Error);
	}
	m_pNormalMappingVariable = m_pEffect->GetVariableByName("m_bNormalMapping")->AsScalar();
	if(!m_pNormalMappingVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_bNormalMapping Failed"),LogLevel::Error);
	}
	//get Environment effect variables
	m_pEnvironmentMapCubeVariable = m_pEffect->GetVariableByName("m_CubeEnvironment")->AsShaderResource();
	if(!m_pSpecularMapVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_CubeEnvironment Failed"),LogLevel::Error);
	}
	m_pEnvironmentVariable = m_pEffect->GetVariableByName("m_bEnvironmentMapping")->AsScalar();
	if(!m_pEnvironmentVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_bEnvironmentMapping Failed"),LogLevel::Error);
	}
	m_pRefractionVariable = m_pEffect->GetVariableByName("m_bRefraction")->AsScalar();
	if(!m_pRefractionVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_bRefraction Failed"),LogLevel::Error);
	}
	m_pReflectionStrengthVariable = m_pEffect->GetVariableByName("m_ReflectionStrength")->AsScalar();
	if(!m_pReflectionStrengthVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_ReflectionStrength Failed"),LogLevel::Error);
	}
	m_pRefractionStrengthVariable = m_pEffect->GetVariableByName("m_RefractionStrength")->AsScalar();
	if(!m_pRefractionStrengthVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_RefractionStrength Failed"),LogLevel::Error);
	}
	m_pRefractionLerpControlVariable = m_pEffect->GetVariableByName("m_RefractionLerpControl")->AsScalar();
	if(!m_pRefractionLerpControlVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_RefractionLerpControl Failed"),LogLevel::Error);
	}
	m_pRefractionIndexVariable = m_pEffect->GetVariableByName("m_RefractionIndex")->AsScalar();
	if(!m_pRefractionIndexVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_RefractionIndex Failed"),LogLevel::Error);
	}
	//get specular model effect variables
	m_pSpecularBlinnVariable = m_pEffect->GetVariableByName("m_SpecularBlinn")->AsScalar();
	if(!m_pSpecularBlinnVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_SpecularBlinn Failed"),LogLevel::Error);
	}
	m_pSpecularPhongVariable = m_pEffect->GetVariableByName("m_SpecularPhong")->AsScalar();
	if(!m_pSpecularPhongVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_SpecularPhong Failed"),LogLevel::Error);
	}
	m_pSpecularCookTorranceVariable = m_pEffect->GetVariableByName("m_SpecularCookTorrance")->AsScalar();
	if(!m_pSpecularCookTorranceVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_SpecularCookTorrance Failed"),LogLevel::Error);
	}
	m_pSpecularLyonVariable = m_pEffect->GetVariableByName("m_SpecularLyon")->AsScalar();
	if(!m_pSpecularLyonVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_SpecularLyon Failed"),LogLevel::Error);
	}
	m_pLyonLerpControlVariable = m_pEffect->GetVariableByName("m_LyonLerpControl")->AsScalar();
	if(!m_pLyonLerpControlVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_LyonLerpControl Failed"),LogLevel::Error);
	}
	m_pCookTorranceLerpControlVariable = m_pEffect->GetVariableByName("m_CookTorranceLerpControl")->AsScalar();
	if(!m_pCookTorranceLerpControlVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_CookTorranceLerpControl Failed"),LogLevel::Error);
	}
	m_pPhongLerpControlVariable = m_pEffect->GetVariableByName("m_PhongLerpControl")->AsScalar();
	if(!m_pPhongLerpControlVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_PhongLerpControl Failed"),LogLevel::Error);
	}
	m_pRoughnessMaterialVariable = m_pEffect->GetVariableByName("m_RoughnessMaterial")->AsScalar();
	if(!m_pRoughnessMaterialVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_RoughnessMaterial Failed"),LogLevel::Error);
	}
	m_pFresnelStrengthVariable = m_pEffect->GetVariableByName("m_FresnelStrength")->AsScalar();
	if(!m_pFresnelStrengthVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_FresnelStrength Failed"),LogLevel::Error);
	}
	//get fresnel falloff effect variables
	m_pFresnelFalloffVariable = m_pEffect->GetVariableByName("m_bFresnelFallOff")->AsScalar();
	if(!m_pFresnelFalloffVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_bFresnelFallOff Failed"),LogLevel::Error);
	}
	m_pFresnelPowerVariable = m_pEffect->GetVariableByName("m_FresnelPower")->AsScalar();
	if(!m_pFresnelPowerVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_FresnelPower Failed"),LogLevel::Error);
	}
	m_pFresnelMultiplierVariable = m_pEffect->GetVariableByName("m_FresnelMultiplier")->AsScalar();
	if(!m_pFresnelMultiplierVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_FresnelMultiplier Failed"),LogLevel::Error);
	}
	m_pFresnelHardnessVariable = m_pEffect->GetVariableByName("m_FresnelHardness")->AsScalar();
	if(!m_pFresnelHardnessVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_FresnelHardness Failed"),LogLevel::Error);
	}
	m_pFresnelFalloffEnvLerpControlVariable = m_pEffect->GetVariableByName("m_FresnelFaloffEnvLerpControl")->AsScalar();
	if(!m_pFresnelFalloffEnvLerpControlVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_FresnelFaloffEnvLerpControl Failed"),LogLevel::Error);
	}
	m_pFresnelMaskDirectionVectorVariable = m_pEffect->GetVariableByName("m_FresnelMaskDirection")->AsVector();
	if(!m_pFresnelMaskDirectionVectorVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_FresnelMaskDirection Failed"),LogLevel::Error);
	}
	m_pColorFresnelVectorVariable = m_pEffect->GetVariableByName("m_ColorFresnel")->AsVector();
	if(!m_pColorFresnelVectorVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_ColorFresnel Failed"),LogLevel::Error);
	}
	//get opacity map effect variables
	m_pOpacityTextureMapVariable = m_pEffect->GetVariableByName("m_TextureOpacity")->AsShaderResource();
	if(!m_pOpacityTextureMapVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_TextureOpacity Failed"),LogLevel::Error);
	}
	m_pOpacityMapVariable = m_pEffect->GetVariableByName("m_bOpacityMap")->AsScalar();
	if(!m_pOpacityMapVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_bOpacityMap Failed"),LogLevel::Error);
	}
	m_pOpacityVariable = m_pEffect->GetVariableByName("m_Opacity")->AsScalar();
	if(!m_pOpacityVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_Opacity Failed"),LogLevel::Error);
	}
	//panning stuf
	m_pPanningAlpha1 = m_pEffect->GetVariableByName("m_PanAlpha1")->AsShaderResource();
	if(!m_pOpacityTextureMapVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_PanAlpha1 Failed"),LogLevel::Error);
	}
	m_pPanningAlpha2 = m_pEffect->GetVariableByName("m_PanAlpha2")->AsShaderResource();
	if(!m_pOpacityTextureMapVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_PanAlpha2 Failed"),LogLevel::Error);
	}
	m_pUsePanningVariable = m_pEffect->GetVariableByName("m_bPanning")->AsScalar();
	if(!m_pUsePanningVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_bPanning Failed"),LogLevel::Error);
	}
	m_pPanningSpeed1Variable = m_pEffect->GetVariableByName("m_PanSpeed1")->AsScalar();
	if(!m_pPanningSpeed1Variable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_PanSpeed1 Failed"),LogLevel::Error);
	}
	m_pPanningSpeed2Variable = m_pEffect->GetVariableByName("m_PanSpeed2")->AsScalar();
	if(!m_pPanningSpeed2Variable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_PanSpeed2 Failed"),LogLevel::Error);
	}
	//Timevalue
	m_pTimeValueVariable = m_pEffect->GetVariableByName("m_Time")->AsScalar();
	if(!m_pTimeValueVariable->IsValid())
	{
		Logger::Log(_T("Getting EffectName m_Time Failed"),LogLevel::Error);
	}
}

void UberShaderMaterial::UpdateEffectVariables(ModelComponent* modelComponent)
{
	HR(m_pLightsEnableVariable->SetBool(m_bMultipleLights));

	//DiffuseVariables
	if(m_bDiffuseTexture && m_pDiffuseResourceView != nullptr)
	{
		HR(m_pDiffuseMapVariabele->SetResource(m_pDiffuseResourceView));
	}
	HR(m_pDiffuseTextureVariable->SetBool(m_bDiffuseTexture));
	HR(m_pColorDiffuseVectorVariable->SetFloatVector(m_v4ColorDiffuse));
	HR(m_pDiffuseLerpControlVariable->SetFloat(m_DiffuseLerpControl));
	HR(m_pHalfLambertVariable->SetBool(m_bHalfLambert && ENABLE_HALF_LAMBERT));
	HR(m_pLambertPowerVariable->SetFloat(m_LambertPower));

	//SpecularVariables
	if(m_bSpecularLevelTexture && m_pSpecularResourceView != nullptr)
		HR(m_pSpecularMapVariable->SetResource(m_pSpecularResourceView));
	HR(m_pSpecularLevelTextureVariable->SetBool(m_bSpecularLevelTexture && ENABLE_SPECULAR));
	HR(m_SpecularVectorVariable->SetFloatVector(m_v4ColorSpecular));
	HR(m_pShininessVariable->SetInt(m_Shininess));
	//AmbientVariables
	HR(m_pAmbientIntensityVariable->SetFloat(m_AmbientIntensity));
	HR(m_pAmbientVectorVariable->SetFloatVector(m_v4ColorAmbient));
	HR(m_pAmbientLerpControlVariable->SetFloat(m_AmbientLerpControl));
	//NormalVariables
	if(m_bNormalMapping && m_pNormalResourceView != nullptr)
		HR(m_pNormalMapVariable->SetResource(m_pNormalResourceView));
	HR(m_pFlipGreenChannelVariable->SetBool(m_bFlipGreenChannel));
	HR(m_pNormalMappingVariable->SetBool(m_bNormalMapping && ENABLE_NORMAL));
	//Environment Variables
	HR(m_pEnvironmentVariable->SetBool(m_bEnvironmentMapping && ENABLE_ENVIRONMENT));
	HR(m_pRefractionVariable->SetBool(m_bRefraction));
	if(m_bEnvironmentMapping && m_pEnvironmentResourceView != nullptr)
		HR(m_pEnvironmentMapCubeVariable->SetResource(m_pEnvironmentResourceView));
	HR(m_pReflectionStrengthVariable->SetFloat(m_ReflectionStrength));
	HR(m_pRefractionStrengthVariable->SetFloat(m_RefractionStrength));
	HR(m_pRefractionLerpControlVariable->SetFloat(m_RefractionLerpControl));
	HR(m_pRefractionIndexVariable->SetFloat(m_RefractionIndex));
	//SpecularModelsVariables
	HR(m_pSpecularBlinnVariable->SetBool(m_bSpecularBlinn));
	HR(m_pSpecularPhongVariable->SetBool(m_bSpecularPhong));
	HR(m_pSpecularLyonVariable->SetBool(m_bSpecularLyon));
	HR(m_pSpecularCookTorranceVariable->SetBool(m_bSpecularCookTorrance));
	HR(m_pCookTorranceLerpControlVariable->SetFloat(m_CookTorranceLerpControl));
	HR(m_pRoughnessMaterialVariable->SetFloat(m_RoughnessMaterial));
	HR(m_pFresnelStrengthVariable->SetFloat(m_FresnelStrength));
	HR(m_pPhongLerpControlVariable->SetFloat(m_PhongLerpControl));
	HR(m_pLyonLerpControlVariable->SetFloat(m_LyonLerpControl));
	//FresnelFalloffVariables
	HR(m_pFresnelFalloffVariable->SetBool(m_bFresnelFaloff && ENABLE_FRESNEL_FALLOF));
	HR(m_pFresnelPowerVariable->SetFloat(m_FresnelPower));
	HR(m_pFresnelMultiplierVariable->SetFloat(m_FresnelMultiplier));
	HR(m_pFresnelHardnessVariable->SetFloat(m_FresnelHardness));
	HR(m_pFresnelFalloffEnvLerpControlVariable->SetFloat(m_FresnelFaloffEnvLerpControl));
	HR(m_pFresnelMaskDirectionVectorVariable->SetFloatVector(m_FresnelMaskDirection));
	HR(m_pColorFresnelVectorVariable->SetFloatVector(m_ColorFresnel));
	//OpacityMapVariables
	HR(m_pOpacityMapVariable->SetBool(m_bOpacityMap && ENABLE_OPACITY));
	HR(m_pOpacityVariable->SetFloat(m_Opacity));
	if(m_bOpacityMap && m_pOpacityResourceView != nullptr)
		HR(m_pOpacityTextureMapVariable->SetResource(m_pOpacityResourceView));
	//panning
	HR(m_pUsePanningVariable->SetBool(m_bUsePanning));
	if(m_bUsePanning)
	{
		if(m_pPanningAlpha1RV)
		{
			HR(m_pPanningAlpha1->SetResource(m_pPanningAlpha1RV));
			SafeRelease(m_pPanningAlpha1RV);
		}
		if(m_pPanningAlpha2RV)
		{
			HR(m_pPanningAlpha2->SetResource(m_pPanningAlpha2RV));
			SafeRelease(m_pPanningAlpha2RV);
		}
		HR(m_pPanningSpeed1Variable->SetFloat(m_PanningSpeed1));
		HR(m_pPanningSpeed2Variable->SetFloat(m_PanningSpeed2));
		HR(m_pTimeValueVariable->SetFloat(m_TimeValue));
	}
}

void UberShaderMaterial::SetLightDirection(const D3DXVECTOR3 &direction)
{
	D3DXVec3Normalize(&m_LightDirection,&direction);
}

void UberShaderMaterial::EnableMultipleLights(bool enable)
{
	m_bMultipleLights = true;
}

//==================================================== Setting Functions
//Diffuse Setting Set/Get
void UberShaderMaterial::SetDiffuseTexture(const tstring& filename)
{
	tstringstream strstr;
	strstr << _T("./Resources/Lemmings3D/textures/") << filename;
	m_pDiffuseResourceView = ContentManager::Load<ID3D10ShaderResourceView>(strstr.str()); 
	EnableDiffuseTexture(true);
}
void UberShaderMaterial::SetDiffuseColor(const D3DXVECTOR3 &color)
{
	m_v4ColorDiffuse = D3DXVECTOR4(color);
}
void UberShaderMaterial::SetDiffuseLerpControl(float lerpControl)
{
	m_DiffuseLerpControl = lerpControl;
}
void UberShaderMaterial::EnableDiffuseTexture(bool enable)
{
	m_bDiffuseTexture = enable;
}

void UberShaderMaterial::EnableHalfLambert(bool enable)
{
	m_bHalfLambert = enable;
}

void UberShaderMaterial::SetLambertPower(float power)
{
	m_LambertPower = power;
}

//Specular Setting Set/Get
void UberShaderMaterial::SetSpecularTexture(const tstring& filename)
{
	tstringstream strstr;
	strstr << _T("./Resources/Lemmings3D/textures/") << filename;
	m_pSpecularResourceView = ContentManager::Load<ID3D10ShaderResourceView>(strstr.str()); 
	EnableSpecularTexture(true);
}
void UberShaderMaterial::SetSpecularColor(const D3DXVECTOR3 &color)
{
	m_v4ColorSpecular = D3DXVECTOR4(color);
}
void UberShaderMaterial::SetShininess(int s)
{
	m_Shininess = s;
}
void UberShaderMaterial::EnableSpecularTexture(bool enable)
{
	m_bSpecularLevelTexture = enable;
}

//Ambient Setting Set/Get
void UberShaderMaterial::SetAmbientColor(const D3DXVECTOR3 &color)
{
	m_v4ColorAmbient = D3DXVECTOR4(color);
}
void UberShaderMaterial::SetAmbientIntensity(float intensity)
{
	m_AmbientIntensity = intensity;
}
void UberShaderMaterial::SetAmbientLerpControl(float lerpControl)
{
	m_AmbientLerpControl = lerpControl;
}

//Normal Setting Set/Get
void UberShaderMaterial::SetNormalTexture(const tstring& filename)
{
	tstringstream strstr;
	strstr << _T("./Resources/Lemmings3D/textures/") << filename;
	m_pNormalResourceView = ContentManager::Load<ID3D10ShaderResourceView>(strstr.str()); 
	EnableNormalTexture(true);
}
void UberShaderMaterial::SetFlipGreenChannel(bool flipGreenChannel)
{
	m_bFlipGreenChannel = flipGreenChannel;
}
bool UberShaderMaterial::GetFlipGreenChannel()
{
	return m_bFlipGreenChannel;
}
void UberShaderMaterial::EnableNormalTexture(bool enable)
{
	m_bNormalMapping = enable;
}
bool UberShaderMaterial::GetStateNormalTexture()
{
	return m_bNormalMapping;
}

//Environment Setting Set/Get
void UberShaderMaterial::SetEnvironmentTexture(const tstring& filename)
{
	tstringstream strstr;
	strstr << _T("./Resources/Lemmings3D/textures/") << filename;
	m_pEnvironmentResourceView = ContentManager::Load<ID3D10ShaderResourceView>(strstr.str()); 
	EnableEnvironmentMapping(true);
}
void UberShaderMaterial::EnableEnvironmentMapping(bool enable)
{
	m_bEnvironmentMapping = enable;
	ID3D10EffectScalarVariable * diffVar = m_pEnvironmentVariable;
}
void UberShaderMaterial::EnableRefraction(bool enable)
{
	m_bRefraction = enable;
	ID3D10EffectScalarVariable * diffVar = m_pRefractionVariable;
}
void UberShaderMaterial::SetReflectionStrength(float strength)
{
	m_ReflectionStrength = strength;
}
void UberShaderMaterial::SetRefractionStrength(float strength)
{
	m_RefractionStrength = strength;
}
void UberShaderMaterial::SetRefractionLerpControl(float lerpControl)
{
	m_RefractionLerpControl = lerpControl;
}
void UberShaderMaterial::SetRefractionIndex(float refractionIndex)
{
	m_RefractionIndex = refractionIndex;
}

//Specular Models Setting Set/Get
void UberShaderMaterial::SetSpecularModel(SpecularModel spec)
{
	switch(spec)
	{
	case Blinn:
		m_bSpecularBlinn = true;
		break;
	case Phong:
		m_bSpecularPhong = true;
		break;
	case CookTorrance:
		m_bSpecularCookTorrance = true;
		break;
	case Lyon:
		m_bSpecularLyon = true;
		break;
	}
}
void UberShaderMaterial::SetSpecularModel(SpecularModel spec, float lerpControl)
{
	switch(spec)
	{
	case Blinn:
		m_bSpecularBlinn = true;
		break;
	case Phong:
		m_bSpecularPhong = true;
		m_PhongLerpControl = lerpControl;
		break;
	case CookTorrance:
		m_bSpecularCookTorrance = true;
		m_CookTorranceLerpControl = lerpControl;
		break;
	case Lyon:
		m_bSpecularLyon = true;
		m_LyonLerpControl = lerpControl;
		break;
	}
}
void UberShaderMaterial::ForceSpecularModel(SpecularModel spec)
{
	switch(spec)
	{
	case Blinn:
		m_bSpecularBlinn = true;
		m_bSpecularPhong = false;
		m_bSpecularCookTorrance = false;
		m_bSpecularLyon = false;
		break;
	case Phong:
		m_bSpecularBlinn = false;
		m_bSpecularPhong = true;
		m_bSpecularCookTorrance = false;
		m_bSpecularLyon = false;
		break;
	case CookTorrance:
		m_bSpecularBlinn = false;
		m_bSpecularPhong = false;
		m_bSpecularCookTorrance = true;
		m_bSpecularLyon = false;
		break;
	case Lyon:
		m_bSpecularBlinn = false;
		m_bSpecularPhong = false;
		m_bSpecularCookTorrance = false;
		m_bSpecularLyon = true;
		break;
	}
}
void UberShaderMaterial::SetRoughnessMaterial(float roughnessMaterial)
{
	m_RoughnessMaterial = roughnessMaterial;
}
void UberShaderMaterial::SetFresnelStrength(float strength)
{
	m_FresnelStrength = strength;
}
//Fresnel Setting Set/Get
void UberShaderMaterial::EnableFresnelFaloff(bool enable)
{
	m_bFresnelFaloff = enable;
}
void UberShaderMaterial::SetFresnelPower(float power)
{
	m_FresnelPower = power;
}
void UberShaderMaterial::SetFresnelMultiplier(float multiplier)
{
	m_FresnelMultiplier = multiplier;
}
void UberShaderMaterial::SetFresnelHardness(float hardness)
{
	m_FresnelHardness = hardness;
}
void UberShaderMaterial::SetFresnelLerpControl(float lerpControl)
{
	m_FresnelFaloffEnvLerpControl = lerpControl;
}
void UberShaderMaterial::SetFresnelMaskDirection(const D3DXVECTOR3 &maskDirection)
{
	m_FresnelMaskDirection = maskDirection;
}
void UberShaderMaterial::SetFresnelColor(const D3DXVECTOR3 &color)
{
	m_ColorFresnel = color;
}

//Opacity Setting Set/Get
void UberShaderMaterial::SetOpacity(float opacity)
{
	m_Opacity = opacity;
}
void UberShaderMaterial::SetOpacityTexture(const tstring& filename)
{
	tstringstream strstr;
	strstr << _T("./Resources/Lemmings3D/textures/") << filename;
	m_pOpacityResourceView = ContentManager::Load<ID3D10ShaderResourceView>(strstr.str()); 
	EnableOpacityTexture(true);
}
void UberShaderMaterial::EnableOpacityTexture(bool enable)
{
	m_bOpacityMap = enable;
}

//Panning Set
void UberShaderMaterial::CreatePanning(float panSpeed, const tstring& alphaMask)
{
	m_bUsePanning = true;
	m_PanningSpeed1 = panSpeed;
	tstringstream strstr;
	strstr << _T("./Resources/Lemmings3D/textures/") << alphaMask;
	m_pPanningAlpha1RV = ContentManager::Load<ID3D10ShaderResourceView>(strstr.str()); 
}

void UberShaderMaterial::CreatePanning(float panSpeed1, float panSpeed2, const tstring& alphaMask1, const tstring& alphaMask2)
{
	m_bUsePanning = true;
	tstringstream strstr;
	strstr << _T("./Resources/Lemmings3D/textures/") << alphaMask1;
	m_pPanningAlpha1RV = ContentManager::Load<ID3D10ShaderResourceView>(strstr.str()); 
	strstr.str(_T(""));
	strstr << _T("./Resources/Lemmings3D/textures/") << alphaMask2;
	m_pPanningAlpha2RV = ContentManager::Load<ID3D10ShaderResourceView>(strstr.str()); 
}

void UberShaderMaterial::UpdatePanning1(float speed)
{
	m_PanningSpeed1 = speed;
}

void UberShaderMaterial::UpdatePanning2(float speed)
{
	m_PanningSpeed2 = speed;
}

//Time Update
void UberShaderMaterial::UpdateTime(float time)
{
	m_TimeValue += time;
}

void UberShaderMaterial::EnableGlobalSpecular(bool enable)
{
	ENABLE_SPECULAR = enable;
}

void UberShaderMaterial::EnableGlobalNormal(bool enable)
{
	ENABLE_NORMAL = enable;
}

void UberShaderMaterial::EnableGlobalEnvironment(bool enable)
{
	ENABLE_ENVIRONMENT = enable;
}

void UberShaderMaterial::EnableGlobalOpacity(bool enable)
{
	ENABLE_OPACITY = enable;
}

void UberShaderMaterial::EnableGlobalHalfLambert(bool enable)
{
	ENABLE_HALF_LAMBERT = enable;
}

void UberShaderMaterial::EnableGlobalFresnelFallof(bool enable)
{
	ENABLE_FRESNEL_FALLOF = enable;
}

bool UberShaderMaterial::ENABLE_SPECULAR = true;
bool UberShaderMaterial::ENABLE_NORMAL = true;
bool UberShaderMaterial::ENABLE_ENVIRONMENT = true;
bool UberShaderMaterial::ENABLE_OPACITY = true;
bool UberShaderMaterial::ENABLE_HALF_LAMBERT = true;
bool UberShaderMaterial::ENABLE_FRESNEL_FALLOF = true;