#include <stdio.h>
#include <stdlib.h>

#include "cgvInterface.h"

// Singleton pattern
cgvInterface* cgvInterface::instance = nullptr;

// Public methods ----------------------------------------
/**
 * Method to access the unique instance of the class. Singleton pattern
 * @return A reference to the unique instance of the class
 */
cgvInterface& cgvInterface::getInstance ()
{  if ( !instance )
   {  instance = new cgvInterface;
   }

   return *instance;
}

/**
 * Create world is a method to define the camera and their properties
 */
void cgvInterface::create_world(void) {

    currentCam= 0;

	/// General view camera
    camera[0] = cgvCamera(cgvPoint3D(6.0, 5.0, 6.0), cgvPoint3D(0, 0, 0), cgvPoint3D(0.0, 1.0, 0.0));
    camera[0].setParallelParameters(1 * 5, 1 * 5, 0.1, 200);
    camera[0].setPerspParameters(78, 1, 0.1, 200);

    // TODO: Practice 2B.b: Define top, lateral and front cameras, respectively

    /// Inside farm camera
    camera[1] = cgvCamera(cgvPoint3D(-4.75, 2.5, 0), cgvPoint3D(-2.5, 0, 0), cgvPoint3D(1, 0, 0));
    camera[1].setParallelParameters(1 * 5, 1 * 5, 0.1, 200);
    camera[1].setPerspParameters(78, 1, 0.1, 200);

    /// Fox Cam
    camera[2] = cgvCamera(cgvPoint3D(0.0, 0.8, -0.33), cgvPoint3D(0, 0.7, -1), cgvPoint3D(0, 0, -1));
    camera[2].setParallelParameters(1 * 5, 1 * 5, 0.1, 200);
    camera[2].setPerspParameters(78, 1, 0.1, 200);

    /// Classic camera
    camera[3] = cgvCamera(cgvPoint3D(3.0, 2.0, 4.0), cgvPoint3D(0, 0, 0), cgvPoint3D(0, 1.0, 0));
    camera[3].setParallelParameters(1 * 5, 1 * 5, -3.4, 200);

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
 * @post Cambia el alto y ancho de ventana almacenado en el objeto
 */
void cgvInterface::configure_environment(int argc, char** argv,
			                       int _width_window, int _height_window,
			                       int _pos_X, int _pos_Y,
													 string _title)
													 {
	// initialization of the interface variables
	width_window = _width_window;
	height_window = _height_window;

	// initialization of the display window
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(_width_window,_height_window);
    glutInitWindowPosition(_pos_X,_pos_Y);
	glutCreateWindow(_title.c_str());

	create_menu();

	glEnable(GL_DEPTH_TEST); // enable the removal of hidden surfaces by using the z-buffer
    glClearColor(1.0,1.0,1.0,0.0); // define the background color of the window

	glEnable(GL_LIGHTING); // enable the lighting of the scene
    glEnable(GL_NORMALIZE); // normalize the normal vectors required by the lighting computation.
	glEnable(GL_TEXTURE_2D); // enable the use of 2D textures


  create_world(); // create the world (scene) to be rendered in the window
}

/**
 * It creates a menu linked with the right mouse button
 */
void cgvInterface::create_menu() {
	int menu_id = glutCreateMenu(menuHandle);
	for (int i = 0; i<nbScenes; ++i) {
		glutAddMenuEntry(getInstance().scene.Scene_Name[i], i);
	}

	glutAttachMenu(GLUT_RIGHT_BUTTON);
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

     case 'r': //Change the animation mode
         cgvInterface::getInstance().setIdleActive(cgvInterface::getInstance().isIdleActive()?false:true);
         break;

     case 'e':
         cgvInterface::getInstance().scene.setEgg(cgvInterface::getInstance().scene.isEgg()?false:true);
         break;
     case 'a': // Section F: increase by 0.1 the R component of the diffuse coefficient of the material.
         cgvInterface::getInstance().scene.movementFunc('X',0.2);
         break;
     case 'd': // Section F: increase by 0.1 the R component of the specular coefficient of the material.
         cgvInterface::getInstance().scene.movementFunc('X',-0.2);
         break;
     case 'w': // Section F: increase by 10 the phong exponent of the material.
         cgvInterface::getInstance().scene.movementFunc('Z',0.2);
         break;
     case 's': // Section F: decrease by 10 the phong exponent of the material.
         cgvInterface::getInstance().scene.movementFunc('Z',-0.2);
         break;
     case 'p': // change the type of projection between parallel and perspective.
         if(cgvInterface::getInstance().currentCam!=2) {
             cgvInterface::getInstance().camera[cgvInterface::getInstance().currentCam].alterPerspective();
             cgvInterface::getInstance().camera[cgvInterface::getInstance().currentCam].apply();
         }
         break;
     case 'v': // change the current camera to show these views: panoramic, top, front and lateral view

         if(cgvInterface::getInstance().currentCam==1){
             cgvInterface::getInstance().scene.loadDisplacement();
             cgvInterface::getInstance().scene.loadAngles();
         }else if(cgvInterface::getInstance().currentCam==2){
             cgvInterface::getInstance().scene.saveDisplacement();
             cgvInterface::getInstance().scene.saveAngles();
             cgvInterface::getInstance().scene.restoreAngles();
             cgvInterface::getInstance().scene.restoreDisplacement();
         } else{
             cgvInterface::getInstance().scene.restoreAngles();
             cgvInterface::getInstance().scene.restoreDisplacement();
         }
         cgvInterface::getInstance().currentCam= (cgvInterface::getInstance().currentCam+1)%4;
         cgvInterface::getInstance().camera[cgvInterface::getInstance().currentCam].apply();
         break;
     case '+': // zoom in
         cgvInterface::getInstance().camera[cgvInterface::getInstance().currentCam].zoom(cgvInterface::getInstance().camera[cgvInterface::getInstance().currentCam].getZoom() - 0.05);
         cgvInterface::getInstance().camera[cgvInterface::getInstance().currentCam].apply();
         break;
     case '-': // zoom out
         cgvInterface::getInstance().camera[cgvInterface::getInstance().currentCam].zoom(cgvInterface::getInstance().camera[cgvInterface::getInstance().currentCam].getZoom() + 0.05);
         cgvInterface::getInstance().camera[cgvInterface::getInstance().currentCam].apply();
         break;
     case 'n': // increment the distance to the near plane
         cgvInterface::getInstance().camera[cgvInterface::getInstance().currentCam].increaseNearPlaneDistance();
         cgvInterface::getInstance().camera[cgvInterface::getInstance().currentCam].apply();
         break;
     case 'N': // decrement the distance to the near plane
         cgvInterface::getInstance().camera[cgvInterface::getInstance().currentCam].decreaseNearPlaneDistance();
         cgvInterface::getInstance().camera[cgvInterface::getInstance().currentCam].apply();
         break;
     case 'x':
         if(cgvInterface::getInstance().currentCam!=2) {
             cgvInterface::getInstance().scene.incrementXAngle();
         }
         break;
     case 'X':
         if(cgvInterface::getInstance().currentCam!=2) {
             cgvInterface::getInstance().scene.decrementXAngle();
         }
         break;
     case 'y':
         cgvInterface::getInstance().scene.incrementYAngle();
         break;
     case 'Y':
         cgvInterface::getInstance().scene.decrementYAngle();
         break;
     case 'z':
         if(cgvInterface::getInstance().currentCam!=2) {
             cgvInterface::getInstance().scene.incrementZAngle();
         }
         break;
     case 'Z':
         if(cgvInterface::getInstance().currentCam!=2) {
             cgvInterface::getInstance().scene.decrementZAngle();
         }
         break;
    case 'm': // enable/disable the visualization of the axes
			getInstance().scene.set_axes(getInstance().scene.get_axes()?false:true);
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
  getInstance().set_width_window(w);
  getInstance().set_height_window(h);

  // Set up the kind of projection to be used
    cgvInterface::getInstance().camera[cgvInterface::getInstance().currentCam].apply();

}

/**
 * Method to render the scene
 */
void cgvInterface::set_glutDisplayFunc() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window and the z-buffer

	// set up the viewport
	glViewport(0, 0, getInstance().get_width_window(), getInstance().get_height_window());
    // Section A: check the mode before applying the camera and projection transformations,
    if (cgvInterface::getInstance().mode == CGV_SELECT) {
        cgvInterface::getInstance().init_selection();
    }
	// Apply the camera and projection parameters
    cgvInterface::getInstance().camera[cgvInterface::getInstance().currentCam].apply();

	// Render the scene
	getInstance().scene.render(cgvInterface::getInstance().mode);

    if (cgvInterface::getInstance().mode == CGV_SELECT) {
        cgvInterface::getInstance().finish_selection();
        glutPostRedisplay();
        //glutSwapBuffers();
    }
    else {
        // refresh the window
        glutSwapBuffers(); // it is used instead of glFlush(), to avoid flickering
    }
}

