float4x4 matTransform : WorldViewProjection;

Texture2D texSprite;
SamplerState samLinear
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = WRAP;
    AddressV = WRAP;
};

BlendState EnableBlending 
{     
	BlendEnable[0] = TRUE;
	SrcBlend = SRC_ALPHA;
    DestBlend = INV_SRC_ALPHA;
};

RasterizerState FrontCulling 
{ 
	CullMode = NONE; 
};

struct VS_INPUT
{
	float3 Position : POSITION;
	float4 Color: COLOR;
	float2 TexCoord: TEXCOORD;
};

struct PS_INPUT
{
	float4 Position : SV_POSITION;
	float4 Color: COLOR;
	float2 TexCoord: TEXCOORD;
};

PS_INPUT MainVS(VS_INPUT input){
	
	PS_INPUT output = (PS_INPUT)0;
	
	output.Position = mul(float4(input.Position, 1.0),matTransform);
	output.Color = input.Color;
	output.TexCoord = input.TexCoord;
	
	return output;
}

float4 MainPS(PS_INPUT input) : SV_TARGET {	
	return texSprite.Sample(samLinear, input.TexCoord) * input.Color;	
}

// Default Technique
technique10 Default {
	pass p0 {
		SetRasterizerState(FrontCulling);
		SetBlendState(EnableBlending,float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
		SetVertexShader(CompileShader(vs_4_0, MainVS()));
		SetPixelShader(CompileShader(ps_4_0, MainPS()));
	}
}
