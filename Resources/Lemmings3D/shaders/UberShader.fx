/*
DAE Ubershader Prototype
*Overlord Style*
*Overlord Brecht Kets*
*Overlord Thomas Goussaert*

*Minion Information
*Name   Glen De Cauwsemaecker
*Class  2DAE-DEV2
*Year   2012-2013

**This Shader Contains:

- Diffuse (Texture & Color)
	- Regular Diffuse
	- Ability to use Half Lambert
- Specular
	- Specular Level (Texture & Value)
	- Shininess (Value)
	- Models
		- Blinn
		- Phong
		- Cook Torrance (WIP)
		- Lyon
- Ambient (Color)
- EnvironmentMapping (Cubemap)
	- Reflection
	- Refraction
- Normal (Texture)
- Fresnel Fallof
- Opacity Map
- Multiple Lights (max. 3)


-Techniques
	- WithAlphaBlending
	- WithoutAlphaBlending
	- WithAlphaBlendingFrontCulling
	- WithoutAlphaBlendingFrontCulling
	- WithAlphaBlendingBackCulling
	- WithoutAlphaBlendingBackCulling
	- WireFrame
*/

//Global constants
float eConstant = 2.718281828;
float piConstant = 3.1415926535f;
float gaussConstant  = 100;

//GLOBAL MATRICES
//***************
cbuffer cbPerObject
{
// The World View Projection Matrix
	float4x4 ViewInverse : VIEWINVERSE;
	// The World Matrix
	float4x4 World : WORLD;
	float4x4 View : VIEW;
	float4x4 Projection : PROJECTION;
}

struct Light
{
	float3 pos;
	float range;
	float3 dir;
	float lightType;
	float4 ambient;
	float4 diffuse;
	float4 spec;
	float3 att; // attenuation parameters (a0, a1, a2)
	float pad;
};

const static int gNumLights = 3;
cbuffer cbPerFrame
{
	Light gLight[gNumLights];
}

//STATES
//******
RasterizerState FrontCulling 
{ 
	CullMode = FRONT; 
};

RasterizerState BackCulling 
{ 
	CullMode = BACK; 
};

RasterizerState DisableCulling 
{ 
	CullMode = NONE; 
};

BlendState EnableBlending 
{     
	BlendEnable[0] = TRUE;
	SrcBlend = SRC_ALPHA;
    DestBlend = INV_SRC_ALPHA;
};

RasterizerState Wireframe
{
	FillMode = WireFrame;
	CullMode = Back;
	FrontCounterClockwise = false;
};

//SAMPLER STATES
//**************
SamplerState m_TextureSampler
{
	Filter = MIN_MAG_MIP_LINEAR;
 	AddressU = WRAP;
	AddressV = WRAP;
	AddressW = WRAP;
};

//LIGHT
//*****
float3 m_LightDirection:DIRECTION
<
	string UIName = "Light Direction";
	string Object = "TargetLight";
> = float3(0.577f, 0.577f, 0.577f);

bool m_bUseMultipleLights
<
	string UIName = "Use Multiple Lights";
	string UIWidget = "Bool";
> = false;

//DIFFUSE
//*******
bool m_bDiffuseTexture
<
	string UIName = "Diffuse Texture";
	string UIWidget = "Bool";
> = false;

bool m_bHalfLambert
<
	string UIName = "Use Half Lambert";
	string UIWidget = "Bool";
> = false;

float4 m_ColorDiffuse
<
	string UIName = "Diffuse Color";
	string UIWidget = "Color";
> = float4(1,1,1,1);

Texture2D m_TextureDiffuse
<
	string UIName = "Diffuse Texture";
	string UIWidget = "Texture";
>;

float m_DiffuseLerpControl
<
	string UIName = "Diffuse Lerp Control";
	string UIWidget = "slider";
	float UIMin = 0;
	float UIMax = 1;
	float UIStep = 0.05;
>  = 0.0f;

