//
// Created by Luc Dreibholz on 27.02.23.
//

#ifndef OPENGL_SANDBOX_RECTANGLE_H
#define OPENGL_SANDBOX_RECTANGLE_H


class Rectangle {
    public:
        Rectangle(float width, float height, float x, float y, float radius, GLfloat r, GLfloat g, GLfloat b);
        void draw();
    private:
        float m_width;
        float m_height;
        float m_x;
        float m_y;
        float m_radius;
        GLfloat m_r;
        GLfloat m_g;
        GLfloat m_b;
};


#endif //OPENGL_SANDBOX_RECTANGLE_H
