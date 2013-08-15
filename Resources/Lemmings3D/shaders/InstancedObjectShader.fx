/////////////
// GLOBALS //
/////////////
float4x4 World : World;
float4x4 View : View;
float4x4 ViewInverse : ViewInverse;
float4x4 Projection : Projection;
Texture2D Texture;

///////////////////
// SAMPLE STATES //
///////////////////
SamplerState SampleType
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};

RasterizerState CullingMode 
{ 
	//todo fix to front
	CullMode = BACK; 
};

BlendState EnableBlending 
{     
	BlendEnable[0] = TRUE;
	SrcBlend = SRC_ALPHA;
    DestBlend = INV_SRC_ALPHA;
};

float3 LightDirection = float3(0.577f, -0.577f, 0.577f);

//////////////
// TYPEDEFS //
//////////////
//The VertexInputType structure now has the third element which will hold the instanced input Position data.

struct VertexInputType
{
    float4 Position : POSITION0;
    float3 Normal : NORMAL0;
    float2 Texture : TEXCOORD0;
    float3 InstancePosition : TEXCOORD1;
	int InstanceID : TEXCOORD2;
};

struct PixelInputType
{
    float4 Position : SV_POSITION;
    float3 Normal : NORMAL0;
    float2 Texture : TEXCOORD0;
	int InstanceID : TEXCOORD1;
};


////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
PixelInputType TextureVertexShader(VertexInputType input)
{
    PixelInputType output;
    
    // Change the Position vector to be 4 units for proper matrix calculations.
    input.Position.w = 1.0f;
	//Here is where we use the instanced Position information to modify the Position of each triangle we are drawing.

    // Update the Position of the vertices based on the data for this particular instance.
    input.Position.x += input.InstancePosition.x;
    input.Position.y += input.InstancePosition.y;
    input.Position.z += input.InstancePosition.z;

    // Calculate the Position of the vertex against the world, view, and projection matrices.
    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);
    
    // Store the texture coordinates for the pixel shader.
    output.Texture = input.Texture;

	// Store the normal
	output.Normal = normalize(input.Normal);

	output.InstanceID = input.InstanceID;
    
    return output;
}


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 TexturePixelShader(PixelInputType input) : SV_Target
{
    float3 textureColor;

	float2 uv = input.Texture;
	uv /= 4;
	uv.y += 0.25 * (input.InstanceID % 4);
	uv.x += 0.50 * (input.InstanceID / 4);
	if(input.Normal.y != 0)
	{
		uv.x += 0.25f;
	}
	
    // Sample the pixel color from the texture using the sampler at this texture coordinate location.
	float diffuseStrength = dot(-input.Normal, LightDirection);
	diffuseStrength += 0.15f;
	diffuseStrength = max(diffuseStrength,0);
	diffuseStrength = min(diffuseStrength,1.0f);
	
    textureColor = Texture.Sample(SampleType,uv).rgb;
	textureColor *= diffuseStrength;
	
	float3 diffColor = abs(input.Normal * 2) + input.Normal;
	diffColor /= 2.0f;
	
	float3 finalColor = lerp(textureColor, diffColor, 0.05f);

    return float4(finalColor,1.0f);
}


////////////////////////////////////////////////////////////////////////////////
// Technique
////////////////////////////////////////////////////////////////////////////////
technique10 TextureTechnique
{
    pass pass0
    {
		SetRasterizerState(CullingMode);
		SetBlendState(EnableBlending,float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
        SetVertexShader(CompileShader(vs_4_0, TextureVertexShader()));
        SetPixelShader(CompileShader(ps_4_0, TexturePixelShader()));
        SetGeometryShader(NULL);
    }
}