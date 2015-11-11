#include <iostream>
#include "Map.h"
#include <GLUT/glut.h>
#include <math.h>  
#include "KeyboardKeys.h"
#include "ParticlePacman.h"
#include "ParticleGhost.h"

using namespace std;

#define COLUMNS 35
#define ROWS 35
#define WIDTH 1000
#define HEIGHT 1000
#define PI 3.14159265

#define MOVE 1
#define QUIET 2

void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius);

void display();
void keyboard(unsigned char key, int x, int y);

void drawPacman(int i, int j);
void drawBlueGhost(int i, int j);
void drawGreenGhost(int i, int j);
void drawRedGhost(int i, int j);
void drawYellowGhost(int i, int j);
void drawFood(int i, int j);
void drawWall(int i, int j);
void movePacman(int key);
bool moveGhost(int key);

void idle();
Map *map;

long last_t=0;

ParticlePacman pacman;
ParticleGhost ghost;

int main(int argc,char *argv[]) {
    
    cout << "Pacman" << endl;
    
    cout << "Generating map..." << endl;
    
    map = new Map(ROWS, COLUMNS);
    map->print();
    
    cout << "Map generated." << endl;

    int i,j;
    for(i=0;i<ROWS;i++){
    for(j=0;j<COLUMNS;j++){
      if (map->isPacman(i,j)){
            pacman.set_position(i,j);

      }
      if(map->isBlueGhost(i,j)){
        ghost.set_position(i,j);
      }        
    }
    }


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Pacman");

    glutDisplayFunc(display);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,WIDTH-1,0,HEIGHT-1);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    exit(0); //fix "Abort trap: 6"
    
}

void display()
{
  int i,j;
  glClearColor(0.0,0.0,0.0,0.0);
  glClear(GL_COLOR_BUFFER_BIT);

  for(i=0;i<ROWS;i++){
    for(j=0;j<COLUMNS;j++){
      if( map->isWall(i,j)) {
            drawWall(i,j);
      }else if (map->hasFood(i,j)){
            drawFood(i,j);
      }else if (map->isPacman(i,j)){
            //drawPacman(i,j);
      }
      /*if (map->isBlueGhost(i,j)){
            drawBlueGhost(i,j);
      }if (map->isGreenGhost(i,j)){
            drawGreenGhost(i,j);
      }if (map->isRedGhost(i,j)){
            drawRedGhost(i,j);
      }if (map->isYellowGhost(i,j)){
            drawYellowGhost(i,j);
      } */       
    }
  }

  pacman.draw();
  if(ghost.state == QUIET){
    bool flag = false;
    //cout << "Fora" << endl;
    
        ghost.move();
        flag = moveGhost(ghost.direction);
    
    //cout << "Fora" << endl;
    
  }
  ghost.draw();
  glutSwapBuffers();

}

void drawWall(int i, int j){

    glColor3f(0.0,0.0,1.0);
            //glColor3f(0.0,0.0,0.0);
    glBegin(GL_QUADS);

    glVertex2i((j+1)*WIDTH/COLUMNS,(ROWS-1-i)*HEIGHT/ROWS); 
    glVertex2i(j*WIDTH/COLUMNS, (ROWS-1-i)*HEIGHT/ROWS); 
    glVertex2i(j*WIDTH/COLUMNS, (ROWS-i)*HEIGHT/ROWS); 
    glVertex2i((j+1)*WIDTH/COLUMNS,(ROWS-i)*HEIGHT/ROWS); 
            
    glEnd();
}

void drawPacman(int i, int j){

    glColor3f(0.0,1.0,1.0);

    int middleX = (((j+1)*WIDTH/COLUMNS)+(j*WIDTH/COLUMNS))/2; 
    int middleY = (((ROWS-i)*HEIGHT/ROWS) + ((ROWS-1-i)*HEIGHT/ROWS))/2;

    drawFilledCircle(middleX,middleY,7.0);
    
}

