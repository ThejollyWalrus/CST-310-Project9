// Mason Hamilton
// CST-310-1:55
// 4/13/20
// Professor Citro
// Project 8 Demo Scene

//All the libaries included
#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include <string>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#define PI 3.1415927
//To use namespace
using namespace std;

GLfloat WHITE[] = {1, 1, 1};
GLfloat RED[] = {1, 0, 0};
GLfloat BLACK[] = {0, 0, 0};
GLfloat GREEN[] = {0, 1, .5};
GLfloat MAGENTA[] = {1, 0, 1};
GLfloat STICK[] = {.8,.7, 1};
float camPitch = 0, yamCam = 0, CamRoll1 = 0, CamRoll2 = 1, angleRoll = 0; //variables for camera angles
float camHeight = 2, camPostition = 2.5, camDepth = -12; //variables to control the camera location
float camX = 0, camY = 0; //variables for camera angles


//checker board class
class Checkerboard {
  int displayListId;
  int width;
  int depth;
public:
  Checkerboard(int width, int depth): width(width), depth(depth) {}
  double centerx() {return width / 2;}
  double centerz() {return depth / 2;}
  void create() {
    displayListId = glGenLists(1);
    glNewList(displayListId, GL_COMPILE);
    GLfloat lightPosition[] = {4, 3, 7, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glBegin(GL_QUADS);
    glNormal3d(0, 1, 0);
    for (int x = 0; x < width - 1; x++) {
      for (int z = 0; z < depth - 1; z++) {
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,
                     (x + z) % 2 == 0 ? BLACK : WHITE);
        glVertex3d(x, 0, z);
        glVertex3d(x+1, 0, z);
        glVertex3d(x+1, 0, z+1);
        glVertex3d(x, 0, z+1);
      }
    }
    glEnd();
    glEndList();
  }
  void draw() {
    glCallList(displayListId);
  }
};

// Global variables: a camera, a checkerboard and some balls.
Checkerboard checkerboard(9, 9);

//sphere calls to create 
void sphere(){
  glPushMatrix();
  glColor3d(.2,.09,.9);
 glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,MAGENTA);
  glutSolidSphere(.5, 12, 12);
  glEnd();
  glPopMatrix();


}

void draw_cylinder(GLfloat radius,GLfloat height,GLubyte R,GLubyte G,GLubyte B)
{
    GLfloat x              = 0.0;
    GLfloat y              = 0.0;
    GLfloat angle          = 0.0;
    GLfloat angle_stepsize = 0.1;
    //glTranslated(25.5,1,0);

    /** Draw the tube */
    glColor3ub(R-40,G-40,B-40);
    glColor3f(1 ,1 ,0);
 glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,STICK);
    glBegin(GL_QUAD_STRIP);
    angle = 0.0;
        while( angle < 2*PI ) {
            x = radius * cos(angle);
            y = radius * sin(angle);
            glVertex3f(x, y , height);
            glVertex3f(x, y , 0.0);
            angle = angle + angle_stepsize;
        }
        glVertex3f(radius, 0.0, height);
        glVertex3f(radius, 0.0, 0.0);
    glEnd();

    /** Draw the circle on top of cylinder */
    glColor3ub(R,G,B);
    glBegin(GL_POLYGON);
    angle = 0.0;
        while( angle < 2*PI ) {
            x = radius * cos(angle);
            y = radius * sin(angle);
            glVertex3f(x, y , height);
            angle = angle + angle_stepsize;
        }
        glVertex3f(radius, 0.0, height);
    glEnd();
}
//cube class given to us 
namespace Cuber {

const int NUM_VERTICES = 8;
const int NUM_FACES = 6;

GLint vertices[NUM_VERTICES][3] = {
  {0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1},
  {1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1}};

GLint faces[NUM_FACES][4] = {
  {1, 5, 7, 3}, {5, 4, 6, 7}, {4, 0, 2, 6},
  {3, 7, 6, 2}, {0, 1, 3, 2}, {0, 4, 5, 1}};

GLfloat vertexColors[NUM_VERTICES][3] = {
  {1.0, 0.02, 0.91}, {8.0, 1.0, 1.0}, {0.0, 0.3, 0.5}, {0.0, 1.0, 1.0},
  {0.0, 0.8, 0.9}, {1.0, 2.0, 1.0}, {1.0, 0.0, 1.0}, {1.0, 1.0, 1.0}};

GLfloat vertexColors2[NUM_VERTICES][3] = {
  {0.0, 0.0, 0.5}, {0.0, 0.0, 1.0}, {0.0, 1.0, 1.0}, {1.0, 1.0, 1.0},
  {1.0, 0.0, 1.0}, {1.0, 0.0, 1.0}, {1.0, 1.0, 0.0}, {0.0, 1.0, 1.0}};


void draw7() {
  glBegin(GL_QUADS);
 glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,GREEN);

  for (int i = 0; i < NUM_FACES; i++) {
    for (int j = 0; j < 4; j++) {
      glColor3fv((GLfloat*)&vertexColors[faces[i][j]]);
      glVertex3iv((GLint*)&vertices[faces[i][j]]);
    }
  }
 	

  glEnd();

}
}

