#include <iostream>
#include "Map.h"
#include <GL/glut.h>
#include <math.h>  
#include "KeyboardKeys.h"
#include "ParticlePacman.h"
#include "ParticleGhost.h"
#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>
#include "Arduino.h"

using namespace std;

#define COLUMNS 35
#define ROWS 35
#define WIDTH 1000
#define HEIGHT 1000
#define PI 3.14159265

#define MOVE 1
#define QUIET 2

void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius);

void ReadJPEG(char *filename,unsigned char **image,int *width, int *height);
GLuint LoadTexture(char *filename,int dim);

void display();
void keyboard(unsigned char key, int x, int y);

void drawBlueGhost(int i, int j);
void drawGreenGhost(int i, int j);
void drawRedGhost(int i, int j);
void drawYellowGhost(int i, int j);
void drawFood(int i, int j);
void drawWall(int i, int j);
void drawGround(int i, int j);
void movePacman(int key);
bool moveGhost(int key);

void PositionObserver(float alpha,float beta,int radi);

void idle();

void readData();

Map *map;

long last_t=0;

ParticlePacman pacman;
ParticleGhost ghost;

int anglealpha = 90;
int anglebeta = 26;

Arduino arduino;
ArduinoData ardData;

void readData(){
  
  arduino.getData();
}

GLuint groundTexture, wallTexture, rogueSquadronTexture;

bool hungry = true;

int DIFFICULTY = 2;

int main(int argc,char *argv[]) {

    thread th1 (readData);
    
    cout << "Configuring controller..." << endl;

    cout << "Pacman" << endl;
    
    cout << "Generating map..." << endl;
    
    map = new Map(ROWS, COLUMNS);
    cout << map->get_map_string() << endl;

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
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Pacman");
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    
    //LoadTexture("grass.jpg",64);
    //LoadTexture("grass.jpg",64);
    groundTexture = LoadTexture("grass.jpg",64);
    wallTexture = LoadTexture("pared.jpg",64);
    rogueSquadronTexture = LoadTexture("rogueSquadron.jpg",64);
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

  

  ardData= arduino.getGameData();

    printf("-----------------------------------------------\n");
    printf("Direction: %s\n", ardData.direction.c_str());
    printf("Pulse Sensor Stable Value: %i\n",ardData.pulseSensorStableValue);
    printf("Pulse Sensor Real Value: %i\n",ardData.pulseSensorRealValue);
    printf("Skin Resistence Stable Value: %i\n",ardData.skinResistenceStableValue);
    printf("Skin Resistence Real Value: %i\n",ardData.skinResistenceRealValue);
    printf("Hungry: %i\n",ardData.hungry);
    printf("-----------------------------------------------\n");

  if(ardData.direction.compare("left")==0){
	movePacman(LEFT);
  }else if(ardData.direction.compare("right")==0){
	movePacman(RIGHT);
  }else if(ardData.direction.compare("up")==0){
	movePacman(UP);
  }else if(ardData.direction.compare("down")==0){
	movePacman(DOWN);
  }
 hungry = ardData.hungry;

  GLint position[4];
  GLfloat color[4];
  GLfloat material[4];

  int i,j;
  glClearColor(0.0,0.0,0.0,0.0);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  PositionObserver(anglealpha,anglebeta,5000);
  cout << "alpha" << anglealpha << endl ;
  cout << "beta" << anglebeta << endl;
  cout << endl;


  

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-WIDTH*0.1,WIDTH*1.0,-HEIGHT*0.1,HEIGHT*1.0,10,10000);

  glMatrixMode(GL_MODELVIEW);

  glPolygonMode(GL_FRONT,GL_FILL);
  glPolygonMode(GL_BACK,GL_LINE);

  //lights

  //-- Ambient light
  
  position[0]=0; position[1]=0; position[2]=-30; position[3]=1; 
  glLightiv(GL_LIGHT0,GL_POSITION,position);
  
  color[0]=0.1; color[1]=0.1; color[2]=0.1; color[3]=1;
  glLightfv(GL_LIGHT0,GL_AMBIENT,color);
  glEnable(GL_LIGHT0);


  for(i=0;i<ROWS;i++){
    for(j=0;j<COLUMNS;j++){
      if( map->isWall(i,j)) {
            drawWall(i,j);
      }else if (map->hasFood(i,j)){
            drawFood(i,j);
            drawGround(i,j);
      }else{
        
        drawGround(i,j);
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
        string mapString = map->get_map_string();
        ghost.move(DIFFICULTY, 1, mapString);
        flag = moveGhost(ghost.direction);
    
    //cout << "Fora" << endl;
    
  }
  ghost.draw();
  glutSwapBuffers();

}


void drawGround(int i, int j){

    int wall_size = -20;

    //glColor3f(0.5,0.2,0.2);

    //below

    GLfloat material[4];
    material[0]=1.0;
    material[1]=1.0;
    material[2]=1.0;
    material[3]=1.0;
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,material);

    glEnable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D,groundTexture);
	
    glShadeModel(GL_SMOOTH);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0,0.0); glVertex3i((j+1)*WIDTH/COLUMNS,(ROWS-i)*HEIGHT/ROWS, wall_size);
    glTexCoord2f(1.0,0.0); glVertex3i((j*WIDTH/COLUMNS), ((ROWS-i)*HEIGHT/ROWS), wall_size);
    glTexCoord2f(1.0,1.0); glVertex3i((j*WIDTH/COLUMNS), (ROWS-1-i)*HEIGHT/ROWS, wall_size); 
    glTexCoord2f(0.0,1.0); glVertex3i((j+1)*WIDTH/COLUMNS,(ROWS-1-i)*HEIGHT/ROWS, wall_size); 
    
    
    
    

    glEnd();
    glDisable(GL_TEXTURE_2D);

}

