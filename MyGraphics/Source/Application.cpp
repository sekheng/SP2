#include "Application.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>
#include "LoadingScreen.h"


GLFWwindow* m_window;
const unsigned char FPS = 60; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame

//global variables needed for transition
Scene* Application::scenario1;
Scene* Application::scene;
Scene* Application::scenario3;
Scene* Application::scenario2;

//Sound effects
BGMDriven* Application::musics;
//Sound effects
/******************************************************************************/
/*!
\brief
define an error callback
*/
/******************************************************************************/
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

/******************************************************************************/
/*!
\brief
Closes the window when press ESC
*/
/******************************************************************************/
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

/******************************************************************************/
/*!
\brief - 
Define the key input callback and prevent the key from pressing twice

\return - whether the key that the player pressed is true
*/
/******************************************************************************/
bool Application::IsKeyPressed(unsigned short key)
{
    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

/******************************************************************************/
/*!
\brief -
Default Constructor
*/
/******************************************************************************/
Application::Application()
{
}

/******************************************************************************/
/*!
\brief -
Destructor
*/
/******************************************************************************/
Application::~Application()
{
}

/******************************************************************************/
/*!
\brief -
update the opengl with new window size

\param window - 
The original window

\param w - 
the new width of the window

\param h - 
the new height of the window
*/
/******************************************************************************/
void resize_callback(GLFWwindow* window, int w, int h)
{ 
	glViewport(0, 0, w, h);	//update opengl the new window size
}

/******************************************************************************/
/*!
\brief -
Where the initialization of the glfw and glew, window size, and window's location
*/
/******************************************************************************/
void Application::Init()
{
	//Set the error callback
	glfwSetErrorCallback(error_callback);
	//Initialize GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 


	//Create a window and create its OpenGL context
    const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    //Obtain Width and Height values from the monitor;

    //Set to fullscreen at primary monitor's resolution;

    // get the primary monitor's size

    m_window = glfwCreateWindow(mode->width, mode->height, "Computer Graphics", NULL, NULL);
    //m_window = glfwCreateWindow(mode->width, mode->height, "Computer Graphics", glfwGetPrimaryMonitor(), NULL);
	glfwSetWindowSizeCallback(m_window, resize_callback);

	//If the window couldn't be created
	if (!m_window)
	{
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//This function makes the context of the specified window current on the calling thread. 
	glfwMakeContextCurrent(m_window);

	//Sets the key callback
	//glfwSetKeyCallback(m_window, key_callback);

	glewExperimental = true; // Needed for core profile
	//Initialize GLEW
	GLenum err = glewInit();

	//If GLEW hasn't initialized
	if (err != GLEW_OK) 
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		//return -1;
	}

    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

/******************************************************************************/
/*!
\brief -
Initializing of the scene, and starting of the game
*/
/******************************************************************************/
void Application::Run()
{
	//Main Loop
    const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    //rendering just the loading screen
    Scene *loadingScreen = new LoadingScreen(static_cast<float>(mode->width), static_cast<float>(mode->height));
    loadingScreen->Init();
    loadingScreen->Update(m_timer.getElapsedTime());
    loadingScreen->Render();
    glfwSwapBuffers(m_window);
    //rendering just the loading screen

    musics = new BGMDriven();
    musics->init();
    //musics->playBackground();

    scenario1 = new sceneSP2(static_cast<float>(mode->width), static_cast<float>(mode->height));
    //scenario1->Init();

    loadingScreen->Update(m_timer.getElapsedTime());
    loadingScreen->Render();
    glfwSwapBuffers(m_window);

    scenario3 = new scene2_SP2(static_cast<float>(mode->width), static_cast<float>(mode->height));
	scenario3->Init();

    loadingScreen->Update(m_timer.getElapsedTime());
    loadingScreen->Render();
    glfwSwapBuffers(m_window);

    scenario2 = new scene3_SP2(static_cast<float>(mode->width), static_cast<float>(mode->height));
   // scenario2->Init();

    scene = scenario3;

	m_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
	while (!glfwWindowShouldClose(m_window) && !IsKeyPressed(VK_ESCAPE))
	{
        scene->Update(m_timer.getElapsedTime());
        scene->Render();
		//Swap buffers
		glfwSwapBuffers(m_window);
		//Get and organize events, like keyboard and mouse input, window resizing, etc...
		glfwPollEvents();
        m_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.   

	} //Check if the ESC key had been pressed or if the window had been closed
    scene->Exit();
    delete scenario1;
    delete scenario3;
    delete scenario2;
    delete loadingScreen;
    delete musics;
}

/******************************************************************************/
/*!
\brief -
Calls for the destroying of windows and cleaning up GLFW
*/
/******************************************************************************/
void Application::Exit()
{
    _CrtDumpMemoryLeaks();
    //Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();
}

void Application::changeIntoScenario3(){
    scene = scenario3;
}

void Application::changeIntoScenario1() {
    scene = scenario1;
}

void Application::changeIntoScenario2() {
    scene = scenario2;
}