#include "ParticleSystem.h"

#ifndef ALIEN_H
#define ALIEN_H

struct Alien{
    Point3D location;
    Point3D color;
    Point2D size;
    Point2D speed;
    GLfloat graveTimer = 5;
    int living = 1;
    bool start = true;
    GLfloat opacity = 0.9;
    ParticleSystem particleSystem = {5, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {50.0, 50.0}, {-3.0, -3.0}, {3.0, 3.0}, 2, -50, false};

    void move(){
        if(location.x + size.x > get_width() || location.x - size.x < 0)
            speed.x *= -1;
        if(location.y + size.x > get_height() || location.y - size.x < 0)
            speed.y *= -1;
        location.x += speed.x;
        location.y += speed.y;
    }

    void draw(){
        particleSystem.location = location;
        if(start){
            start = false;
        }
        if(living == 1){
            move();
        }
        else if(living == 0){
            particleSystem.initializeParticles();
            living = -1;
        }
        drawBody();
        drawEyes();
        if(location.z > 2)
            drawMouth();
        else
            drawSmile();
        if(living == -1){
            die();
        }
    }

    void drawBody(){
        glColor4f(color.x - location.z * 50.0/255.0, color.y - location.z * 50.0/255.0, color.z - location.z * 50.0/255.0, opacity);
        draw_elipse(location.x, location.y, size.x, size.x, 0, true, true, 2);
    }

    void drawEyes(){
        GLfloat angle = -45;
        if(location.z > 2) glColor4f(1.0, 0.0, 0.0, opacity);
        else glColor4f(0.0, 0.0, 1.0, opacity);

        draw_elipse(location.x - size.x/2.5, location.y, size.x/3, size.x/5, angle, true, true, 2);
        draw_elipse(location.x + size.x/2.5, location.y, size.x/3, size.x/5, -angle, true, true, 2);
    }

    void drawMouth(){
        glColor4f(0.0, 0.0, 0.0, opacity);
        draw_rectangle(location.x, location.y - size.x*2/3, size.x*2/3, size.x*0.2);
    }

    void drawSmile(){
        glColor4f(0.0, 0.0, 0.0, opacity);
        draw_elipse(location.x, location.y - size.x/2, size.x/4, size.x/4, 0, true, false, -1);
    }

    void drawGrave(){
        if(graveTimer > 0){
            graveTimer -= get_delta_time();
            GLfloat localOpacity = opacity > 0.4 ? opacity - 0.4 : 0.0;
            glColor4f(150.0/255.0, 157.0/255.0, 150.0/255.0, localOpacity);
            draw_rectangle(location.x, location.y, size.y, size.y/2);
            draw_rectangle(location.x, location.y + size.y/2, size.y*0.6, size.y/2);
            draw_elipse(location.x, location.y + 3*size.y/4, 3*size.y/10, size.y/6, 0, true, true, 1);
            writeText(location.x - 15, location.y - 4, 0.1, opacity, 2, "RIP");
        }
    }

    void die(){
        drawGrave();
        particleSystem.step();
        if(size.x > 0)
            size.x -= 0.5;
        else size.x = 0;
    }
};

#endif