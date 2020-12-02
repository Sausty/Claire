#pragma once

#include <cstdint>

namespace ClaireInput
{
	class Keyboard
	{
	public:
		bool IsKeyPressed(uint32_t key);
		bool IsKeyReleased(uint32_t key);
	private:
		unsigned char keys[256];
		unsigned char oldKeysState[256];
	};
}