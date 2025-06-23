#include <cstdlib>
#include <stdio.h>
#include <chrono>

#include "cgvInterface.h"


// Singleton pattern
cgvInterface *cgvInterface::instance = nullptr;

// Public methods ----------------------------------------
/**
 * Method to access the unique instance of the class. Singleton pattern
 * @return A reference to the unique instance of the class
 */
cgvInterface &cgvInterface::getInstance() {
    if (!instance) {
        instance = new cgvInterface;
    }

    return *instance;
}

/**
 * Create a new empty world with a camera
 */
void cgvInterface::create_world(void) {
    camera[0] = cgvCamera(cgvPoint3D(3.0, 2.0, 4), cgvPoint3D(0, 0, 0), cgvPoint3D(0, 1.0, 0));
    camera[0].setParallelParameters(1 * 4, 1 * 4, 0.5, 200);

    camera[1] = cgvCamera(cgvPoint3D(0, 5.5, 0), cgvPoint3D(0, 0, 0), cgvPoint3D(1, 0, 0));
    camera[1].setParallelParameters(1 * 4, 1 * 4, 0.5, 200);

    camera[2] = cgvCamera(cgvPoint3D(5.5, 0, 0), cgvPoint3D(0, 0, 0), cgvPoint3D(0, 1, 0));
    camera[2].setParallelParameters(1 * 4, 1 * 4, 0.5, 200);

    camera[3] = cgvCamera(cgvPoint3D(0, 0, 5.5), cgvPoint3D(0, 0, 0), cgvPoint3D(0, 1, 0));
    camera[3].setParallelParameters(1 * 4, 1 * 4, 0.5, 200);
}



/**
 * Initialize the required parameters to create a window
 * @param argc Parameter from the main function of the program to know the number of input parameters from the command line
 * @param argv Parámeter from the command line to run the whole program
 * @param _width_window Initial width of the window
 * @param _height_window Initial height of the window
 * @param _pos_X Initial position of the window (X coordinate)
 * @param _pos_Y Initial position of the window (Y coordinate)
 * @param _title Title of the window
 * @pre It is assumed that the parameters have valid values
 * @post Change the height and weight of the window stored in the object
 */
void cgvInterface::configure_environment(int argc, char **argv,
                                         int _width_window, int _height_window,
                                         int _pos_X, int _pos_Y,
                                         string _title) {
    // initialization of the interface variables
    width_window = _width_window;
    height_window = _height_window;

    // initialization of the display window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(_width_window, _height_window);
    glutInitWindowPosition(_pos_X, _pos_Y);
    glutCreateWindow(_title.c_str());

    glEnable(GL_DEPTH_TEST); // enable the removal of hidden surfaces by using the z-buffer
    glClearColor(1.0, 1.0, 1.0, 0.0); // define the background color of the window

    glEnable(GL_LIGHTING); // enable the lighting of the scene
    glEnable(GL_NORMALIZE); // normalize the normal vectors required by the lighting computation.

    create_world(); // create the world (scene) to be rendered in the window
}

/**
 * Infinite loop to render the scene and wait for new events in the interface
 */
void cgvInterface::init_rendering_loop() {
    glutMainLoop(); // initialize the visualization loop of OpenGL
}

/**
 * Method to control the keyboard events
 * @param key Pressed key code 
 * @param x Mouse position (x coordinate) when the key was pressed
 * @param y Mouse position (y coordinate) when the key was pressed
 * @pre It is assumed that the parameters have valid values
 * @post The attribute that indicate whether the axes are rendered or not can be updated.
 */