void drawGreenGhost(int i, int j){
    glColor3f(0.0,0.75,1.0);

    int middleX = (((j+1)*WIDTH/COLUMNS)+(j*WIDTH/COLUMNS))/2; 
    int middleY = (((ROWS-i)*HEIGHT/ROWS) + ((ROWS-1-i)*HEIGHT/ROWS))/2;

    drawFilledCircle(middleX,middleY,7.0);

}
void drawRedGhost(int i, int j){
    glColor3f(0.25,0.75,1.0);

    int middleX = (((j+1)*WIDTH/COLUMNS)+(j*WIDTH/COLUMNS))/2; 
    int middleY = (((ROWS-i)*HEIGHT/ROWS) + ((ROWS-1-i)*HEIGHT/ROWS))/2;

    drawFilledCircle(middleX,middleY,7.0);

}
void drawYellowGhost(int i, int j){
    glColor3f(0.0,0.4,0.7);

    int middleX = (((j+1)*WIDTH/COLUMNS)+(j*WIDTH/COLUMNS))/2; 
    int middleY = (((ROWS-i)*HEIGHT/ROWS) + ((ROWS-1-i)*HEIGHT/ROWS))/2;

    drawFilledCircle(middleX,middleY,7.0);

}

void drawBlueGhost(int i, int j){
    glColor3f(0.5,0.4,0.7);

    int middleX = (((j+1)*WIDTH/COLUMNS)+(j*WIDTH/COLUMNS))/2; 
    int middleY = (((ROWS-i)*HEIGHT/ROWS) + ((ROWS-1-i)*HEIGHT/ROWS))/2;

    drawFilledCircle(middleX,middleY,7.0);

}


void drawFood(int i, int j){

    glColor3f(1.0,1.0,0.0);

    int middleX = (((j+1)*WIDTH/COLUMNS)+(j*WIDTH/COLUMNS))/2; 
    int middleY = (((ROWS-i)*HEIGHT/ROWS) + ((ROWS-1-i)*HEIGHT/ROWS))/2;

    drawFilledCircle(middleX,middleY,5.0);

}


void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius){
    int i;
    int triangleAmount = 20;
    GLfloat twicePi = 2.0f * PI;
    
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y);
        for(i = 0; i <= triangleAmount;i++) { 
            glVertex2f(
                    x + (radius * cos(i *  twicePi / triangleAmount)), 
                y + (radius * sin(i * twicePi / triangleAmount))
            );
        }
    glEnd();
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key){
        case 'a': movePacman(LEFT); break;
        case 'w': movePacman(UP); break;
        case 'd': movePacman(RIGHT); break;
        case 's': movePacman(DOWN); break;
    };
    glutPostRedisplay();
}


void movePacman(int key){


    switch(key)
    {
        case LEFT: 
            if (!map->isWall(map->pacmanX,map->pacmanY-1) && pacman.state == QUIET)
            {

                if(map->isGhost(map->pacmanX,map->pacmanY-1)){
                    exit(0);
                }
                //cout << "Pacman y" << map->pacmanY << endl;
                pacman.init_movement(map->pacmanX,map->pacmanY-1,100);
                map->setCorridor(map->pacmanX,map->pacmanY);
                map->setPacman(map->pacmanX,(map->pacmanY)-1);
                //map->pacmanY=map->pacmanY-1;
            }
        break;

        case UP: 
            if (!map->isWall(map->pacmanX-1,map->pacmanY) && pacman.state == QUIET)
            {
                if(map->isGhost(map->pacmanX-1,map->pacmanY)){
                    exit(0);
                }

                pacman.init_movement(map->pacmanX-1,map->pacmanY,100);
                map->setCorridor(map->pacmanX,map->pacmanY);
                map->setPacman(map->pacmanX-1,(map->pacmanY));
            }
        break;

        case RIGHT: 
            if (!map->isWall(map->pacmanX,map->pacmanY+1) && pacman.state == QUIET)
            {
                if(map->isGhost(map->pacmanX,map->pacmanY+1)){
                    exit(0);
                }

                pacman.init_movement(map->pacmanX,map->pacmanY+1,100);
                map->setCorridor(map->pacmanX,map->pacmanY);
                map->setPacman(map->pacmanX,(map->pacmanY)+1);
            }
        break;

        case DOWN: 
            if (!map->isWall(map->pacmanX+1,map->pacmanY) && pacman.state == QUIET)
            {
                if(map->isGhost(map->pacmanX+1,map->pacmanY)){
                    exit(0);
                }

                pacman.init_movement(map->pacmanX+1,map->pacmanY,100);
                map->setCorridor(map->pacmanX,map->pacmanY);
                map->setPacman(map->pacmanX+1,(map->pacmanY));
            }
            break;
            
    }
}