/**
 * Mouse buttom detection function
 * @param button The button parameter is one of GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, or GLUT_RIGHT_BUTTON.
 * @param state The state parameter is either GLUT_UP or GLUT_DOWN
 * @param x X position of the mouse at the time the buttom is pressed or released
 * @param y Y position of the mouse at the time the buttom is pressed or released
 */
void cgvInterface::set_glutMouseFunc(GLint button,GLint state,GLint x,GLint y) {

// TODO: Section A: check if the left button of the mouse has been clicked
    // Review the documentation of glutMouseFunc in
    // Check if the state is GLUT_DOWN or not
    // If the state is GLUT_DOWN then, change to select mode, store the position of the mouse and modify the state of pressed_button
    // if the state is not GLUT_DOWN change to display mode and modify the state of pressed_button accordingly.

    // x and y are the coordinates of the click (respect the top left, remember real_y=ymax-y)
    //std::cout << "HOLA" << std::endl;
    if(button == GLUT_LEFT_BUTTON){
        cgvInterface::getInstance().pressed_button= (state==GLUT_DOWN);
        if(cgvInterface::getInstance().pressed_button){
            //std::cout << "HOLA" << std::endl;
            cgvInterface::getInstance().mode= CGV_SELECT;
        }
        else{
            cgvInterface::getInstance().mode= CGV_DISPLAY;
            cgvInterface::getInstance().pressed_button= false;
            /*if(state == GLUT_UP){
                cgvInterface::getInstance().scene.unSelectAll();
            }*/
        }
    }

    cgvInterface::getInstance().cursorX= x;
    cgvInterface::getInstance().cursorY= cgvInterface::getInstance().height_window - y;

    glutPostRedisplay();
}


