#include <cstdlib>
#include <stdio.h>

#include "cgvScene3D.h"


// Constructor
/**
 * Default constructor
 */
cgvScene3D::cgvScene3D () {
	// // TODO. Section C: init the attributes to control the degrees of freedom of the model
    head_mov=0.0;
    beak_mov=0.0;
    leg_mov=0.0;

}
/**
 * Default destructor
 */
cgvScene3D::~cgvScene3D() {
	
}


// Public methods ----------------------------------------

void cgvScene3D::add_rotation(double x_angle, double y_angle, double z_angle) {
    if (x_angle != 0.0) {
        rotate_x_axis+=10;
    }
    else {
        if (y_angle != 0.0) {
            rotate_y_axis+=10;
        }
        else {
            if (z_angle != 0.0) {
                rotate_z_axis+=10;
            }
        }
    }
}

void cgvScene3D::remove_rotation(double x_angle, double y_angle, double z_angle) {
    if (x_angle != 0.0) {
        rotate_x_axis-=10;
    }
    else {
        if (y_angle != 0.0) {
            rotate_y_axis-=10;
        }
        else {
            if (z_angle != 0.0) {
                rotate_z_axis-=10;
            }
        }
    }
}

void cgvScene3D::move_head(double angle){
    if (!movement) {
        head_mov += angle;
    }
    if (head_mov == 10 || head_mov > 10) {
        movement = true;
    }
    if (movement) {
        head_mov = head_mov - angle;
        if (head_mov == 0 || head_mov < 0) {
            movement = false;
        }
    }
}

void cgvScene3D::move_beak(double angle){
    if (!movement) {
        beak_mov += angle;
    }
    if (beak_mov == 3 || beak_mov > 3) {
        movement = true;
    }
    if (movement) {
        beak_mov = beak_mov - angle;
        if (beak_mov == 0 || beak_mov < 0) {
            movement = false;
        }
    }
}

void cgvScene3D::move_leg(double angle){
    if (!movement) {
        leg_mov += angle;
    }
    if (leg_mov == 10 || leg_mov > 10) {
        movement = true;
    }
    if (movement) {
        leg_mov = leg_mov - angle;
        if (leg_mov == 0 || leg_mov < 0) {
            movement = false;
        }
    }
}


/**
 * Render the scene
 */
void cgvScene3D::render() {

	// lights
	GLfloat light0[4]={5.0,5.0,5.0,1}; // point light source  
	glLightfv(GL_LIGHT0,GL_POSITION,light0); // this light is placed here and it remains still 
    glEnable(GL_LIGHT0);
  
	// create the model
	glPushMatrix(); // store the model matrices

	  // draw the axes
	if (axes) draw_axes();

	float mesh_color[4] = {1.0, 0.0, 0.0, 1.0};
	glMaterialfv(GL_FRONT,GL_EMISSION,mesh_color);

///// TODO: Section B: include here the visualization of the tree of the model by using the OpenGL stack of matrices 
/////           it is advisable to create an auxiliary method to encapsulate the code to visualize the model
/////           leaving here only the call to this method. 

    double x_axis = getRotateXAxis();
    double y_axis = getRotateYAxis();
    double z_axis = getRotateZAxis();

    glPushMatrix();
    glRotated(x_axis, 1.0, 0.0, 0.0);
    glRotated(y_axis, 0.0, 1.0, 0.0);
    glRotated(z_axis, 0.0, 0.0, 1.0);
    body();
    glPopMatrix();

    glPushMatrix();
    put_egg();
    glPopMatrix();
	
	glPopMatrix (); // restore the modelview matrix 
  
}

/**
 * Render the axes of the scene
 */
