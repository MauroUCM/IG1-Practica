#include "IG1App.h"

#include <iostream>

using namespace std;

// static single instance (singleton pattern)
IG1App IG1App::s_ig1app; // default constructor (constructor with no parameters)

// Print OpenGL errors and warnings
void GLAPIENTRY debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
                   GLsizei length, const GLchar* message, const void* userParam)
{
	const char* prefix = (type == GL_DEBUG_TYPE_ERROR)
		? "\x1b[31m[ERROR]\x1b[0m "
		: "\x1b[33m[WARNING]\x1b[0m ";
	cout << prefix << message << endl;
}

void
IG1App::close()
{
	cout << "Closing GLFW...\n";
	glfwSetWindowShouldClose(mWindow, true); // stops main loop
}

void
IG1App::run() // enters the main event processing loop
{
	if (mWindow == 0) // if not intilialized
		init();

	// IG1App main loop
	while (!glfwWindowShouldClose(mWindow)) {
		// Redisplay the window if needed
		if (mNeedsRedisplay) {
			display();
			mNeedsRedisplay = false;
		}

		if (mUpdateEnabled) {
			if (glfwGetTime() > mNextUpdate) {
				mNextUpdate = glfwGetTime() + FRAME_DURATION;
				mScenes[mCurrentScene]->update();
				mNeedsRedisplay = true;
			}
		}

		glfwWaitEventsTimeout(mNextUpdate - glfwGetTime());
	}

	destroy();
}

void
IG1App::init()
{
	// create an OpenGL Context
	iniWinOpenGL();

	// create the scene after creating the context
	// allocate memory and resources
	mViewPort = new Viewport(mWinW, mWinH);
	mCamera = new Camera(mViewPort);
	mScenes.push_back(new Scene0);
	mScenes.push_back(new Scene1);
	mScenes.push_back(new Scene2);
	mScenes.push_back(new Scene3);
	mScenes.push_back(new Scene4);
	mScenes.push_back(new Scene5);
	mScenes.push_back(new Scene6);

	mCamera->set2D();
	for (Scene* scen : mScenes) {
		scen->init();
	}
	mScenes[mCurrentScene]->load();

	mNextUpdate = glfwGetTime() + FRAME_DURATION;
}

void
IG1App::iniWinOpenGL()
{ // Initialization
	cout << "Starting GLFW...\n";
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // enable on macOS
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	// Create window with its associated OpenGL context, return window's pointer
	mWindow = glfwCreateWindow(mWinW, mWinH, "IG1App", nullptr, nullptr);

	if (mWindow == nullptr) {
		glfwTerminate();
		throw std::logic_error("cannot create GLFW window");
	}

	glfwMakeContextCurrent(mWindow);

	// Initialize OpenGL extension library
	if (GLenum err = glewInit(); err != GLEW_OK) {
		glfwTerminate();
		throw std::logic_error("Error while loading extensions: "s +
		                       reinterpret_cast<const char*>(glewGetErrorString(err)));
	}

	// Callback registration
	glfwSetWindowSizeCallback(mWindow, s_resize);
	glfwSetCharCallback(mWindow, s_key);
	glfwSetKeyCallback(mWindow, s_specialkey);
	glfwSetWindowRefreshCallback(mWindow, s_display);
	glfwSetMouseButtonCallback(mWindow, s_mouse);
	glfwSetCursorPosCallback(mWindow, s_motion);
	glfwSetScrollCallback(mWindow, s_mouseWheel);

	// Error message callback (all messages)
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0u, 0, GL_TRUE);
	glDebugMessageCallback(debugCallback, nullptr);

	cout << glGetString(GL_VERSION) << '\n';
	cout << glGetString(GL_VENDOR) << '\n';
}

void
IG1App::destroy()
{ // release memory and resources
	for (Scene* scene : mScenes)
		delete scene;
	mScenes.clear();

	delete mCamera;
	mCamera = nullptr;
	delete mViewPort;
	mViewPort = nullptr;

	glfwTerminate();
}

void
IG1App::display() const
{ // double buffering

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clears the back buffer
	
	if (!m2Vistas) mScenes[mCurrentScene]->render(*mCamera); // uploads the viewport and camera to the GPU
	else display2V();

	glfwSwapBuffers(mWindow); // swaps the front and back buffer
}

void
IG1App::resize(int newWidth, int newHeight)
{
	mWinW = newWidth;
	mWinH = newHeight;

	// Resize Viewport to the new window size
	mViewPort->setSize(newWidth, newHeight);

	// Resize Scene Visible Area such that the scale is not modified
	mCamera->setSize(mViewPort->width(), mViewPort->height());
}

