#include "cgvLight.h"
#include <iostream>

// Constructor methods 


/**
 * Parameterized constructor
 * @param _idLight, Identification of the light GL_LIGHT0, GL_LIGHT1, ...
 * @param _position, Position of the light. 
 * @param cAmb, Ambient component of the energy emitted
 * @param cDif, Diffuse component of the energy emitted
 * @param cEsp, Specular component of the energy emitted
 * @param a0, Constant attenuation parameter. 
 * @param a1, Linear attenuation parameter
 * @param a2, Quadratic attenuation parameter
 */
cgvLight::cgvLight(const unsigned int _idLight,
  				   const cgvPoint3D  & _position,
				   const cgvColor4f & cAmb, const cgvColor4f & cDif, const cgvColor4f & cEsp,
				   const double a0, const double a1, const double a2) {

  idLight = _idLight;
														 
	position = _position;
														 
	ambientColor = cAmb;
	diffuseColor = cDif;
	specularColor = cEsp;

	atten_a0 = a0;
	atten_a1 = a1;
	atten_a2 = a2;

	// Default values for point lights 
	spotlight_direction = cgvPoint3D(0,0,0);
	spotlight_angle = 180; // with this angle the spotlight becomes a point light source
	spotlight_exponent = 0;

	on = true;
}
/**
 * Parameterized constructor
 * @param _idLight, Identification of the light GL_LIGHT0, GL_LIGHT1, ...
 * @param _position, Position of the light. 
 * @param cAmb, Ambient component of the energy emitted
 * @param cDif, Diffuse component of the energy emitted
 * @param cEsp, Specular component of the energy emitted
 * @param a0, Constant attenuation parameter. 
 * @param a1, Linear attenuation parameter
 * @param a2, Quadratic attenuation parameter
 * @param spotlight_dir, Vector defining the central direction of the spotlight
 * @param spotlight_ang, Angle of aperture of the spotlight
 * @param spotlight_exp, Exponent to adjust the radial attenuation. 
 */
cgvLight::cgvLight(const unsigned int _idLight,
                   const cgvPoint3D & _position, 
                   const cgvColor4f& cAmb, const cgvColor4f& cDif, const cgvColor4f& cEsp,
		           const double a0, const double a1, const double a2,
				   const cgvPoint3D& spotlight_dir, const double spotlight_ang, const double spotlight_exp) {

  idLight = _idLight;
														 
	position = _position;
														 
	ambientColor = cAmb;
	diffuseColor = cDif;
	specularColor = cEsp;

	atten_a0 = a0;
	atten_a1 = a1;
	atten_a2 = a2;

	spotlight_direction = spotlight_dir;
	spotlight_angle = spotlight_ang;
	spotlight_exponent = spotlight_exp;

	on = true;
}

// Public methods ----------------------------------------

/**
 * Get the position of the light
 */
cgvPoint3D& cgvLight::getPosition(void) {
	return position;
}

/**
 * Set the position of the light
 * @param pos, New position of the light
 * @post The position of the light is updated. 
 */
void cgvLight::setPosition(cgvPoint3D pos) {
	position = pos;
}

/**
 * Method to set the material components
 * @param cAmb: Ambient component 
 * @param cDif: Diffuse component 
 * @param cSpec: Specular component 
 * @param Ns: Phong/Specular exponent
 * @post material components assigned
 */
void cgvLight::set(const cgvColor4f & cAmb, const cgvColor4f & cDif, const cgvColor4f & cSpec) {
	ambientColor = cAmb;
	diffuseColor = cDif;
	specularColor = cSpec;
	
}

/**
 * Method that set the ambient color component
 * @param cAmb: Ambient component 
 * @post ambient color component assigned
 */
void cgvLight::setAmbient(const cgvColor4f & cAmb) {
	ambientColor = cAmb;
}

/**
 * Method that set the diffuse color component
 * @param cDif: Specular component 
 * @post diffuse color component assigned
 */
void cgvLight::setDiffuse(const cgvColor4f & cDif) {
	diffuseColor = cDif;
}

/**
 * Method that set the specular color component
 * @param cSpec: Specular component 
 * @post specular color component assigned
 */
