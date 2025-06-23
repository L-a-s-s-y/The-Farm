#include <stdlib.h>
#include <stdio.h>

#include "cgvScene3D.h"
#include "cgvLight.h"
#include "cgvMaterial.h"
#include "cgvTexture.h"

// Constructor methods -----------------------------------

/**
 * Basic constructor 
 */
cgvScene3D::cgvScene3D () {

    //Scene_Name[1] = (char *)"The World";
    /*Scene_Name[4] = (char *)"The Chicken";
    Scene_Name[3] = (char *)"The Fox";
    Scene_Name[2] = (char *)"The Building";
	Scene_Name[1] = (char *)"The World";*/
	Scene_Name[0] = (char *)"The Farm";
    nose= cgvSphere(0,0,255);
    button1= cgvButton(0,255,0);
    //button2= cgvButton(255,0,0);

}



// Public methods ----------------------------------------

/**
 * Method to set the part of the scene to be rendered. 
 */
void cgvScene3D::set(int scene) {
	selectedScene = scene;
}



/**
 * Method to render the scene
 */
void cgvScene3D::render(RenderMode mode) {
  
	// create the model
	//glPushMatrix(); // store the model matrices

	  // draw the axes
	  if ((axes) && (mode==CGV_DISPLAY)) draw_axes();

      cgvLight helios= cgvLight(GL_LIGHT0,
                              {5.0,5.0,5.0},
                              {0.80,0.8,0.8,0.1},
                              {1.0,1.0,1.0,1.0},
                              {1.0,1.0,1.0,1.0},
                              1.0, 0.0, 0.0);

      helios.apply();

      glPushMatrix(); /// 0
        glPushMatrix();
            glTranslatef(0,0.5,0);
            glScalef(0.10,0.10,0.10);
            glRotated(180,0,1,0);
            fox(mode);
        glPopMatrix();

        glTranslated(xMovement,0,zMovement);

        glRotated(angleX,1,0,0);
        glRotated(angleY,0,1,0);
        glRotated(angleZ,0,0,1);

        cgvLight little_helios= cgvLight(GL_LIGHT1,
                                         {-4,2.5,0},
                                         {0.8,0.0,0.0,1.0},
                                         {0.8,0.0,0.0,1.0},
                                         {0.8,0.0,0.0,1.0},
                                         1.0, 0.0, 0.0,
                                         {0.47,-1.0, 0.0},
                                         25,0);
        little_helios.apply();

    if (selectedScene == 0) {

        glPushMatrix(); /// 1

        if(button1.isSelected()){
            setEgg(true);
        } else{
            setEgg(false);
        }

        glPushMatrix();
            glTranslatef(-2,0,0);
            glTranslatef(0,1,0);
            glTranslatef(0,0,1.35);
            glScalef(0.1,0.1,0.1);
            glRotated(90,1,0,0);
            glTranslatef(0,0,-2.5);
            cgvButton button1= cgvButton(0,255,0);
            button1.render(mode);
        glPopMatrix();

        /// CHICKENS
            glPushMatrix();/// 2
                glTranslatef(-3,0.3,0);
                glScalef(0.5,0.5,0.5);

                glPushMatrix();
                    glRotated(123,0,1,0);
                    chicken();
                glPopMatrix();

                glTranslated(0,0,-1);
                chicken();

                glTranslatef(1,0,0.1);
                glPushMatrix();
                    glRotated(30,0,1,0);
                    chicken();
                glPopMatrix();

                glTranslatef(1.3,0,1.1);
                glPushMatrix();
                    glRotated(60,0,1,0);
                    chicken();
                glPopMatrix();

                glTranslatef(-3.3,0,0);
                glPushMatrix();
                    glRotated(65,0,1,0);
                    chicken();
                glPopMatrix();

                glTranslatef(1.3,0,1.3);
                glPushMatrix();
                    glRotated(-32,0,1,0);
                    chicken();
                glPopMatrix();

                glTranslatef(-1.7,0,-2.3);
                glPushMatrix();
                    glRotated(33,0,1,0);
                    chicken();
                glPopMatrix();
            glPopMatrix(); ///2

            glPushMatrix();/// 3

                cgvMaterial eter= cgvMaterial({1.0,1.0,1.0},
                                               {1.0,1.0,1.0},
                                               {0.0,0.0,0.0},
                                               128);
                eter.apply();

                /// SOIL
                cgvTexture* texture= new cgvTexture("grass512.png");
                texture->apply();
                glPushMatrix();
                    glTranslated(-6.5,0,-6.5);
                    draw_quad_textured(50,50,13,13);
                glPopMatrix();
                delete texture;

                /// SKY
                cgvTexture* sky_texture= new cgvTexture("skysun_veryLow.png");
                sky_texture->apply();
                glPushMatrix();
                    glTranslated(-6.5,6,-6.5);
                    draw_quad_textured(50,50,13,13);
                glPopMatrix();
                delete sky_texture;

                /// Back-right
                cgvTexture* hedge_texture= new cgvTexture("crops_veryLow.png");
                hedge_texture->apply();
                glPushMatrix();
                    glTranslatef(0,0,-6.5);
                    glRotated(90,1,0,0);
                    glTranslatef(-6.5,0,-6);
                    draw_quad_textured(50,50,13,6);
                glPopMatrix();

                /// Back-left
                glPushMatrix();
                    glTranslated(-6.5,0,0);
                    glRotated(180,0,1,0);
                    glRotated(-90,0,0,1);
                    glTranslated(-6,0,6.5);
                    glRotated(90,0,1,0);
                    draw_quad_textured(50,50,13,6);
                glPopMatrix();

                ///Front-left
                glPushMatrix();
                    glTranslatef(0,0,6.5);
                    glRotated(180,0,1,0);
                    glRotated(90,1,0,0);
                    glTranslatef(-6.5,0,-6);
                    draw_quad_textured(50,50,13,6);
                glPopMatrix();

                ///Front-right
                glPushMatrix();
                    glTranslatef(6.5,0,0);
                    glRotated(-90,0,0,1);
                    glTranslated(-6,0,6.5);
                    glRotated(90,0,1,0);
                    draw_quad_textured(50,50,13,6);
                glPopMatrix();
                delete hedge_texture;
            glPopMatrix();/// 3

            glPushMatrix();
                glTranslatef(-3,0.1,0);
                glScalef(0.5,0.5,0.5);
                farm();
            glPopMatrix();
        glPopMatrix(); /// 1
	  }

	  // Assign the OpenGL default material. 
	  cgvMaterial defaultMat(cgvColor4f( 0.2, 0.2, 0.2, 1 ), cgvColor4f( 0.8, 0.8, 0.8, 1 ), cgvColor4f( 0.0, 0, 0, 1 ), 0);
	  defaultMat.apply();

	glPopMatrix (); /// 0; restore the modelview matrix
  
}

