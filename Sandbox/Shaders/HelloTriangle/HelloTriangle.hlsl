float4 VSMain(float4 pos : POSITION) : SV_Position
{
	return pos;
}

float4 PSMain(float4 pos : SV_POSITION) : SV_Target
{
	return float4(0.8f, 0.9f, 0.4f, 1.0f);
}