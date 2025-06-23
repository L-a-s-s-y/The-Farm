#pragma once

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#else

#include <GL/glut.h>

#endif // defined(__APPLE__) && defined(__MACH__)

#include <string>

#include "cgvScene3D.h"
#include "cgvCamera.h"

#include <chrono>

using namespace std;

class cgvInterface {
	protected:
		// Attributes
		int width_window; ///< initial width of the display window
		int height_window;  ///< initial height of the display window

		cgvScene3D scene; ///< Scene to be rendered in the display window defined by cgvInterface.
        cgvCamera camera[4];
        int currentCam;


        /// Color buffer stuff
        RenderMode mode= CGV_DISPLAY;
        int cursorX, cursorY;
        bool pressed_button= false;

		// Singleton pattern
		static cgvInterface *instance; ///< Pointer to the unique instance of the class

        ///Animation stuff
        std::chrono::steady_clock::time_point lastUpdateTime;
        bool animate;
        bool earsFlag= true;
        bool tailFlag= true;
        bool idleActive= true;
        bool legsFlag= true;
        bool headFlag= true;


	public:
		// Singleton pattern
		static cgvInterface& getInstance();

		// Default constructor and destructor
		cgvInterface()=default;
		~cgvInterface()=default;

		// Static methods
		// event callbacks
		static void set_glutKeyboardFunc(unsigned char key, int x, int y); // method to control keyboard events
		static void set_glutReshapeFunc(int w, int h); // method to define the camera and the viewport
		                                               // it is automatically called when the window is resized
		static void set_glutDisplayFunc(); // method to render the scene

        /// Methods to control the click of the mouse
        static void set_glutMouseFunc(GLint button, GLint state, GLint x, GLint y); //control mouse clicking

        static void set_glutIdleFunc();

		static void menuHandle(int value); // method to handle the menu

		// Methods

        void init_selection();
        void finish_selection();

		// create the world that is render in the window
		void create_world(void);
		// initialize all the parameters to create a display window
		void configure_environment(int argc, char** argv, // main parameters
			                       int _width_window, int _height_window, // width and height of the display window
			                       int _pos_X, int _pos_Y, // init position of the display window
													 string _title // title of the display window
													 );
		void create_menu(); // Create a menu that is handle with the right button of the mouse.

		void init_callbacks(); // init all the callbacks

		void init_rendering_loop(); // render the scene and wait for an event in the interface

		// methods get_ and set_ to access the attributes
		int get_width_window(){return width_window;};
		int get_height_window(){return height_window;};

		void set_width_window(int _width_window){width_window = _width_window;};
		void set_height_window(int _height_window){height_window = _height_window;};

        void theFoxIdleAnimation();
        void setIdleActive(bool idleActive);
        bool isIdleActive() const;

};

