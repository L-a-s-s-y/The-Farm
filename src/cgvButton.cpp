//
// Created by hardraade on 4/01/24.
//

#include "cgvButton.h"
#include "cgvSphere.h"
#include "cgvMaterial.h"
#include "cgvTexture.h"

cgvButton::cgvButton(GLubyte _r, GLubyte _g, GLubyte _b) {
    color_as_ID[0] = _r;
    color_as_ID[1] = _g;
    color_as_ID[2] = _b;
}


cgvButton::cgvButton(GLubyte _color_as_ID[3]) {
    for (int i = 0; i < 3; ++i) {
        color_as_ID[i] = _color_as_ID[i];
    }
}

/*cgvButton::cgvButton(float r, float g, float b){
    color_as_ID[0] = r;
    color_as_ID[1] = g;
    color_as_ID[2] = b;
    red= r;
    green= g;
    blue= b;
}*/

/**
 * Method to render the box
 * @param mode It can be CGV_DISPLAY (normal rendering) or CGV_SELECT and render with the color_as_ID to use the color buffer technique
 * @pre It is assumed that the parameters are valid
 * @post If mode=CGV_DISPLAY->(normal rendering) if CGV_SELECT render with the color_as_ID to use the color buffer technique
 */
void cgvButton::render(RenderMode mode) {

    //GLfloat color_piece[] = { red,green,blue, 1.0};
    /*GLfloat color_piece_top[] = { 0,0.3,0 };

    GLfloat selected_color[] = { 1,1,0,1.0 };*/


// TODO: Section A. Add the required code to render in selection mode. Use glColor instead of glMaterial.

    // TODO: Section A. Add the required code to render the selected box as yellow (selected_color).

    //glColor3ub(); unsigned byte.

    if(mode==CGV_SELECT) {
        glColor3ubv(color_as_ID);
        draw_quad(25,25,2,2.5);
    }
    if(mode==CGV_DISPLAY) {
        //glMaterialfv(GL_FRONT, GL_EMISSION, color_piece);

        cgvMaterial eter= cgvMaterial({1.0,1.0,1.0,1},
                                      {1.0,1.0,1.0,1},
                                      {0.0,0.0,0.0,1.0}, 128);
        eter.apply();
        cgvTexture* button= new cgvTexture("button_off.png");
        button->apply();
        draw_quad_textured(25,25,2,2.5);
        delete button;
    }





}

/**
 * Method to identify the box as selected
 * @param c RGB color with three components
 * @pre It is assumed that the parameters are valid
 * @post The instance is marked as selected if c==color_as_ID
 */
void cgvButton::select(GLubyte c[3]) {
    // TODO: Section A. Add the required code to check and select the appropriate box.

    if(color_as_ID[0]==c[0] && color_as_ID[1]==c[1] && color_as_ID[2]==c[2]){
        selected= true;
    }
    else{
        selected= false;
    }

}

void cgvButton::draw_quad_textured(unsigned int divX, unsigned int divY, const float quadLength, const float quadWidth) const {


    glBegin(GL_QUADS);

    const float xIncrement= quadLength/divX;
    const float yIncrement= quadWidth/divY;

    for (float i = 0; i < quadLength; i+= xIncrement) {
        for (float j = 0; j < quadWidth ; j+= yIncrement) {

            glNormal3f(0, 1, 0);

            glTexCoord2f(i/quadLength, j/quadWidth);
            glVertex3f(i,0,j);

            glTexCoord2f(i/quadLength, (j+yIncrement)/quadWidth);
            glVertex3f(i,0,j+yIncrement);

            glTexCoord2f((i+xIncrement)/quadLength, (j+yIncrement)/quadWidth);
            glVertex3f(i+xIncrement,0, j+yIncrement);

            glTexCoord2f((i+xIncrement)/quadLength, j/quadWidth);
            glVertex3f(i+xIncrement,0, j);
        }
    }
    glEnd();

}

void cgvButton::draw_quad(unsigned int divX, unsigned int divY, const float quadLength, const float quadWidth) const {


    glBegin(GL_QUADS);

    const float xIncrement= quadLength/divX;
    const float yIncrement= quadWidth/divY;

    for (float i = 0; i < quadLength; i+= xIncrement) {
        for (float j = 0; j < quadWidth ; j+= yIncrement) {

            glNormal3f(0, 1, 0);

            //glTexCoord2f(i/quadLength, j/quadWidth);
            glVertex3f(i,0,j);

            //glTexCoord2f(i/quadLength, (j+yIncrement)/quadWidth);
            glVertex3f(i,0,j+yIncrement);

            //glTexCoord2f((i+xIncrement)/quadLength, (j+yIncrement)/quadWidth);
            glVertex3f(i+xIncrement,0, j+yIncrement);

            //glTexCoord2f((i+xIncrement)/quadLength, j/quadWidth);
            glVertex3f(i+xIncrement,0, j);
        }
    }
    glEnd();

}