float m_LambertPower
<
	string UIName = "Lambert Power";
	string UIWidget = "slider";
	float UIMin = 1;
	float UIMax = 10;
	float UIStep = 0.5;
> = 1.0f;

//SPECULAR
//********
float4 m_ColorSpecular
<
	string UIName = "Specular Color";
	string UIWidget = "Color";
> = float4(1,1,1,1);

Texture2D m_TextureSpecularLevel
<
	string UIName = "Specular Level Texture";
	string UIWidget = "Texture";
>;

bool m_bSpecularLevelTexture
<
	string UIName = "Specular Level Texture";
	string UIWidget = "Bool";
> = false;

int m_Shininess<
	string UIName = "Shininess";
	string UIWidget = "Slider";
	float UIMin = 1;
	float UIMax = 100;
	float UIStep = 0.1f;
> = 15;

//AMBIENT
//*******
float4 m_ColorAmbient
<
	string UIName = "Ambient Color";
	string UIWidget = "Color";
> = float4(0,0,0,1);

float m_AmbientIntensity
<
	string UIName = "Ambient Intensity";
	string UIWidget = "slider";
	float UIMin = 0;
	float UIMax = 1;
>  = 0.0f;

float m_AmbientLerpControl
<
	string UIName = "Ambient Lerp Control";
	string UIWidget = "slider";
	float UIMin = 0;
	float UIMax = 1;
	float UIStep = 0.05;
>  = 0.25f;

//NORMAL MAPPING
//**************
bool m_FlipGreenChannel
<
	string UIName = "Flip Green Channel";
	string UIWidget = "Bool";
> = false;

bool m_bNormalMapping
<
	string UIName = "Normal Mapping";
	string UIWidget = "Bool";
> = false;

Texture2D m_TextureNormal
<
	string UIName = "Normal Texture";
	string UIWidget = "Texture";
>;

//ENVIRONMENT MAPPING
//*******************
TextureCube m_CubeEnvironment
<
	string UIName = "Environment Cube";
	string ResourceType = "Cube";
>;

bool m_bEnvironmentMapping
<
	string UIName = "Environment Mapping";
	string UIWidget = "Bool";
> = false;

bool m_bRefraction
<
	string UIName = "Refraction";
	string UIWidget = "Bool";
> = false;

float m_ReflectionStrength<
	string UIName = "Reflection Strength";
	string UIWidget = "slider";
	float UIMin = 0;
	float UIMax = 1;
	float UIStep = 0.1;
>  = 0.0f;

float m_RefractionStrength<
	string UIName = "Refraction Strength";
	string UIWidget = "slider";
	float UIMin = 0;
	float UIMax = 1;
	float UIStep = 0.1;
>  = 0.0f;

float m_RefractionLerpControl<
	string UIName = "Refraction Lerp Control";
	string UIWidget = "slider";
	float UIMin = 0;
	float UIMax = 1;
	float UIStep = 0.05;
>  = 0.25f;

float m_RefractionIndex<
	string UIName = "Refraction Index";
>  = 0.3f;

//SPECULAR MODELS
//***************
bool m_SpecularBlinn
<
	string UIName = "Specular Blinn";
	string UIWidget = "Bool";
> = false;

bool m_SpecularPhong
<
	string UIName = "Specular Phong";
	string UIWidget = "Bool";
> = false;

float m_PhongLerpControl<
	string UIName = "Phong Lerp Control";
	string UIWidget = "slider";
	float UIMin = 0;
	float UIMax = 1;
	float UIStep = 0.1;
>  = 0.5f;

bool m_SpecularCookTorrance
<
	string UIName = "Specular Cook Torrance";
	string UIWidget = "Bool";
> = false;

float m_CookTorranceLerpControl<
	string UIName = "CookTorrance Lerp Control";
	string UIWidget = "slider";
	float UIMin = 0;
	float UIMax = 1;
	float UIStep = 0.1;
>  = 0.5f;

float m_RoughnessMaterial<
	string UIName = "Roughness Material";
	string UIWidget = "slider";
	float UIMin = 0;
	float UIMax = 1;
	float UIStep = 0.05;