//fucntion to display our scene
void display() {
  //cleares all the previous buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //loads idenity matrix
  glLoadIdentity();
  //calls our camera look funtion
  gluLookAt(camPostition, camHeight, camDepth, camPostition + camX, camHeight + camY, 3.5, CamRoll1, 1.0 + CamRoll2, 0.0);
  glTranslatef(0, -1, 0);
  //calls our bottom checker board
  checkerboard.draw();
  glTranslatef(3, 1, 3);
  //calls the sphere class
  sphere();
  glTranslatef(1, 0,0);
  //calls cuber class
  Cuber::draw7();
  glRotatef(90, 1, 0, 0);
  glTranslatef(0, 4, 0);
//draws our cylinder class
  draw_cylinder(0.3, 2.0, 255, 160, 100);
  glFlush();
  glutSwapBuffers();
}



//fucntions start all of our gl libraires
//also starts all the lighting for out scene
void init() {
  glEnable(GL_DEPTH_TEST);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, WHITE);
  glLightfv(GL_LIGHT0, GL_SPECULAR, WHITE);
  glMaterialfv(GL_FRONT, GL_SPECULAR, WHITE);
  glMaterialf(GL_FRONT, GL_SHININESS, 30);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  checkerboard.create();
}

//reshape function called to adjust the camera and view
void reshape(GLint w, GLint h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(40.0, GLfloat(w) / GLfloat(h), 1.0, 150.0);
  glMatrixMode(GL_MODELVIEW);
}

void special(int key, int, int) {
  //sets a variable to handle shift, alt, and ctrl keys
    int adjust;
    
   
    switch (key) {
        
        //checks if the input is the left key
        case GLUT_KEY_LEFT: {
            //sets adjust to additional key
            adjust= glutGetModifiers();
            //if input is 'ctrl'
            if (adjust== GLUT_ACTIVE_CTRL) {
                //decreases the yaw
                yamCam -= 2 * PI / 180;
                camX = tan(yamCam);
            }
     
            else {
                //increases the camera to the left
                camPostition += 1;
            }
            break;
        }
        
        
        case GLUT_KEY_RIGHT: {
            //Sets adjust to additional key
            adjust= glutGetModifiers();
            //Checks if adjustis ctrl
            if (adjust== GLUT_ACTIVE_CTRL) {
                //increases the yaw
                yamCam += 2 * PI / 180;
                camX = tan(yamCam);
            }
            
            else {
                //decreases the camera to the right
                camPostition -= 1; 
            }
            break;
        }
        
        //checks if the input is the up key
        case GLUT_KEY_UP: {
            //Sets adjust to additonal key
            adjust= glutGetModifiers();
            //if input is 'shift'
            if (adjust== GLUT_ACTIVE_SHIFT) {
                //Zooms in
                camDepth += 1;
            }
            //Checks if adjustis ctrl
            else if (adjust== GLUT_ACTIVE_CTRL) {
                //decreases pitch
                camPitch -= 2 * PI / 180;
                camY = tan(camPitch);
            }
            
            else {
                //increases the camera height
                camHeight += 1;
            }
            break;
        }
        
        //checks if the input is the down key
        case GLUT_KEY_DOWN: {
            //sets adjust to special button
            adjust= glutGetModifiers();
            //if the input has 'shift'
            if (adjust== GLUT_ACTIVE_SHIFT) {
                //decreaes camera depth
                camDepth -= 1;
            }
            //if the input has 'ctrl' clicked
            else if (adjust== GLUT_ACTIVE_CTRL) {
                //increases pitch
                camPitch += 2 * PI / 180;
                camY = tan(camPitch);
            }
            else {
                //decreases the camera height
                camHeight -= 1;
            }
            break;
        }
    }
    //calls this funciton to redisplay
    glutPostRedisplay();
}

void onKeyboard(unsigned char key, int, int) {
    
    //switch case 
    switch (key) {
        
        //case input '<'
        case '<': {
            //increases roll
            angleRoll += 2 * PI / 180;
            CamRoll1 = 2 * sin(angleRoll);
            CamRoll2 = 2 * cos(angleRoll);
            break;
        }
        
        //case input '<'
        case '>': {
            //decreases roll
            angleRoll -= 2 * PI / 180;
            CamRoll1 = 2 * sin(angleRoll);
            CamRoll2 = 2 * cos(angleRoll);
            break;
        }
        
        //case input esc
        case 27: {
            //exits program
            exit(0);
        }
        
        //case input 'r'
        case 'r': {
            //resest the camera to the starting positon
            camHeight = 2, camPostition = 2.5, camDepth = -12;
            camX = 0, camY = 0;
            camPitch = 0, yamCam = 0, CamRoll1 = 0, CamRoll2 = 1, angleRoll = 0;
        }
    }
    //calls the function to redisplay
    glutPostRedisplay();
}

//Main function that calls all above functions
//then loads into the termnial
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(800, 800);
  glutCreateWindow("Project 9");
  glutDisplayFunc(display); 
  glutReshapeFunc(reshape);
  glutSpecialFunc(special);
  glutKeyboardFunc(onKeyboard);
  glEnable(GL_DEPTH_TEST);
  init();
  glutMainLoop();
  return 1;
}
  
