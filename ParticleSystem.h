#include "Particle.h"

#ifndef ParticleSystem_h
#define ParticleSystem_h

struct ParticleSystem{
    int startNumberOfParticle;
    Point3D location;
    Point3D color;
    Point2D size;
    Point2D minSpeed;
    Point2D maxSpeed;
    float startLifeTime;
    int sizeByLifetime;
    bool loop;
    float lifeTime;
    Particle particles[10];

    void initializeParticles(){
        lifeTime = startLifeTime;
        for(int i=0; i<startNumberOfParticle; i++){
            Point2D randomSpeed = {get_random(minSpeed.x, maxSpeed.x), get_random(minSpeed.y, maxSpeed.y)};
            particles[i] = {location, color, size, randomSpeed, startLifeTime, sizeByLifetime};
        }
    }

    bool step(){
        int numberOfLivingParticle = 0;
        for(int i=0; i<startNumberOfParticle; i++){
            if(particles[i].lifeTime > 0 && particles[i].size.x > 0) 
                numberOfLivingParticle++;
            particles[i].draw();
        }
        if(numberOfLivingParticle == 0 && loop){
            initializeParticles();
        }
        return numberOfLivingParticle > 0;
    }

};

#endif