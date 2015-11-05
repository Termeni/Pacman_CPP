#include <iostream>
#include "Map.h"
#include <GLUT/glut.h>
#include <math.h> 

using namespace std;

#define COLUMNS 35
#define ROWS 35
#define WIDTH 1000
#define HEIGHT 1000
#define PI 3.14159265

void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius);
void display();
void drawPacman();
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
    glutCreateWindow("Chess board");

    glutDisplayFunc(display);
    //glutKeyboardFunc(keyboard);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,WIDTH-1,0,HEIGHT-1);

    glutMainLoop();

    exit(0); //fix "Abort trap: 6"
    
    
    /*
    Cell c = Cell('5');
    
    Cell c2 = Cell();
    
    cout << c.getValue() << c2.getValue() << c.getValue() << endl;
    */
}

void display()
{
  int i,j;

  glClearColor(0.0,0.0,0.0,0.0);
  glClear(GL_COLOR_BUFFER_BIT);

  for(i=0;i<ROWS;i++)
    for(j=0;j<COLUMNS;j++)
      if( map->isWall(i,j)) {
            glColor3f(0.0,0.0,1.0);
            //glColor3f(0.0,0.0,0.0);
            glBegin(GL_QUADS);

            glVertex2i((j+1)*WIDTH/COLUMNS,(ROWS-1-i)*HEIGHT/ROWS); 
            glVertex2i(j*WIDTH/COLUMNS, (ROWS-1-i)*HEIGHT/ROWS); 
            glVertex2i(j*WIDTH/COLUMNS, (ROWS-i)*HEIGHT/ROWS); 
            glVertex2i((j+1)*WIDTH/COLUMNS,(ROWS-i)*HEIGHT/ROWS); 
            

            glEnd();
      }else if (map->hasFood(i,j))
      {
            glColor3f(1.0,1.0,0.0);

            int middleX = (((j+1)*WIDTH/COLUMNS)+(j*WIDTH/COLUMNS))/2; 
            int middleY = (((ROWS-i)*HEIGHT/ROWS) + ((ROWS-1-i)*HEIGHT/ROWS))/2;

            drawFilledCircle(middleX,middleY,5.0);

            /*

            glBegin(GL_QUADS);

            glVertex2i((j+1)*WIDTH/COLUMNS,(ROWS-1-i)*HEIGHT/ROWS); 
            glVertex2i(j*WIDTH/COLUMNS, (ROWS-1-i)*HEIGHT/ROWS); 
            glVertex2i(j*WIDTH/COLUMNS, (ROWS-i)*HEIGHT/ROWS); 
            glVertex2i((j+1)*WIDTH/COLUMNS,(ROWS-i)*HEIGHT/ROWS); 
            
            glEnd();

            */
      }

      drawPacman();

  glutSwapBuffers();

}

void drawPacman(){
    
}



void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius){
    int i;
    int triangleAmount = 20; //# of triangles used to draw circle
    
    //GLfloat radius = 0.8f; //radius
    GLfloat twicePi = 2.0f * PI;
    
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y); // center of circle
        for(i = 0; i <= triangleAmount;i++) { 
            glVertex2f(
                    x + (radius * cos(i *  twicePi / triangleAmount)), 
                y + (radius * sin(i * twicePi / triangleAmount))
            );
        }
    glEnd();
}