
#pragma once

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else

#include <GL/glut.h>

#endif


class cgvScene3D {
protected:
////// TODO: Section B: add here the attributes to control the degrees of freedom of the model
    bool movement = false;
    double rotate_x_axis = 0.0;
    double rotate_y_axis = 0.0;
    double rotate_z_axis = 0.0;
    double head_mov;
    double beak_mov;
    double leg_mov;

    bool egg=false;


    // Additional attributes

    bool axes = true; ///< Axes rendering enable/disable


public:
    // Default constructor and destructor
    cgvScene3D();

    ~cgvScene3D();

    // Static methods

    // Methods
    // method with the OpenGL calls to render the scene
    void render();


    // Primitives
    void body();

    void left_wing();

    void right_wing();

    void head();

    void beak();

    void wattle();

    void right_eye();

    void left_eye();

    void left_leg();

    void right_leg();

    void right_foot();

    void left_foot();

    void put_egg();




    ////// TODO: Section B: include here the methods to modify the degrees of freedom of the model


    bool get_axes() { return axes; };

    void set_axes(bool _axes) { axes = _axes; };

    void add_rotation(double x_angle, double y_angle, double z_angle);

    void remove_rotation(double x_angle, double y_angle, double z_angle);

    double getRotateXAxis() const;

    double getRotateYAxis() const;

    double getRotateZAxis() const;

    void move_head(double angle);

    void move_beak(double angle);

    void move_leg(double angle);

    bool isEgg() const;

    void setEgg(bool egg);

    double getHeadMov() const;

    void setHeadMov(double headMov);

    double getLegMov() const;

    void setLegMov(double legMov);

private:
    void draw_axes(void);
};


