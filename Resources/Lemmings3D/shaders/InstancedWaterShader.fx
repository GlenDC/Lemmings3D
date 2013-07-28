/////////////
// GLOBALS //
/////////////
float4x4 World : World;
float4x4 View : View;
float4x4 ViewInverse : ViewInverse;
float4x4 Projection : Projection;
Texture2D Texture;
float WaterLevel = 0;
float WaterAlpha = 0;

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
    float InstancedHeightLevel : TEXCOORD2;
};

struct PixelInputType
{
    float4 Position : SV_POSITION;
    float3 Normal : NORMAL0;
    float2 Texture : TEXCOORD0;
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
    input.Position.y += input.InstancePosition.y + WaterLevel + input.InstancedHeightLevel;
    input.Position.z += input.InstancePosition.z;

    // Calculate the Position of the vertex against the world, view, and projection matrices.
    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);
    
    // Store the texture coordinates for the pixel shader.
    output.Texture = input.Texture;

	// Store the normal
	output.Normal = normalize(input.Normal);
    
    return output;
}


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 TexturePixelShader(PixelInputType input) : SV_Target
{
    float4 textureColor;


    // Sample the pixel color from the texture using the sampler at this texture coordinate location.
    textureColor = Texture.Sample(SampleType, input.Texture);

	//Diffuse
	float diffuseStrength = dot(-input.Normal, LightDirection);
	diffuseStrength += 0.15f;
	diffuseStrength = max(diffuseStrength,0);
	diffuseStrength = min(diffuseStrength,1.0f);
	//float3 diffColor = float3(0.2f, .07f, 0.4f) * diffuseStrength;
	
	float3 diffColor = abs(input.Normal * 2) + input.Normal;
	diffColor /= 2.0f;

	//float lineWidth = 0.1f;
	//float VNNDot = mul(ViewInverse, input.Normal);
	//float StepResult = step( lineWidth, VNNDot);
	
	//diffColor *= diffColor;
	//diffColor += (lineWidth - StepResult) * float3(1,1,1);//float3(0.3f,0.8f,0.3f);// * _fLineColor;

	float scalar = (1.0f - WaterAlpha) * 0.4f;
    return float4(scalar,scalar,1.0f,1.0f);
}


////////////////////////////////////////////////////////////////////////////////
// Technique
////////////////////////////////////////////////////////////////////////////////
technique10 TextureTechnique
{
    pass pass0
    {
		SetRasterizerState(CullingMode);
        SetVertexShader(CompileShader(vs_4_0, TextureVertexShader()));
        SetPixelShader(CompileShader(ps_4_0, TexturePixelShader()));
        SetGeometryShader(NULL);
    }
}