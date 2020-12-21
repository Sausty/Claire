struct VS_INPUT
{
	float4 position: POSITION;
	float3 color: COLOR;
	float2 texcoord: TEXCOORD;
};

struct VS_OUTPUT
{
	float4 position: SV_POSITION;
	float3 color: COLOR;
	float2 texcoord: TEXCOORD;
};

Texture2D Texture: register(t0);
sampler TextureSampler: register(s0);

struct PS_INPUT
{
	float4 position: SV_POSITION;
	float3 color: COLOR;
	float2 texcoord: TEXCOORD;
};

cbuffer constant : register(b0)
{
	matrix ViewProjectionMatrix;
};

VS_OUTPUT VSMain(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	output.position = mul(input.position, ViewProjectionMatrix);
	output.color = input.color;
	output.texcoord = input.texcoord;

	return output;
}

float4 PSMain(PS_INPUT input) : SV_Target
{
	return Texture.Sample(TextureSampler, input.texcoord);
}