#include <GLUT/glut.h>
#include <math.h>  

#define COLUMNS 35
#define ROWS 35
#define WIDTH 1000
#define HEIGHT 1000
#define PI 3.14159265

#define MOVE 1
#define QUIET 2

class ParticleGhost {
    public:
  float x,y;   //-- Current position
  float vx,vy; //-- Velocity vector
  int state;
  int direction;

  long time_remaining;



  ParticleGhost();
  void set_position(int x,int y);
  void init_movement(int destination_x,int destination_y,int duration);
  void integrate(long t);
  void draw();

  void move();

  void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius);

};