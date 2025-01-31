#include <stdlib.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "../utils/figura.hpp"
#include "../utils/ponto.hpp"
#include "../utils/groups.hpp"
#include "../tinyxml/tinyxml.h"
#include "leitor.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <list>
#include <string>
#include <sstream>

using namespace std;

float alpha = M_PI / 4;
float beta1 = M_PI / 4;
float radius = 5.0f;
float cameraPosX = 5.0f;
float cameraPosY = 5.0f;
float cameraPosZ = 5.0f;
float lookAtX = 0.0f;
float lookAtY = 0.0f;
float lookAtZ = 0.0f;
float upX = 0.0f;
float upY = 0.0f;
float upZ = 0.0f;
float fov = 60.0f;
float near = 1.0f;
float far = 1000.0f;
int mode = GL_LINE;
list<Figura> figuras;

Leitor leitor = nullptr;

void changeSize(int w, int h)
{

    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if (h == 0)
        h = 1;

    // compute window's aspect ratio
    float ratio = w * 1.0 / h;

    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load Identity Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set perspective
    gluPerspective(fov, ratio, near, far);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}

void drawFiguras(const list<Figura>& lista) {
    glColor3f(1.0f, 1.0f, 1.0f);
    
    for (const auto& figura : lista) {
        list<Ponto> pontos = getPontos(figura);
        glBegin(GL_TRIANGLES);
        for (const auto& ponto : pontos) {
            //cout << "(" << getX(ponto) << "," << getY(ponto) << "," << getZ(ponto) << ")";
            glVertex3f(getX(ponto), getY(ponto), getZ(ponto));
        }
        glEnd();
    }
}

void renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(radius * cos(beta1) * sin(alpha), radius * sin(beta1), radius * cos(beta1) * cos(alpha), lookAtX, lookAtY, lookAtZ, upX, upY, upZ);

    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-100.0f, 0.0f, 0.0f);
    glVertex3f(100.0f, 0.0f, 0.0f);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -100.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -100.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, mode);
    drawFiguras(figuras);

    glutSwapBuffers();
}

void processSpecialKeys(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_UP:
            beta1 -= 1.0f;
            break;
            
        case GLUT_KEY_DOWN:
            beta1 += 1.0f;
            break;

        case GLUT_KEY_LEFT:
            alpha -= 1.0f;
            break;

        case GLUT_KEY_RIGHT:
            alpha += 1.0f;
            break;

        default:
            break;
    }

    glutPostRedisplay();
}

void processKeys(unsigned char key, int x, int y)
{
    switch (key) 
    {
        case 'w':
            beta1 -= 1.0f; // Move the camera forward
            break;

        case 's':
            beta1 += 1.0f; // Move the camera backward
            break;

        case 'a':
            alpha -= 1.0f; // Move the camera left (along the x-axis)
            break;

        case 'd':
            alpha += 1.0f; // Move the camera right (along the x-axis)
            break;

        case 'f':
            mode = GL_FILL;
            break;
            
        case 'l':
            mode = GL_LINE;
            break;

        case 'p':
            mode = GL_POINT;
            break;
        
        case '+':
            radius -= 0.1f; // Zoom in
            break;

        case '-':
            radius += 0.1f; // Zoom out
            break;
    }

    // Request redraw
    glutPostRedisplay();
}


int main(int argc, char **argv)
{
    leitor = extrair_XML(argv[1]);
    Group listafiguras = getNode(leitor);
    
    if(listafiguras) figuras = criarListaFiguras(listafiguras);

    cameraPosX = getXPosCam(leitor);
    cameraPosY = getYPosCam(leitor);
    cameraPosZ = getZPosCam(leitor);
    radius = sqrt(cameraPosX * cameraPosX + cameraPosY * cameraPosY + cameraPosZ * cameraPosZ);
    lookAtX = getXLookAt(leitor);
    lookAtY = getYLookAt(leitor);
    lookAtZ = getZLookAt(leitor);
    upX = getXUp(leitor);
    upY = getYUp(leitor);
    upZ = getZUp(leitor);
    alpha = acos(cameraPosZ / sqrt(cameraPosX * cameraPosX + cameraPosZ * cameraPosZ));
    beta1 = asin(cameraPosY / radius);
    fov = getFov(leitor);
    near = getNear(leitor);
    far = getFar(leitor);

    // init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Fase 2 - Transformacoes Geometricas");

    // Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

    // Callback registration for keyboard processing
    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);

    //  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // enter GLUT's main cycle
    glutMainLoop();

    figuras.clear();
    deleteLeitor(leitor);

    return 1;
}