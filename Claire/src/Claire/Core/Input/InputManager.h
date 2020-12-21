#pragma once

#include "Keyboard.h"
#include "Mouse.h"

namespace ClaireInput
{
	class InputManager
	{
	public:
		static bool IsKeyPressed(uint32_t key) { return m_Keyboard.IsKeyPressed(key); }
		static bool IsKeyReleased(uint32_t key) { return m_Keyboard.IsKeyReleased(key); }

		static float GetMousePositionX() { return m_Mouse.GetMousePositionX(); }
		static float GetMousePositionY() { return m_Mouse.GetMousePositionY(); }
		static glm::vec2 GetMousePosition() { return m_Mouse.GetMousePosition(); }

		static bool IsMouseButtonPressed(uint32_t button) { return m_Mouse.IsMouseButtonPressed(button); }
		static bool IsMouseButtonReleased(uint32_t button) { return m_Mouse.IsMouseButtonReleased(button); }

		static Keyboard& GetKeyboardHandle() { return m_Keyboard; }
		static Mouse& GetMouseHandle() { return m_Mouse; }
	private:
		static Mouse m_Mouse;
		static Keyboard m_Keyboard;
	};
}