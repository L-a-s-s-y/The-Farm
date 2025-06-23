//
// Created by hardraade on 4/01/24.
//

#ifndef FINALPROJECT_CGVBUTTON_H
#define FINALPROJECT_CGVBUTTON_H

#include <GL/glut.h>
#include "cgvSphere.h"


class cgvButton {
private:
    GLubyte color_as_ID[3]={0,0,0}; ///< RGB color used as an identifier
    bool selected=false; ///< Indicate whether the box is selected or not
    //float red, green, blue= 0;
    void draw_quad_textured(unsigned int divX, unsigned int divY, const float quadLength, const float quadWidth) const;
    void draw_quad(unsigned int divX, unsigned int divY, const float quadLength, const float quadWidth) const;

public:
    cgvButton() = default;
    cgvButton(GLubyte _r, GLubyte _g, GLubyte _b);
    cgvButton(GLubyte _color_as_ID[3]);
    //cgvButton(float r, float g, float b);
    ~cgvButton() = default;

    void render(RenderMode mode);

    void select(GLubyte c[3]);

    void unSelect(){ selected = false; }

    bool isSelected() const { return selected; }
};


#endif //FINALPROJECT_CGVBUTTON_H
