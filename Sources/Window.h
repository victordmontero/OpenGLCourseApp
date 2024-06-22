#pragma once

#include <cstdio>
#include <cmath>

extern "C"
{
#include <glad/gl.h>
#include <SDL2/SDL.h>
#include <SDL_opengl.h>
}

class Window
{
public:

	Window(GLint windowWidth = 800, GLint windowHeight = 600);
	~Window();

	int Initialise();

	GLint getBufferWidth() { return bufferWidth; }
	GLint getBufferHeight() { return bufferHeight; }

	bool getShouldClose() { return shouldClose; }

	bool* getsKeys() { return keys; }
	const unsigned char* getButtons();
	const float* getAxes();
	GLfloat getXChange();
	GLfloat getYChange();

	void pollJoystickAxes();

	void swapBuffers() {
		SDL_GL_SwapWindow(mainWindow);

	}

	void handleEvents();

private:
	SDL_Window* mainWindow;
	SDL_GLContext context;
	SDL_Joystick* joystick;

	GLint width, height;
	GLint bufferWidth, bufferHeight;

	bool keys[1024];
	float* axes;
	unsigned char* buttons;

	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	int buttonCount;
	int axesCount;
	short initialJoystickAxisValue;
	char players;
	bool mouseFirstMoved;
	bool joystickFirstMoved;
	bool shouldClose;

	static void handleKeys(Window* window, int key, int code, int action, int mode);
	static void handleMouse(Window* window, double xPos, double yPos);
	static void handleJoystickConnected(Window* window, int joy, int event);
};