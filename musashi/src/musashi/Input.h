//static, global storing Input Data

#pragma once

#include "musashi/Core.h"

namespace musashi
{
	class MSSHI_API Input
	{
	public:
		//to have unified interface to check input, hiding platform specific implementation
		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		inline static float GetMouseX() { return s_Instance->GetMousePosition().first; }
		inline static float GetMouseY() { return s_Instance->GetMousePosition().second; }

	protected:
		//the fns which will be implemented in platform specific files - WindowsInput.h
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private:
		static Input* s_Instance; //we will initialize s_Instance and then can call IsKeyPressed fn to check Input Polling
	};
}