>  = 0.2f;

float m_FresnelStrength<
	string UIName = "Fresnel Strength";
	string UIWidget = "slider";
	float UIMin = 0;
	float UIMax = 1;
	float UIStep = 0.05;
>  = 0.01f;

bool m_SpecularLyon
<
	string UIName = "Specular Lyon";
	string UIWidget = "Bool";
> = false;

float m_LyonLerpControl<
	string UIName = "Lyon Lerp Control";
	string UIWidget = "slider";
	float UIMin = 0;
	float UIMax = 1;
	float UIStep = 0.1;
>  = 0.5f;

//**************
// Fresnell Falloff
bool m_bFresnelFallOff
<
	string UIName = "Fresnel Fallof";
	string UIWidget = "Bool";
> = false;

float m_FresnelPower<
	string UIName = "Fresnel Power";
	string UIWidget = "slider";
	float UIMin = 0;
	float UIMax = 15;
	float UIStep = 0.25;
>  = 4.20f;

float m_FresnelMultiplier<
	string UIName = "Fresnel Multiplier";
	string UIWidget = "slider";
	float UIMin = 0;
	float UIMax = 15;
	float UIStep = 0.25;
>  = 4.34f;

float3 m_FresnelMaskDirection<
	string UIName = "Fresnel Mask Direction";
> = float3(0.0f, -1.0f, 0.0f);

float m_FresnelHardness<
	string UIName = "Fresnel Hardness";
	string UIWidget = "slider";
	float UIMin = 0;
	float UIMax = 15;
	float UIStep = 0.23;
>  = 3.25f;

float3 m_ColorFresnel
<
	string UIName = "Fresnel Color";
	string UIWidget = "Color";
> = float3(1,1,1);

float m_FresnelFaloffEnvLerpControl<
	string UIName = "Fresnel Fallof Environment Lerp Control";
	string UIWidget = "slider";
	float UIMin = 0;
	float UIMax = 1;
	float UIStep = 0.05;
>  = 1.0f;

//**************
// Opacity (map)
float m_Opacity<
	string UIName = "Opacity";
	string UIWidget = "slider";
	float UIMin = 0;
	float UIMax = 1;
>  = 1.0f;

bool m_bOpacityMap
<
	string UIName = "Opacity Map";
	string UIWidget = "Bool";
> = false;

Texture2D m_TextureOpacity
<
	string UIName = "Opacity Texture";
	string UIWidget = "Texture";
>;

//***************
// Time Parameter
float m_Time : TIME <
	string UIName = "Time";
	string Object ="Time";
>;

//**************
// Panning
bool m_bPanning
<
	string UIName = "Use Panning";
	string UIWidget = "Bool";
> = false;

float m_PanSpeed1<
	string UIName = "Pan Speed 1";
	string UIWidget = "slider";
	float UIMin = -1;
	float UIMax = 1;
>  = 1.0f;

float m_PanSpeed2<
	string UIName = "Pan Speed 2";
	string UIWidget = "slider";
	float UIMin = -1;
	float UIMax = 1;
>  = 1.0f;

Texture2D m_PanAlpha1
<
	string UIName = "Pan Alpha 1";
	string UIWidget = "Texture";
>;

Texture2D m_PanAlpha2
<
	string UIName = "Pan Alpha 2";
	string UIWidget = "Texture";
>;

//In- and Output structs
// (POS,NOR,TEX,TAN) -> VS -> ( POS,NOR,TEX,TAN ) -> PS
//***************
struct VS_INPUT 
{
	float3 pos: POSITION;	// the position of the vertex
	float3 normal : NORMAL;	// the normal of the vertex
	float2 texCoord : TEXCOORD0; // the texture coordinate of the vertex
	float3 tangent : TANGENT; // the tangent of the vertex
};

