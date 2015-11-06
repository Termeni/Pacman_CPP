#include <iostream>
#include "Map.h"
#include <GLUT/glut.h>
#include <math.h>  
#include "KeyboardKeys.h"
using namespace std;

#define COLUMNS 35
#define ROWS 35
#define WIDTH 1000
#define HEIGHT 1000
#define PI 3.14159265


void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius);

void display();
void keyboard(unsigned char key, int x, int y);

void drawPacman(int i, int j);
void drawFood(int i, int j);
void drawWall(int i, int j);
Map *map;

int main(int argc,char *argv[]) {
    
    cout << "Pacman" << endl;
    
    cout << "Generating map..." << endl;
    
    map = new Map(ROWS, COLUMNS);
    map->print();
    
    cout << "Map generated." << endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Pacman");

    glutDisplayFunc(display);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,WIDTH-1,0,HEIGHT-1);

    glutKeyboardFunc(keyboard);
    glutMainLoop();

    exit(0); //fix "Abort trap: 6"
    
}

void display()
{
  int i,j;

  glClearColor(0.0,0.0,0.0,0.0);
  glClear(GL_COLOR_BUFFER_BIT);

  for(i=0;i<ROWS;i++)
    for(j=0;j<COLUMNS;j++)
      if( map->isWall(i,j)) {

            drawWall(i,j);

      }else if (map->hasFood(i,j))
      {
            drawFood(i,j);

      }else if (map->isPacman(i,j)){

            drawPacman(i,j);
      }      

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
        case 'a': map->movePacman(LEFT); break;
        case 'w': map->movePacman(UP); break;
        case 'd': map->movePacman(RIGHT); break;
        case 's': map->movePacman(DOWN); break;
    };
    glutPostRedisplay();
}