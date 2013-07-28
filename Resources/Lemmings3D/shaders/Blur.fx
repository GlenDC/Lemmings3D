Texture2D gTexture;

SamplerState samLinear
{
    Filter = MIN_MAG_MIP_POINT;
    AddressU = Border;
    AddressV = Border;
};

struct VS_INPUT_STRUCT
{
    float3 Pos : POSITION;
	float2 TexCoord : TEXCOORD0;

};
struct PS_INPUT_STRUCT
{
    float4 Pos : SV_POSITION;
	float2 TexCoord : TEXCOORD1;
};

PS_INPUT_STRUCT VS(VS_INPUT_STRUCT input)
{
	PS_INPUT_STRUCT output = (PS_INPUT_STRUCT)0;
	//FIXME
	return output;
}

float4 PS(PS_INPUT_STRUCT input):SV_TARGET
{
	float4 color = gTexture.Sample(samLinear, input.TexCoord);
	
    color += gTexture.Sample(samLinear, input.TexCoord + (0.01));
    color += gTexture.Sample(samLinear, input.TexCoord - (0.01));
    color = color / 3; // Reduce the color to the normal color values

    return float4(color.rgb, 1.0f );
}

technique10 Blur
{
    pass P0
    {          
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS() ) );
    }
}