struct VS_OUTPUT 
{
	float4 position : SV_POSITION; // the position that was transformed with the 
								   // worldviewrojection matrix. Without this the 
								   // pixel shader cannot function.
	float3 normal : NORMAL;			// the normal rotated in world space.
	float4 worldPosition: COLOR0;
	float2 texCoord : TEXCOORD0;	// the texture coordinate of the vertex.
	float3 tangent : TANGENT;		// the tangent rotated in world space.
};

//[TODO] is this correct?
float CalculateSpecularBlinn(float3 viewDirection, float3 lightDir, float3 normal, float2 texCoord)
{
	/*float3 calculation = (m_LightDirection+viewDirection);
	float3 reflectedVector = reflect(-m_LightDirection, normal);
	float specularStrength = dot(calculation/length(calculation), reflectedVector);
	specularStrength = max(specularStrength, 0);
	specularStrength = pow(specularStrength, m_Shininess);
	float3 specColor = m_ColorSpecular * specularStrength;
	return specColor;*/
	
	float3 hn = normalize(viewDirection + lightDir);
	float specularStrength = dot(normal, -hn);
	specularStrength = saturate(specularStrength);
	specularStrength = pow(specularStrength, m_Shininess);
	
	return specularStrength;
}

float CalculateSpecularPhong(float3 viewDirection, float3 lightDir, float3 normal, float2 texCoord)
{
	float3 reflectedVector = reflect(lightDir, normal);
	float specularStrength = dot(-viewDirection, reflectedVector);
	specularStrength = max(specularStrength, 0);
	specularStrength = pow(specularStrength, m_Shininess);
	return specularStrength;
}

// Source: http://renderman.pixar.com/view/cook-torrance-shader
//[TODO] FIX THE GOD DAMN Cook Torrance Model
float CalculateSpecularCookTorrance(float3 viewDirection, float3 lightDir, float3 normal, float2 texCoord)
{
	float3 Ln = normalize(-lightDir);
	float3 Vn = normalize(-viewDirection);
	float3 H = normalize(Ln+Vn);
	
	float F = pow(1+dot(Vn,normal),m_FresnelStrength);
	
	float NdotV = dot(normal,Vn);
	float NdotH = dot(normal,H);
	float NdotL = dot(normal,Ln);
	float VdotH = dot(Vn,H);
	
	float D;
	float alpha = acos(NdotH);
	
	//microfacet distribution
	D = gaussConstant * exp(-(alpha*alpha)/(m_RoughnessMaterial*m_RoughnessMaterial));
	
	//Geometric attenuation factor
	float G = min(1, min((2*NdotH*NdotV/VdotH), (2*NdotH*NdotL/VdotH)));
	
	//sum contributions
	float specularStrength = (D*F*G)/dot(Vn,H);
	//float specularStrength = (D*F*G)/(4*dot(Vn,normal)*dot(normal,Ln));
	
	specularStrength = max(specularStrength, 0);
	specularStrength = pow(specularStrength, m_Shininess);
	return specularStrength;
}

/*float3 CalculatePixarSpecularCookTorrance(float3 viewDirection, float3 normal, float2 texCoord)
{
	float3 halfVector = -normalize(viewDirection + m_LightDirection);
	
	//beckmanDistributionFactor
	float cosang = dot(halfVector,normal);
	float angbet = acos(cosang);
	float angle = abs((1.0f/piConstant)*angbet);
	
	//float angle = acos((dot(halfVector,normal))/());

	float t = tan(angle)*tan(angle);
	float num = pow(eConstant,t); 
	float denum = m_RoughnessMaterial*m_RoughnessMaterial*pow(cos(angle),4);
	float beckmanDistributionFactor = num/denum;
	
	//fresnel
	float fresnel = pow((1 + dot(viewDirection,normal)),m_FresnelStrength);
	
	//geometricAttenuationTerm
	float G1 = (2*(dot(halfVector,normal))*dot(viewDirection,normal))/(dot(viewDirection,halfVector));
	float G2 = (2*(dot(halfVector,normal))*dot(m_LightDirection,normal))/(dot(viewDirection,halfVector));
	
	float gBuffer = min(1,G1);
	float geometricAttenuationTerm = min(gBuffer,G2);
	
	//all
	float specularStrength = (beckmanDistributionFactor*fresnel*geometricAttenuationTerm)/(dot(viewDirection,halfVector));
	
	//specularStrength = saturate(specularStrength);
	//specularStrength = pow(specularStrength, m_Shininess);
	
	float3 specularColor = m_ColorSpecular * specularStrength;
	
	if (m_bSpecularLevelTexture)
		specularColor *= m_TextureSpecularLevel.Sample(m_TextureSampler,
										texCoord).r;
	
	return specularColor;
}*/