void drawWall(int i, int j){

    int wall_size = -20;



    glPolygonMode(GL_FRONT,GL_FILL);
    glPolygonMode(GL_BACK,GL_LINE);

    glEnable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D,rogueSquadronTexture);
            //glColor3f(0.0,0.0,0.0);

    //top

    GLfloat material[4];
    material[0]=1.0;
    material[1]=1.0;
    material[2]=1.0;
    material[3]=1.0;
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,material);
    glBegin(GL_QUADS);

    glTexCoord2f(0.0,0.0); glVertex3i((j+1)*WIDTH/COLUMNS,(ROWS-i)*HEIGHT/ROWS, 0);
    glTexCoord2f(1.0,0.0); glVertex3i((j*WIDTH/COLUMNS), ((ROWS-i)*HEIGHT/ROWS), 0);
    glTexCoord2f(1.0,1.0); glVertex3i((j*WIDTH/COLUMNS), (ROWS-1-i)*HEIGHT/ROWS, 0); 
    glTexCoord2f(0.0,1.0); glVertex3i((j+1)*WIDTH/COLUMNS,(ROWS-1-i)*HEIGHT/ROWS, 0); 

    glEnd();
    


    //front
    glBindTexture(GL_TEXTURE_2D,wallTexture);
    glBegin(GL_QUADS);

    glTexCoord2f(0.0,0.0); glVertex3i((j+1)*WIDTH/COLUMNS,(ROWS-1-i)*HEIGHT/ROWS, 0);
    glTexCoord2f(1.0,0.0); glVertex3i((j*WIDTH/COLUMNS), (ROWS-1-i)*HEIGHT/ROWS, 0); 
    glTexCoord2f(1.0,1.0); glVertex3i((j*WIDTH/COLUMNS), (ROWS-1-i)*HEIGHT/ROWS, wall_size);
    glTexCoord2f(0.0,1.0); glVertex3i((j+1)*WIDTH/COLUMNS,(ROWS-1-i)*HEIGHT/ROWS, wall_size); 
    
    glDisable(GL_TEXTURE_2D);
    

    glEnd();

    //back
    

    glBegin(GL_QUADS);

    glTexCoord2f(0.0,0.0); glVertex3i((j+1)*WIDTH/COLUMNS,(ROWS-i)*HEIGHT/ROWS, wall_size);
    glTexCoord2f(1.0,0.0); glVertex3i((j*WIDTH/COLUMNS), ((ROWS-i)*HEIGHT/ROWS), wall_size);
    glTexCoord2f(1.0,1.0); glVertex3i((j*WIDTH/COLUMNS), ((ROWS-i)*HEIGHT/ROWS), 0);
    glTexCoord2f(0.0,1.0); glVertex3i((j+1)*WIDTH/COLUMNS,(ROWS-i)*HEIGHT/ROWS, 0);
    
    
    
    
    glEnd();

    

    //right
    glBegin(GL_QUADS);

    glTexCoord2f(0.0,0.0); glVertex3i((j+1)*WIDTH/COLUMNS,(ROWS-i)*HEIGHT/ROWS, 0);
    glTexCoord2f(1.0,0.0); glVertex3i((j+1)*WIDTH/COLUMNS,(ROWS-1-i)*HEIGHT/ROWS, 0);
    glTexCoord2f(1.0,1.0); glVertex3i((j+1)*WIDTH/COLUMNS,(ROWS-1-i)*HEIGHT/ROWS, wall_size); 
    glTexCoord2f(0.0,1.0); glVertex3i((j+1)*WIDTH/COLUMNS,(ROWS-i)*HEIGHT/ROWS, wall_size);

    
    glEnd();


    
    //left
    glBegin(GL_QUADS);

    glTexCoord2f(0.0,0.0); glVertex3i((j*WIDTH/COLUMNS), (ROWS-1-i)*HEIGHT/ROWS, 0); 
    glTexCoord2f(1.0,0.0); glVertex3i((j*WIDTH/COLUMNS), ((ROWS-i)*HEIGHT/ROWS), 0);
    glTexCoord2f(1.0,1.0); glVertex3i((j*WIDTH/COLUMNS), ((ROWS-i)*HEIGHT/ROWS), wall_size);
    glTexCoord2f(0.0,1.0); glVertex3i((j*WIDTH/COLUMNS), (ROWS-1-i)*HEIGHT/ROWS, wall_size);
     
    
    
    

    glEnd();
	glDisable(GL_TEXTURE_2D);

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

    glPushMatrix();
        glTranslated(middleX,middleY,-6);
        glutSolidSphere(10,50,50);
    glPopMatrix(); 

}


