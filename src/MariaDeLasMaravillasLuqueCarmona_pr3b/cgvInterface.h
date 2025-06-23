
#pragma once

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <chrono>
#endif

#include <string>

#include "cgvScene3D.h"
#include "cgvCamera.h"

using namespace std;




class cgvInterface {
	private:
		// Attributes
		int width_window; ///< initial width of the display window
		int height_window;  ///< initial height of the display window

		cgvScene3D scene; ///< scene to be rendered in the display window defined by cgvInterface. 
		cgvCamera camera[4]; ///< Cameras to visualize the scene in four different views
        int currentCam;
        int counter = 0; //Counter to change the camera
		cameraType camType=CGV_PARALLEL; ///< Camera type 	CGV_PARALLEL or CGV_PERSPECTIVE

		///// Section D: attributes to selecting by mouse

        bool animate;
		
		// Singleton pattern
		static cgvInterface *instance; ///< Pointer to the unique instance of the class

		// Default constructor
		cgvInterface()=default;

        std::chrono::steady_clock::time_point lastUpdateTime;

		
	public:
		// Singleton pattern
		static cgvInterface& getInstance();

		// Default destructor
		~cgvInterface()=default;

		// Static methods
		// event callbacks
		static void set_glutKeyboardFunc(unsigned char key, int x, int y); // method to control keyboard events
		static void set_glutReshapeFunc(int w, int h); // method to define the camera and the viewport
		                                               // it is automatically called when the window is resized
		static void set_glutDisplayFunc(); // method to render the scene
		static void set_glutIdleFunc(); // method to animate the model. It is called whenever glut is idle. 

		// create the world that is render in the window
		void create_world(void);
		// initialize all the parameters to create a display window
		void configure_environment(int argc, char** argv, // main parameters
			                       int _width_window, int _height_window, // width and height of the display window
			                       int _pos_X, int _pos_Y, // init position of the display window
													 string _title // title of the display window
													 ); 
		void init_callbacks(); // initialize all the callbacks

		void init_rendering_loop(); // render the scene and wait for an event in the interface

		// methods get_ and set_ to access the attributes
		int get_width_window(){return width_window;};
		int get_height_window(){return height_window;};

		void set_width_window(int _width_window){width_window = _width_window;};
		void set_height_window(int _height_window){height_window = _height_window;};

    void setLastUpdateTime(std::chrono::steady_clock::time_point time);
    std::chrono::steady_clock::time_point getLastUpdateTime() const;

    bool isAnimate() const;

    void setAnimate(bool animate);

    int getCounter() const;

    void nextCounter();


    int getCurrentCam() const;

    void setCurrentCam(int currentCam);

    void change_camera();
};