float CalculateSpecularLyon(float3 viewDirection, float3 lightDir, float3 normal, float2 texCoord)
{
	float3 halfVector = normalize(viewDirection + lightDir);
	halfVector += normal;
	float xs = saturate(dot(halfVector,halfVector) * m_Shininess / 2.0f);
	float specularStrength = pow(1 - xs,3);
	return specularStrength;
}

float CalculateSpecular(float3 viewDirection, float3 lightDir, float3 normal, float2 texCoord)
{
	float specular;
	
	if(m_SpecularBlinn)
	{
		specular = CalculateSpecularBlinn(viewDirection, lightDir, normal, texCoord);
	}
	if(m_SpecularPhong)
	{
		float specularPhong = CalculateSpecularPhong(viewDirection, lightDir, normal, texCoord);
		if(m_SpecularBlinn)
			specular = lerp(specularPhong,specular,m_PhongLerpControl);
		else
			specular = specularPhong;
	}
	if(m_SpecularCookTorrance)
	{
		float specularCookTorrance  = CalculateSpecularCookTorrance(viewDirection, lightDir, normal, texCoord);
		if(m_SpecularBlinn || m_SpecularPhong)
			specular = lerp(specularCookTorrance,specular,m_CookTorranceLerpControl);
		else
			specular = specularCookTorrance;
	}
	if(m_SpecularLyon)
	{
		float specularLyon  = CalculateSpecularLyon(viewDirection, lightDir, normal, texCoord);
		if(m_SpecularBlinn || m_SpecularPhong || m_SpecularCookTorrance)
			specular = lerp(specularLyon,specular,m_LyonLerpControl);
		else
			specular = specularLyon;
	}
	return specular;
}

void CalculatePanningNormal(float2 texCoord, inout float3 resultColor)
{
	float alpha1 = m_PanAlpha1.Sample(m_TextureSampler, texCoord).r;
	float alpha2 = m_PanAlpha2.Sample(m_TextureSampler, texCoord).r;
	float aniSpeed = m_Time / 4;
	
	//reset color value to 0
	resultColor *= (1 - (alpha1+alpha2));
	
	float3 newColor = 2.0f *
	m_TextureNormal.Sample(m_TextureSampler,texCoord + aniSpeed*float2(-m_PanSpeed1,0)) - 1;
	resultColor += alpha1 * newColor;
	newColor = 2.0f *
	m_TextureNormal.Sample(m_TextureSampler,texCoord + aniSpeed*float2(m_PanSpeed2,0)) - 1;
	resultColor += alpha2 * newColor;
}

float3 CalculateNormal(float3 tangent, float3 normal, float2 texCoord)
{
	float3 binormal = normalize(cross(tangent, normal));
	float3x3 localAxis = float3x3(tangent, binormal, normal);
	float3 sampledNormal = 2.0f * 
		m_TextureNormal.Sample(m_TextureSampler, texCoord) - 1.0f;
		
	if(m_bPanning)
		CalculatePanningNormal(texCoord, sampledNormal);
		
	if(m_FlipGreenChannel)
		sampledNormal.g = 1 - sampledNormal.g;
	float3 newNormal = mul ( sampledNormal, localAxis );
	return normalize(newNormal);
}

