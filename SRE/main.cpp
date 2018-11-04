#include <stdio.h>
#include <iostream>
#include "Log.h"
#include "Window.h"
#include "App.h"
#include "Camera.h"
#include "Model.h"
#include "ShaderManager.h"
#include "glm/gtx/transform.hpp"
#include "Timer.h"
#include "Scene.h"
#include "SceneObject.h"
#include "MeshDrawComponent.h"


// settings
const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 800;
const float MOVE_SPEED = 5.0; // units per second
const float MOUSE_SENSITIVITY = 0.1f;

// instances
SRE::App* gApp;
SRE::Model* gHead;
SRE::Model* gFloor;
SRE::ShaderManager* gShaderManager;
SRE::FPSCamera* gCamera;

//objects
SRE::Scene* gScene;
SRE::SceneObject* gSceneObjectFloor;
SRE::SceneObject* gSceneObjectHead;




//light global
glm::vec3 gLightPos(0.0f, 3.0f, -10.0f);
glm::vec3 gLightColor(1.0f, 1.0f, 1.0f);
float gAngle = 0.0f;;

void update(double elapsedTime);

int main(int argc, char* argv[])
{
	//create a instance of app by creating a singleton
	gApp = SRE::App::GetAppInstance();

	// get refernce to the main window
	SRE::Window* pWindow = gApp->GetWindow();

	// create a Camera
	gCamera = new SRE::FPSCamera();

	//ceate a instance of the timer class
	SRE::Timer time;
	time.Reset();

	// load model
	gHead = new SRE::Model();
	gHead->LoadModel("assets/Models/head.obj");

	gFloor = new SRE::Model();
	gFloor->LoadModel("assets/Models/floor.obj");

	// scene
	gScene = new SRE::Scene();


	// objects
	gSceneObjectFloor = new SRE::SceneObject();
	SRE::MeshDrawComponent* md = new SRE::MeshDrawComponent(gFloor);
	gSceneObjectFloor->AddComponent(md);
	gSceneObjectFloor->GetTransform()->SetPosition(glm::vec3(0.0f, -0.5f, 0.0f));
	gSceneObjectFloor->GetTransform()->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));

	gSceneObjectHead = new SRE::SceneObject();
	md = new SRE::MeshDrawComponent(gHead);
	gSceneObjectHead->AddComponent(md);
	gSceneObjectHead->GetTransform()->SetPosition(glm::vec3(0.0f, 1.0f, 0.0f));
	gSceneObjectHead->GetTransform()->SetScale(glm::vec3(5.0f,5.f,5.f));

	gScene->AddChild(gSceneObjectFloor);
	gScene->AddChild(gSceneObjectHead);
	

	// load shader
	gShaderManager = SRE::ShaderManager::GetShaderManagerInstance();
	SRE::ShaderProgram* pShaderProgram = gShaderManager->GetShaderProgram("res/Shader/Lighting.vert", "res/Shader/Lighting.frag");
	// activate the shader
	pShaderProgram->Activate();
	while (!gApp->GetWindow()->IsClosing())
	{
		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// hanlde the input
		glfwPollEvents();
		time.Tick();
		
		// update Camera
		update(time.GetDeltaTime());

		// update Lightpos
		gAngle += (float)time.GetDeltaTime() * 50.0f;
		gLightPos.x = 8.0f * sinf(glm::radians(gAngle));

		// set view projection matrices
		glm::mat4 projection, view, model;
		view = gCamera->getViewMatrix();
		projection = glm::perspective(glm::radians(gCamera->getFOV()), (float)pWindow->GetWidth() / pWindow->GetHeight(), 0.1f, 1000.f);
		pShaderProgram->SetProjection(projection);
		pShaderProgram->SetView(view);


		//light params
		glm::vec3 viewPos(gCamera->getPosition());
		pShaderProgram->SetUniform("viewPos", viewPos);
		pShaderProgram->SetUniform("lightPos", gLightPos);
		pShaderProgram->SetUniform("lightColor", gLightColor);



		// our model matrix 
		glm::mat4 modelmatrix;

		for (SRE::SceneObject* _pObjects : gScene->GetSceneObjects())
		{
			SRE::Context context;
			context.mProjection = projection;
			context.mView = view;
			context.fDelta = time.GetDeltaTime();
			_pObjects->Render(context, pShaderProgram);
		}

		// swap buffers
		pWindow->SwapBuffers();
	}

	// deactivate the shader
	pShaderProgram->Deactivate();

	// if we come here the app should close
	gApp->Shutdown();

	return 0;
}

void update(double elapsedTime)
{
	// camera orientation
	double mouseX, mouseY;

	// get the current mouse cursor position delta
	glfwGetCursorPos(gApp->GetWindow()->GetGLFWWindow(), &mouseX, &mouseY);

	// rotate the camera the difference in mouse distance from the center screen.  Multiply this delta by a speed scaler
	gCamera->rotate((float)(gApp->GetWindow()->GetWidth() / 2.0 - mouseX) * MOUSE_SENSITIVITY, (float)(gApp->GetWindow()->GetHeight() / 2.0 - mouseY) * MOUSE_SENSITIVITY);

	/*uncomment this if we set the camera to fps*/
	 //clamp mouse cursor to center of screen
	glfwSetCursorPos(gApp->GetWindow()->GetGLFWWindow(), gApp->GetWindow()->GetWidth() / 2.0, gApp->GetWindow()->GetHeight() / 2.0);

	// forward/backward
	if (glfwGetKey(gApp->GetWindow()->GetGLFWWindow(), GLFW_KEY_W) == GLFW_PRESS)
		gCamera->move(MOVE_SPEED * (float)elapsedTime * gCamera->getLook());
	else if (glfwGetKey(gApp->GetWindow()->GetGLFWWindow(), GLFW_KEY_S) == GLFW_PRESS)
		gCamera->move(MOVE_SPEED * (float)elapsedTime * -gCamera->getLook());

	// strafe left/right
	if (glfwGetKey(gApp->GetWindow()->GetGLFWWindow(), GLFW_KEY_A) == GLFW_PRESS)
		gCamera->move(MOVE_SPEED * (float)elapsedTime * -gCamera->getRight());
	else if (glfwGetKey(gApp->GetWindow()->GetGLFWWindow(), GLFW_KEY_D) == GLFW_PRESS)
		gCamera->move(MOVE_SPEED * (float)elapsedTime * gCamera->getRight());

	// up/down
	if (glfwGetKey(gApp->GetWindow()->GetGLFWWindow(), GLFW_KEY_Z) == GLFW_PRESS)
		gCamera->move(MOVE_SPEED * (float)elapsedTime * glm::vec3(0.0f, 1.0f, 0.0f));
	else if (glfwGetKey(gApp->GetWindow()->GetGLFWWindow(), GLFW_KEY_X) == GLFW_PRESS)
		gCamera->move(MOVE_SPEED * (float)elapsedTime * -glm::vec3(0.0f, 1.0f, 0.0f));
}