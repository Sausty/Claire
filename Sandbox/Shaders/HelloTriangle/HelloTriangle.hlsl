struct VS_INPUT
{
	float4 position: POSITION;
	float3 color: COLOR;
};

struct VS_OUTPUT
{
	float4 position: SV_POSITION;
	float3 color: COLOR;
};

struct PS_INPUT
{
	float4 position: SV_POSITION;
	float3 color: COLOR;
};

cbuffer constant : register(b0)
{
	float4x4 ModelMatrix;
	float4x4 ViewMatrix;
	float4x4 ProjectionMatrix;
};

VS_OUTPUT VSMain(VS_INPUT input)
{
	VS_OUTPUT output;

	output.position = mul(input.position, ModelMatrix);
	output.position = mul(output.position, ViewMatrix);
	output.position = mul(output.position, ProjectionMatrix);
	output.color = input.color;

	return output;
}

float4 PSMain(PS_INPUT input) : SV_Target
{
	return float4(input.color, 1.0);
}