float3 CalculateDiffuse(float3 normal, float3 lightDir, float2 texCoord)
{	
	float diffuseStrength;
	if(m_bHalfLambert)
	{
		diffuseStrength = 0.5f * dot(normal, -lightDir) + 0.5;
		diffuseStrength = pow(diffuseStrength,m_LambertPower);
	}
	else
	{
		diffuseStrength = dot(-normal, lightDir);
		diffuseStrength = saturate(diffuseStrength);
	}
	float3 diffuseColor = m_ColorDiffuse;
	if(m_bDiffuseTexture)
		diffuseColor = lerp(m_TextureDiffuse.Sample( m_TextureSampler, texCoord).xyz,
						diffuseColor,m_DiffuseLerpControl);
	diffuseColor *= diffuseStrength;
	return diffuseColor;
}

float3 CalculateEnvironment(float3 viewDirection, float3 normal, float2 texCoord)
{
	float3 reflectedVector = reflect(viewDirection, normal);
	float3 reflectColor = m_CubeEnvironment.Sample(m_TextureSampler, reflectedVector).xyz;
	reflectColor *= m_ReflectionStrength;
	if(m_bSpecularLevelTexture)
		reflectColor *= m_TextureSpecularLevel.Sample(m_TextureSampler, texCoord).r;
	
	return reflectColor;
}

float3 CalculateRefraction(float3 viewDirection, float3 normal, float3 ambientColor)
{
	float3 refractionVector = refract(viewDirection,normal,m_RefractionIndex);
	float3 refractionColor = m_CubeEnvironment.Sample(m_TextureSampler, refractionVector).xyz + ambientColor;
	refractionColor *= m_RefractionStrength;
	return refractionColor;
}

float3 CalculateFresnelFalloff(float3 normal, float3 viewDirection, float3 enironmentColor)
{
	float3 En = normalize(enironmentColor);
	float3 Vn = normalize(viewDirection);
	float3 Nn = normalize(normal);
	
	//Fresnel
	float fresnel = pow(1 - saturate(abs(dot(Nn,Vn))),m_FresnelPower);
	fresnel = saturate(fresnel) * m_FresnelMultiplier;
	
	//Fresnel Mask
	float fresnelMask = 1 - saturate(dot(m_FresnelMaskDirection,Nn));
	fresnelMask = pow(fresnelMask,m_FresnelHardness);
	
	fresnel *= m_FresnelHardness;
	return fresnel;
}

void ParallelLight(Light L, float3 normal, float3 specular, float3 viewDirection, 
		float3 ambientColor, float3 specularColor, float3 diffuseColor, float2 texCoord, inout float3 resultColor)
{
	float3 newColor = ambientColor * L.ambient;
	newColor += dot(max(dot(normalize(L.dir),normal),0),L.diffuse) * diffuseColor;
	float3 specColor = specular * L.spec;
	if(m_bSpecularLevelTexture)
		specColor *= m_TextureSpecularLevel.Sample(m_TextureSampler, texCoord).rgb;
	newColor += specColor * specularColor;
	resultColor += newColor;
	
}

void PointLight(Light L, float3 normal, float3 specular, float3 viewDirection, float3 ambientColor, 
		float3 specularColor, float3 diffuseColor, float3 position, float2 texCoord, inout float3 resultColor)
{
	if(length(L.pos-position) <= L.range)
	{
		float3 newColor = ambientColor * L.ambient;
		newColor += dot(max(dot(normalize(L.dir),normal),0),L.diffuse) * diffuseColor;
		float3 specColor = specular * L.spec;
		if(m_bSpecularLevelTexture)
			specColor *= m_TextureSpecularLevel.Sample(m_TextureSampler, texCoord).rgb;
		newColor += specColor * specularColor;
		float distance = length(L.pos-position);
		resultColor += newColor / ( L.att[0] + L.att[1] * distance + L.att[2] * pow(distance,2) );
	}
}