void cgvScene3D::assignSelection(GLubyte *_c) {
    nose.select(_c);
    button1.select(_c);
    //vbutton2.select(_c);
}


/**** P R I V A T E    M E T H O D S                    ***/

/**
 Method to render the axes
 */
void cgvScene3D::draw_axes(void) const {
  GLfloat red[]={1,0,0,1.0};
  GLfloat green[]={0,1,0,1.0};
  GLfloat blue[]={0,0,1,1.0};

	glBegin(GL_LINES);
    glMaterialfv(GL_FRONT,GL_EMISSION,red);
		glVertex3f(1000,0,0);
		glVertex3f(-1000,0,0);

    glMaterialfv(GL_FRONT,GL_EMISSION,green);
		glVertex3f(0,1000,0);
		glVertex3f(0,-1000,0);

    glMaterialfv(GL_FRONT,GL_EMISSION,blue);
		glVertex3f(0,0,1000);
		glVertex3f(0,0,-1000);
	glEnd();
}


void cgvScene3D::draw_triangle_textured(unsigned int divX, unsigned int divY, const float quadLength, const float quadWidth) const {

    //const float quadLength= 13;
    //const float quadWidth= 13;

    glBegin(GL_QUADS);

    const float xIncrement= quadLength/divX;
    const float yIncrement= quadWidth/divY;

    for (float i = 0; i < quadLength; i+= xIncrement) {
        for (float j = 0; j < quadWidth-(quadWidth-i) ; j+= yIncrement) {

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

void cgvScene3D::draw_quad_textured(unsigned int divX, unsigned int divY, const float quadLength, const float quadWidth) const {


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

void cgvScene3D::humerus() {
    glPushMatrix();

        cgvMaterial eter= cgvMaterial({0.8,0.47,0.0,1},
                                      {0.47,0.34,0.0,1},
                                      {0.0,0.0,0.0,1.0}, 128);
        eter.apply();

        GLUquadricObj* humerus= gluNewQuadric();
        glRotated(-77,1,0,0);
        glRotated(45,0,0,1);
        gluCylinder(humerus, 0.4, 0.7, 1.6, 4,2);
        gluDeleteQuadric(humerus);
    glPopMatrix();
}

void cgvScene3D::hand() {
    glPushMatrix();
        cgvMaterial eter= cgvMaterial({0.4,0.4,0.4,1},
                                      {0.3,0.3,0.3,1},
                                      {0.0,0.0,0.0,1.0}, 128);
        eter.apply();

        glScalef(0.4,0.18,0.8);
        glutSolidCube(1);
    glPopMatrix();
}

void cgvScene3D::armR() {

    glPushMatrix();
        glTranslatef(-1.4,0,3.5);
        joint(1, 0.647,0);
        glTranslatef(0,-1.8,-0.4);
        humerus();

        glPushMatrix();
            glScalef(0.65,0.65,0.65);
            joint(1, 0.647,0);
        glPopMatrix();

        radio();

        glTranslatef(0,-2.3,0.53);
        glPushMatrix();
            glScalef(0.45,0.45,0.45);
            joint(1, 0.647,0);
        glPopMatrix();

        glTranslatef(0,-0.135,0.2);
        hand();
    glPopMatrix();
}

void cgvScene3D::armL() {
    glPushMatrix();
        glTranslatef(1.4,0,3.5);
        joint(1, 0.647,0);
        glTranslatef(0,-1.8,-0.4);
        humerus();

        glPushMatrix();
            glScalef(0.65,0.65,0.65);
            joint(1, 0.647,0);
        glPopMatrix();

        radio();

        glTranslatef(0,-2.3,0.53);
        glPushMatrix();
            glScalef(0.45,0.45,0.45);
            joint(1, 0.647,0);
        glPopMatrix();

        glTranslatef(0,-0.135,0.2);
        hand();
    glPopMatrix();
}

void cgvScene3D::femur() {
    glPushMatrix();

        cgvMaterial eter= cgvMaterial({0.8,0.47,0.0,1},
                                      {0.47,0.34,0.0,1},
                                      {0.0,0.0,0.0,1.0}, 128);
        eter.apply();

        GLUquadricObj* humerus= gluNewQuadric();
        glRotated(77,1,0,0);
        glRotated(45,0,0,1);
        gluCylinder(humerus, 0.7, 0.4, 2, 4,2);
        gluDeleteQuadric(humerus);
    glPopMatrix();
}

void cgvScene3D::tibia() {
    glPushMatrix();

        cgvMaterial eter= cgvMaterial({0.25,0.25,0.25,1},
                                      {0.14,0.14,0.14,1},
                                      {0.0,0.0,0.0,1.0}, 128);
        eter.apply();

        GLUquadricObj* tibia= gluNewQuadric();
        glRotated(-57,1,0,0);
        glRotated(45,0,0,1);
        gluCylinder(tibia, 0.3, 0.4, 1.5, 4,2);
        gluDeleteQuadric(tibia);
    glPopMatrix();
}

void cgvScene3D::foot() {
    glPushMatrix();
        cgvMaterial eter= cgvMaterial({0.30,0.30,0.30,1},
                                      {0.20,0.20,0.20,1},
                                      {0.0,0.0,0.0,1.0}, 128);
        eter.apply();

        GLUquadricObj* tibia= gluNewQuadric();
        glRotated(37,1,0,0);
        glRotated(45,0,0,1);
        gluCylinder(tibia, 0.3, 0.2, 1.1, 4,2);
        gluDeleteQuadric(tibia);
    glPopMatrix();
}

void cgvScene3D::legR() {
    glPushMatrix();
        glTranslatef(-1,0,0.5);
        joint(1, 0.647,0);
        femur();
        glTranslatef(0,-1.95,0.5);

        glPushMatrix();
            glTranslatef(0,0,-0.1);
            glScalef(0.65,0.65,0.65);
            joint(1, 0.647,0);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0,-1.4,-1);
            tibia();

            glTranslatef(0,-0.1,-0.06);
            glPushMatrix();
                glScalef(0.45,0.45,0.45);
                joint(1, 0.647,0);
            glPopMatrix();

            foot();

            glTranslatef(0,-0.68,0.9);
            glPushMatrix();
                glScalef(0.3,0.3,0.3);
                joint(1, 0.647,0);
            glPopMatrix();

            glTranslatef(0,-0.1,0.3);
            hand();
        glPopMatrix();
    glPopMatrix();
}

void cgvScene3D::legL() {
    glPushMatrix();
        glTranslatef(1,0,0.5);
        joint(1, 0.647,0);
        femur();
        glTranslatef(0,-1.95,0.5);

        glPushMatrix();
            glTranslatef(0,0,-0.1);
            glScalef(0.65,0.65,0.65);
            joint(1, 0.647,0);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0,-1.4,-1);
            tibia();

            glTranslatef(0,-0.1,-0.06);
            glPushMatrix();
                glScalef(0.45,0.45,0.45);
                joint(1, 0.647,0);
            glPopMatrix();

            foot();

            glTranslatef(0,-0.68,0.9);
            glPushMatrix();
                glScalef(0.3,0.3,0.3);
                joint(1, 0.647,0);
            glPopMatrix();

            glTranslatef(0,-0.1,0.3);
            hand();
        glPopMatrix();
    glPopMatrix();
}

void cgvScene3D::radio() {
    glPushMatrix();

        cgvMaterial eter= cgvMaterial({0.25,0.25,0.25,1},
                                      {0.14,0.14,0.14,1},
                                      {0.0,0.0,0.0,1.0}, 128);
        eter.apply();

        GLUquadricObj* humerus= gluNewQuadric();
        glRotated(77,1,0,0);
        glRotated(45,0,0,1);
        gluCylinder(humerus, 0.4, 0.3, 2.3, 4,2);
        gluDeleteQuadric(humerus);
    glPopMatrix();
}

void cgvScene3D::joint(float r, float g, float b) {
    glPushMatrix();

        cgvMaterial eter= cgvMaterial({1,0.67,0.0,1},
                                      {0.67,0.34,0.0,1},
                                      {0.0,0.0,0.0,1.0}, 128);
        eter.apply();

        GLUquadricObj* joint= gluNewQuadric();
        gluSphere(joint, 0.5, 50,50);
        gluDeleteQuadric(joint);
    glPopMatrix();
}

void cgvScene3D::neck() {
    glPushMatrix();

        cgvMaterial eter= cgvMaterial({0.8,0.47,0.0,1},
                                      {0.47,0.34,0.0,1},
                                      {0.0,0.0,0.0,1.0}, 128);
        eter.apply();

        GLUquadricObj* neck= gluNewQuadric();
        glScalef(0.85,0.85,0.85);
        gluCylinder(neck , 0.4, 0.4, 1, 50, 50);
        gluDeleteQuadric(neck);
    glPopMatrix();
}

void cgvScene3D::tail() {
    glPushMatrix();
        cgvMaterial eter= cgvMaterial({1,0.67,0.0,1},
                                      {0.67,0.34,0.0,1},
                                      {0.0,0.0,0.0,1.0}, 128);
        eter.apply();

        GLUquadricObj* tail1= gluNewQuadric();
        gluCylinder(tail1 , 0.7, 0.5, 0.8, 50, 50);

        glTranslatef(0,0,-2);
        GLUquadricObj* tail2= gluNewQuadric();
        gluCylinder(tail2 , 0.7, 0.7, 2, 50, 50);

        cgvMaterial eter2= cgvMaterial({0.7,0.7,0.7,1},
                                      {0.6,0.6,0.6,1},
                                      {0.0,0.0,0.0,1.0}, 128);
        eter2.apply();

        glTranslatef(0,0,-2);
        GLUquadricObj* tail4= gluNewQuadric();
        gluCylinder(tail4, 0.5, 0.7, 2, 50, 50);

        glTranslatef(0,0,-1.5);
        GLUquadricObj* tail3= gluNewQuadric();
        gluCylinder(tail3, 0, 0.5, 1.5, 50, 50);

        gluDeleteQuadric(tail1);
        gluDeleteQuadric(tail2);
        gluDeleteQuadric(tail3);
        gluDeleteQuadric(tail4);
    glPopMatrix();
}

void cgvScene3D::head(RenderMode mode) {
    cgvMaterial eter= cgvMaterial({0.8,0.47,0.0,1},
                                  {0.47,0.34,0.0,1},
                                  {0.0,0.0,0.0,1.0}, 128);
    eter.apply();

    glPushMatrix();
        glPushMatrix();
            glScalef(2,2,1);
            glutSolidCube(1);
        glPopMatrix();

        eter= cgvMaterial({1.0,0.67,0.0,1},
                          {0.67,0.34,0.0,1},
                          {0.0,0.0,0.0,1.0}, 128);
        eter.apply();

        glPushMatrix();

            glRotated(-90,1,0,0);
            ////TODO: ear rotation
            glRotated(earR,0,0,1);
            glRotated(-30,0,0,1);
            glTranslatef(-0.45,-0.3,1.0);
            glScalef(0.5,0.5,0.5);
            glutSolidCone(1,2,3,3);
        glPopMatrix();

        glPushMatrix();
            glRotated(-90,1,0,0);
            ////TODO: earRotation
            glRotated(earL,0,0,1);
            glRotated(-30,0,0,1);
            glTranslatef(0.5,0.2,1.0);
            glScalef(0.5,0.5,0.5);
            glutSolidCone(1,2,3,3);
        glPopMatrix();

        //--glPopMatrix();
        glTranslatef(0,-0.15,0.7);
        glPushMatrix();
        eter= cgvMaterial({0.0,0.0,0.0,1},
                          {0.0,0.0,0.0,1},
                          {0.0,0.0,0.0,1.0}, 128);
        eter.apply();
            glScalef(1.25,1.25,0.4);
            glutSolidCube(1);
        glPopMatrix();

        glTranslatef(0,0,0.2);
        glPushMatrix();
            cgvMaterial eter2= cgvMaterial({0.7,0.7,0.7,1},
                                           {0.6,0.6,0.6,1},
                                           {0.0,0.0,0.0,1.0}, 128);
            eter2.apply();
            glRotated(45,0,0,1);
            glutSolidCone(0.89,2,4,4);
        glPopMatrix();

        glTranslatef(0,0,1.8);
        glScalef(0.5,0.5,0.5);
        //joint(0, 0,0);
        nose.render(mode);
    glPopMatrix();
}

void cgvScene3D::chest(RenderMode mode) {

    cgvMaterial eter= cgvMaterial({0.8,0.47,0.0,1},
                                  {0.47,0.34,0.0,1},
                                  {0.0,0.0,0.0,1.0}, 128);
    eter.apply();

    glPushMatrix();
        GLUquadricObj* chest= gluNewQuadric();
        glPushMatrix();
            glRotated(45,0,0,1);
            gluCylinder(chest, 1, 1.7, 4, 4,2);
        glPopMatrix();

        GLUquadricObj* chest2= gluNewQuadric();
        glTranslatef(0,0,4);
        glPushMatrix();
            glRotated(45,0,0,1);
            gluCylinder(chest2, 1.7, 0.5, 0.5, 4,2);
        glPopMatrix();

        glTranslatef(0,0,0.45);
        glPushMatrix();
            glRotated(-40,1,0,0);
            glPushMatrix();
                glScalef(0.85,0.85,0.85);
                joint(1, 0.647,0);
            glPopMatrix();

            glTranslatef(0,0,0.3);
            neck();
        glPopMatrix();

        glTranslatef(0,0.85,1.0);
        ////TODO: head rotation
        glRotated(headX,1,0,0);
        glRotated(headY,0,1,0);
        glRotated(headZ,0,0,1);
        glPushMatrix();
            glScalef(0.75,0.75,0.75);
            joint(1, 0.647,0);
        glPopMatrix();

        glTranslatef(0,0.2,0.4);
        glPushMatrix();
            glScalef(0.75,0.75,0.75);
            head(mode);
        glPopMatrix();
    glPopMatrix();

    eter= cgvMaterial({0.8,0.47,0.0,1},
                                  {0.47,0.34,0.0,1},
                                  {0.0,0.0,0.0,1.0}, 128);
    eter.apply();
    glPushMatrix();
        //glMaterialfv(GL_FRONT,GL_EMISSION,mesh_color);

        GLUquadricObj* back= gluNewQuadric();
        glTranslatef(0,0,-0.5);
        glPushMatrix();
            glRotated(45,0,0,1);
            gluCylinder(back, 0.5, 1, 0.5, 4,2);
        glPopMatrix();

        ////TODO: tail rotation
        glRotated(tailX,1,0,0);
        glRotated(tailY,0,1,0);
        glRotated(tailZ,0,0,1);

        glPushMatrix();
            glScalef(0.80,0.80,0.80);
            joint(1, 0.647,0);
        glPopMatrix();

        glRotated(-20,1,0,0);
        glTranslatef(0,0,-0.75);

        glPushMatrix();
            glScalef(0.75,0.75,0.75);
            tail();
        glPopMatrix();
    glPopMatrix();

    armL();
    armR();
    legL();
    legR();

    gluDeleteQuadric(chest);
    gluDeleteQuadric(chest2);
    gluDeleteQuadric(back);
}

void cgvScene3D::fox(RenderMode mode){
    chest(mode);
}

double cgvScene3D::getAngleX() const {
    return angleX;
}

double cgvScene3D::getAngleY() const {
    return angleY;
}

double cgvScene3D::getAngleZ() const {
    return angleZ;
}

double cgvScene3D::getHeadX() const {
    return headX;
}

double cgvScene3D::getHeadY() const {
    return headY;
}

double cgvScene3D::getHeadZ() const {
    return headZ;
}

double cgvScene3D::getTailY() const {
    return tailY;
}

double cgvScene3D::getEarR() const {
    return earR;
}

double cgvScene3D::getEarL() const {
    return earL;
}

void cgvScene3D::chicken(){
    glPushMatrix();
        glScalef(0.12,0.12,0.12);
        body();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0,-0.32,-0.4);
        glScalef(0.11,0.11,0.11);
        put_egg();
    glPopMatrix();
}

void cgvScene3D::body() {
    glPushMatrix();
    cgvMaterial eter= cgvMaterial({0.6,0.6,0.6,1},
                                  {0.7,0.7,0.7,1},
                                  {0.0,0.0,0.0,1.0}, 128);
    eter.apply();

    glPushMatrix();
    glScaled(3, 2.5, 4);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    left_wing();
    glPopMatrix();

    glPushMatrix();
    right_wing();
    glPopMatrix();

    glPushMatrix();
    glRotated(head_mov, 1, 0, 0);
    head_chicken();
    glPopMatrix();

    glPushMatrix();
    glRotated(leg_mov, 1, 0, 0);
    left_leg();
    glPopMatrix();

    glPushMatrix();
    glRotated(-leg_mov, 1, 0, 0);
    right_leg();
    glPopMatrix();

    glPopMatrix();
}

void cgvScene3D::left_wing() {
    glPushMatrix();

    cgvMaterial eter= cgvMaterial({0.5,0.5,0.5,1},
                                  {0.6,0.6,0.6,1},
                                  {0.0,0.0,0.0,1.0}, 128);
    eter.apply();

    glPushMatrix();
    glTranslated(1.6, 0.5, 0.1);
    glScaled(0.2, 1.5, 2.2);
    glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
}

void cgvScene3D::right_wing() {
    glPushMatrix();

    cgvMaterial eter= cgvMaterial({0.5,0.5,0.5,1},
                                  {0.6,0.6,0.6,1},
                                  {0.0,0.0,0.0,1.0}, 128);
    eter.apply();

    glPushMatrix();
    glTranslated(-1.6, 0.5, 0.1);
    glScaled(0.2, 1.5, 2.2);
    glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
}

void cgvScene3D::head_chicken() {
    glPushMatrix();

    cgvMaterial eter= cgvMaterial({0.6,0.6,0.6,1},
                                  {0.7,0.7,0.7,1},
                                  {0.0,0.0,0.0,1.0}, 128);
    eter.apply();

    glPushMatrix();
    glTranslated(0, 1.75, 2.5);
    glScaled(1.5, 1.55, 1.25);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glRotated(beak_mov, 1, 0, 0);
    beak();
    glPopMatrix();

    glPushMatrix();
    right_eye();
    glPopMatrix();

    glPushMatrix();
    left_eye();
    glPopMatrix();


    glPopMatrix();
}

void cgvScene3D::beak(){
    glPushMatrix();

    cgvMaterial eter= cgvMaterial({0.75,0.631,0.4,1},
                                  {0.55,0.431,0.2,1},
                                  {0.0,0.0,0.0,1.0}, 128);
    eter.apply();

    glPushMatrix();
    glTranslated(0.0, 1.4, 3);
    glScaled(1.45, 0.6, 1.5);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    wattle();
    glPopMatrix();

    glPopMatrix();
}

void cgvScene3D::wattle(){
    glPushMatrix();

    cgvMaterial eter= cgvMaterial({0.3,0.0,0.0,1},
                                  {0.8,0.0,0.0,1},
                                  {0.0,0.0,0.0,1.0}, 128);
    eter.apply();

    glPushMatrix();
    glTranslated(0.0, 1, 3);
    glScaled(0.5, 0.75, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
}

void cgvScene3D::right_eye() {
    glPushMatrix();

    cgvMaterial eter= cgvMaterial({0.0,0.0,0.0,1},
                                  {0.0,0.0,0,1},
                                  {0.0,0.0,0.0,1.0}, 128);
    eter.apply();

    glPushMatrix();
    glTranslated(-0.525, 2, 3.1);
    glScaled(0.4, 0.4, 0.1);
    glutSolidCube(1);
    glPopMatrix();


    glPopMatrix();
}

void cgvScene3D::left_eye() {
    glPushMatrix();
    cgvMaterial eter= cgvMaterial({0.0,0.0,0.0,1},
                                  {0.0,0.0,0,1},
                                  {0.0,0.0,0.0,1.0}, 128);
    eter.apply();

    glPushMatrix();
    glTranslated(0.525, 2, 3.1);
    glScaled(0.4, 0.4, 0.1);
    glutSolidCube(1);
    glPopMatrix();


    glPopMatrix();
}

void cgvScene3D::left_leg() {
    glPushMatrix();

    cgvMaterial eter= cgvMaterial({0.75,0.631,0.4,1},
                                  {0.55,0.431,0.2,1},
                                  {0.0,0.0,0.0,1.0}, 128);
    eter.apply();


    glPushMatrix();
    glTranslated(1, -1, 0);
    glRotated(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 0.2, 0.2, 2, 10, 10);
    glPopMatrix();

    glPushMatrix();
    left_foot();
    glPopMatrix();

    glPopMatrix();
}

void cgvScene3D::right_leg() {
    glPushMatrix();

    cgvMaterial eter= cgvMaterial({0.75,0.631,0.4,1},
                                  {0.55,0.431,0.2,1},
                                  {0.0,0.0,0.0,1.0}, 128);
    eter.apply();

    glPushMatrix();
    glTranslated(-1, -1, 0);
    glRotated(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 0.2, 0.2, 2, 10, 10);
    glPopMatrix();

    glPushMatrix();
    right_foot();
    glPopMatrix();

    glPopMatrix();

}

void cgvScene3D::right_foot() {
    glPushMatrix();

    cgvMaterial eter= cgvMaterial({0.75,0.631,0.4,1},
                                  {0.55,0.431,0.2,1},
                                  {0.0,0.0,0.0,1.0}, 128);
    eter.apply();

    glPushMatrix();
    glTranslated(-1, -3, 0.3);
    glScaled(1, 0.2, 1.4);
    glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
}

void cgvScene3D::left_foot() {
    glPushMatrix();

    cgvMaterial eter= cgvMaterial({0.75,0.631,0.4,1},
                                  {0.55,0.431,0.2,1},
                                  {0.0,0.0,0.0,1.0}, 128);
    eter.apply();
    glPushMatrix();
    glTranslated(1, -3, 0.3);
    glScaled(1, 0.2, 1.4);
    glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
}

void cgvScene3D::put_egg() {
    if(isEgg()){
        glPushMatrix();

            cgvMaterial eter= cgvMaterial({0.6,0.6,0.6,1},
                                          {0.7,0.7,0.7,1},
                                          {0.0,0.0,0.0,1.0}, 128);
            eter.apply();
            glPushMatrix();
                glScaled(1.0, 1.5, 1.0);
                glutSolidSphere(.5, 50, 50);
            glPopMatrix();
        glPopMatrix();
    }
}

bool cgvScene3D::isEgg() const {
    return egg;
}

void cgvScene3D::setEgg(bool egg) {
    cgvScene3D::egg = egg;
}

double cgvScene3D::getHeadMov() const {
    return head_mov;
}

double cgvScene3D::getLegMov() const {
    return leg_mov;
}

void cgvScene3D::farm(){

    glPushMatrix();


        ////FLOOR
        if(button1.isSelected()) {

            cgvTexture* texture = new cgvTexture("oppie.png");
            texture->apply();
            glPushMatrix();
            glTranslated(-3.5,0,-2.5);
            draw_quad_textured(50,50,7,5);
            glPopMatrix();
            delete texture;
        }
        else {
            cgvTexture* texture = new cgvTexture("farmsoilv2_veryLow.png");
            texture->apply();
            glPushMatrix();
            glTranslated(-3.5,0,-2.5);
            draw_quad_textured(50,50,7,5);
            glPopMatrix();
            delete texture;
        }

        ///Backright wall
        cgvTexture* wall_texture= new cgvTexture("brickwall_veryLow.png");
        wall_texture->apply();
        glPushMatrix();
            glTranslatef(0,0,-2.5);
            glRotated(90,1,0,0);
            glTranslatef(-3.5,0,-3);
            draw_quad_textured(50,50,7,3);
        glPopMatrix();

        /// Backleft wall
        glPushMatrix();
            glTranslated(-3.5,0,0);
            glRotated(180,0,1,0);
            glRotated(-90,0,0,1);
            glTranslated(-3,0,2.5);
            glRotated(90,0,1,0);
            draw_quad_textured(50,50,5,3);
        glPopMatrix();

        /// Frontleft wall
        glPushMatrix();
            glTranslatef(0,0,2.6);
            glRotated(180,0,1,0);
            glRotated(90,1,0,0);
            glTranslatef(-3.6,0,-3);

            draw_quad_textured(50,50,7,3);
        glPopMatrix();
        delete wall_texture;

        /// Door
        cgvTexture* door_texture= new cgvTexture("greydoor_veryLow.png");
        door_texture->apply();
        glPushMatrix();
            glTranslated(3.6,0,0);
            glRotated(180,0,1,0);
            glRotated(-90,0,0,1);
            glTranslated(-3,0,2.5);
            glRotated(90,0,1,0);
            draw_quad_textured(50,50,5,3);
        glPopMatrix();
        delete door_texture;

        /// ROOF

        cgvMaterial eter2= cgvMaterial({1.0,1.0,1.0},
                                       {1.0,1.0,1.0},
                                       {0.0,0.0,0.0}, 128);
        eter2.apply();

        cgvTexture* roof_texture= new cgvTexture("woodroof_veryLow.png");
        roof_texture->apply();
        glPushMatrix();
            glTranslatef(0,3,0);
            glTranslatef(-3.5,2.5,0);
            glRotated(45,1,0,0);
            draw_quad_textured(50,50,7,3.5355339);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0,3,0);
            glTranslatef(-3.5,2.5,0);
            glRotated(135,1,0,0);
            draw_quad_textured(50,50,7,3.5355339);
        glPopMatrix();
        delete roof_texture;

        /// Glass triangles
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        cgvMaterial transparent_eter= cgvMaterial({1.0,1.0,1.0,0.2},
                                                  {1.0,1.0,1.0,0.2},
                                                  {1.0,1.0,1.0,0.2}, 60);
        transparent_eter.apply();

        cgvTexture* glass_texture= new cgvTexture("glass_veryLow.png");
        glass_texture->apply();
        glPushMatrix();
            glScalef(1,1,1.04);
            glTranslatef(3.6,2.9,0.05);
            glRotated(-90,0,0,1);
            glTranslatef(0,0,2.53);
            glRotated(135,0,1,0);
            draw_triangle_textured(50,50,3.5355339,3.5355339);
        glPopMatrix();

        glPushMatrix();
            glScalef(1,1,1.04);
            glTranslatef(-3.5,2.9,0.05);
            glRotated(-90,0,0,1);
            glTranslatef(0,0,2.53);
            glRotated(135,0,1,0);
            draw_triangle_textured(50,50,3.5355339,3.5355339);
        glPopMatrix();
        delete glass_texture;
        glDisable(GL_BLEND);
    glPopMatrix();
}

void cgvScene3D::movementFunc(char direction, double distance) {
    switch(direction){
        case 'X':
            xMovement+= distance;
            break;
        case 'Z':
            zMovement+= distance;
            break;
    }
}



void cgvScene3D::incrementRightEar(){
    if(earR<BORDER){
        earR+=1;
    }
}
void cgvScene3D::decrementRightEar(){
    if(earR>-BORDER){
        earR-=1;
    }
}
void cgvScene3D::incrementLeftEar(){
    if(earL<BORDER){
        earL+=1;
    }
}
void cgvScene3D::decrementLeftEar(){
    if(earL>-BORDER){
        earL-=1;
    }
}

void cgvScene3D::restoreAngles() {

    angleX= angleY= angleZ= 0;
}

void cgvScene3D::saveAngles(){
    storeAngleX= angleX;
    storeAngleY= angleY;
    storeAngleZ= angleZ;
}

void cgvScene3D::restoreDisplacement() {
    xMovement= zMovement= 0;
}

void cgvScene3D::saveDisplacement() {
    storeXMovement= xMovement;
    storeZMovement= zMovement;
}

void cgvScene3D::loadDisplacement() {
    xMovement= storeXMovement;
    zMovement= storeZMovement;
}

void cgvScene3D::loadAngles() {
    angleX= storeAngleX;
    angleY= storeAngleY;
    angleZ= storeAngleZ;
}