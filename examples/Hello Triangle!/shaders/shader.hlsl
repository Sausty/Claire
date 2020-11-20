cbuffer ColorConstantBuffer : register(b0)
{
	float red;
	float green;
	float blue;
};

float4 VSMain(float4 pos : POSITION) : SV_Position
{
	return pos;
}

float4 PSMain(float4 pos : SV_POSITION) : SV_Target
{
	return float4(red, green, blue, 1.0);
}