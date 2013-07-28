//=============================================================================
//// Shader uses position and texture
//=============================================================================
SamplerState samLinear
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Mirror;
    AddressV = Mirror;
};

Texture2D gTexture;

struct VS_INPUT_STRUCT
{
	float3 Pos : POSITION;
    float2 Tex : TEXCOORD;

};
struct PS_INPUT_STRUCT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD1;

};
//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT_STRUCT VS( VS_INPUT_STRUCT input )
{
	PS_INPUT_STRUCT output = (PS_INPUT_STRUCT)0;
	//Fixme

	return output;
}
//--------------------------------------------------------------------------------------
// Pixel XMeshShader
//--------------------------------------------------------------------------------------
float4 PS( PS_INPUT_STRUCT input): SV_Target
{
	//FIXME
	float4 diffuse = gTexture.Sample(samLinear, input.Tex);
	diffuse = dot(diffuse, float3(0.3, 0.59, 0.11));
    return float4(diffuse.rgb, 1.0f );
}

technique10 Grayscale
{
    pass P0
    {          
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS() ) );
    }
}