void cgvScene3D::draw_axes(void) {
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

double cgvScene3D::getRotateXAxis() const {
    return rotate_x_axis;
}

double cgvScene3D::getRotateYAxis() const {
    return rotate_y_axis;
}

double cgvScene3D::getRotateZAxis() const {
    return rotate_z_axis;
}

void cgvScene3D::body() {
    glPushMatrix();
    GLfloat body_color[] = { 0.5,0.5,0.5 };
    glMaterialfv(GL_FRONT, GL_EMISSION, body_color);

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
    head();
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
    GLfloat left_wing_color[] = { 0.4,0.4,0.4 };
    glMaterialfv(GL_FRONT, GL_EMISSION, left_wing_color);

    glPushMatrix();
    glTranslated(1.6, 0.5, 0.1);
    glScaled(0.2, 1.5, 2.2);
    glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
}

void cgvScene3D::right_wing() {
    glPushMatrix();
    GLfloat right_wing_color[] = { 0.4,0.4,0.4  };
    glMaterialfv(GL_FRONT, GL_EMISSION, right_wing_color);

    glPushMatrix();
    glTranslated(-1.6, 0.5, 0.1);
    glScaled(0.2, 1.5, 2.2);
    glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
}

void cgvScene3D::head() {
    glPushMatrix();
    GLfloat head_color[] = { 0.5,0.5,0.5 };
    glMaterialfv(GL_FRONT, GL_EMISSION, head_color);

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
    GLfloat beak_color[] = { 0.75,0.631,0.40 };
    glMaterialfv(GL_FRONT, GL_EMISSION, beak_color);

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
    GLfloat wattle_color[] = { 0.5,0,0 };
    glMaterialfv(GL_FRONT, GL_EMISSION, wattle_color);

    glPushMatrix();
    glTranslated(0.0, 1, 3);
    glScaled(0.5, 0.75, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
}

void cgvScene3D::right_eye() {
    glPushMatrix();
    GLfloat eye_color[] = { 0,0,0 };
    glMaterialfv(GL_FRONT, GL_EMISSION, eye_color);

    glPushMatrix();
    glTranslated(-0.525, 2, 3.1);
    glScaled(0.4, 0.4, 0.1);
    glutSolidCube(1);
    glPopMatrix();


    glPopMatrix();
}

void cgvScene3D::left_eye() {
    glPushMatrix();
    GLfloat eye_color[] = { 0,0,0 };
    glMaterialfv(GL_FRONT, GL_EMISSION, eye_color);

    glPushMatrix();
    glTranslated(0.525, 2, 3.1);
    glScaled(0.4, 0.4, 0.1);
    glutSolidCube(1);
    glPopMatrix();


    glPopMatrix();
}

void cgvScene3D::left_leg() {
    glPushMatrix();
    GLfloat leg_color[] = { 0.75,0.631,0.40 };
    glMaterialfv(GL_FRONT, GL_EMISSION, leg_color);

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
    GLfloat leg_color[] = { 0.75,0.631,0.40 };
    glMaterialfv(GL_FRONT, GL_EMISSION, leg_color);

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
    GLfloat foot_color[] = { 0.75,0.631,0.40 };
    glMaterialfv(GL_FRONT, GL_EMISSION, foot_color);

    glPushMatrix();
    glTranslated(-1, -3, 0.3);
    glScaled(1, 0.2, 1.4);
    glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
}

void cgvScene3D::left_foot() {
    glPushMatrix();
    GLfloat foot_color[] = { 0.75,0.631,0.40 };
    glMaterialfv(GL_FRONT, GL_EMISSION, foot_color);

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
        GLfloat right_wing_color[] = { 0.5,0.5,0.5  };
        glMaterialfv(GL_FRONT, GL_EMISSION, right_wing_color);

        glPushMatrix();
        glTranslated(0.0, -3, -3.0);
        glScaled(1.0, 1.5, 1.0);
        glColor3f(1.0, 1.0, 0.0);
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

void cgvScene3D::setHeadMov(double headMov) {
    head_mov = headMov;
}

double cgvScene3D::getLegMov() const {
    return leg_mov;
}

void cgvScene3D::setLegMov(double legMov) {
    leg_mov = legMov;
}
