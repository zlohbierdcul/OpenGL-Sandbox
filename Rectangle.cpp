//
// Created by Luc Dreibholz on 27.02.23.
//

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>
#include "Rectangle.h"


Rectangle::Rectangle(float width, float height, float x, float y, float radius, GLfloat r, GLfloat g, GLfloat b)
    : m_width(width), m_height(height), m_x(x), m_y(y), m_radius(radius), m_r(r), m_g(g), m_b(b)
{
}

typedef struct
{
    float x;
    float y;
} Vector2f;

#define ROUNDING_POINT_COUNT 80      // Larger values makes circle smoother.

void Rectangle::draw() {
    Vector2f top_left[ROUNDING_POINT_COUNT];
    Vector2f bottom_left[ROUNDING_POINT_COUNT];
    Vector2f top_right[ROUNDING_POINT_COUNT];
    Vector2f bottom_right[ROUNDING_POINT_COUNT];

    if( m_radius == 0.0 )
    {
        m_radius = fmin(m_width, m_height);
        m_radius *= 0.10; // 10%
    }

    int i = 0;
    float x_offset, y_offset;
    float step = ( 2.0f * M_PI ) / (ROUNDING_POINT_COUNT * 4),
            angle = 0.0f;

    unsigned int index = 0, segment_count = ROUNDING_POINT_COUNT;
    Vector2f bottom_left_corner = { m_x + m_radius, m_y - m_height + m_radius };


    while( i != segment_count )
    {
        x_offset = cosf( angle );
        y_offset = sinf( angle );


        top_left[ index ].x = bottom_left_corner.x -
                              ( x_offset * m_radius );
        top_left[ index ].y = ( m_height - ( m_radius * 2.0f ) ) +
                              bottom_left_corner.y -
                              ( y_offset * m_radius );


        top_right[ index ].x = ( m_width - ( m_radius * 2.0f ) ) +
                               bottom_left_corner.x +
                               ( x_offset * m_radius );
        top_right[ index ].y = ( m_height - ( m_radius * 2.0f ) ) +
                               bottom_left_corner.y -
                               ( y_offset * m_radius );


        bottom_right[ index ].x = ( m_width - ( m_radius * 2.0f ) ) +
                                  bottom_left_corner.x +
                                  ( x_offset * m_radius );
        bottom_right[ index ].y = bottom_left_corner.y +
                                  ( y_offset * m_radius );


        bottom_left[ index ].x = bottom_left_corner.x -
                                 ( x_offset * m_radius );
        bottom_left[ index ].y = bottom_left_corner.y +
                                 ( y_offset * m_radius );


        top_left[ index ].x = top_left[ index ].x;
        top_left[ index ].y = top_left[ index ].y;


        top_right[ index ].x = top_right[ index ].x;
        top_right[ index ].y = top_right[ index ].y;


        bottom_right[ index ].x = bottom_right[ index ].x ;
        bottom_right[ index ].y = bottom_right[ index ].y;


        bottom_left[ index ].x =  bottom_left[ index ].x ;
        bottom_left[ index ].y =  bottom_left[ index ].y ;

        angle -= step;

        ++index;

        ++i;
    }

    static GLubyte clr[] = { 156, 207, 255, 128 };   // Light blue, 50% transparent.

    glColor3f(m_r, m_g, m_b);

    glBegin( GL_TRIANGLE_STRIP );
    {
        // Top
        for( i = segment_count - 1 ; i >= 0 ; i--)
        {
            glVertex2f( top_left[ i ].x, top_left[ i ].y );
            glVertex2f( top_right[ i ].x, top_right[ i ].y );
        }

        // In order to stop and restart the strip.
        glVertex2f( top_right[ 0 ].x, top_right[ 0 ].y );
        glVertex2f( top_right[ 0 ].x, top_right[ 0 ].y );

        // Center
        glVertex2f( top_right[ 0 ].x, top_right[ 0 ].y );
        glVertex2f( top_left[ 0 ].x, top_left[ 0 ].y );
        glVertex2f( bottom_right[ 0 ].x, bottom_right[ 0 ].y );
        glVertex2f( bottom_left[ 0 ].x, bottom_left[ 0 ].y );

        // Bottom
        for( i = 0; i != segment_count ; i++ )
        {
            glVertex2f( bottom_right[ i ].x, bottom_right[ i ].y );
            glVertex2f( bottom_left[ i ].x, bottom_left[ i ].y );
        }
    }
    glEnd();
} //DrawRoundRect

