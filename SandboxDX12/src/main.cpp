#define CLAIRE_VERSION_12
#include <Claire/Claire.h>
#include <iostream>

int main()
{
	Window window(1280, 720, L"My Window", API::DirectX12);

	while (window.IsOpen())
	{
		window.Update();
	}
}