#include <stdio.h>
#include <math.h>
#include "Utility.h"
#include "Bomb.h"
#include "Alien.h"
#include <time.h> 

void myInit(void);
void myDisplay(void);
void myDraw(void);
void evalScore(int);
void output(GLfloat, GLfloat, char*);
void myKeyboard(unsigned char key, int x, int y);
void drawBackground(void);
void hitEffect(float r, float g, float b);
void shakeCamera(void);
void myIdle(int value);
void removeBomb(int index);
void myReshape(int w, int h);
void myMouse(int, int, int, int);
void initializeAliens(void);
void initializeStars(void);
void resultScreen(void);
void addScore(int);


int score = 0, shakeCameraCheck = 1, numberOfBomb = 0, numberOfStars = 100, numberOfEvilAlien = 8;
bool pause, oneStep, hitAlly, hitEnemy, end = true;
float hitAllyTimer, hitEnemyTimer, addScoreTimer, starsAngle;

Point3D stars[100];
Bomb bombArray[100];
Alien alienArray[20];

int main(int argc, char ** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

  glutInitWindowSize(get_width(), get_height());
  glutInitWindowPosition(100, 100);

  glutCreateWindow("Alien");
  myInit();
  glutDisplayFunc(myDisplay);
  glutMouseFunc(myMouse);
  glutKeyboardFunc(myKeyboard);
  glutTimerFunc(1000/get_fps(), myIdle, 0);
  glutReshapeFunc(myReshape);
  glutMainLoop();
}

void myInit(void){
  glClearColor(0.0, 0.1, 0.15, 1.0);
  glPointSize(1.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, get_width(), 0, get_height());
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  srand(time(0));
  
  initializeStars();
  initializeAliens();
}

void initializeAliens(){
  Point2D locArray [300];
  
  int sizeX = (int) (get_width()/(get_alien_size()*2.5));
  int sizeY = (int) (get_height()/(get_alien_size()*2.5));
  
  for(int i=0; i<sizeX; i++){
    for(int j=0; j<sizeY; j++){
      locArray[i * sizeY + j] = {(float) (i), (float) (j)};
    }
  }

  shuffle_array(locArray, sizeX*sizeY);
    
  for(int i=0; i<20; i++){
    Point3D location = {(locArray[i].x) * get_width()/sizeX + get_alien_size(), (locArray[i].y) * get_height()/sizeY + get_alien_size(), (float)((int) (i/4))};
    Point3D color = {0.3, 1.0, 0.3};
    Point2D size = {get_alien_size(), get_alien_size()};
    Point2D speed = {get_random(-3.0, 3.0), get_random(-3.0, 3.0)};
    alienArray[i] = {location, color, size, speed};
  } 

}

void initializeStars(){
  starsAngle = 0;
  for(int i=0; i<numberOfStars; i++){
    stars[i] = {(float) get_random(0, get_width()), (float) get_random(0, get_height()), get_random(3.0, 5.0)};
  }
}

void evalScore(int depth){
  switch (depth){
    case 0: addScore(-4000); hitAlly = true; break;
    case 1: addScore(-2000); hitAlly = true; break;
    case 2: addScore(-1000); hitAlly = true; break;
    case 3: addScore(1000); hitEnemy = true; numberOfEvilAlien--; break;
    case 4: addScore(2000); hitEnemy = true; numberOfEvilAlien--; break;
  }
}

void drawBackground(){
  glColor4f(1, 1, 1, 0.5);
  for(int c=0; c<numberOfStars; c++){
    float rotatedX = (stars[c].x - get_width()/2) * cos(starsAngle) - (stars[c].y - get_height()/2) * sin(starsAngle) + get_width()/2;
    float rotatedY = (stars[c].x - get_width()/2) * sin(starsAngle) + (stars[c].y - get_height()/2) * cos(starsAngle) + get_height()/2;
    draw_elipse(rotatedX, rotatedY, stars[c].z, stars[c].z, 0, true, true, 2);
  }
  starsAngle += 0.002;
}

void hitEffect(float r, float g, float b){
  glColor4f(r, g, b, 0.2);
  draw_rectangle(get_width()/2, get_height()/2, get_width()*1.2, get_height()*1.2);
}

void removeBomb(int index){
  for(int i=index; i<numberOfBomb; i++){
    bombArray[i] = bombArray[i+1];
  }
  numberOfBomb--;
}

void shakeCamera(){
  GLfloat degree = 2;
  glTranslatef(get_width()/2, get_height()/2, 0.0);
  glRotatef(((shakeCameraCheck < 2) ? degree : -degree), 0.0, 0.0, 1.0);
  shakeCameraCheck = (shakeCameraCheck + 1)%4;
  glTranslatef(-get_width()/2, -get_height()/2, 0.0);
}

void myDisplay(void){
  glClear(GL_COLOR_BUFFER_BIT);
  myDraw();
  glutSwapBuffers();
}

