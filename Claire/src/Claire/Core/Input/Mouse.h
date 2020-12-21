#pragma once

#include <glm/glm.hpp>
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
		glm::vec2 GetMousePosition();
	
		std::unordered_map<uint32_t, bool> buttons;
	};
}