/**
 * Method to handle the menu
 * @param value A new option selected
 * @pre It is assumed that the parameter is valid
 * @post It stores the selected option
 */
void cgvInterface::menuHandle(int value)
{
	getInstance().scene.set(value);
	glutPostRedisplay(); // renew the content of the window
}

/**
 * Method to indicate the callback functions
 */
void cgvInterface::init_callbacks() {
	glutKeyboardFunc(set_glutKeyboardFunc);
	glutReshapeFunc(set_glutReshapeFunc);
	glutDisplayFunc(set_glutDisplayFunc);

    glutMouseFunc(set_glutMouseFunc);
    glutIdleFunc(set_glutIdleFunc);
    //glutMotionFunc(set_glutMotionFunc);
}

/**
 * Function to do the required operations when the selection begins
 */
void cgvInterface::init_selection() {

    glDisable(GL_LIGHTING);

}

/**
 * Function to do the required operations when the selection ends
 */
void cgvInterface::finish_selection() {

    glReadBuffer(GL_BACK);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);


    GLubyte pixels[3] = { 0, 0, 0 };

    // TODO: Section A. Use the function glReadPixels to read the value of the pixel in the position of the mouse
    glReadPixels(cgvInterface::getInstance().cursorX, cgvInterface::getInstance().cursorY, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    // TODO: Section A. Once the color below the mouse is stored, then look for the corresponding box and select it.
    // Use the function assignSelection from Scene

    cgvInterface::getInstance().scene.assignSelection(pixels);

    glEnable(GL_LIGHTING); //at the end
}

void cgvInterface::set_glutIdleFunc() {
    ///// TODO: Section D: Add the required code to animate your model in a realistic way.

    if (cgvInterface::getInstance().idleActive) {
        //std::this_thread::sleep_for(20ms);
        cgvInterface::getInstance().theFoxIdleAnimation();


        glutPostRedisplay();
    }

}

void cgvInterface::theFoxIdleAnimation() {
    if(earsFlag){
        cgvInterface::getInstance().scene.incrementLeftEar();
        cgvInterface::getInstance().scene.decrementRightEar();
    }
    else{
        cgvInterface::getInstance().scene.decrementLeftEar();
        cgvInterface::getInstance().scene.incrementRightEar();
    }
    if(cgvInterface::getInstance().scene.getEarL()>=BORDER){
        earsFlag= false;
    }
    if(cgvInterface::getInstance().scene.getEarL()<=-BORDER){
        earsFlag= true;
    }

    if(tailFlag){
        cgvInterface::getInstance().scene.incrementTailY();
    }
    else{
        cgvInterface::getInstance().scene.decrementTailY();
    }
    if(cgvInterface::getInstance().scene.getTailY()>=LIMIT){
        tailFlag= false;
    }
    if(cgvInterface::getInstance().scene.getTailY()<=-LIMIT){
        tailFlag= true;
    }

    if(legsFlag){
        cgvInterface::getInstance().scene.incrementMove_leg();
    }else{
        cgvInterface::getInstance().scene.decrementMove_leg();
    }
    if(cgvInterface::getInstance().scene.getLegMov()>=BORDER){
        legsFlag= false;
    }
    if(cgvInterface::getInstance().scene.getLegMov()<=-BORDER){
        legsFlag= true;
    }

    if(headFlag){
        cgvInterface::getInstance().scene.incrementMove_head();

    }else{
        cgvInterface::getInstance().scene.decrementMove_head();
    }
    if(cgvInterface::getInstance().scene.getHeadMov()>=BORDER){
        headFlag= false;
    }
    if(cgvInterface::getInstance().scene.getHeadMov()<=-BORDER){
        headFlag= true;
    }
}

bool cgvInterface::isIdleActive() const {
    return idleActive;
}

void cgvInterface::setIdleActive(bool idleActive) {
    cgvInterface::idleActive = idleActive;
}