void myIdle(int value){
  if(!pause){
    glutPostRedisplay();
  }
  else if(pause && oneStep){
    glutPostRedisplay();
    oneStep = false;
  }
  glutTimerFunc(1000/get_fps(), myIdle, 0);
}

void drawDiedAliens(){
  for(int i=20; i>=0; i--){
    if(alienArray[i].living != 1){
      alienArray[i].draw();
    }
  }
}

void drawAliensAndBombs(){
  for(int i=20; i>=0; i--){
    if(alienArray[i].living == 1){
      if(get_fps() <= 15) alienArray[i].opacity -= 0.04;
      alienArray[i].draw();
      for(int j=i/4*4; j<i/4*4 + 4; j++){
        if(i != j){
          if(alienArray[j].living == 1){
            Point3D minus = (alienArray[i].location - alienArray[j].location);
            if(sqrt(minus.x * minus.x + minus.y * minus.y) < alienArray[i].size.x * 2){
              alienArray[i].speed.swap(alienArray[j].speed);
            }
          }
        }
      }
    }
    for(int j=0; j<numberOfBomb; j++){
      if(bombArray[j].location.z > 4) removeBomb(j);
      Point3D minus = (alienArray[i].location - bombArray[j].location);
      if(alienArray[i].living == 1 && minus.z == 0 && sqrt(minus.x * minus.x + minus.y * minus.y) < alienArray[i].size.x + bombArray[j].size.x ){
        alienArray[i].living = 0;
        evalScore(i/4);
        removeBomb(j);
      }
      if(i%4 == 3){
        if(bombArray[j].location.z == i/4){
          bombArray[j].draw();
        }
      }
    }
  }
}

void myDraw(){
  drawBackground();
  if(addScoreTimer < 0){
    addScoreTimer+=50;
    score-=50;
  }
  else if(addScoreTimer > 0){
    addScoreTimer-=50;
    score+=50;
  }
  if(!end){
    drawDiedAliens();
    drawAliensAndBombs();

    if(hitAlly){
      hitEffect(1.0, 0.0, 0.0);
      hitAllyTimer += get_delta_time();
      shakeCamera();
      if(hitAllyTimer > 0.5 * ( 60 / get_fps())){
        glLoadIdentity();
        shakeCameraCheck = 1;
        hitAlly = false;
        hitAllyTimer = 0;
      }
    }

    if(hitEnemy){
      if(numberOfEvilAlien == 0){
        set_fps(15);
      }
      hitEffect(0.0, 1.0, 0.0);
      hitEnemyTimer += get_delta_time();
      if(hitEnemyTimer > 0.5 * ( 60 / get_fps())){
        hitEnemy = false;
        hitEnemyTimer = 0;
        if(numberOfEvilAlien == 0){  
          end = true;
        }
      }
    }    
  }
  else{
    resultScreen();
  }
  char test[30];
  snprintf(test, 30, "Score: %d", score);

  float gag = 123;

  if(abs(score) >= 1000 && abs(score) < 10000){
    gag += 67;
  }
  else if(abs(score) >= 10000){
    gag += 80;
  }

  writeText(get_width()/2 - gag, get_height() - 100, 0.3, 1.0, 2, &test[0]);
}

void myMouse(int button, int state, int x, int y){
  if(numberOfEvilAlien != 0 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
    Point3D location = {(float) x, get_height() - (float) y, 0};
    Point3D color = {0.4, 0.6, 0.3};
    Point2D size = {get_bomb_size(), get_bomb_size()};
    Point2D speed = {3.0, 2.0};
    bombArray[numberOfBomb++] = {location, color, size, speed};
  }
}

void myKeyboard(unsigned char key, int x, int y){
  if(key == 'P' || key == 'p'){
    pause = !pause;
  }
  else if(key == 'S' || key == 's'){
    if(!pause)
      pause = true;
    if(pause)
      oneStep = true;
  }
  else if(key == 'R' || key == 'r'){
    initializeStars();
    initializeAliens();
    set_fps(60);
    numberOfEvilAlien = 8;
    end = false;
    score = 0;
    numberOfBomb = 0;
    addScoreTimer = 0;
  }
}

void myReshape(int w, int h){
  glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLfloat)w, 0.0, (GLfloat)h);
	glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
	glViewport(0,0,w,h);
	set_width(w);
	set_height(h);

  initializeStars();
}

void resultScreen(){
  glLoadIdentity();
  writeText(get_width()/2 - 235, get_height()/2, 0.5, 1.0, 10, "GAME OVER");
  if(score <= 0)
    writeText(get_width()/2 - 125, 100, 0.2, 1.0, 2, "Never give up");

  writeText(get_width()/2 - 115, get_height()/2 - 100, 0.3, 1.0, 3, "Press R");
  writeText(get_width()/2 - 190, get_height()/2 - 150, 0.3, 1.0, 3, "to try again");
}

void addScore(int score){
  addScoreTimer += score;
}