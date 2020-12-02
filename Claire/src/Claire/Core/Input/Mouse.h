#pragma once

#include "Claire/Maths/vectors/tvec2.h"
#include <unordered_map>

namespace ClaireInput
{
	class Mouse
	{
	public:
		bool IsMouseButtonPressed(uint32_t button);
		bool IsMouseButtonReleased(uint32_t button);

		float GetMousePositionX();
		float GetMousePositionY();
		ClaireMath::vec2 GetMousePosition();
	
		std::unordered_map<uint32_t, bool> buttons;
	};
}