bool moveGhost(int key){


    switch(key)
    {
        case LEFT: 
            if (!map->isWall(map->BlueGhostX,map->BlueGhostY-1))
            {

                if(map->isPacman(map->BlueGhostX,map->BlueGhostY-1)){
                    exit(0);
                }
                //cout << "Pacman y" << map->pacmanY << endl;
                ghost.init_movement(map->BlueGhostX,map->BlueGhostY-1,100);
                map->setCorridor(map->BlueGhostX,map->BlueGhostY);
                map->setBlueGhost(map->BlueGhostX,(map->BlueGhostY)-1);
                //map->pacmanY=map->pacmanY-1;
                return true;
            }
            return false;
        break;

        case UP: 
            if (!map->isWall(map->BlueGhostX-1,map->BlueGhostY))
            {

                if(map->isPacman(map->BlueGhostX-1,map->BlueGhostY)){
                    exit(0);
                }
                //cout << "Pacman y" << map->pacmanY << endl;
                ghost.init_movement(map->BlueGhostX-1,map->BlueGhostY,100);
                map->setCorridor(map->BlueGhostX,map->BlueGhostY);
                map->setBlueGhost(map->BlueGhostX-1,(map->BlueGhostY));
                //map->pacmanY=map->pacmanY-1;
                return true;
            }
            return false;
        break;

        case RIGHT: 
            if (!map->isWall(map->BlueGhostX,map->BlueGhostY+1))
            {

                if(map->isPacman(map->BlueGhostX,map->BlueGhostY+1)){
                    exit(0);
                }
                //cout << "Pacman y" << map->pacmanY << endl;
                ghost.init_movement(map->BlueGhostX,map->BlueGhostY+1,100);
                map->setCorridor(map->BlueGhostX,map->BlueGhostY);
                map->setBlueGhost(map->BlueGhostX,(map->BlueGhostY)+1);
                //map->pacmanY=map->pacmanY-1;
                return true;
            }
            return false;
        break;

        case DOWN: 
            if (!map->isWall(map->BlueGhostX+1,map->BlueGhostY))
            {

                if(map->isPacman(map->BlueGhostX+1,map->BlueGhostY)){
                    exit(0);
                }
                //cout << "Pacman y" << map->pacmanY << endl;
                ghost.init_movement(map->BlueGhostX+1,map->BlueGhostY,100);
                map->setCorridor(map->BlueGhostX,map->BlueGhostY);
                map->setBlueGhost(map->BlueGhostX+1,(map->BlueGhostY));
                //map->pacmanY=map->pacmanY-1;
                return true;
            }
            return false;
            break;
            
    }
}


void idle()
{
  long t;

  t=glutGet(GLUT_ELAPSED_TIME); 

  if(last_t==0)
    last_t=t;
  else
    {
      pacman.integrate(t-last_t);
      ghost.integrate(t-last_t);
      last_t=t;
    }


  glutPostRedisplay();
}










