cbuffer cbPerObject{
	float4x4 World : World;
	float4x4 View : View;
	float4x4 ViewInverse;
	float4x4 Projection : Projection;
};

float m_Time : TIME;

Texture2D m_Mask, m_ColorMask;
float3 m_PortalColor;

SamplerState samLinear
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};

RasterizerState Wireframe
{
	FillMode = WIREFRAME;
};

RasterizerState Solid
{
	FillMode = SOLID;
	CullMode = NONE;
};
BlendState Blend
{
    BlendEnable[0] = TRUE;
    SrcBlend = SRC_ALPHA;
    DestBlend = INV_SRC_ALPHA;
};

struct VS_INPUT{
	//iPosH represents the position in Local (object) space
	float3 PosL : POSITION;
	float3 Normal : NORMAL;
	float2 TexCoord : TEXCOORD0;
};

struct VS_OUTPUT{
	//oPosH represents the position in homogeneous clip space
	float4 PosH : SV_POSITION;
	float3 Normal : NORMAL;
	float2 TexCoord : TEXCOORD0;
};

VS_OUTPUT VS(VS_INPUT input){

	VS_OUTPUT output = (VS_OUTPUT)0;

	// Step 1:	convert position into float4 and multiply with matWorldViewProj
	//			the result is the position in homogeneous clip space
	float4x4 matWorld = mul(mul(World, View), Projection);
	output.PosH = mul(float4(input.PosL,1), matWorld);
	
	// Step 2:	rotate the normal: NO TRANSLATION
	//			this is achieved by casting the 4x4 to a 3x3 matrix, 
	//			thus removing the postion row of the matrix
	output.Normal = mul(normalize(input.Normal), (float3x3)matWorld);

	// Step3:	Just copy the texcoord
	output.TexCoord = input.TexCoord;

	return output;
}

float4 PS(VS_OUTPUT input):SV_TARGET
{
	float time = m_Time + 1000.0f;
	float2 uv = input.TexCoord.xy;
	float2 or_uv = input.TexCoord.xy;
	
	float4 result = float4(1,1,1,1);
	result *= m_Mask.Sample(samLinear, uv).r;
	
	float scale_shift_a = (time % 5) * 10; 
	
	float4 color = float4(m_PortalColor.rgb * m_ColorMask.Sample(samLinear, uv).r, 1);
	
	result *= color;
	
	float4 final_result = result;
	
	result.r *= m_Mask.Sample( samLinear , uv + (scale_shift_a/100)).r; 
	result.g *= m_Mask.Sample( samLinear , uv + (scale_shift_a/200)).g; 
	result.b *= m_Mask.Sample( samLinear , uv + (scale_shift_a/300)).b;
	result.a *= m_Mask.Sample( samLinear , uv + (scale_shift_a/400)).b;
	
	if (color.r<0.2 || color.r>0.9) final_result.r *= 0.25f; 
	else final_result.r *= 1.25f;
	if (color.g<0.2 || color.g>0.9) final_result.g *= 0.25f; 
	else final_result.g *= 1.25f;
	if (color.b<0.2 || color.b>0.9) final_result.b  *= 0.25f; 
	else final_result.b *= 1.25f;
	
	final_result = final_result + (final_result * result) * 0.1;
	
	//final_result += m_Mask.Sample(samLinear, uv + (0.01)) * float4(m_PortalColor,1);
    //final_result += m_Mask.Sample(samLinear, uv - (0.01)) * float4(m_PortalColor,1);
    //final_result = final_result / 3; // Reduce the color to the normal color values
	
	float2 ori = float2(0.5,0.5);
	//Twirl Cyclone
	uv = uv - ori; // Translate eye to origin

    // Convert to polars
    float r = length(uv);
    float theta = atan2(uv.y, uv.x);
    
    // Calculate finite-range influence according to distance from the eye
    float proximity = 1 - saturate(length(uv) / 0.5f);
    proximity = pow(proximity * cos(theta + time), 1.0f);
    
    // Lerp for rotation
    float rotation = lerp(0, r * (sin(200.0f+time)-5.0f) * 5.0f, proximity);
    
    // Perform rotation
    theta += rotation;
    
    // Convert back to Cartesian
    uv.x = r * cos(theta * time * 0.25);
    uv.y = r * sin(theta * time * 0.25);

    float2 tex_out = uv.xy / 2.5f + ori; // Translate back
    float4 final_mask = m_Mask.Sample(samLinear, tex_out); // And finally sample
    float4 final_mask_color = m_ColorMask.Sample(samLinear, tex_out); // And finally sample
	
	final_result *= final_mask.r * final_mask_color.r;
	final_result *= float4(m_PortalColor,1.0f);
	
	float4 the_result = final_result;
	
	float clip_value = 0.05f;
	if(input.TexCoord.x < clip_value || input.TexCoord.y < clip_value
	|| input.TexCoord.x > 1.0f - clip_value || input.TexCoord.y > 1.0f - clip_value)
	{
		final_result.a = 0;
	}
	
	float4 funk_result = float4(final_result.rgb,final_result.a + ((r * 2.5f) % 5.0) );
	funk_result *= m_Mask.Sample(samLinear,input.TexCoord).r;
	
	funk_result += final_result; 
	
	float4 result_mask = m_Mask.Sample(samLinear, tex_out); // And finally sample
    float4 result_mask_color = m_ColorMask.Sample(samLinear, tex_out); // And finally sample
	
	funk_result *= result_mask * result_mask_color;
	float4 da_result = the_result * 0.2f + the_result * funk_result;
	da_result.a *= ((da_result.g + da_result.r + da_result.b) / 3 + da_result.a) / 2.0;
	
	da_result *= final_result;
	
    float rotation_2 = lerp(0, r * cos(theta * time * 20.0f) , proximity);
    
	float2 uv_2 = input.TexCoord.xy;
    float theta_2 = atan2(uv_2.y, uv_2.x);
    // Perform rotation
    theta_2 *= rotation;
	//Twirl Cyclone
	uv_2 = uv_2 + ori; // Translate eye to origin
    
    // Convert back to Cartesian
    uv_2.x = r * cos(theta_2 * time * -0.25f);
    uv_2.y = r * sin(theta_2 * time * -0.25f);
	
	float4 di_result = da_result * 0.5;
	di_result += da_result * m_ColorMask.Sample(samLinear, uv_2).r * 10;
	return di_result * 0.25f + m_Mask.Sample(samLinear, or_uv).b * di_result;
}

technique10 TechSolid
{
	pass one
	{
		SetVertexShader( CompileShader ( vs_4_0, VS() ));
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader ( ps_4_0, PS() ));
		SetRasterizerState(Solid);
		SetBlendState(Blend, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xffffffff);
	}
}