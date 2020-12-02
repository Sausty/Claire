#include "Mouse.h"

#include <Windows.h>

namespace ClaireInput
{
	bool Mouse::IsMouseButtonPressed(uint32_t button)
	{
		return buttons[button];
	}

	bool Mouse::IsMouseButtonReleased(uint32_t button)
	{
		return !IsMouseButtonPressed(button);
	}

	float Mouse::GetMousePositionX()
	{
		POINT current_mouse_pos = {};
		::GetCursorPos(&current_mouse_pos);

		return current_mouse_pos.x;
	}

	float Mouse::GetMousePositionY()
	{
		POINT current_mouse_pos = {};
		::GetCursorPos(&current_mouse_pos);

		return current_mouse_pos.y;
	}

	ClaireMath::vec2 Mouse::GetMousePosition()
	{
		POINT current_mouse_pos = {};
		::GetCursorPos(&current_mouse_pos);

		return ClaireMath::vec2(current_mouse_pos.x, current_mouse_pos.y);
	}
}