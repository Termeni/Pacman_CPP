#include "ParticlePacman.h"
#include <iostream>


ParticlePacman::ParticlePacman()
{
  state=QUIET;
}

//-----------------------------------------------

void ParticlePacman::set_position(int x,int y)
{
  this->x = x;
  this->y = y;
}

//-----------------------------------------------

void ParticlePacman::init_movement(int destination_x,int destination_y,int duration)
{
  vx = (destination_x - x)/duration;
  vy = (destination_y - y)/duration;

  state=MOVE;
  time_remaining=duration;
}

//-----------------------------------------------

void ParticlePacman::integrate(long t)
{
  if(state==MOVE && t<time_remaining)
    {
      x = x + vx*t;
      y = y + vy*t;
      time_remaining-=t;
    }
  else if(state==MOVE && t>=time_remaining)
    {
      x = x + vx*time_remaining;
      y = y + vy*time_remaining;
      std::cout << x << std::endl;
      std::cout << y << std::endl;
      state=QUIET;
    }
}

//-----------------------------------------------

void ParticlePacman::draw()
{

    glColor3f(0.0,1.0,1.0);

    int middleX = (((y+1)*WIDTH/COLUMNS)+(y*WIDTH/COLUMNS))/2; 
    int middleY = (((ROWS-x)*HEIGHT/ROWS) + ((ROWS-1-x)*HEIGHT/ROWS))/2;

    drawFilledCircle(middleX,middleY,7.0);



/*

  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glVertex2i(x-6,y-6);
  glVertex2i(x+6,y-6);
  glVertex2i(x+6,y+6);
  glVertex2i(x-6,y+6);
  glEnd();
*/

}


void ParticlePacman::drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius){
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
