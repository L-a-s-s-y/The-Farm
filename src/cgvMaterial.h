#pragma once

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#else

#include <GL/glut.h>

#endif // defined(__APPLE__) && defined(__MACH__)


#include "cgvColor.h"

class cgvMaterial {

	protected:
		// attributes
		cgvColor4f Ka; ///< ambient coefficient 
		cgvColor4f Kd; ///< diffuse coefficient
		cgvColor4f Ks; ///< specular coefficient
		double   Ns=0; ///< Phong exponent
		
		// Methods

	public:
		// Default constructor and destructor
		cgvMaterial()=default;
		~cgvMaterial()=default;

		// Other constructors
		cgvMaterial(const cgvMaterial& m);	//copy constructor
		cgvMaterial(cgvColor4f _Ka, cgvColor4f _Kd, cgvColor4f _Ks, double _Ns);

		// Methods 
		void apply(void);
        void materialData();
		void set(cgvColor4f _Ka, cgvColor4f _Kd, cgvColor4f _Ks, double _Ns);
};



