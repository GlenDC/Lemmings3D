cbuffer cbPerObject{
	float4x4 World;
	float4x4 View;
	float4x4 ViewInverse;
	float4x4 Projection;
	float3 vLightDir : LightDir;
	float4 color;
};

cbuffer cbPerFrame{

};

RasterizerState Wireframe
{
	FillMode = WIREFRAME;
};

RasterizerState Solid
{
	FillMode = SOLID;
};

BlendState NoBlend
{
	BlendEnable[0] = FALSE;
};

BlendState SrcAlphaBlendingAdd
{
    BlendEnable[0] = TRUE;
    SrcBlend = SRC_ALPHA;
    DestBlend = INV_SRC_ALPHA;
    BlendOp = ADD;
    SrcBlendAlpha = ZERO;
    DestBlendAlpha = ZERO;
    BlendOpAlpha = ADD;
    RenderTargetWriteMask[0] = 0x0F;
};


struct VS_INPUT{
	//iPosH represents the position in Local (object) space
	float3 PosL : POSITION;
	float3 Normal : NORMAL;
	float4 Color : COLOR;
};

struct VS_OUTPUT{
	//oPosH represents the position in homogeneous clip space
	float4 PosH : SV_POSITION;
	float3 Normal : NORMAL;
	float4 Color : COLOR;
};

VS_OUTPUT VS(VS_INPUT input){

	VS_OUTPUT output = (VS_OUTPUT)0;

	float4x4 worldView = mul(World, View);
	float4x4 worldViewProj = mul(worldView, Projection);
	
	// Step 1:	convert position into float4 and multiply with matWorldViewProj
	//			the result is the position in homogeneous clip space
	output.PosH = mul(float4(input.PosL,1), worldViewProj);
	
	// Step 2:	rotate the normal: NO TRANSLATION
	//			this is achieved by casting the 4x4 to a 3x3 matrix, 
	//			thus removing the postion row of the matrix
	output.Normal = normalize(mul(input.Normal, (float3x3)World));

	// Step3:	Just copy the color
	output.Color = input.Color;

	return output;
}

float4 PS(VS_OUTPUT input):SV_TARGET
{
	//return color;
	float diffStrength = saturate(dot(input.Normal, normalize(vLightDir)));
	return float4(color.xyz*diffStrength,color.a);
}

float4 PS_VERTCOL(VS_OUTPUT input):SV_TARGET
{
	//return color;
	float diffStrength = saturate(dot(input.Normal, normalize(vLightDir)));
	
	return float4(input.Color.xyz*diffStrength, input.Color.a);
}

//no diffuse light when rendering wireframe
float4 PSNoNormal(VS_OUTPUT input):SV_TARGET
{
	return color;
}

technique10 TechSolid
{
	pass one
	{
		SetVertexShader( CompileShader ( vs_4_0, VS() ));
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader ( ps_4_0, PS() ));
		SetRasterizerState(Solid);
		SetBlendState(NoBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xffffffff);
	}
}

technique10 TechVertCol
{
	pass one
	{
		SetVertexShader( CompileShader ( vs_4_0, VS() ));
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader ( ps_4_0, PS_VERTCOL() ));
		SetBlendState(SrcAlphaBlendingAdd, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xffffffff);
	}
}

technique10 TechWireframe
{
	pass one
	{
		SetVertexShader( CompileShader ( vs_4_0, VS() ));
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader ( ps_4_0, PSNoNormal() ));
		SetRasterizerState(Wireframe);
	}
}

