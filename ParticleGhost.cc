#include "ParticleGhost.h"


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
}

void ParticleGhost::move(int DIFFICULTY, int ghostIndex,string map_string){
  
	std::cout << DIFFICULTY << std::endl;  
	std::cout << ghostIndex << std::endl;  
	std::cout << map_string << std::endl;  

	PyObject *pName, *pModule, *pDict, *pFunc;
    PyObject *pArgs, *pValue;
    int i;

    setenv("PYTHONPATH", "./IA", 0);
    Py_Initialize();
    pName = PyString_FromString("IAController");
    /* Error checking of pName left out */

    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, "getMovement");
        /* pFunc is a new reference */

        if (pFunc && PyCallable_Check(pFunc)) {
        	pArgs = PyTuple_New(3);
            /*
            for (i = 0; i < argc - 3; ++i) {
                pValue = PyInt_FromLong(atoi(argv[i + 3]));
                if (!pValue) {
                    Py_DECREF(pArgs);
                    Py_DECREF(pModule);
                    fprintf(stderr, "Cannot convert argument\n");
                    return 1;
                }
                // pValue reference stolen here:
                PyTuple_SetItem(pArgs, 0, pValue);
        	}
        	*/
        	pValue = Py_BuildValue("s", map_string.c_str());
        	PyTuple_SetItem(pArgs, 0, pValue);
        	pValue = Py_BuildValue("i", ghostIndex); 
        	PyTuple_SetItem(pArgs, 1, pValue);
        	pValue = Py_BuildValue("i", DIFFICULTY); 
        	PyTuple_SetItem(pArgs, 2, pValue);
            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);
            if (pValue != NULL) {
                printf("Result of call: %ld\n", PyInt_AsLong(pValue));
                Py_DECREF(pValue);
            }
            else {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                fprintf(stderr,"Call failed\n");
                exit(1);
            }
        }
        else {
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function \"%s\"\n", "getMovement");
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }
    else {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"%s\"\n", "IAController");
        exit(1);
    }
    Py_Finalize();

 int r = PyInt_AsLong(pValue);

  direction = r;
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

