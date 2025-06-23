#pragma once

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#else

#include <GL/glut.h>

#endif // defined(__APPLE__) && defined(__MACH__)

#include "cgvLight.h"
#include "cgvSphere.h"
#include "cgvButton.h"

#define nbScenes 1

const int INCREMENT= 1;
const int BORDER= 20;
const int LIMIT= 90;

class cgvScene3D {
	public:
		char *Scene_Name[nbScenes]; ///<  Names of the scenes into which the solution is divided

	private:
		// Attributes
		bool axes = false; ///< It displays the axis or not.
		int selectedScene = 0; ///< The practice is divided into 5 scenes. Initially, it is rendered the first one.

        /// Needed for the buffer color
        cgvSphere nose;
        cgvButton button1;

        /// Scene rotation parameters
        double angleX=0, angleY=0, angleZ=0;
        double storeAngleX, storeAngleY, storeAngleZ= 0;

        /// Fox stuff
        double headX=0, headY=0, headZ=0;
        double tailX=0, tailY=0, tailZ=0;
        double earR= 0, earL= 0;

        /// Chicken stuff
        double head_mov= 0.0;
        double beak_mov= 0.0;
        double leg_mov= 0.0;
        bool egg=false;

        /// New cam stuff
        double xMovement, zMovement= 0.0;
        double storeXMovement, storeZMovement= 0;

        /// private funtions
        void draw_axes(void) const;
        void draw_triangle_textured(unsigned int divX, unsigned int divY, const float quadLength, const float quadWidth) const;
        void draw_quad_textured(unsigned int divX, unsigned int divY, const float quadLength, const float quadWidth) const;

	public:
		// Public attributes

		// Default constructor and destructor
		cgvScene3D();
		~cgvScene3D()=default;

		void set(int scene);

		// Static methods

		// Methods
		// method with the OpenGL calls to render the scene
        void render(RenderMode mode);
        void farm();
        void movementFunc(char direction, double distance);

        bool get_axes() {return axes;};
		void set_axes(bool _axes){axes = _axes;};
        void assignSelection(GLubyte _c[3]);


        /// Scene rotation functions
        double getAngleX() const;
        double getAngleY() const;
        double getAngleZ() const;
        void incrementXAngle(){angleX+=INCREMENT;};
        void decrementXAngle(){angleX-=INCREMENT;};
        void incrementYAngle(){angleY+=INCREMENT;};
        void decrementYAngle(){angleY-=INCREMENT;};
        void incrementZAngle(){angleZ+=INCREMENT;};
        void decrementZAngle(){angleZ-=INCREMENT;};
        void restoreAngles();
        void saveAngles();
        void loadAngles();
        void restoreDisplacement();
        void saveDisplacement();
        void loadDisplacement();

        /// Chicken functions
        void chicken();
        void body();
        void left_wing();
        void right_wing();
        void head_chicken();
        void beak();
        void wattle();
        void right_eye();
        void left_eye();
        void left_leg();
        void right_leg();
        void right_foot();
        void left_foot();
        void put_egg();
        /// Chicken movement funtions
        double getRotateXAxis() const;
        double getRotateYAxis() const;
        double getRotateZAxis() const;
        void incrementMove_head(){head_mov+=INCREMENT;}
        void decrementMove_head(){head_mov-=INCREMENT;}
        void incrementMove_leg(){leg_mov+=INCREMENT;}
        void decrementMove_leg(){leg_mov-=INCREMENT;}
        bool isEgg() const;
        void setEgg(bool egg);
        double getHeadMov() const;
        double getLegMov() const;

        ///Fox Functions
        void fox(RenderMode mode);
        void chest(RenderMode mode);
        void tail();
        void head(RenderMode mode);
        void armR();
        void armL();
        void legR();
        void legL();
        void joint(float r, float g, float b);
        void humerus();
        void femur();
        void radio();
        void tibia();
        void hand();
        void foot();
        void neck();
        ///Fox movement functions
        double getHeadX() const;
        double getHeadY() const;
        double getHeadZ() const;
        double getTailY() const;
        double getEarR() const;
        double getEarL() const;
        void incrementHeadX(){headX+=INCREMENT;};
        void decrementHeadX(){headX-=INCREMENT;};
        void incrementHeadY(){headY+=INCREMENT;};
        void decrementHeadY(){headY-=INCREMENT;};
        void incrementHeadZ(){headZ+=INCREMENT;};
        void decrementHeadZ(){headZ-=INCREMENT;};
        void incrementTailY(){tailY+=INCREMENT;};
        void decrementTailY(){tailY-=INCREMENT;};
        void incrementRightEar();
        void decrementRightEar();
        void incrementLeftEar();
        void decrementLeftEar();
};

