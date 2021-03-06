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
  this->direction=UP;
}

void ParticlePacman::set_direction(int direction)
{
  this->direction = direction;
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
      //std::cout << x << std::endl;
      //std::cout << y << std::endl;
      state=QUIET;
    }
}

//-----------------------------------------------

void ParticlePacman::draw()
{
/*
    glColor3f(0.0,1.0,1.0);

    int middleX = (((y+1)*WIDTH/COLUMNS)+(y*WIDTH/COLUMNS))/2; 
    int middleY = (((ROWS-x)*HEIGHT/ROWS) + ((ROWS-1-x)*HEIGHT/ROWS))/2;

    drawFilledCircle(middleX,middleY,7.0);
*/


    GLint position[4];
    GLfloat color[4];
    GLfloat material[4];
    material[0]=0.0;
    material[1]=0.0;
    material[2]=1.0;
    material[3]=1.0;
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,material);

    int faro1x,faro1y,faro2x,faro2y;

    int middleX = (((y+1)*WIDTH/COLUMNS)+(y*WIDTH/COLUMNS))/2; 
    int middleY = (((ROWS-x)*HEIGHT/ROWS) + ((ROWS-1-x)*HEIGHT/ROWS))/2;

    GLfloat dir[3];

    switch(direction){
        case UP:     
		dir[0]=0; dir[1]=1; dir[2]=0;
		position[0]=middleX; position[1]=middleY-25; position[2]=-50; position[3]=1;
                faro1x=middleX+4;faro1y=middleY+10;faro2x=middleX-4;faro2y=middleY+10;  
	break;
        case DOWN:   
		dir[0]=0; dir[1]=-1; dir[2]=0; 
		position[0]=middleX; position[1]=middleY+25; position[2]=-50; position[3]=1;
                faro1x=middleX+4;faro1y=middleY-10;faro2x=middleX-4;faro2y=middleY-10;
	break;
        case RIGHT:  
		dir[0]=1; dir[1]=0; dir[2]=0; 
		position[0]=middleX-25; position[1]=middleY; position[2]=-50; position[3]=1;
                faro1x=middleX+10;faro1y=middleY+4;faro2x=middleX+10;faro2y=middleY-4;
	break;
        case LEFT:   
		dir[0]=-1; dir[1]=0; dir[2]=0; 
		position[0]=middleX+25; position[1]=middleY; position[2]=-50; position[3]=1;
                faro1x=middleX-10;faro1y=middleY+4;faro2x=middleX-10;faro2y=middleY-4; 
	break;
    };


    
    
    glLightiv(GL_LIGHT1,GL_POSITION,position);
  
    color[0]=0.1; color[1]=0.1; color[2]=0.1; color[3]=1;
    glLightfv(GL_LIGHT1,GL_DIFFUSE,color);
    glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,dir);

    glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,30);

    glLightf(GL_LIGHT1,GL_CONSTANT_ATTENUATION,0.00);
    glLightf(GL_LIGHT1,GL_LINEAR_ATTENUATION,0.0);
    glLightf(GL_LIGHT1,GL_QUADRATIC_ATTENUATION,0.0);

    glEnable(GL_LIGHT1);
 
    glPushMatrix();
        glTranslated(middleX,middleY,-6);
        glutSolidSphere(10,50,50);
    glPopMatrix(); 


    material[0]=1.0;
    material[1]=1.0;
    material[2]=1.0;
    material[3]=1.0;
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,material);
    glPushMatrix();
        glTranslated(faro1x,faro1y,-6);
        glutSolidSphere(3,50,50);
    glPopMatrix();
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,material);
    glPushMatrix();
        glTranslated(faro2x,faro2y,-6);
        glutSolidSphere(3,50,50);
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

