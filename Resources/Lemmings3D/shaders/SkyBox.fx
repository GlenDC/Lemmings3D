SamplerState samLinear
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};
TextureCube m_CubeMap;

float4x4 World : World;
float4x4 View : View;
float4x4 ViewInverse : ViewInverse;
float4x4 Projection : Projection;

struct VS_IN
{
	float3 posL : POSITION;
};
struct VS_OUT
{
	float4 posH : SV_POSITION;
	float3 texC : TEXCOORD;
};
//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUT VS( VS_IN vIn )
{

	VS_OUT vOut = (VS_OUT)0;
	vOut.posH  = mul(float4(vIn.posL, 1.0f), World);
    vOut.posH  = mul(vOut.posH , View);
    vOut.posH  = mul(vOut.posH , Projection);

	// use local vertex position as cubemap lookup vector
	vOut.texC = vIn.posL;

	return vOut;
}
//--------------------------------------------------------------------------------------
// Pixel XMeshShader
//--------------------------------------------------------------------------------------
float4 PS( VS_OUT pIn): SV_Target
{
	return m_CubeMap.Sample(samLinear, pIn.texC);
}

RasterizerState NoCull
{
	CullMode = NONE;
};

DepthStencilState LessEqualDSS
{
	DepthFunc = LESS_EQUAL;
};

technique10 Render
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS() ) );
		SetRasterizerState(NoCull);
		SetDepthStencilState(LessEqualDSS,0);
    }
}