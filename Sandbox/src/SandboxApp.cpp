#include <Llama.h>

class Sandbox : public Llama:: Application
{
public:
	Sandbox()
	{
	}

	~Sandbox()
	{
	}


private:

};

Llama::Application* Llama::CreateApplication()
{
	return new Sandbox();
}