#include <stdlib.h>

#include "cgvInterface.h"


int main (int argc, char** argv) {
	// initialize the display window
	cgvInterface::getInstance().configure_environment(argc,argv,
											1000,1000, // window size
											100,100, // window position
											"de_farm" // title of the window
														 );

	// define the callbacks to manage the events. 
	cgvInterface::getInstance().init_callbacks();

	// initialize the loop of the OpenGL visualization
	cgvInterface::getInstance().init_rendering_loop();

	return(0);
}
