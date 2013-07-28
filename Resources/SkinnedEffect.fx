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

const float MAX_BONES = 70;
cbuffer cbPerObject
{
	float4x4 World : World;
	float4x4 View : VIEW;
	float4x4 Projection : PROJECTON;
	float4x4 ViewInverse : VIEWINVERSE;
	float3 vLightDir : DIRECTION;
	// TODO: INSERT TEXTURE AND BONES
	float4x4 matBones[70];
};

Texture2D m_Texture
<
	string UIName = "Diffuse texture";
	string UIWidget = "Texture";
>;

SamplerState samLinear
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;// or Mirror or Clamp or Border
    AddressV = Wrap;// or Mirror or Clamp or Border
};

RasterizerState Solid
{
	FillMode = SOLID;
	CullMode = NONE;
};

BlendState NoBlend
{
	BlendEnable[0] = FALSE;
};

struct VS_INPUT
{
	float3 Position : POSITION;
	float3 Normal : NORMAL;
	float2 TexCoord : TEXCOORD0;
	float4 BoneIndices : BLENDINDICES0; // array of 4 floats
	float4 BoneWeights : BLENDWEIGHTS0; // array of 4 floats
};

struct VS_OUTPUT
{
	float4 Position : SV_POSITION;
	float3 Normal : NORMAL;
	float2 TexCoord : TEXCOORD0;
};

VS_OUTPUT VS_Anim(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	//TODO: TRANSFORM POSITION AND NORMALS USING MAX 4 BONES
	float4 transformedPosition;
	float3 transformedNormal;
	for(int i = 0 ; i < 4 ; ++i)
	{
		if(input.BoneIndices[i] > -1)
		{
			transformedPosition += mul( float4(input.Position, 1.f), matBones[input.BoneIndices[i]])
										* input.BoneWeights[i];
			transformedNormal += mul( input.Normal, (float3x3)matBones[input.BoneIndices[i]])
										* input.BoneWeights[i];
		}		
	}
	transformedPosition.w = 1;
	output.Position = mul(transformedPosition, World);
	output.Position = mul(output.Position, View);
	output.Position = mul(output.Position, Projection);
	output.Position.y -= 4;
	output.Normal = mul(transformedNormal, (float3x3)World);
	output.TexCoord = input.TexCoord;

	return output;
}

float4 PS(VS_OUTPUT input):SV_TARGET
{
	input.Normal = normalize(input.Normal);
	
	// TODO: CALCULATE DIFFUSE
	float diffuseStrength = dot(-input.Normal, vLightDir);
	diffuseStrength = saturate(diffuseStrength);
	
	float3 diffuseColor = m_Texture.Sample( samLinear, input.TexCoord).xyz;
	diffuseColor *= diffuseStrength;
	return float4(diffuseColor,1);
}

technique10 SkinnedAnimationTechnique
{
	pass one
	{
		SetVertexShader( CompileShader ( vs_4_0, VS_Anim() ));
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader ( ps_4_0, PS() ));
		SetRasterizerState(Solid);
		SetBlendState(NoBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xffffffff);
	}
}