void cgvLight::setSpecular(const cgvColor4f & cSpec) {
	specularColor = cSpec;
}
/**
 * Method that returns the ambient color component
 * @return ambient color component
 */
cgvColor4f & cgvLight::getAmbient(void) {
	return ambientColor;
}

/**
 * Method that returns the diffuse color component
 * @return diffuse color component
 */
 cgvColor4f & cgvLight::getDiffuse(void) {
	return diffuseColor;
}

/**
 * Method that returns the specular color component
 * @return specular color component
 */
cgvColor4f & cgvLight::getSpecular(void) {
	return specularColor;
}

/**
 * Method to set the radial attenuation parameters
 * @param a0 Constant attenuation
 * @param a1 Linear attenuation with respect to the distance
 * @param a2 Quadratic attenuation with respect to the distance. 
 * @pre The parameters are assumed to be valid
 * @post A new radial attenation configuration is set
 */
void cgvLight::setAttenuation(double a0, double a1, double a2) {
	atten_a0 = a0;
	atten_a1 = a1;
	atten_a2 = a2;
}


/**
 * Method to get the radial attenuation parameters
 * @param a0 Constant attenuation
 * @param a1 Linear attenuation with respect to the distance
 * @param a2 Quadratic attenuation with respect to the distance. 
 */
void cgvLight::getAttenuation(double & a0, double & a1, double & a2) {
	a0 = atten_a0;
	a1 = atten_a1;
	a2 = atten_a2;
}

/**
 * Method to switch on the light
 */
 void cgvLight::switchOn(void) {
  on = true;
}

/**
 * Method to switch off the light
 */
void cgvLight::switchOff(void) {
  on = false;
}

/**
 * Method to check whether the light is on or off. 
 * @return It returns true if on. 
 */
unsigned int cgvLight::is_On(void) {
  return on;
}

/**
 * Method to apply / use the light
 */
void cgvLight::apply(void) {

// Section A
// if the light is on
//	enable the light
//	set the position of the light
//	set ambient, diffuse and specular colors
//	set radial attenuation
//	set the spotlight parameters: direction, cutoff, exponent. 

// If the light is off
//	disable the light

//// function to use: glLight, look it at the internet
    if(on){

        glEnable(idLight);

        //// Position
        glLightfv(idLight, GL_POSITION, position.data());

        //// Ambient, diffuse and specular attributes of the light
        glLightfv(idLight, GL_AMBIENT, ambientColor.data());
        glLightfv(idLight, GL_DIFFUSE, diffuseColor.data());
        glLightfv(idLight, GL_SPECULAR, specularColor.data());

        //// Radial attenuation coefficients
        glLightf(idLight, GL_CONSTANT_ATTENUATION, atten_a0);
        glLightf(idLight, GL_LINEAR_ATTENUATION, atten_a1);
        glLightf(idLight, GL_QUADRATIC_ATTENUATION, atten_a2);

        /// Direction, cutoff and exponent
        glLightfv(idLight, GL_SPOT_DIRECTION, spotlight_direction.data());
        glLightf(idLight, GL_SPOT_CUTOFF, spotlight_angle);
        glLightf(idLight, GL_SPOT_EXPONENT, spotlight_exponent);

        //glEnable(idLight);
        //lightData();
    }
    else{
        glDisable(idLight);
    }


}

void cgvLight::lightData(){
    std::cout << "POSITION: ";
    for (int i = 0; i < 3; ++i) {
        std::cout << position.data()[i] <<", ";
    }
    std::cout << std::endl;

    std::cout << "AmbientColor: ";
    for (int i = 0; i < 4; ++i) {
        std::cout << ambientColor.data()[i] << ", ";
    }
    std::cout << std::endl;

    std::cout << "DiffuseColor: ";
    for (int i = 0; i < 4; ++i) {
        std::cout << diffuseColor.data()[i] << ", ";
    }
    std::cout << std::endl;

    std::cout << "SpecularColor: ";
    for (int i = 0; i < 4; ++i) {
        std::cout << specularColor.data()[i] << ", ";
    }
    std::cout << std::endl;

    std::cout << "a0: " << atten_a0 << std::endl;
    std::cout << "a1: " << atten_a1 << std::endl;
    std::cout << "a2: " << atten_a2 << std::endl;
}

