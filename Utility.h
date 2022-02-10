#include <GL/glut.h>
#include "Point2D.h"
#include "Point3D.h"
#include <cstdio>
#include <cstring>

#ifndef UTILITY_H
#define UTILITY_H

double PI = 3.1413;
int FPS = 60;
int UNIT = 800;
int HEIGHT = UNIT;
int WIDTH = UNIT;

double get_pi(){
    return PI;
}

int get_fps(){
    return FPS;
}

int get_unit(){
    return UNIT;
}

int get_height(){
    return HEIGHT;
}

int get_width(){
    return WIDTH;
}

GLfloat get_bomb_size(){
    return get_unit()*0.08/2;
}

GLfloat get_alien_size(){
    return get_unit()*0.1/2;
}

GLfloat get_delta_time(){
    return 1000.0 / ((float)FPS) / 1000.0;
}

GLfloat get_random(double min, double max){
    double random = (double)rand() / RAND_MAX;
    return min + random * (max - min);
}

int get_random(int min, int max){
    int random = rand()%(max - min + 1) + min -1;
    return random;
}

GLfloat degree_to_radius(GLfloat degree){
    return degree / 180 * PI;
}

void shuffle_array(Point2D arr[], int size){
    for(int i=0; i<size; i++){
        Point2D temp = arr[i];
        int randomLoc = get_random(i+1, size);
        arr[i] = arr[randomLoc];
        arr[randomLoc] = temp;
    }
}

void set_fps(int _FPS){
    FPS = _FPS;
}

void set_height(int _HEIGHT){
    HEIGHT = _HEIGHT;
}

void set_width(int _WIDTH){
    WIDTH = _WIDTH;
}

void draw_rectangle(GLfloat centerX, GLfloat centerY, GLfloat topEdge, GLfloat sideEdge){
  glBegin(GL_POLYGON);
    glVertex2f(centerX - topEdge/2, centerY - sideEdge/2);
    glVertex2f(centerX - topEdge/2, centerY + sideEdge/2);
    glVertex2f(centerX + topEdge/2, centerY + sideEdge/2);
    glVertex2f(centerX + topEdge/2, centerY - sideEdge/2);
  glEnd();
}

void draw_elipse(GLfloat centerX, GLfloat centerY, GLfloat radius, GLfloat radius2, GLfloat angle, bool filled, bool clockwise, GLfloat PI_constant){
  float degree = degree_to_radius(angle);
  glBegin(GL_POLYGON);
    for(double i=0; clockwise ? i<get_pi() * PI_constant : i>=get_pi() * PI_constant; i = clockwise ? i += 0.01 : i -= 0.01){
      GLfloat x = radius * cos(i);
      GLfloat y = radius2 * sin(i);

      GLfloat rotatedX = centerX + x * cos(degree) - y * sin(degree);
      GLfloat rotatedY = centerY + x * sin(degree) + y * cos(degree);
      glVertex2f(rotatedX, rotatedY);
    }
  glEnd();
}

void writeText(GLfloat x, GLfloat y, GLfloat scale, GLfloat opacity, GLfloat width, const char text[]){
  glRasterPos2f(x, y);
  glPushMatrix();
  glTranslatef(x, y, 0);
  glColor4f(1.0, 1.0, 0.0, opacity);
  glScalef(scale, scale, 1);
  glLineWidth(width);
  for (int i=0; i<strlen(text); i++){
    char curr = text[i];
    glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, curr);
  }
  glScalef(1, 1, 1);
  glLineWidth(1);
  glPopMatrix();
}
#endif