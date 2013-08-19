cbuffer cbPerObject{
	float4x4 World : World;
	float4x4 View : View;
	float4x4 ViewInverse;
	float4x4 Projection : Projection;
	float2 UVTile = float2(1,1);
	float2 UVScale = float2(1,1);
};

cbuffer cbPerFrame{

};

Texture2D m_Texture;

SamplerState samLinear
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};

RasterizerState Wireframe
{
	FillMode = WIREFRAME;
};

RasterizerState Solid
{
	FillMode = SOLID;
	CullMode = NONE;
};
BlendState Blend
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

	// Step 1:	convert position into float4 and multiply with matWorldViewProj
	//			the result is the position in homogeneous clip space
	float4x4 matWorld = mul(mul(World, View), Projection);
	output.PosH = mul(float4(input.PosL,1), matWorld);
	
	// Step 2:	rotate the normal: NO TRANSLATION
	//			this is achieved by casting the 4x4 to a 3x3 matrix, 
	//			thus removing the postion row of the matrix
	output.Normal = mul(normalize(input.Normal), (float3x3)matWorld);

	// Step3:	Just copy the texcoord
	output.TexCoord = input.TexCoord;

	return output;
}

float4 PS(VS_OUTPUT input):SV_TARGET
{
	float2 uv = input.TexCoord.xy;
	uv *= UVScale;
	uv += UVTile * UVScale; 
	return m_Texture.Sample(samLinear, uv);
}

technique10 TechSolid
{
	pass one
	{
		SetVertexShader( CompileShader ( vs_4_0, VS() ));
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader ( ps_4_0, PS() ));
		SetRasterizerState(Solid);
		SetBlendState(Blend, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xffffffff);
	}
}