void CalculatePanningDiffuse(float3 normal, float3 viewDirection, float2 texCoord, inout float3 resultColor)
{
	float alpha1 = m_PanAlpha1.Sample(m_TextureSampler, texCoord).r;
	float alpha2 = m_PanAlpha2.Sample(m_TextureSampler, texCoord).r;
	float aniSpeed = m_Time / 4;
	
	//reset color value to 0
	resultColor *= (1 - (alpha1+alpha2));
	
	float3 newColor = 
	m_TextureDiffuse.Sample(m_TextureSampler,texCoord + aniSpeed*float2(-m_PanSpeed1,0)).rgb;
	resultColor += alpha1 * newColor;
	newColor = 
	m_TextureDiffuse.Sample(m_TextureSampler,texCoord + aniSpeed*float2(m_PanSpeed2,0)).rgb;
	resultColor += alpha2 * newColor;
}

// The main vertex shader
VS_OUTPUT MainVS(VS_INPUT input) {
	VS_OUTPUT output = (VS_OUTPUT)0;
	float4 position = float4(input.pos,1);
	
	float4x4 wvp = mul(World, View);
	wvp = mul(wvp, Projection);
	
	//Step 1: 	To calculate the position we need to use homogeneeus coordinates.
	//			We transform this position with the World matrix.
	output.position = mul(float4(input.pos,1),wvp);
	//Step 2:	The normal must be rotated with the _World matrix. But not 
	//			translated, because this would after the length of the normal.
	//			The float3x3 cast operation on the '_World' matrix gives us 
	//			only the rortation part of this matrix.
	output.worldPosition = mul(position, World);
	output.normal = mul(normalize(input.normal), (float3x3)World);
	//Step 3:	We pass the texture coordinates.
	output.texCoord = input.texCoord;
	//Step 4:	The tangent must be rotated with the _World matrix, but not 
	//			translated, because this would after the length of the normal.
	//			The float3x3 cast operation on the '_World' matrix gives us
	//			only the rotation part of this matrix.
	output.tangent = mul(normalize(input.tangent), (float3x3)World);
	//Step 5: return output
	return output;
}

