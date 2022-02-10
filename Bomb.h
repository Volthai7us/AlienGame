#include "Utility.h"

#ifndef BOMB_H
#define BOMB_H

struct Bomb{
    Point3D location;
    Point3D color;
    Point2D size;
    Point2D speed;
    GLfloat current_time;

    void draw(){
        current_time += get_delta_time();
        if(current_time >= 1){
            current_time = 0;
            location.z += 1;
        }
        drawBody();
        drawRope();
        drawHead();
    }

    void drawBody(){
        glColor3f(color.x - (location.z * (color.x/5)), color.y - (location.z * (color.y/5)), color.z - (location.z * (color.z/5)));
        draw_elipse(location.x, location.y, size.x, size.x, 0, true, true, 2);
    }

    void drawHead(){
        float degreeToLeft = 80;
        float degreeToRight = 40;
        glBegin(GL_POLYGON);
            glColor3f(0.8, 0.2, 0.1);
            glVertex2f(location.x + size.x * cos(degree_to_radius(degreeToLeft)), location.y + size.x * sin(degree_to_radius(degreeToLeft)));
            glVertex2f(location.x + size.x/6 + size.x * cos(degree_to_radius(degreeToLeft)), location.y + size.x/6 + size.x * sin(degree_to_radius(degreeToLeft)));
            glVertex2f(location.x + size.x/6 + size.x * cos(degree_to_radius(degreeToRight)), location.y + size.x/6 + size.x * sin(degree_to_radius(degreeToRight)));
            glVertex2f(location.x + size.x * cos(degree_to_radius(degreeToRight)), location.y + size.x * sin(degree_to_radius(degreeToRight)));
        glEnd();
    }

    void drawRope(){
        float degree = 40;
        glBegin(GL_POLYGON);
            glColor3f(231.0/255 + (location.z * 10)/255.0, 152.0/255 - (location.z * 20)/255.0, 76.0/255 - (location.z * 20)/255.0);
            for(double i=2 * get_pi() / 6; i < 3 * get_pi() / 4; i+= 0.1){
                glVertex2f(
                    location.x + 8*size.x/7 * cos(degree_to_radius(degree)) + size.x/3 * cos(i), 
                    location.y + 8*size.x/7 * sin(degree_to_radius(degree)) + size.x/3 * sin(i)
                );
            }
            for(double i=3 * get_pi() / 4; i >= 2 * get_pi() / 6; i-= 0.1){
                glVertex2f(
                    location.x + 8*size.x/7 * cos(degree_to_radius(degree)) + size.x/4 * cos(i), 
                    location.y + 8*size.x/7 * sin(degree_to_radius(degree)) + size.x/4 * sin(i)
                );
            }
        glEnd();
    }
};

#endif