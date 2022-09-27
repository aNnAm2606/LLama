#include "llamapch.h"
#include "Application.h"

#include "Llama/Log.h"

#include <glad/glad.h>

#include "Input.h"

namespace Llama {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr; //Need this bc wherever we r we want to access oir APP for info

	Application::Application()
	{
		LLAMA_CORE_ASSERT(!s_Instance, "Application already exists!");//We only have one APP
		s_Instance = this; //Holds a to our APP, which gets set when we construct the APP

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		unsigned int id;
		glGenVertexArrays(1, &id);
	}

	Application::~Application()
	{

	}
	//Push layer to layerstack
	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	//Push overlayer to layerstack
	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		//If dispatcher sees close event, the he has to dispatch it to the Bind Event function
		EventDispatcher dispatcher(e); // If "e" event that comes through is close event, checks that by going through event.h get static type
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		//Here we go backwards through layerstack and we call OnEvent() whenever we recieve an event, if event is marked as handled we break
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.2, 0.2, 0.5, 0.5);
			glClear(GL_COLOR_BUFFER_BIT);
			//We itterate over all the layers, called on Update()
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}