// The main pixel shader
float4 MainPS(VS_OUTPUT input) : SV_TARGET {
	input.normal = normalize(input.normal);
	input.tangent = normalize(input.tangent);
	
	float3 viewDirection = normalize(input.worldPosition - ViewInverse[3].xyz);
	
	float3 normal = input.normal;
	if(m_bNormalMapping)
		normal = CalculateNormal(input.tangent,input.normal,input.texCoord);
	
	float3 diffuseColor = CalculateDiffuse(normal, m_LightDirection, input.texCoord);
		
	float3 resultColor = diffuseColor;
	
	float3 specularStrength = CalculateSpecular(viewDirection, m_LightDirection, normal, input.texCoord);
	
	//Panning
	if(m_bPanning)
		CalculatePanningDiffuse(normal, viewDirection, input.texCoord, resultColor);
		
	//Environment
	float3 ambientColor = m_ColorAmbient * m_AmbientIntensity;
	if(m_bEnvironmentMapping)
	{
		float3 reflectColor = CalculateEnvironment(viewDirection, normal, input.texCoord);
		ambientColor = lerp(reflectColor, ambientColor, m_AmbientLerpControl);
	}
	
	//Multiple Lights
	if(m_bUseMultipleLights)
	{
		diffuseColor = ( CalculateDiffuse(normal, gLight[0].dir, input.texCoord)
							+ CalculateDiffuse(normal, gLight[1].dir, input.texCoord)
							+ CalculateDiffuse(normal, gLight[2].dir, input.texCoord) ) / 3;
		//float3 litColor = float3(0,0,0);
		for(int i = 0 ; i < gNumLights ; ++i)
		{
			specularStrength = CalculateSpecular(viewDirection, gLight[i].dir, normal, input.texCoord);
			if( gLight[i].lightType == 1 ) // Parallel
			{
				PointLight(gLight[i], normal, specularStrength, viewDirection, 
							ambientColor, specularStrength * m_ColorSpecular, 
							diffuseColor, 
							input.worldPosition, input.texCoord, resultColor);
			}
			else
			{
				ParallelLight(gLight[i], normal, specularStrength, viewDirection, 
							ambientColor, specularStrength * m_ColorSpecular,
							diffuseColor, 
							input.texCoord, resultColor);
			}
		}
	}
	
	//Refraction
	if(m_bRefraction)
	{
		float3 refractColor = CalculateRefraction(viewDirection,normal,ambientColor);
		refractColor = lerp(refractColor, resultColor, m_RefractionLerpControl);
		resultColor += refractColor;
	}
	
	//Fresnell Fallof
	float3 fresnelFalloffColor = float3(0,0,0);
	if(m_bFresnelFallOff)
	{
		fresnelFalloffColor = CalculateFresnelFalloff(normal,viewDirection, ambientColor);
		if(!m_bEnvironmentMapping)
			fresnelFalloffColor *= m_ColorFresnel;
		else
		{
			fresnelFalloffColor *= 
				lerp(m_ColorFresnel,ambientColor,m_FresnelFaloffEnvLerpControl);
		}
	}
	if(!m_bUseMultipleLights)
	{
		float3 specularColor = specularStrength * m_ColorSpecular;
		if(m_bSpecularLevelTexture)
			specularColor *= m_TextureSpecularLevel.Sample(m_TextureSampler, input.texCoord).r;
		resultColor += specularColor;
		resultColor += ambientColor;
	}
	resultColor += fresnelFalloffColor;
	
	
	//Opacity
	float opacity = m_Opacity;
	if(m_bOpacityMap)
		opacity = m_TextureOpacity.Sample(m_TextureSampler, input.texCoord).r;
	
	return float4(resultColor,opacity);
}
//**********************************
//Techniques DisableCulling
// Default Technique
technique10 WithAlphaBlending {
	pass p0 {
		SetRasterizerState(DisableCulling);
		SetBlendState(EnableBlending,float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
		SetVertexShader(CompileShader(vs_4_0, MainVS()));
		SetPixelShader(CompileShader(ps_4_0, MainPS()));
	}
}

// Default Technique
technique10 WithoutAlphaBlending {
	pass p0 {
		SetRasterizerState(DisableCulling);
		SetVertexShader(CompileShader(vs_4_0, MainVS()));
		SetPixelShader(CompileShader(ps_4_0, MainPS()));
	}
}

//**********************************
//Techniques BackCulling
// Default Technique
technique10 WithAlphaBlendingBackCulling {
	pass p0 {
		SetRasterizerState(BackCulling);
		SetBlendState(EnableBlending,float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
		SetVertexShader(CompileShader(vs_4_0, MainVS()));
		SetPixelShader(CompileShader(ps_4_0, MainPS()));
	}
}

// Default Technique
technique10 WithoutAlphaBlendingBackCulling {
	pass p0 {
		SetRasterizerState(BackCulling);
		SetVertexShader(CompileShader(vs_4_0, MainVS()));
		SetPixelShader(CompileShader(ps_4_0, MainPS()));
	}
}

//**********************************
//Techniques FrontCulling
// Default Technique
technique10 WithAlphaBlendingFrontCulling {
	pass p0 {
		SetRasterizerState(FrontCulling);
		SetBlendState(EnableBlending,float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
		SetVertexShader(CompileShader(vs_4_0, MainVS()));
		SetPixelShader(CompileShader(ps_4_0, MainPS()));
	}
}

// Default Technique
technique10 WithoutAlphaBlendingFrontCulling {
	pass p0 {
		SetRasterizerState(FrontCulling);
		SetVertexShader(CompileShader(vs_4_0, MainVS()));
		SetPixelShader(CompileShader(ps_4_0, MainPS()));
	}
}

// Default Technique
technique10 WireFrame {
	pass p0 {
		SetRasterizerState(Wireframe);
		SetVertexShader(CompileShader(vs_4_0, MainVS()));
		SetPixelShader(CompileShader(ps_4_0, MainPS()));
	}
}