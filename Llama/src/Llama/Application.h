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
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack; //Inherits the lifetime of this application class
	};

	//TO BE DEFINED IN "CLIENT"
	Application* CreateApplication();

}