void
IG1App::key(unsigned int key)
{
	bool need_redisplay = true;

	switch (key) {
		case 'w':
			mCamera->moveFB(+10.0);	// move forward
			break;
		case 's':
			mCamera->moveFB(-10.0);	// move back
			break;
		case 'a':
			mCamera->moveLR(+10.0);	// move left
			break;
		case 'd':
			mCamera->moveLR(-10.0);	// move right
			break;
		case 'W':
			mCamera->moveUD(-10.0);	// move up
			break;
		case 'S':
			mCamera->moveUD(+10.0);	// move down
			break;
		case '+':
			mCamera->setScale(+1.0); // zoom in  (increases the scale)
			break;
		case '-':
			mCamera->setScale(-1.0); // zoom out (decreases the scale)
			break;
		case 'l':
			mCamera->set3D();
			break;
		case 'o':
			mCamera->set2D();
			break;
		case 'u':
			mUpdateEnabled = !mUpdateEnabled;
			break;
		case 'p':
			mCamera->changePrj();
			break;
		case 'k':
			m2Vistas = !m2Vistas;
			need_redisplay = true;
			break;
		default:
			if (key >= '0' && key <= '9') {
				if (changeScene(char(key) - '0')) break;
				cout << "[NOTE] There is no scene " << char(key) << ".\n";
			}
			need_redisplay = false;
			break;
	} // switch

	if (need_redisplay)
		mNeedsRedisplay = true;
}

void
IG1App::specialkey(int key, int scancode, int action, int mods)
{
	// Only interested in press events
	if (action == GLFW_RELEASE)
		return;

	bool need_redisplay = true;

	// Handle keyboard input
	// (key reference: https://www.glfw.org/docs/3.4/group__keys.html)
	switch (key) {
		case GLFW_KEY_ESCAPE:                     // Escape key
			glfwSetWindowShouldClose(mWindow, true); // stops main loop
			break;
		case GLFW_KEY_RIGHT:
			if (mods == GLFW_MOD_CONTROL)
				mCamera->rollReal(-10); // rotates -1 on the X axis
			else
				mCamera->yawReal(10); // rotates 1 on the X axis
			break;
		case GLFW_KEY_LEFT:
			if (mods == GLFW_MOD_CONTROL)
				mCamera->rollReal(10); // rotates 1 on the Y axis
			else
				mCamera->yawReal(-10); // rotate -1 on the Y axis
			break;
		case GLFW_KEY_UP:
			mCamera->pitchReal(-10); // rotates 1 on the Z axis
			break;
		case GLFW_KEY_DOWN:
			mCamera->pitchReal(10); // rotates -1 on the Z axis
			break;
		default:
			need_redisplay = false;
			break;
	} // switch

	if (need_redisplay)
		mNeedsRedisplay = true;
}

bool
IG1App::changeScene(size_t sceneNr)
{
	// Check whether the scene exists
	if (sceneNr >= mScenes.size())
		return false;

	// Change only if a different scene
	if (sceneNr != mCurrentScene) {
		mScenes[mCurrentScene]->unload();
		mCurrentScene = sceneNr;
		mScenes[mCurrentScene]->load();
	}

	return true;
}

void 
IG1App::display2V() const {
	Camera auxCam = *mCamera;
	Viewport auxVP = *mViewPort;
	mViewPort->setSize(mWinW / 2, mWinH);

	// cenital vista
	mViewPort->setPos(mWinW / 2, 0);
	mCamera->setSize(mViewPort->width(), mViewPort->height());
	mCamera->setCenital();
	mScenes[mCurrentScene]->render(*mCamera);

	*mCamera = auxCam;

	// user vista
	mViewPort->setPos(0, 0);
	mCamera->setSize(mViewPort->width(), mViewPort->height());
	mScenes[mCurrentScene]->render(*mCamera);

	// reset configuration before leaving
	*mCamera = auxCam;
	*mViewPort = auxVP;
}

void 
IG1App::mouse(int button, int state, int mods)
{
	mMouseButt = button;
	mMouseStat = state;
	glfwGetCursorPos(mWindow, &mMouseCoord.x, &mMouseCoord.y);
}

void 
IG1App::motion(double x, double y)
{
	if (mMouseStat == GLFW_PRESS) {
		switch (mMouseButt)
		{
		case GLFW_MOUSE_BUTTON_1:	// left button
			mCamera->orbit((mMouseCoord.x - x) * 0.5, y - mMouseCoord.y);
			break;
		case GLFW_MOUSE_BUTTON_2:	// right button
			mCamera->moveLR(mMouseCoord.x - x);
			mCamera->moveUD(y - mMouseCoord.y);
			break;
		}
		mMouseCoord.x = x;
		mMouseCoord.y = y;
	}
}

void
IG1App::mouseWheel(double dx, double dy)
{
	if (glfwGetKey(mWindow, GLFW_KEY_LEFT_CONTROL) || glfwGetKey(mWindow, GLFW_KEY_RIGHT_CONTROL)) mCamera->setScale(dy * 0.3);
	else mCamera->moveFB(dy * 10.0);
}
