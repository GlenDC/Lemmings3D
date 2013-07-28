cbuffer cbPerObject{
	float4x4 matWorld : World;
	float4x4 matWorldViewProj : WorldViewProjection;
	float3 vLightDir : DIRECTION;
	float4x4 m_ViewInv: ViewInverse;
	float4 m_ColorEmissive = float4(1,1,1,1);
	float4 m_ColorAmbient= float4(.8f,.8f,.8f,1.0f);
	float4 m_ColorSpecular = float4(1.0f,1.0f,1.0f,1.0f);
	float4 m_ColorAmbientMax = float4(0.1f,0.1f,0.1f,1.0f);
	int m_Shininess = 5;
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

struct PS_INPUT{
	
	float4 Pos: SV_POSITION;
	float4 Color: COLOR0;
	float2 Lighting: COLOR1;
};

PS_INPUT VS(float3 pos : POSITION, 
float3 normal: NORMAL){
	
	PS_INPUT output = (PS_INPUT)0;
	
	//Transformations
	//Step 1
	float4 position = float4(pos,1);
	
	//Step 2
	float4 worldPosition = mul(position, matWorld);
	
	//Step 3
	float3 tNormal = mul(normal,
					(float3x3)matWorld);
					
	//Step 4
	output.Pos = mul(position, matWorldViewProj);
	
	output.Color = m_ColorEmissive +
					m_ColorAmbientMax *
					m_ColorAmbient;
					
	//Specular
	float3 vn = normalize(worldPosition.xyz -
							m_ViewInv[3].xyz);
	float3 hn = normalize(vn + vLightDir);
	float specularBasis = dot(hn, -tNormal);
	specularBasis = max(specularBasis,0);
	float specularStrength = pow (specularBasis,
									m_Shininess);
							
	output.Lighting.y = specularStrength;
	
	return output;
}

float4 PS(PS_INPUT input):SV_TARGET
{
	float4 resultColor = input.Color;
	resultColor.xyz += m_ColorSpecular * input.Lighting.y;
	
	return resultColor;
}

//no diffuse light when rendering wireframe
float4 PSNoNormal(PS_INPUT input):SV_TARGET
{
	return m_ColorEmissive;
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
