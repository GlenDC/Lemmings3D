cbuffer cbPerObject{
	float4x4 World : World;
	float4x4 View : View;
	float4x4 ViewInverse : ViewInverse;
	float4x4 Projection : Projection;
	float3 vLightDir : DIRECTION;
	float4 color = float4(1,1,1,1);
	float Alpha = 1.0f;
};

Texture2D m_Texture;

SamplerState samLinear
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;// or Mirror or Clamp or Border
    AddressV = Wrap;// or Mirror or Clamp or Border
};

RasterizerState Solid
{
	FillMode = SOLID;
	CullMode = BACK;
};
BlendState EnableBlend
{
	BlendEnable[0] = TRUE;
	SrcBlend = SRC_ALPHA;
    DestBlend = INV_SRC_ALPHA;
};

struct VS_INPUT{
	//iPosH represents the position in Local (object) space
	float3 PosL : POSITION;
	float3 Normal : NORMAL;
	float2 TexCoord : TEXCOORD0;
};

struct VS_OUTPUT{
	//oPosH represents the position in homogeneous clip space
	float4 PosH : SV_POSITION;
	float3 Normal : NORMAL;
	float2 TexCoord : TEXCOORD0;
};

VS_OUTPUT VS(VS_INPUT input){

	VS_OUTPUT output = (VS_OUTPUT)0;

    output.PosH = mul(float4(input.PosL,1.0f), World);
    output.PosH = mul(output.PosH, View);
    output.PosH = mul(output.PosH, Projection);
	
	output.Normal = normalize(input.Normal);

	output.TexCoord = input.TexCoord;

	return output;
}

float4 PS(VS_OUTPUT input):SV_TARGET
{
	float diffStrength = saturate(dot(-input.Normal, vLightDir));
	float4 result = m_Texture.Sample(samLinear, input.TexCoord) * color * diffStrength;
	return float4(result.rgb, Alpha);
}

technique10 TechSolid
{
	pass one
	{
		SetVertexShader( CompileShader ( vs_4_0, VS() ));
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader ( ps_4_0, PS() ));
		SetRasterizerState(Solid);
		SetBlendState(EnableBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xffffffff);
	}
}