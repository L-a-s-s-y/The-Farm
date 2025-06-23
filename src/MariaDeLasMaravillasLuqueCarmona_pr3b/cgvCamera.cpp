#if defined(__APPLE__) && defined(__MACH__)

#include <GLUT/glut.h>

#include <OpenGL/gl.h>

#include <OpenGL/glu.h>

#else

#include <GL/glut.h>

#endif

#include <math.h>
#include <stdio.h>

#include "cgvCamera.h"

/** 
 * Constructor
 * @param _PV point of view
 * @param _rp reference point
 * @param _up up vector
 * @pre It is assumed that the values of the parameters is valid
 * @post A new instance of parallel cgvCamera is created with the indicated parameters
 */
cgvCamera::cgvCamera(cgvPoint3D _PV, cgvPoint3D _rp, cgvPoint3D _up) {
	setCameraParameters(_PV, _rp, _up);
	setParallelParameters(1, 1, 1, 20);
}

/**
 * Assign camera parameters
 * @param _PV point of view
 * @param _rp reference point
 * @param _up up vector
 * @pre It is assumed that the values of the parameters is valid
 * @post The attributes corresponding to the parameters are changed 
 */
void cgvCamera::setCameraParameters(cgvPoint3D _PV, cgvPoint3D _rp, cgvPoint3D _up) {
	PV = _PV;
	rp = _rp;
	up = _up;
}

/**
 * Get camera parameters
 * @param _PV point of view
 * @param _rp reference point
 * @param _up up vector
 * @return The attributes corresponding to the camera parameters 
 */
void cgvCamera::getCameraParameters(cgvPoint3D& _PV, cgvPoint3D& _rp, cgvPoint3D& _up) {
	_PV = PV;
	_rp = rp;
	_up = up;
}

/**
 * Assign parallel projection parameters
 * @param _xwhalfdistance Parameter to define the left and right planes of the parallel projection
 * @param _ywhalfdistance Parameter to define the bottom and top planes of the parallel projection
 * @param _znear Near plane
 * @param _zfar  Far plane
 * @pre It is assumed that the values of the parameters is valid
 * @post The camera becomes parallel. xwmin, xwmax, ywmin, ywmax are updated from the parameters value 
 */
void cgvCamera::setParallelParameters(double _xwhalfdistance, double _ywhalfdistance,
	double _znear, double _zfar)
{
	camType = CGV_PARALLEL; 

	xwmin = -_xwhalfdistance;
	xwmax = _xwhalfdistance;
	ywmin = -_ywhalfdistance;
	ywmax = _ywhalfdistance;
	znear = _znear;
	zfar = _zfar;

}

/**
 * Get parallel camera parameters
 * @param _xwmin left plane 
 * @param _xwmax right plane
 * @param _ywmin bottom plane
 * @param _ywmax top plane
 * @param _znear near plane
 * @param _zfar far plane
 * @return The attributes corresponding to the parallel camera parameters 
 */
void cgvCamera::getParallelParameters(double& _xwmin, double& _xwmax, double& _ywmin, double& _ywmax, 
										double& _znear, double& _zfar)
{
	_xwmin = xwmin;
	_xwmax = xwmax;
	_ywmin = ywmin;
	_ywmax = ywmax;
	_znear = znear;
	_zfar = zfar;
}

/**
 * Set perspective camera
 * @param _fovy Field of view angle (y direction)
 * @param _aspect Aspect ratio (x direction)
 * @param _znear Near plane
 * @param _zfar  Far plane
 * @pre It is assumed that the values of the parameters is valid
 * @post The camera becomes perspective. The perspective parameters are updated. 
 */
void cgvCamera::setPerspParameters(double _fovy, double _aspect, double _znear, double _zfar) {

	camType = CGV_PERSPECTIVE;

	fovy = _fovy;
	aspect = _aspect;
	znear = _znear;
	zfar = _zfar;

}

/**
 * Get perspective camera parameters
 * @param _fovy Field of view angle (y direction)
 * @param _aspect Aspect ratio (x direction)
 * @param _znear Near plane
 * @param _zfar  Far plane
 * @return The perspective camera parameters. 
 */
void cgvCamera::getPerspParameters(double& _fovy, double& _aspect, double& _znear, double& _zfar) {

	_fovy = fovy; 
	_aspect = aspect; 
	_znear = znear;
	_zfar = zfar;

}

/**
 * Apply the defined camera (parallel or perspective) using the corresponding OpenGL instructions. 
 */
void cgvCamera::apply() {

// TODO: Practice 2b.C: Modify this method in order to adequately apply a zoom to the camera. 

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();

	if (camType==CGV_PARALLEL) {
		glOrtho(xwmin, xwmax, ywmin, ywmax, znear, zfar);
	}
	if (camType==CGV_PERSPECTIVE) {
		gluPerspective(fovy,aspect,znear,zfar);
	}
	
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(PV[X],PV[Y],PV[Z], rp[X],rp[Y],rp[Z], up[X],up[Y],up[Z]);
}

/**
 * Assignment operator
 * @param cam Camera to be assigned
 * @pre It is assumed that the parameter is valid
 * @post Update the camera parameters according to the parameter (camera)
 */
cgvCamera &cgvCamera::operator=(const cgvCamera &cam) {
	this->xwmin = cam.xwmin; 
	this->xwmax = cam.xwmax; 
	this->ywmin = cam.ywmin;
	this->ywmax = cam.ywmax;

	this->znear = cam.znear; 
	this->zfar = cam.zfar; 

	this->PV = cam.PV;

	this->rp = cam.rp;

	this->up = cam.up; 
	return *this; 
}