void cgvInterface::set_glutKeyboardFunc(unsigned char key, int x, int y) {
    switch (key) {
////// TODO: Section C: include here the modification of the degree of freedom by pressing the corresponding keys


        case 'a': // enable/disable the visualization of the axes
            cgvInterface::getInstance().scene.set_axes(cgvInterface::getInstance().scene.get_axes() ? false : true);

            break;
        case 'x': // Positive rotation in the x axis
            cgvInterface::getInstance().scene.add_rotation(1.0, 0.0, 0.0);
            break;
        case 'X':// Negative rotation in the x axis
            cgvInterface::getInstance().scene.remove_rotation(1.0, 0.0, 0.0);
            break;
        case 'y': // Positive rotation in the y axis
            cgvInterface::getInstance().scene.add_rotation(0.0, 1.0, 0.0);
            break;
        case 'Y':// Negative rotation in the y axis
            cgvInterface::getInstance().scene.remove_rotation(0.0, 1.0, 0.0);
            break;
        case 'z':  // Positive rotation in the z axis
            cgvInterface::getInstance().scene.add_rotation(0.0, 0.0, 1.0);
            break;
        case 'Z': // Negative rotation in the z axis
            cgvInterface::getInstance().scene.remove_rotation(0.0, 0.0, 1.0);
            break;
        case 'h':
            cgvInterface::getInstance().scene.move_head(2);
            break;
        case 'b':
            cgvInterface::getInstance().scene.move_beak(1);
            break;
        case 'l':
            cgvInterface::getInstance().scene.move_leg(2);
            break;
        case 'r': //Change the animation mode
            if (cgvInterface::getInstance().isAnimate())
                cgvInterface::getInstance().setAnimate(false);
            else
                cgvInterface::getInstance().scene.setHeadMov(-cgvInterface::getInstance().scene.getHeadMov());
                cgvInterface::getInstance().scene.setLegMov(-cgvInterface::getInstance().scene.getLegMov());
                cgvInterface::getInstance().setAnimate(true);
            break;
        case 'e':
            if(cgvInterface::getInstance().scene.isEgg()){
                cgvInterface::getInstance().scene.setEgg(false);
            }else{
                cgvInterface::getInstance().scene.setEgg(true);
            }
            break;
        case 'v': // change the current camera to show these views: panoramic, top, front and lateral view
            cgvInterface::getInstance().change_camera();
            break;
        case 27: // Escape key to exit
            exit(1);
            break;
    }
    glutPostRedisplay(); // renew the content of the window
}

/**
 * Method that is called when the window changes its size. It defines the camera, the projection and the viewport 
 * @param w Width of the window
 * @param h Height of the window
 * @pre It is assumed that the parameters have valid values
 */
void cgvInterface::set_glutReshapeFunc(int w, int h) {
    // dimension of the viewport with a new width and a new height of the display window



    // store the new values of the viewport and the display window.
    cgvInterface::getInstance().set_width_window(w);
    cgvInterface::getInstance().set_height_window(h);

    // Set up the kind of projection to be used
    cgvInterface::getInstance().camera[cgvInterface::getInstance().currentCam].apply();

}

/**
 * Method to render the scene
 */
void cgvInterface::set_glutDisplayFunc() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window and the z-buffer

    // set up the viewport
    glViewport(0, 0, cgvInterface::getInstance().get_width_window(), cgvInterface::getInstance().get_height_window());

    // Apply the camera and projection transformations
    cgvInterface::getInstance().camera[cgvInterface::getInstance().currentCam].apply();

    // Render the scene
    cgvInterface::getInstance().scene.render();

    // refresh the window
    glutSwapBuffers(); // it is used instead of glFlush(), to avoid flickering

}

/**
 * Method where it is included the changes for animating the model
 */
void cgvInterface::set_glutIdleFunc() {
    ///// TODO: Section D: Add the required code to animate your model in a realistic way.
    if (cgvInterface::getInstance().isAnimate()) {
        // Get the current time
        auto currentTime = std::chrono::steady_clock::now();
        // Calculate the elapsed time since the last frame
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - cgvInterface::getInstance().getLastUpdateTime()).count();
        // Set the last update time to the current time
        cgvInterface::getInstance().setLastUpdateTime(currentTime);

        int rotation = 20;

        cgvInterface::getInstance().scene.move_head(rotation * elapsedTime / 1000.0);
        cgvInterface::getInstance().scene.move_leg(rotation * elapsedTime / 1000.0);

        glutPostRedisplay(); // Trigger a redraw
    }
}


/**
 * Method to indicate the callback functions
 */
void cgvInterface::init_callbacks() {
    glutKeyboardFunc(set_glutKeyboardFunc);
    glutReshapeFunc(set_glutReshapeFunc);
    glutDisplayFunc(set_glutDisplayFunc);
    glutIdleFunc(set_glutIdleFunc);

}

bool cgvInterface::isAnimate() const {
    return animate;
}

void cgvInterface::setAnimate(bool animate) {
    cgvInterface::animate = animate;
}

// Method to set the last update time
void cgvInterface::setLastUpdateTime(std::chrono::steady_clock::time_point time) {
    lastUpdateTime = time;
}

std::chrono::steady_clock::time_point cgvInterface::getLastUpdateTime() const {
    return lastUpdateTime;
}


void cgvInterface::change_camera(){
    cgvInterface::getInstance().setCurrentCam(cgvInterface::getInstance().getCounter());
    cgvInterface::getInstance().nextCounter();
}


int cgvInterface::getCurrentCam() const {
    return currentCam;
}

void cgvInterface::setCurrentCam(int currentCam) {
    cgvInterface::currentCam = currentCam;
}

int cgvInterface::getCounter() const {
    return counter;
}

void cgvInterface::nextCounter() {
    if(counter==3){
        cgvInterface::counter = 0;
    }else{
        cgvInterface::counter = counter+1;
    }

}




