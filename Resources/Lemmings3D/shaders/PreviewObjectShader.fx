/////////////
// GLOBALS //
/////////////
float4x4 World : World;
float4x4 View : View;
float4x4 ViewInverse : ViewInverse;
float4x4 Projection : Projection;
Texture2D Texture;
int ObjectID;
float3 PreviewPosition;

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
    float3 Position : POSITION0;
    float3 Normal : NORMAL0;
    float2 Texture : TEXCOORD0;
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
    
	//Here is where we use the instanced Position information to modify the Position of each triangle we are drawing.

    // Update the Position of the vertices based on the data for this particular instance.
    input.Position.x += PreviewPosition.x;
    input.Position.y += PreviewPosition.y;
    input.Position.z += PreviewPosition.z;

    // Calculate the Position of the vertex against the world, view, and projection matrices.
    output.Position = mul(float4(input.Position,1.0f), World);
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

    return float4(diffColor,0.5f);
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