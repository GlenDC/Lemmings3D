//************
// VARIABLES *
//************
cbuffer cbPerObject
{
	float4x4 m_MatrixWorldViewProj : WORLDVIEWPROJECTION;
	float4x4 m_MatrixWorld : WORLD;
	float3 m_LightDir={0.2f,-1.0f,0.2f};
	float3 m_Color=(1.0f,1.0f,1.0f);
	float m_SpikeHeight=5.0f;
	float m_Negative = 1;
}

RasterizerState FrontCulling 
{ 
	CullMode = NONE; 
};

SamplerState samLinear
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;// of Mirror of Clamp of Border
    AddressV = Wrap;// of Mirror of Clamp of Border
};

Texture2D m_TextureDiffuse;

//**********
// STRUCTS *
//**********
struct VS_DATA
{
	float3 Position : POSITION;
	float3 Normal : NORMAL;
    float2 TexCoord : TEXCOORD;
};

struct GS_DATA
{
	float4 Position : SV_POSITION;
	float3 Normal : NORMAL;
	float2 TexCoord : TEXCOORD0;
};

float rand(float2 co){
      return 0.5+(frac(sin(dot(co.xy ,float2(12.9898,78.233))) * 43758.5453))*0.5;
}

//****************
// VERTEX SHADER *
//****************
VS_DATA MainVS(VS_DATA vsData)
{
	//Step 1.
	//Delete this transformation code and just return the VS_DATA parameter (vsData)
	//Don't forget to change the return type!
	
	return vsData;
}

//******************
// GEOMETRY SHADER *
//******************
void CreateVertex(inout TriangleStream<GS_DATA> triStream, float3 pos, float3 normal, float2 texCoord)
{
	//Step 1. Create a GS_DATA object
	GS_DATA newData;
	//Step 2. Transform the position using the WVP Matrix and assign it to (GS_DATA object).Position (Keep in mind: float3 -> float4)
	newData.Position = mul( float4(pos, 1.f), m_MatrixWorldViewProj);
	//Step 3. Transform the normal using the World Matrix and assign it to (GS_DATA object).Normal (Only Rotation, No translation!)
	newData.Normal = mul( normal, (float3x3)m_MatrixWorld);
	//Step 4. Assign texCoord to (GS_DATA object).TexCoord
	newData.TexCoord = texCoord;
	//Step 5. Append (GS_DATA object) to the TriangleStream parameter (TriangleStream::Append(...))
	triStream.Append(newData);
}


[maxvertexcount(6)]
void SpikeGenerator(triangle VS_DATA vertices[3], inout TriangleStream<GS_DATA> triStream)
{
	//Use these variable names
	float3 basePoint, top, left, right, spikeNormal;

	//Step 1. Calculate The basePoint
	basePoint = (vertices[0].Position + vertices[1].Position + vertices[2].Position)/3;
	//Step 2. Calculate The normal of the basePoint
	float3 basePointNormal = (vertices[0].Normal + vertices[1].Normal + vertices[2].Normal)/3;
	//Step 3. Calculate The Spike's Top Position
	top = basePoint + (m_SpikeHeight * basePointNormal);
	//Step 4. Calculate The Left And Right Positions
	float3 spikeDirection = (vertices[2].Position - vertices[0].Position) * m_SpikeHeight / 2.0f * rand(vertices[0].TexCoord);
	left = basePoint - spikeDirection;
	right = basePoint + spikeDirection;
	//Step 5. Calculate The Normal of the spike
	spikeNormal = cross((top-left),(top-right));
	//Step 6. Create The Vertices [Complete code in CreateVertex(...)]
	
	//Create Existing Geometry
	CreateVertex(triStream,vertices[0].Position,vertices[0].Normal,vertices[0].TexCoord);
	CreateVertex(triStream,vertices[1].Position,vertices[1].Normal,vertices[1].TexCoord);
	CreateVertex(triStream,vertices[2].Position,vertices[2].Normal,vertices[2].TexCoord);

	//Restart the strip so we can add another (independent) triangle!
	triStream.RestartStrip();

	//Create Spike Geometry
	CreateVertex(triStream, top, spikeNormal, vertices[0].TexCoord);
	CreateVertex(triStream, left, spikeNormal, vertices[1].TexCoord);
	CreateVertex(triStream, right, spikeNormal, vertices[2].TexCoord);
}

//***************
// PIXEL SHADER *
//***************
float4 MainPS(GS_DATA input) : SV_TARGET 
{
	input.Normal=-normalize(input.Normal);
	float alpha = m_TextureDiffuse.Sample(samLinear,input.TexCoord).a;
	float3 color = m_TextureDiffuse.Sample( samLinear,input.TexCoord ).rgb;
	color = m_Color * rand(input.TexCoord) * m_TextureDiffuse.Sample( samLinear,input.TexCoord ).r;
	float s = max(dot(m_LightDir,input.Normal), 0.4f);
	color.r *= sin(input.TexCoord.x*100)*2; 
	color.g *= cos(input.TexCoord.x*150)*2; 
	color.b *= sin(input.TexCoord.x*50)*2;
	if(m_Negative == 1)
	{
		color = 1 - color;
	}
	else
	{
		if (color.r<0.2 || color.r>0.9) color.r = 0; else color.r = 1.0f; 
		if (color.g<0.2 || color.g>0.9) color.g = 0; else color.g = 1.0f; 
		if (color.b<0.2 || color.b>0.9) color.b = 0; else color.b = 1.0f;
	}
	return float4(color*s,alpha);
}


//*************
// TECHNIQUES *
//*************
technique10 DefaultTechnique 
{
	pass p0 {
		SetRasterizerState(FrontCulling);	
		SetVertexShader(CompileShader(vs_4_0, MainVS()));
		SetGeometryShader(CompileShader(gs_4_0, SpikeGenerator()));
		SetPixelShader(CompileShader(ps_4_0, MainPS()));
	}
}