#include "ParticleGhost.h"
#include <iostream>


ParticleGhost::ParticleGhost()
{
  state=QUIET;

}

//-----------------------------------------------

void ParticleGhost::set_position(int x,int y)
{
  srand(time(NULL));
  this->x = x;
  this->y = y;
  move();
}

void ParticleGhost::move(){
  
  int r = rand() % 4;

  direction = r+1;
  /*switch(r){
    case 0:
      std::cout << "UP" << std::endl;
    break;
    case 1:
      std::cout << "DOWN" << std::endl;
    break;
    case 2:
      std::cout << "RIGHT" << std::endl;
    break;
    case 3:
      std::cout << "LEFT" << std::endl;
    break;
  }*/
}

//-----------------------------------------------

void ParticleGhost::init_movement(int destination_x,int destination_y,int duration)
{
  vx = (destination_x - x)/duration;
  vy = (destination_y - y)/duration;

  state=MOVE;
  time_remaining=duration;
}

//-----------------------------------------------

void ParticleGhost::integrate(long t)
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
      //std::cout << x << std::endl;
      //std::cout << y << std::endl;
      state=QUIET;
    }
}

//-----------------------------------------------

void ParticleGhost::draw()
{

    GLint position[4];
    GLfloat color[4];
    GLfloat material[4];
    material[0]=1.0;
    material[1]=0.0;
    material[2]=0.0;
    material[3]=1.0;
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,material);

    int middleX = (((y+1)*WIDTH/COLUMNS)+(y*WIDTH/COLUMNS))/2; 
    int middleY = (((ROWS-x)*HEIGHT/ROWS) + ((ROWS-1-x)*HEIGHT/ROWS))/2;


    position[0]=middleX; position[1]=middleY; position[2]=-10; position[3]=1; 
    glLightiv(GL_LIGHT2,GL_POSITION,position);
  
    color[0]=1; color[1]=1; color[2]=1; color[3]=1;
    glLightfv(GL_LIGHT2,GL_AMBIENT,color);
    glLightf(GL_LIGHT2,GL_CONSTANT_ATTENUATION,0.0);

    glLightf(GL_LIGHT2,GL_LINEAR_ATTENUATION,0.025);
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 90.0);
    glEnable(GL_LIGHT2);

    glPushMatrix();
        glTranslated(middleX,middleY,-6);
        glutSolidSphere(10,50,50);
    glPopMatrix();



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


void ParticleGhost::drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius){
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

