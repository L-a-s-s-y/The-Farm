#pragma once

#if defined(__APPLE__) && defined(__MACH__)

#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#else

#include <GL/glut.h>

#endif // defined(__APPLE__) && defined(__MACH__)


#include <string>



/**
 * The instances of this class represent OpenGL textures
 */
class cgvTexture {

	protected:
		// Attributes
		unsigned int idTexture = 0; ///< Texture identifier
		unsigned int height = 0,      ///< height of the texture
			          width = 0;     ///< weight of the texture

		
	public:
		// Default Constructors and destructor
		cgvTexture(); // Chess texture of 64 x 64 texels
		cgvTexture( std::string file ); // Texture from a BMP file
		~cgvTexture();

		// Methods
		void apply(void); // bind the texture as the active texture
};

