//--------------------------------------------------------------------------------------
//   _____     _______ ____  _     ___  ____  ____    _____ _   _  ____ ___ _   _ _____ 
//  / _ \ \   / / ____|  _ \| |   / _ \|  _ \|  _ \  | ____| \ | |/ ___|_ _| \ | | ____|
// | | | \ \ / /|  _| | |_) | |  | | | | |_) | | | | |  _| |  \| | |  _ | ||  \| |  _|  
// | |_| |\ V / | |___|  _ <| |__| |_| |  _ <| |_| | | |___| |\  | |_| || || |\  | |___ 
//  \___/  \_/  |_____|_| \_\_____\___/|_| \_\____/  |_____|_| \_|\____|___|_| \_|_____|
//
// Overlord Engine v0.44
// Copyright Overlord Brecht Kets & Overlord Thomas Goussaert
// http://www.digitalartsandentertainment.com/
// Student: Glen De Cauwsemaecker
//			2DAE Game Development GD2
//			2012-2013 HOWEST

//reference: 
//	http://msdn.microsoft.com/en-us/library/windows/desktop/bb205052(v=vs.85).aspx
//--------------------------------------------------------------------------------------

float4x4 matTransform : WorldViewProjection;
Texture2D texSprite;
float2 texSize;

SamplerState samPoint
{
    Filter = MIN_MAG_MIP_POINT;
    AddressU = WRAP;
    AddressV = WRAP;
};

RasterizerState BackCulling
{ 
    CullMode = BACK; 
};

BlendState EnableBlending
{
	BlendEnable[0] = TRUE;
	SrcBlend = SRC_ALPHA;
	DestBlend = INV_SRC_ALPHA;
};

DepthStencilState DisableDepth
{
	DepthEnable = FALSE;
};

//SHADER STRUCTS
//**************
struct VS_DATA
{
	float3 Position : POSITION;
	float4 Color: COLOR;
	float2 TexCoord: TEXCOORD0;
	float2 CharSize: TEXCOORD1;
	int Channel: TEXCOORD2;
};

struct GS_DATA
{
	float4 Position : SV_POSITION;
	float4 Color: COLOR;
	float2 TexCoord: TEXCOORD0;
	int Channel: TEXCOORD1;
};

//VERTEX SHADER
//*************
VS_DATA MainVS(VS_DATA input)
{
	return input;
}

//GEOMETRY SHADER
//***************
void CreateVertex(inout TriangleStream<GS_DATA> triStream, float3 pos, float4 col, float2 texCoord, int channel)
{
	GS_DATA newData;
	//Transform the position using the WVP Matrix and assign it to (GS_DATA object).Position (Keep in mind: float3 -> float4)
	newData.Position = mul( float4(pos, 1.f), matTransform);
	newData.TexCoord = texCoord;
	newData.Color = col;
	newData.Channel = channel;
	triStream.Append(newData);
}

[maxvertexcount(4)]
void MainGS(point VS_DATA vertex[1], inout TriangleStream<GS_DATA> triStream)
{
	//TEMP - REMOVE THIS
	// GS_DATA temp = (GS_DATA)0;
	// triStream.Append(temp);
	
	//VERTEX 1 (using input without offset)
	CreateVertex(triStream, vertex[0].Position, vertex[0].Color, vertex[0].TexCoord, vertex[0].Channel);
	
	//Calculate texOffset
	float2 ORT = float2(vertex[0].TexCoord.x + vertex[0].CharSize.x / texSize.x, vertex[0].TexCoord.y);
	float2 ORB = float2(vertex[0].TexCoord.x + vertex[0].CharSize.x / texSize.x, vertex[0].TexCoord.y + vertex[0].CharSize.y / texSize.y);
	float2 OLB = float2(vertex[0].TexCoord.x, vertex[0].TexCoord.y + vertex[0].CharSize.y / texSize.y);
	
	//VERTEX 2 [RT]
	CreateVertex(triStream, vertex[0].Position + float3(vertex[0].CharSize.x, 0, 0), vertex[0].Color, ORT, vertex[0].Channel);
	
	//VERTEX 3 [LB]
	CreateVertex(triStream, vertex[0].Position + float3(0, vertex[0].CharSize.y, 0), vertex[0].Color, OLB, vertex[0].Channel);
	
	//VERTEX 4 [RB]
	CreateVertex(triStream, vertex[0].Position + float3(vertex[0].CharSize.x, vertex[0].CharSize.y, 0), vertex[0].Color, ORB, vertex[0].Channel);
}
	
//PIXEL SHADER
//************
float4 MainPS(GS_DATA input) : SV_TARGET {
	return texSprite.Sample(samPoint, input.TexCoord)[input.Channel] * input.Color;	
}

// Default Technique
technique10 Default {

	pass p0 {
		SetRasterizerState(BackCulling);
		SetBlendState(EnableBlending,float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
		SetDepthStencilState(DisableDepth, 0);
		SetVertexShader(CompileShader(vs_4_0, MainVS()));
		SetGeometryShader(CompileShader(gs_4_0, MainGS()));
		SetPixelShader(CompileShader(ps_4_0, MainPS()));
	}
}
