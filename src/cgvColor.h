#pragma once


#include <array>
#include <iostream>

/**
 * Enumerator that represent the different channel. Red (R), green (G), blue (B) and alpha (A) channels. 
 */
typedef enum {
	R,
	G,
	B,
	A
};

/**
 * The instances of this class represent a color
 */
class cgvColor4f {
	std::array<float, 4> color = {0,0,0,1}; ///< Color. Initially black

public:
	cgvColor4f()=default; 

	/**
	 * Parameterized constructor. 
	 * @param r: float value for the red channel
	 * @param g: float value for the green channel
	 * @param b: float value for the blue channel
	 * @param a: float value for the alpha channel
	 * @pre The value of the parameters is assumed to be valid.  
	 * @post The new color is defined with the parameters
	*/
	cgvColor4f(float r, float g, float b, float a=1) {
		color = { r,g,b,a };
	}

	/**
	 * Method to return a float vector pointer of the color to be used in the OpenGL instructions
	 */
	//float *data() { return color.data(); }
    float *data() {
        float* data= new float[4]{(float)color[0], (float)color[1], (float)color[2], (float)color[3]};
        /*std::cout << "COLOR" << std::endl;
        for (int i = 0; i < 4; ++i) {
            std::cout << data[i] << std::endl;
        }*/
        return data;
        //return new float[4]{color[0], color[1], color[2], color[3]};
    }

};

