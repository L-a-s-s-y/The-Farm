#include "cgvMaterial.h"

// Alternative constructors


/**
 * Parameterized constructor
 * @param _Ka: Ambient component of the material
 * @param _Kd: Diffuse component of the material
 * @param _Ks: Specular component of the material
 * @param _Ns: Specular / Phong exponent for specular/glossy materials
 * @pre It is assumed the values of the parameters are valid
 * @post A new material is created with the properties indicated. 
 */
cgvMaterial::cgvMaterial(cgvColor4f _Ka, cgvColor4f _Kd, cgvColor4f _Ks, double _Ns) {
	Ka = _Ka;
	Kd = _Kd;
	Ks = _Ks;
	Ns = _Ns;
}


/**
 * Copy constructor
 */
cgvMaterial::cgvMaterial (const cgvMaterial& m) {	//copy constructor
	Ka = m.Ka;
	Kd = m.Kd;
	Ks = m.Ks;
	Ns = m.Ns;
}


// Public methods 
/**
 * Method to apply/use the material. 
 */
void cgvMaterial::apply(void) {

// Section C
// Apply the attributes of the cgvMaterial object:
// - ambient coefficient 
// - diffuse coefficient
// - specular coefficient
// - Phong exponent

// set the color (0.0, 0.0, 0.0) as emission color (the object is not a light source )

    //float* emission= new float [4]{0.0,0.0,0.0,0.0};

    glMaterialf(GL_FRONT, GL_EMISSION, 0);

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Ka.data());
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Kd.data());
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Ks.data());
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, Ns);

    /*glMaterialfv(GL_FRONT, GL_AMBIENT, Ka.data());
    glMaterialfv(GL_FRONT, GL_DIFFUSE, Kd.data());
    glMaterialfv(GL_FRONT, GL_SPECULAR, Ks.data());
    glMaterialf(GL_FRONT, GL_SHININESS, Ns);*/

    //materialData();

    //delete [] emission;

}


/**
 * Method to assign the properties of the material
 */
void cgvMaterial::set(cgvColor4f _Ka, cgvColor4f _Kd, cgvColor4f _Ks, double _Ns) {
	Ka = _Ka;
	Kd = _Kd;
	Ks = _Ks;
	Ns = _Ns;
}

void cgvMaterial::materialData() {
    std::cout << "Ka: " << std::endl;
    for (int i = 0; i < 4; ++i) {
        std::cout << Ka.data()[i] << ", ";
    }
    std::cout << std::endl;

    std::cout << "Kd: " << std::endl;
    for (int i = 0; i < 4; ++i) {
        std::cout << Kd.data()[i] << ", ";
    }
    std::cout << std::endl;

    std::cout << "Ks: " << std::endl;
    for (int i = 0; i < 4; ++i) {
        std::cout << Ks.data()[i] << ", ";
    }
    std::cout << std::endl;

    std::cout << "Phong coef (Ns): " << Ns << std::endl;
}



