#include "cgvTexture.h"
#include "lodepng.h"

#include <vector>
#include <stdexcept>

// Constructor and destructor methods


/**
 * Basic constructor. It creates a 64x64 chessboard texture
 */
cgvTexture::cgvTexture() {
  width = 64;
  height = 64;

 GLubyte texture[64][64][4];

  // store a chessboard image as a texture array
	int i, j, c;
  for (i = 0; i < height ; i++) {
    for (j = 0; j < width ; j++) {
		  c = (((i&0x8) == 0) ^ ((j&0x8)) == 0) * 255;
		  texture[i][j][0] = (GLubyte) c;
		  texture[i][j][1] = (GLubyte) c;
		  texture[i][j][2] = (GLubyte) c;
		  texture[i][j][3] = (GLubyte) 255;
	  }
	}

	glEnable(GL_TEXTURE_2D);
	if (!glIsTexture(idTexture)) {
		
		/* TODO: Section G: Add here the code to load the chessboard texture */
 
		/*
		- Enable GL_TEXTURE_2D
		- Generate the identifier of the texture and assign it to the attribute idTexture (use glGenTextures)
		- Bind the texture with its name. (glBindTexture)
		- Environment mode of the texture  (glTexEnvf)
		- Parameters of the texture: repeat and filters glTexParameteri
		- Specify the texture assigning it the image array glTexImage2D.
		*/

        glGenTextures(1, &idTexture);
        glBindTexture(GL_TEXTURE_2D, idTexture);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture);
    }

}

/**
  * Parameterized constructor. Load an image as an OpenGL texture. 
  * @param file: Name of the image file
  */
cgvTexture::cgvTexture(std::string file) {


	glEnable(GL_TEXTURE_2D);
	if (!glIsTexture(idTexture)) {
		std::vector<unsigned char> texels;
		unsigned int error = lodepng::decode(texels, width, height, file);

		if ( error ){  
			std::string message = "decoder error " + std::to_string(error) + ": " + lodepng_error_text(error) + " ";
            throw std::runtime_error ( message + file );
		}

		/* TODO: 
		- Enable GL_TEXTURE_2D
		- Generate the identifier of the texture and assign it to the attribute idTexture (use glGenTextures)
		- Bind the texture with its name. (glBindTexture)
		- Environment mode of the texture  (glTexEnvf)
		- Parameters of the texture: repeat and filters glTexParameteri
		- Specify the texture assigning it the image array glTexImage2D.
		*/

        glGenTextures(1, &idTexture);
        glBindTexture(GL_TEXTURE_2D, idTexture);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texels.data());

	}
}
/**
  * Destructor
  */
cgvTexture::~cgvTexture() {
  glDeleteTextures(1, &idTexture); 
}


/**
  * Method to be called when the texture is going to be used
  */
void cgvTexture::apply(void) {
  glBindTexture(GL_TEXTURE_2D, idTexture);
}

