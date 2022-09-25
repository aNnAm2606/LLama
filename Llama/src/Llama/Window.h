#pragma once

#include "llamapch.h"

#include "Llama/Core.h"
#include "Llama/Events/Event.h"

namespace Llama
{
	//This is an abstract representation of a Window
	//If we dont specify this is created as default.
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Llama Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	//Interface representing a desktop system based Window. It's mostly an interface.
	class LLAMA_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		//Window Attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual bool SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};

}
