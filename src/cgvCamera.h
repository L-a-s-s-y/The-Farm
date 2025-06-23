#pragma once

#include "cgvPoint.h"
#include <iostream>

/**
 * Labels to define the types of cameras
 */
typedef enum {
    CGV_FRUSTUM,
    CGV_PARALLEL,
    CGV_PERSPECTIVE
} cameraType;

//const float INCREMENT= 0.2;



/**
 * cgvCamera contains the basic functionality to create and manipulate cameras and projections
 */
class cgvCamera {

protected:
    // attributes
    cameraType camType=CGV_PARALLEL; ///< Camera type

    // view plane: parameters parallel projection and frustum
    GLdouble xwmin = -3 ///< Minimum X to define the parallel projection (left)
    , xwmax = 3  ///< Maximum X to define the parallel projection (right)
    , ywmin = -3 ///< Minimum Y to define the parallel projection (bottom)
    , ywmax = 3  ///< Maximum Y to define the parallel projection (top)
    ;

    // perspective projection parameters
    double fovy = 60 ///< Field of view angle (y direction). Perspective projection
    , aspect = 1 ///< Aspect ratio (x direction). Perspective projection.
    ;

    // distances of near and far planes
    GLdouble znear = 1  ///< Distance from the camera to the near plane
    , zfar = 20 ///< Distance from the camera to the far plane
    ;

    // point of view
    cgvPoint3D PV={3,2,4}; ///< Point of view. Camera position.

    // view reference point
    cgvPoint3D rp = {0,0,0}; ///< View reference point

    // up vector
    cgvPoint3D up = {0,1,0}; ///< Up vector

    // zoom factor
    double currentZoom = 1; ///< Current zoom.

    // Near plane modifications
    double nearPlaneMod= 0;

    // Methods

public:
    // Default Constructors and destructor
    cgvCamera()=default;
    ~cgvCamera()=default;

    // Other constructor
    cgvCamera(cgvPoint3D _PV, cgvPoint3D _rp, cgvPoint3D _up);

    // State
    /**
     * @retval Return true if a parallel projection is defined
     */
    bool isParallel() const { return (camType == CGV_PARALLEL); }

    // Methods
    // Defining the camera parameters
    void setCameraParameters(cgvPoint3D _PV, cgvPoint3D _rp, cgvPoint3D _up);
    void getCameraParameters(cgvPoint3D& _PV, cgvPoint3D& _rp, cgvPoint3D& _up);

    // Defining the projection
    void setParallelParameters(double _xwhalfdistance, double _ywhalfdistance,
                               double _znear, double _zfar);
    void getParallelParameters(double& _xwmin, double& _xwmax, double& _ywmin, double& _ywmax,
                               double& _znear, double& _zfar);

    void setPerspParameters(double _fovy, double _aspect, double _znear, double _zfar);
    void getPerspParameters(double& _fovy, double& _aspect, double& _znear, double& _zfar);

    // Apply the camera
    void apply(); // apply the view and projection transformations to the object of the scene.


    void zoom(double factor); // Apply an additional zoom of factor "factor"

    double getZoom(){return currentZoom;};
    //void increaseZoomFactor(){currentZoom+=0.05; std::cout << currentZoom << std::endl;};
    //void decreaseZoomFactor(){currentZoom-=0.05; std::cout << currentZoom << std::endl;};

    void increaseNearPlaneDistance(){nearPlaneMod+=0.2; std::cout << nearPlaneMod << std::endl;};
    void decreaseNearPlaneDistance(){nearPlaneMod-=0.2; std::cout << nearPlaneMod << std::endl;};

    void alterPerspective();



    cgvCamera &operator=(const cgvCamera &cam);


};

