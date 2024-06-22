#include "Window.h"

Window::Window(GLint windowWidth, GLint windowHeight)
    : mainWindow(nullptr), context(nullptr), joystick(nullptr),
      width(windowWidth), height(windowHeight), axes(nullptr), buttons(nullptr),
      initialJoystickAxisValue(0), players(-1), shouldClose(false)
{
    xChange = 0.0f;
    yChange = 0.0f;

    for (size_t i = 0; i < 1024; i++)
    {
        keys[i] = 0;
    }
}

int Window::Initialise()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Setup GLFW Windows Properties
    // OpenGL version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    // Core Profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // Create the window
    mainWindow = SDL_CreateWindow("Test Window", SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED, width, height,
                                  SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    context = SDL_GL_CreateContext(mainWindow);

    if (context == nullptr)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
                        "Failed to create OpenGL context: %s\n",
                        SDL_GetError());
        return 1;
    }

    int version = gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);
    SDL_Log("GL %d.%d\n", GLAD_VERSION_MAJOR(version),
            GLAD_VERSION_MINOR(version));

    if (mainWindow == nullptr)
    {
        SDL_Log("Main window not initialized! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Get buffer size information
    SDL_GetWindowSize(mainWindow, &bufferWidth, &bufferHeight);

    SDL_GL_SetSwapInterval(-1);

    glEnable(GL_DEPTH_TEST);

    // Create Viewport
    glViewport(0, 0, bufferWidth, bufferHeight);

    SDL_Log("Viewport created %u, %u", bufferWidth, bufferHeight);

    return 0;
}

void Window::destroy()
{
    if (this->joystick != nullptr && SDL_JoystickGetAttached(this->joystick))
    {
        delete[] axes;
        delete[] buttons;
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(mainWindow);
    SDL_Quit();
}

const unsigned char* Window::getButtons()
{
    if (this->joystick != nullptr && SDL_JoystickGetAttached(this->joystick))
    {
        for (int i = 0; i < buttonCount; i++)
        {
            // SDL_Log("button %d is %d\n", i, buttons[i]);
            buttons[i] = SDL_JoystickGetButton(joystick, i);
        }

        if (buttons[SDL_CONTROLLER_BUTTON_X] == 1)
        {
            shouldClose = true;
        }
    }

    return buttons;
}

const float* Window::getAxes()
{
    if (this->joystick != nullptr && SDL_JoystickGetAttached(this->joystick))
    {
        for (int i = 0; i < axesCount; i++)
        {
            const float axisValue = SDL_JoystickGetAxis(joystick, i);
            short axisValueInitialValue = 0;
            SDL_JoystickGetAxisInitialState(joystick, i,
                                            &axisValueInitialValue);
            axes[i] = fabsf(axisValue) > fabs(axisValueInitialValue)
                          ? axisValue * 0.005f
                          : 0;
            // SDL_Log("axe %d is %.3f\n", i, axes[i]);
        }
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

void Window::handleKeys(Window* theWindow, int key, int code, int action,
                        int mode)
{
    if (key == SDL_KeyCode::SDLK_ESCAPE && action == SDL_KEYDOWN)
    {
        theWindow->shouldClose = true;
    }

    if (key >= 0 && key < 1024)
    {
        if (action == SDL_KEYDOWN)
        {
            theWindow->keys[key] = true;

            SDL_Log("%d pressed\n", key);
        }
        else if (action == SDL_KEYUP)
        {
            theWindow->keys[key] = false;

            SDL_Log("%d released\n", key);
        }
    }
}

void Window::handleMouse(Window* theWindow, double xPos, double yPos)
{

    if (theWindow->mouseFirstMoved)
    {
        theWindow->lastX = xPos;
        theWindow->lastY = yPos;
        theWindow->mouseFirstMoved = false;
    }

    theWindow->xChange = xPos - theWindow->lastX;
    theWindow->yChange = theWindow->lastY - yPos;

    // SDL_Log("xChanged %f , yChanged %f\n", theWindow->xChange,
    // theWindow->yChange);

    theWindow->lastX = xPos;
    theWindow->lastY = yPos;
}

void Window::pollJoystickAxes()
{
    short axisXInitialValue = 0;
    short axisYInitialValue = 0;

    if (axes == nullptr)
        return;

    if (joystickFirstMoved)
    {
        xChange = 0.0f;
        yChange = 0.0f;
        joystickFirstMoved = false;
    }

    float axisX = axes[SDL_CONTROLLER_AXIS_RIGHTX];
    float axisY = axes[SDL_CONTROLLER_AXIS_RIGHTY];

    xChange = axisX * 0.08f;
    yChange = axisY * 0.08f;
}

void Window::handleJoystickConnected(Window* window, int joy, int event)
{

    if (event == SDL_JOYDEVICEADDED)
    {
        window->joystick = SDL_JoystickOpen(joy);
        if (window->joystick == nullptr)
        {
            SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
                        "Joystick %u error opening [%s]\n", joy,
                        SDL_GetError());
            return;
        }

        if (SDL_JoystickGetAttached(window->joystick))
        {
            SDL_JoystickSetPlayerIndex(window->joystick, ++(window->players));

            SDL_Log("Joystick %s[%d] connected\n",
                    SDL_JoystickName(window->joystick),
                    static_cast<int>(SDL_JoystickInstanceID(window->joystick)));
            SDL_Log("Player index [%d]\n",
                    SDL_JoystickGetPlayerIndex(window->joystick));

            window->buttonCount = SDL_JoystickNumButtons(window->joystick);
            window->buttons = new unsigned char[window->buttonCount]{0};

            window->axesCount = SDL_JoystickNumAxes(window->joystick);
            window->axes = new float[window->axesCount]{0};

            SDL_Log("Joystick button count [%d]\n", window->buttonCount);
            SDL_Log("Joystick axis count [%d]\n", window->axesCount);

            if (SDL_JoystickHasRumble(window->joystick))
            {
                SDL_JoystickRumble(window->joystick, 500, 500, 1000);
            }

            if (SDL_JoystickHasLED(window->joystick))
            {
                SDL_JoystickSetLED(window->joystick, 0, 255, 255);
            }
        }
    }
    else if (event == SDL_JOYDEVICEREMOVED)
    {
        SDL_Log("Joystick %s[%d] disconnected\n",
                SDL_JoystickName(window->joystick),
                static_cast<int>(SDL_JoystickInstanceID(window->joystick)));
        SDL_JoystickClose(window->joystick);
        window->joystick = nullptr;
        window->players = ((window->players - 1) < 0) ? -1 : window->players--;

        delete[] window->axes;
        delete[] window->buttons;

        window->axes = nullptr;
        window->buttons = nullptr;

        window->axesCount = 0;
        window->buttonCount = 0;
    }
    else
    {
        SDL_Log("Joystick event %d\n", event);
    }
}

Window::~Window()
{
    destroy();
}

void Window::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            SDL_Log("Window quit");
            shouldClose = true;
            break;

        case SDL_KEYDOWN:
            SDL_Log("SDL_KEYDOWN %u %u", event.key.keysym.sym,
                    event.key.keysym.scancode);
            handleKeys(this, event.key.keysym.sym, event.key.keysym.scancode,
                       event.key.type, event.key.keysym.mod);
            break;

        case SDL_KEYUP:
            SDL_Log("SDL_KEYUP %u %u", event.key.keysym.sym,
                    event.key.keysym.scancode);
            handleKeys(this, event.key.keysym.sym, event.key.keysym.scancode,
                       event.key.type, event.key.keysym.mod);
            break;

        case SDL_MOUSEMOTION:
            SDL_Log("SDL_MOUSEMOTION x: %ld,  y:%ld", event.motion.x,
                    event.motion.y);
            handleMouse(this, event.motion.x, event.motion.y);
            break;

        case SDL_MOUSEWHEEL:
            SDL_Log("SDL_MOUSEWHEEL");
            break;

        case SDL_JOYAXISMOTION:
        case SDL_CONTROLLERAXISMOTION:
            SDL_Log("SDL_CONTROLLERAXISMOTION Axis %d, Value %d",
                    event.jaxis.axis, event.jaxis.value);
            break;
        case SDL_JOYBUTTONUP:
            SDL_Log("SDL_JOYBUTTONUP  %d", event.jbutton.button);
            break;
        case SDL_JOYBUTTONDOWN:
            SDL_Log("SDL_JOYBUTTONDOWN %d", event.jbutton.button);
            break;

        case SDL_JOYDEVICEREMOVED:
            SDL_Log("SDL_JOYDEVICEREMOVED  %d", event.jbutton.which);
            handleJoystickConnected(this, event.jdevice.which,
                                    event.jdevice.type);
            break;

        case SDL_JOYDEVICEADDED:
            SDL_Log("SDL_JOYDEVICEADDED  %d", event.jbutton.which);
            handleJoystickConnected(this, event.jdevice.which,
                                    event.jdevice.type);
            break;

        default:
            break;
        }
    }
}
