#include "cgvSphere.h"

#include <iostream>
#include "cgvMaterial.h"

using namespace std;

/**
 * Parametrized constructor
 * @param _r Red component [0, 255]
 * @param _g Red component [0, 255]
 * @param _b Red component [0, 255] 
 * @pre It is assumed that the parameters are valid
 * @post Create a new instance of the box with an RGB color as identifier
 */
/*cgvSphere::cgvSphere(GLubyte _r, GLubyte _g, GLubyte _b) {
	color_as_ID[0] = _r; 
	color_as_ID[1] = _g; 
	color_as_ID[2] = _b;
}*/

/**
 * Parametrized constructor
 * @param _color_as_ID It is a vector with the three component of a color Valid range [0, 255] per component
 * @pre It is assumed that the parameters are valid
 * @post Create a new instance of the box with an RGB color as identifier
 */
cgvSphere::cgvSphere(GLubyte _color_as_ID[3]) {
	for (int i = 0; i < 3; ++i) {
		color_as_ID[i] = _color_as_ID[i];
	}
}

cgvSphere::cgvSphere(float r,  float g, float b){
    color_as_ID[0] = 255;
    color_as_ID[1] = 0;
    color_as_ID[2] = 0;
    red= r;
    green= g;
    blue= b;
}

/**
 * Method to render the box
 * @param mode It can be CGV_DISPLAY (normal rendering) or CGV_SELECT and render with the color_as_ID to use the color buffer technique
 * @pre It is assumed that the parameters are valid
 * @post If mode=CGV_DISPLAY->(normal rendering) if CGV_SELECT render with the color_as_ID to use the color buffer technique
 */
void cgvSphere::render(RenderMode mode) {

	//GLfloat color_piece[] = { red,green,blue, 1.0};
	/*GLfloat color_piece_top[] = { 0,0.3,0 };

	GLfloat selected_color[] = { 1,1,0,1.0 };*/


// TODO: Section A. Add the required code to render in selection mode. Use glColor instead of glMaterial.

	// TODO: Section A. Add the required code to render the selected box as yellow (selected_color).

    //glColor3ub(); unsigned byte.

    if(mode==CGV_SELECT) {
        glColor3ubv(color_as_ID);

    }
    if(mode==CGV_DISPLAY) {
        //glMaterialfv(GL_FRONT, GL_EMISSION, color_piece);
        cgvMaterial eter= cgvMaterial({0.0,0.0,0.0,1},
                                      {0.0,0.0,0,1},
                                      {0.0,0.0,0.0,1.0}, 128);
        eter.apply();
    }


	glPushMatrix();

    GLUquadricObj* joint= gluNewQuadric();
    gluSphere(joint, 0.5, 50,50);
    gluDeleteQuadric(joint);

	glPopMatrix();


}

/**
 * Method to identify the box as selected
 * @param c RGB color with three components 
 * @pre It is assumed that the parameters are valid
 * @post The instance is marked as selected if c==color_as_ID
 */
void cgvSphere::select(GLubyte c[3]) {
	// TODO: Section A. Add the required code to check and select the appropriate box.

    if(color_as_ID[0]==c[0] && color_as_ID[1]==c[1] && color_as_ID[2]==c[2]){
        selected= true;
    }
    else{
        selected= false;
    }
	
}

