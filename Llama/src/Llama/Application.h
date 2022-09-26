#pragma once

#include "Core.h"

#include "Window.h"
#include "Llama/LayerStack.h"
#include "Llama/Events/Event.h"
#include "Llama/Events/ApplicationEvent.h"

namespace Llama 
{
	class LLAMA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer); //Functions to take in layers
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }//We need to return the window to the guilayer

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack; //Inherits the lifetime of this application class
	private:
		static Application* s_Instance;
	};

	//TO BE DEFINED IN "CLIENT"
	Application* CreateApplication();

}