void drawFood(int i, int j){

    GLfloat material[4];
    material[0]=1; material[1]=1; material[2]=0; material[3]=1.0; 
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,material);
    int middleX = (((j+1)*WIDTH/COLUMNS)+(j*WIDTH/COLUMNS))/2; 
    int middleY = (((ROWS-i)*HEIGHT/ROWS) + ((ROWS-1-i)*HEIGHT/ROWS))/2;

    glPushMatrix();
        glTranslated(middleX,middleY,-6);
        glutSolidSphere(5,50,50);
    glPopMatrix(); 

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

    if (key=='i' && anglebeta<=(90-4))
        anglebeta=(anglebeta+3);
    else if (key=='k' && anglebeta>=(-90+4))
        anglebeta=anglebeta-3;
    else if (key=='j')
        anglealpha=(anglealpha+3)%360;
    else if (key=='l')
        anglealpha=(anglealpha-3+360)%360;


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
                pacman.set_direction(LEFT);
                //cout << "Pacman y" << map->pacmanY << endl;
                pacman.init_movement(map->pacmanX,map->pacmanY-1,100);
                map->setCorridor(map->pacmanX,map->pacmanY);
                map->setPacman(map->pacmanX,(map->pacmanY)-1, hungry);
                //map->pacmanY=map->pacmanY-1;
            }
        break;

        case UP: 
            if (!map->isWall(map->pacmanX-1,map->pacmanY) && pacman.state == QUIET)
            {
                if(map->isGhost(map->pacmanX-1,map->pacmanY)){
                    exit(0);
                }
                pacman.set_direction(UP);
                pacman.init_movement(map->pacmanX-1,map->pacmanY,100);
                map->setCorridor(map->pacmanX,map->pacmanY);
                map->setPacman(map->pacmanX-1,(map->pacmanY), hungry);
            }
        break;

        case RIGHT: 
            if (!map->isWall(map->pacmanX,map->pacmanY+1) && pacman.state == QUIET)
            {
                if(map->isGhost(map->pacmanX,map->pacmanY+1)){
                    exit(0);
                }
                pacman.set_direction(RIGHT);
                pacman.init_movement(map->pacmanX,map->pacmanY+1,100);
                map->setCorridor(map->pacmanX,map->pacmanY);
                map->setPacman(map->pacmanX,(map->pacmanY)+1, hungry);
            }
        break;

        case DOWN: 
            if (!map->isWall(map->pacmanX+1,map->pacmanY) && pacman.state == QUIET)
            {
                if(map->isGhost(map->pacmanX+1,map->pacmanY)){
                    exit(0);
                }
                pacman.set_direction(DOWN);
                pacman.init_movement(map->pacmanX+1,map->pacmanY,100);
                map->setCorridor(map->pacmanX,map->pacmanY);
                map->setPacman(map->pacmanX+1,(map->pacmanY), hungry);
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

void PositionObserver(float alpha,float beta,int radi)
{
  float x,y,z;
  float upx,upy,upz;
  float modul;

  x = (float)radi*cos(alpha*2*PI/360.0)*cos(beta*2*PI/360.0);
  y = (float)radi*sin(beta*2*PI/360.0);
  z = (float)radi*sin(alpha*2*PI/360.0)*cos(beta*2*PI/360.0);

  if (beta>0)
    {
      upx=-x;
      upz=-z;
      upy=(x*x+z*z)/y;
    }
  else if(beta==0)
    {
      upx=0;
      upy=1;
      upz=0;
    }
  else
    {
      upx=x;
      upz=z;
      upy=-(x*x+z*z)/y;
    }


  modul=sqrt(upx*upx+upy*upy+upz*upz);

  upx=upx/modul;
  upy=upy/modul;
  upz=upz/modul;

  gluLookAt(x,y,z,    0.0, 0.0, 0.0,     upx,upy,upz);
}


void ReadJPEG(char *filename,unsigned char **image,int *width, int *height)
{
  struct jpeg_decompress_struct cinfo;
  struct jpeg_error_mgr jerr;
  FILE * infile;
  unsigned char **buffer;
  int i,j;

  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_decompress(&cinfo);


  if ((infile = fopen(filename, "rb")) == NULL) {
    printf("Unable to open file %s\n",filename);
    exit(1);
  }

  jpeg_stdio_src(&cinfo, infile);
  jpeg_read_header(&cinfo, TRUE);
  jpeg_calc_output_dimensions(&cinfo);
  jpeg_start_decompress(&cinfo);

  *width = cinfo.output_width;
  *height  = cinfo.output_height;


  *image=(unsigned char*)malloc(cinfo.output_width*cinfo.output_height*cinfo.output_components);

  buffer=(unsigned char **)malloc(1*sizeof(unsigned char **));
  buffer[0]=(unsigned char *)malloc(cinfo.output_width*cinfo.output_components);


  i=0;
  while (cinfo.output_scanline < cinfo.output_height) {
    jpeg_read_scanlines(&cinfo, buffer, 1);

    for(j=0;j<cinfo.output_width*cinfo.output_components;j++)
      {
	(*image)[i]=buffer[0][j];
	i++;
      }   

    }

  free(buffer);
  jpeg_finish_decompress(&cinfo);
} 



/*--------------------------------------------------------*/
/*--------------------------------------------------------*/

GLuint LoadTexture(char *filename,int dim)
{
  unsigned char *buffer;
  unsigned char *buffer2;
  int width,height;
  long i,j;
  long k,h;

  ReadJPEG(filename,&buffer,&width,&height);

  buffer2=(unsigned char*)malloc(dim*dim*3);

  //-- The texture pattern is subsampled so that its dimensions become dim x dim --
  for(i=0;i<dim;i++)
    for(j=0;j<dim;j++)
      {
	k=i*height/dim;
	h=j*width/dim;
	
	buffer2[3*(i*dim+j)]=buffer[3*(k*width +h)];
	buffer2[3*(i*dim+j)+1]=buffer[3*(k*width +h)+1];
	buffer2[3*(i*dim+j)+2]=buffer[3*(k*width +h)+2];

      }

  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
  glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,dim,dim,0,GL_RGB,GL_UNSIGNED_BYTE,buffer2);

  free(buffer);
  free(buffer2);

return texture;
}







