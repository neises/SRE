#pragma once

#include <list>
#include "GLEW/include/GL/glew.h"
#include "GLFW/vc2017/glfw3.h"

namespace SRE
{
	class Window
	{
	public:

		Window(int _iHeight = 768, int _iWidth = 1360, bool _bFullscreen = false, const char* _cTitle = "Test App");
		~Window();

		GLFWwindow* GetGLFWWindow();
		int GetHeight();
		int GetWidth();
		bool IsFullScreen();
		void DestroyWindow(Window* _pWindow);
		void Close();
		void ToggleWireFrameMode();
		void SwapBuffers();

		bool IsClosing() const;
		bool* GetKeys();

		GLfloat GetXChange();
		GLfloat GetYChange();

	private:
		GLFWwindow * m_pWindow;
		void Initialise();

		bool m_bFullscreen;
		bool m_bWireFrame;
		int m_iHeight;
		int m_iWidth;
		int m_iBufferWidth;
		int m_iBufferHeight;
		const char* m_cTitle;
		int m_iMouseState;

		GLint m_glPolymode;

		//static std::list<Window *> windows;   // List of windows for resize callback
		
		// mouse relevant 
		bool m_bMouseFirstMoved;
		GLfloat m_fLastX;
		GLfloat m_fLastY;
		GLfloat m_fChangeY;
		GLfloat m_fChangeX;

		// input
		bool m_aKeys[1024];

		void createCallbacks();
		static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
		static void handleMouse(GLFWwindow* window, double xPos, double yPos);
		static void handleMouseCallback(GLFWwindow* window, double xPos, double yPos);
	};
}
