#include "App.h"
#include "Log.h"
#include "Window.h"
#include "GLEW/include/GL/glew.h"
#include "GLFW/vc2017/glfw3.h"
#include "Utils.h"


namespace SRE
{
using namespace SRE;
App* App::m_pAppInstance = 0;

App::App()
{
	Initialise();
}

App::~App()
{
	Shutdown();
}


void App::glfwErrorCallback(int _iError, const char *_cDescription)
{
	SRE::Logger::GetLoggerInstance()->L_WARNING("OpenGL Error");
}


void App::SetWindow(SRE::Window* _pWindow)
{
	m_pWindow = _pWindow;
	glfwMakeContextCurrent(m_pWindow->GetGLFWWindow());
}


SRE::Window* App::GetWindow() const
{
	return m_pWindow;
}
App* App::GetAppInstance()
{
	if (m_pAppInstance == nullptr)
	{
		m_pAppInstance = new App();

	}
	return m_pAppInstance;
}

int App::Initialise()
{
	// set opengl callback
	glfwSetErrorCallback(glfwErrorCallback);

	//init glfw
	if (!glfwInit())
	{
		SRE::Logger::GetLoggerInstance()->L_CRITIC("App Class: Fail to init glfw");
		return GLFW_INIT_FAILURE;
	}

	// glfw context
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 16);

	// create Window
	m_pWindow = new SRE::Window();

	if (!m_pWindow)
	{
		SRE::Logger::GetLoggerInstance()->L_ERROR("Could not create Window! Check App Class - Closing App");
		Terminate(CREATE_WINDOW_FAILURE);
		return CREATE_WINDOW_FAILURE;
	}

	return SUCCESS;
}


void App::Terminate(ErrorCode _eError)
{
	if (_eError != GLFW_INIT_FAILURE)
	{
		glfwTerminate();
	}
}

void App::Shutdown()
{
	SAFE_DELETE(m_pWindow);
	glfwTerminate();
}

}