#include "Window.h"
#include "Log.h"


namespace SRE
{
	using namespace SRE;
	//std::list<Window *> Window::windows;
	Window::Window(int _iHeight /*= 1024*/, int _iWidth /*= 800*/, bool _bFullscreen /*= false*/, const char* _cTitle /*= "Test App"*/)
		: m_bFullscreen(_bFullscreen), m_iHeight(_iHeight)
		, m_iWidth(_iWidth), m_cTitle(_cTitle), m_glPolymode(GL_FILL), m_bWireFrame(false)
	{
		Initialise();
	}
	
	void Window::Initialise()
	{

		if (!glfwInit())
		{
			SRE::Logger::GetLoggerInstance()->L_ERROR("Erro Initialising GLFW");
			glfwTerminate();
			return;
		}


		// Make GLFW Window
		// TODO: Control which monitor it goes to and figure out last parameter
		m_pWindow = glfwCreateWindow(m_iWidth, m_iHeight, m_cTitle, nullptr, nullptr);

		// Check that Window opened
		if (!m_pWindow)
		{
			SRE::Logger::GetLoggerInstance()->L_ERROR("Can´t create GL-Window");
			glfwTerminate();
			return; // TODO: Return error instead of nothing
		}

		// Make the current context be the window that was just created
		glfwMakeContextCurrent(m_pWindow);

		// Get buff size information
		glfwGetFramebufferSize(m_pWindow, &m_iBufferWidth, &m_iBufferHeight);

		// Handle Key + Mouse
		glfwSetKeyCallback(m_pWindow, handleKeys);
		glfwSetCursorPosCallback(m_pWindow, handleMouse);
		//glfwSetMouseButtonCallback(m_Window, mouseCallback);

		// Set mouse mode to be captured
		glfwSetInputMode(m_pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		// Set mouse position to center
		glfwSetCursorPos(m_pWindow, m_iWidth * 0.5f, m_iHeight * 0.5f);

		glfwGetWindowAttrib(m_pWindow, GLFW_FOCUSED);

		// Allow modern extension access
		glewExperimental = GL_TRUE;

		GLenum error = glewInit();
		if (error != GLEW_OK)
		{
			printf("Error: %s", glewGetErrorString(error));
			glfwDestroyWindow(m_pWindow);
			glfwTerminate();
			return;
		}

		glEnable(GL_DEPTH_TEST);

		// Create Viewport
		glViewport(0, 0, m_iBufferWidth, m_iBufferHeight);

		glfwSetWindowUserPointer(m_pWindow, this);

		for (size_t i = 0; i < 1024; i++)
		{
			m_aKeys[i] = 0;
		}

	}
	Window::~Window()
	{
		glfwDestroyWindow(m_pWindow);
	}

	GLFWwindow* Window::GetGLFWWindow()
	{
		if (m_pWindow)
		{
			return m_pWindow;
		}

	}

	int Window::GetHeight()
	{
		return m_iHeight;
	}

	int Window::GetWidth()
	{
		return m_iWidth;
	}

	void Window::DestroyWindow(Window* _pWindow)
	{
		//find window
		glfwDestroyWindow(_pWindow->GetGLFWWindow());
	}

	void Window::Close()
	{
		glfwSetWindowShouldClose(this->GetGLFWWindow(), GLFW_TRUE);
	}

	void Window::ToggleWireFrameMode()
	{
		m_bWireFrame ? glPolygonMode(GL_FRONT_AND_BACK, GL_FILL) : glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		m_bWireFrame = !m_bWireFrame;
	}

	void Window::handleMouse(GLFWwindow* _window, double xPos, double yPos)
	{
		Window* pWindow = static_cast<Window*>(glfwGetWindowUserPointer(_window));
		pWindow->m_iMouseState = glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_RIGHT);

		if (pWindow->m_bMouseFirstMoved)
		{
			pWindow->m_fLastX = xPos;
			pWindow->m_fLastY = yPos;
			pWindow->m_bMouseFirstMoved = false;
		}

		pWindow->m_fChangeX = xPos - pWindow->m_fLastX;
		pWindow->m_fChangeY = pWindow->m_fLastY - yPos;

		pWindow->m_fLastX = xPos;
		pWindow->m_fLastY = yPos;
	}

	void Window::handleMouseCallback(GLFWwindow* window, double xPos, double yPos)
	{

	}

	void Window::handleKeys(GLFWwindow* _window, int key, int code, int action, int mode)
	{
		Window* pWindow = static_cast<Window*>(glfwGetWindowUserPointer(_window));

		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(_window, GL_TRUE);
		}

		if (key == GLFW_KEY_R)
		{
			pWindow->ToggleWireFrameMode();
		}

		if (key >= 0 && key < 1024)
		{
			if (action == GLFW_PRESS)
			{
				pWindow->m_aKeys[key] = true;
			}
			else if (action == GLFW_RELEASE)
			{
				pWindow->m_aKeys[key] = false;
			}
		}
	}

	void Window::SwapBuffers()
	{
		glfwSwapBuffers(m_pWindow);
	}

	bool Window::IsClosing() const
	{
		return glfwWindowShouldClose(m_pWindow);
	}

	bool* Window::GetKeys()
	{
		return m_aKeys;
	}

	GLfloat Window::GetXChange()
	{
		return m_fLastX;
	}

	GLfloat Window::GetYChange()
	{
		return m_fLastY;
	}

}

