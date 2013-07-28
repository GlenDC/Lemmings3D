cbuffer cbPerObject{
	float4x4 matWorldViewProj : WorldViewProjection;
};

RasterizerState Debug
{
	FillMode = SOLID;
	CullMode = NONE;
};

DepthStencilState NoDepth
{
	DepthEnable = FALSE;
};

BlendState EnableBlending 
{     
	BlendEnable[0] = TRUE;
	SrcBlend = SRC_ALPHA;
    DestBlend = INV_SRC_ALPHA;
};

Texture2D UIMask;

SamplerState samLinear
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;// or Mirror or Clamp or Border
    AddressV = Wrap;// or Mirror or Clamp or Border
};

struct VS_INPUT{
	float3 Pos : POSITION;
	float4 Color : COLOR;
};

struct VS_OUTPUT{
	float4 Pos : SV_POSITION;
	float4 Color : COLOR;
    float4 ScreenPosition : TEXCOORD0;
};

VS_OUTPUT VS(VS_INPUT input){

	VS_OUTPUT output = (VS_OUTPUT)0;

	output.Pos = mul(float4(input.Pos,1), matWorldViewProj);
	output.Color = input.Color;
    output.ScreenPosition = output.Pos;

	return output;
}

float4 PS(VS_OUTPUT input):SV_TARGET
{
	//cull if beyond UI!
	//==================================
	 input.ScreenPosition /=  input.ScreenPosition.w;
    float2 texCoord = 0.5f * (float2(input.ScreenPosition.x,-input.ScreenPosition.y) + 1);
    //allign texels to pixels
    //texCoord -= 0.05f;
	float value = UIMask.Sample( samLinear, texCoord).x;

	//==================================

	return float4(input.Color.rgb, value);
}

technique10 Default
{
	pass one
	{
		SetVertexShader( CompileShader ( vs_4_0, VS() ));
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader ( ps_4_0, PS() ));
		SetRasterizerState(Debug);
		SetDepthStencilState(NoDepth,0);
		SetBlendState(EnableBlending,float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
	}
}

