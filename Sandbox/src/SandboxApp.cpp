#include <Llama.h>

class ExampleLayer : public Llama::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (Llama::Input::IsKeyPressed(LLAMA_KEY_TAB))
			LLAMA_TRACE("Tab key is pressed (poll)!");
	}

	void OnEvent(Llama::Event& event) override
	{
		if (event.GetEventType() == Llama::EventType::KeyPressed)
		{
			Llama::KeyPressedEvent& e = (Llama::KeyPressedEvent&)event;
			if (e.GetKeyCode() == LLAMA_KEY_TAB)
				LLAMA_TRACE("Tab key is pressed (event)!");
			LLAMA_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

	class Sandbox : public Llama::Application
	{
	public:
		Sandbox()
		{
			PushLayer(new ExampleLayer());
			PushOverlay(new Llama::ImGuiLayer());
		}

		~Sandbox()
		{
		}

	};

	Llama::Application* Llama::CreateApplication()
	{
		return new Sandbox();
	}