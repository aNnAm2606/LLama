#pragma once

#include "Llama/Window.h"

#include <GLFW/glfw3.h>


namespace Llama
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;

		//We have this struct bc we need to pass it to glfw (for Events). This is where we store our data that might be requested
		//by glfw during event callbacks. 
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};
		//Create function which gets implemented in format specific file
		WindowData m_Data;//We have this struct, so this way we just pass the struct as custom data, not passing the enitire class
	};

}