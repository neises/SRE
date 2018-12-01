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
#include "SplineComponent.h"


// settings
const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 800;
const float MOVE_SPEED = 5.0; // units per second
const float MOUSE_SENSITIVITY = 0.1f;

// instances
SRE::App* gApp;
SRE::Model* gHead;
SRE::Model* gFloor;
SRE::Model* gLightProxy;
SRE::ShaderManager* gShaderManager;
SRE::FPSCamera* gCamera;

//objects
SRE::Scene* gScene;
SRE::SceneObject* gSceneObjectFloor;
SRE::SceneObject* gSceneObjectHead;
SRE::SceneObject* gSceneObjectLightProxy;




//light global
glm::vec3 gLightPos(0.0f, 2.0f, 2.0f);
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
	gHead->LoadModel("assets/Models/head2.obj");

	gFloor = new SRE::Model();
	gFloor->LoadModel("assets/Models/floor.obj");

	gLightProxy = new SRE::Model();
	gLightProxy->LoadModel("assets/Models/cube.obj");

	//spline
	SRE::t_Spline spline;
	spline.m_aControlPoints.push_back(glm::vec3(0.0f, 0.f, -1.0f ));
	spline.m_aControlPoints.push_back(glm::vec3(1.0f, 0.f, -2.0f ));
	spline.m_aControlPoints.push_back(glm::vec3(2.0f, 0.f, -3.0f ));
	spline.m_aControlPoints.push_back(glm::vec3(3.0f, 0.f, -4.0f ));
	spline.m_aControlPoints.push_back(glm::vec3(2.0f, 0.f, -3.0f ));
	spline.m_aControlPoints.push_back(glm::vec3(1.0f, 0.f, -2.0f ));
	spline.m_aControlPoints.push_back(glm::vec3(0.0f, 0.f, -1.0f ));
	spline.m_aControlPoints.push_back(glm::vec3(1.0f, 0.f, -2.0f ));
	spline.m_aControlPoints.push_back(glm::vec3(2.0f, 0.f, -3.0f ));

	// scene
	gScene = new SRE::Scene();


	// objects
	gSceneObjectFloor = new SRE::SceneObject();
	SRE::MeshDrawComponent* pMeshComponent = new SRE::MeshDrawComponent(gFloor);
	gSceneObjectFloor->AddComponent(pMeshComponent);
	gSceneObjectFloor->GetTransform()->SetPosition(glm::vec3(0.0f, -0.5f, 0.0f));

	gSceneObjectHead = new SRE::SceneObject();
	pMeshComponent = new SRE::MeshDrawComponent(gHead);
	SRE::SplineComponent* pSpline = new SRE::SplineComponent();
	pSpline->SetSpline(spline);
	pSpline->SetSpeed(0.1f);
	gSceneObjectHead->AddComponent(pMeshComponent);
	gSceneObjectHead->AddComponent(pSpline);
	gSceneObjectHead->GetTransform()->SetPosition(glm::vec3(0.0f, 0.5f, 0.0f));

	gSceneObjectLightProxy = new SRE::SceneObject();
	pMeshComponent = new SRE::MeshDrawComponent(gLightProxy);
	gSceneObjectLightProxy->AddComponent(pMeshComponent);
	gSceneObjectLightProxy->GetTransform()->SetScale(glm::vec3(0.2f, 0.2f, 0.2f));
	

	gScene->AddChild(gSceneObjectFloor);
	gScene->AddChild(gSceneObjectHead);
	//gScene->AddChild(gSceneObjectLightProxy);
	

	// load shader
	gShaderManager = SRE::ShaderManager::GetShaderManagerInstance();
	SRE::ShaderProgram* pShaderProgram = gShaderManager->GetShaderProgram("res/Shader/simpleShader.vert", "res/Shader/simpleShader.frag", "Basic");
	pShaderProgram = gShaderManager->GetShaderProgram("res/Shader/Lighting.vert", "res/Shader/Lighting.frag", "Light");

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
		//gSceneObjectHead->GetTransform()->SetEuler(glm::vec3(0.0f, time.GetTotalTime(), 0.0f));

		// try to avoid this
		gSceneObjectLightProxy->GetTransform()->SetPosition(gLightPos);

		//view projection matrices we will pass them later
		glm::mat4 projection, view;
		view = gCamera->getViewMatrix();
		projection = glm::perspective(glm::radians(gCamera->getFOV()), (float)pWindow->GetWidth() / pWindow->GetHeight(), 0.1f, 1000.f);

		//light params
		glm::vec3 viewPos(gCamera->getPosition());

		// convert lightpos in objectspace from head
		glm::mat3 localObjectspace = gSceneObjectHead->GetTransform()->GetMatrix();
		localObjectspace = glm::inverse(localObjectspace);
		glm::vec3 LightPosinObjectSpace = localObjectspace * gLightPos;

		//draw the objects with the light shader
		pShaderProgram = gShaderManager->GetShaderProgrambyName("Light");
		SRE::Context context;
		for (SRE::SceneObject* _pObjects : gScene->GetSceneObjects())
		{

			context.m_Projection = projection;
			context.m_View = view;
			context.m_ViewPos = viewPos;
			context.m_LightPos = LightPosinObjectSpace;
			context.m_LightColor = gLightColor;
			context.fDelta = time.GetDeltaTime();

			_pObjects->Update(context);
			_pObjects->Render(context, pShaderProgram);
		}
		pShaderProgram->Deactivate();


		//draw the light proxy but use different shader
		pShaderProgram = gShaderManager->GetShaderProgrambyName("Basic");
		pShaderProgram->Activate();
		// update the view 
		context.m_View = view;
		context.m_Projection = projection;
		gSceneObjectLightProxy->Update(context);
		gSceneObjectLightProxy->Render(context, pShaderProgram);
		pShaderProgram->Deactivate();
		
		
		
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