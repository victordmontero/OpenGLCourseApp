#include "Window.h"

Window::Window()
{
	width = 800;
	height = 600;
	xChange = 0.0f;
	yChange = 0.0f;

	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}

Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
	xChange = 0.0f;
	yChange = 0.0f;

	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}

int Window::Initialise()
{
	if (!glfwInit())
	{
		printf("Error Initialising GLFW");
		glfwTerminate();
		return 1;
	}

	// Setup GLFW Windows Properties
	// OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core Profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allow forward compatiblity
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create the window
	mainWindow = glfwCreateWindow(width, height, "Test Window", NULL, NULL);
	if (!mainWindow)
	{
		printf("Error creating GLFW window!");
		glfwTerminate();
		return 1;
	}

	// Get buffer size information
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set the current context
	glfwMakeContextCurrent(mainWindow);

	// Handle Key + Mouse Input
	createCallbacks();
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Allow modern extension access
	glewExperimental = GL_TRUE;

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		printf("Error: %s", glewGetErrorString(error));
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST);

	// Create Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);

	glfwSetWindowUserPointer(mainWindow, this);
	glfwSetJoystickUserPointer(GLFW_JOYSTICK_1, this);
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, handleKeys);
	glfwSetCursorPosCallback(mainWindow, handleMouse);
	glfwSetJoystickCallback(handleJoystickConnected);
}

const unsigned char* Window::getButtons()
{
	const unsigned char* buttons = NULL;;
	if (glfwJoystickPresent(GLFW_JOYSTICK_1))
	{
		int buttonCount = 0;
		int stickCount = 0;

		buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);

		if (buttons[GLFW_GAMEPAD_BUTTON_CROSS] == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(mainWindow, GL_TRUE);
		}
		/*for (int i = 0; i < buttonCount; i++)
		{
			printf("button %d is %d\n", i, buttons[i]);
		}
		printf("\n");*/
	}
	return buttons;
}

const float* Window::getAxes()
{
	int axesCount;
	axes = NULL;;
	if (glfwJoystickPresent(GLFW_JOYSTICK_1))
	{
		axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
		/*for (int i = 0; i < axesCount; i++)
		{
			printf("axe %d is %.3f\n", i, axes[i]);
		}*/
	}
	return axes;
}

GLfloat Window::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}

void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
		}
	}
}

void Window::handleMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}

void Window::pollJoystickAxes()
{
	if (axes == NULL)
		return;

	if (joystickFirstMoved)
	{
		xChange = 0.0f;
		yChange = 0.0f;
		joystickFirstMoved = false;
	}

	float axisX = axes[GLFW_GAMEPAD_AXIS_RIGHT_X];
	float axisY = axes[GLFW_GAMEPAD_AXIS_RIGHT_Y];

	xChange = fabsf(axisX) > fabsf(0.5f) ? axisX*0.08f : 0;
	yChange = fabsf(axisY) > fabsf(0.5f) ? axisY*0.08f : 0;

}

void Window::handleJoystickConnected(int joy, int event)
{
	if (glfwJoystickPresent(joy))
	{
		Window* window = static_cast<Window*>(glfwGetJoystickUserPointer(joy));
	}

	if (event == GLFW_CONNECTED)
	{
		printf("Joystick %s[%d] connected\n", glfwGetJoystickName(joy), joy);
	}
	else if (event == GLFW_DISCONNECTED)
	{
		printf("Joystick %s[%d] disconnected\n", glfwGetJoystickName(joy), joy);
	}
	else
	{
		printf("Joystick event %d\n", event);
	}
}

Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}
