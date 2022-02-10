#include "Utility.h"

#ifndef PARTICLE_H
#define PARTICLE_H

struct Particle{
    Point3D location;
    Point3D color;
    Point2D size;
    Point2D speed;
    float startLifeTime;
    int sizeByLifetime;
    float lifeTime = startLifeTime;

    void move(){
        location.x += speed.x;
        location.y += speed.y;
    }
    
    void draw(){
        lifeTime -= get_delta_time() * get_fps()/60;
        if(lifeTime > 0 && size.x > 0){
            move();
            size.x += sizeByLifetime * lifeTime * get_delta_time() * get_fps()/60;
            glColor4f(color.x, color.y, color.z, 0.8);
            glBegin(GL_POLYGON);
                for(double i=0; i<get_pi() * 2; i += 0.01){
                    glVertex2f(location.x + size.x * cos(i), location.y + size.x * sin(i));
                }
            glEnd();
        }
    }
};

#endif