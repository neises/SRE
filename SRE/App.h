#pragma once
#include <vector>


//forward declaration
namespace SRE
{
	class Window;
}


enum ErrorCode
{
	GLFW_INIT_FAILURE,
	GLEW_INIT_FAILIRE,
	CREATE_WINDOW_FAILURE,
	SUCCESS
};

namespace SRE
{

class App
{
public:
	App();
	~App();

	static void glfwErrorCallback(int _iError, const char *_cDescription);
	static App* GetAppInstance();

	void SetWindow(SRE::Window* _pWindow);
	Window* GetWindow() const;

	void Shutdown();

private:
	
	int Initialise();
	void Terminate(ErrorCode _eError);

	SRE::Window* m_pWindow;

	static App* m_pAppInstance;
};

}
