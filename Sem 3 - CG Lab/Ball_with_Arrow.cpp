#include<iostream>
#include<stdlib.h>
#ifdef __APPLE__
#include<openGL/openGL.h>
#include<GLUT/glut.h>
#else
#include<GL/glut.h>
#endif

using namespace std;

float ballX = -0.8f;
float ballY = -0.3f;
float ballZ = -1.2f;

static int flag=1;
void drawBall(void) {
        glColor3f(1,1,1); //set ball colour
        glTranslatef(ballX,ballY,ballZ); //moving it toward the screen a bit on creation
        glutSolidSphere (0.05, 30, 30); //create ball.

}
void keyPress(int key, int x, int y)
{
      if(key==GLUT_KEY_RIGHT)
        ballX += 0.05f;
    if(key==GLUT_KEY_LEFT)
        ballX  -= 0.05f;
if(key==GLUT_KEY_UP)
        ballY += 0.05f;
    if(key==GLUT_KEY_DOWN)
        ballY  -= 0.05f;
    glutPostRedisplay();
}
//Called when the window is resized
void handleResize(int w, int h) {
    //Tell OpenGL how to convert from coordinates to pixel values
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective
    //Set the camera perspective
    glLoadIdentity(); //Reset the camera
    gluPerspective(45.0,                  //The camera angle
                   (double)w / (double)h, //The width-to-height ratio
                   1.0,                   //The near z clipping coordinate
                   200.0);                //The far z clipping coordinate
}

void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  //  glClearColor(bgColR,bgColG,bgColB,0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //drawing the SUN
    glPushMatrix();
        drawBall();
    glPopMatrix();
    //drawing the Mount Avarest
    glPushMatrix();
    glPopMatrix();
    //drawing the Clouds
    glPushMatrix();
    glPopMatrix();
    glutSwapBuffers();
}

int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(400,400);
    glutCreateWindow("Sun");
    glutDisplayFunc(drawScene);
    glutFullScreen();
    glutSpecialFunc(keyPress);
    glutReshapeFunc(handleResize);
    //glutTimerFunc(25, update, 0);
    glutMainLoop();
    return(0);
}
