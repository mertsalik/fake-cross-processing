#include <iostream>
#include <windows.h>
#include <GL\glew.h>
#include <GL\GLU.h>
#include <GL\glut.h>
#include "Scene.h"
#include "TextureEffect.h"
#include <glm.hpp>
#include <ext.hpp>

#define WINDOW_TITLE_PREFIX "Mert Salýk"
void IdleFunction(void);
void ResizeFunction(int Width, int Height);
void setupScene();
unsigned FrameCount = 0;
int CurrentWidth = 800,
CurrentHeight = 600;
Light* light;
Camera *camera;
Scene* scene;

static void Draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    scene->draw();
    
    glutSwapBuffers();
}

void ResizeFunction(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;
	glViewport(0, 0, CurrentWidth, CurrentHeight);
    scene->resize();
}

static void timerCallback (int value)
{
    if (0 != value) {
		char* TempString = (char*)
        malloc(512 + strlen(WINDOW_TITLE_PREFIX));
        
		sprintf(
                TempString,
                "%s: %d Frames Per Second @ %d x %d",
                WINDOW_TITLE_PREFIX,
                FrameCount * 4,
                CurrentWidth,
                CurrentHeight
                );
        
		glutSetWindowTitle(TempString);
		free(TempString);
	}
	FrameCount = 0;
	glutTimerFunc(250, timerCallback, 1);
}

void IdleFunction(void)
{
	glutPostRedisplay();
}

void setupScene(){
    scene = new Scene();
    camera = new Camera();
    camera->translate(0.f, 0.f, 30.f);
    scene->setCamera(camera);
    
    scene->addEffect(new TextureEffect(CurrentWidth,CurrentHeight));
    
    light = new Light();
    light->translate(0, 400.f, 400.f);
    scene->addLight(light);
}

int main (int argc, char ** argv)
{
    GLenum type;
	glutInit(&argc, argv);
	glutInitWindowSize(CurrentWidth,CurrentHeight);
	type = GLUT_RGB;
	type |= GLUT_DOUBLE;
	type |= GLUT_DEPTH;
    type |= GLUT_MULTISAMPLE;
	glutInitDisplayMode(type);
	glutCreateWindow("");
#ifdef _WIN32
    GLenum err = glewInit();
	if (GLEW_OK != err)
	{
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
#endif
    const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
    
    printf("GLSL Version: %s\n",glslVersion);
    
    const GLubyte* glVersion = glGetString(GL_VERSION);
    
    printf("GL Version: %s\n",glVersion);
    
    glClearColor(0.0, 1.0, 0.0, 1.0);
    // Z-Buffer i aciyoruz
    glEnable(GL_DEPTH_TEST);
    
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE); 
    
       
    setupScene();
    
    timerCallback(0);
    glutReshapeFunc(ResizeFunction);
    glutDisplayFunc(Draw);
    glutIdleFunc(IdleFunction);
    glutMainLoop();
    
    return 0;
}


