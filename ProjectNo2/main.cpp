//
//  main.cpp
//  ProjectNo2 for Computer Graphics Class
//
//  Created by Damian Lasecki on 29/12/2019.
//  Copyright © 2019 Damian Lasecki. All rights reserved.
//

#include <vector>
#include <GLUT/GLUT.h>
#include <math.h>

float odleglosc = 30.0;
float katX = 0.00, katY = 10.00;

#define PI_CONST 3.14159265358979323846
float katynaradiany(float alfa) {
    return alfa * (PI_CONST / 180);
}

void drawCone(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat h){
    glPushMatrix();
    glTranslated(x,y,z);
    glRotatef(-90.0, 0.0, 0.0, 0.0);
    glutSolidCone(r,h,20,10);
    glPopMatrix();
}


void drawTorus(GLfloat x, GLfloat y, GLfloat z, GLfloat i, GLfloat o){
    glPushMatrix();
    glTranslated(x,y,z);
    glRotatef(-90.0, 0.0, 0.0, 0.0);
    glutSolidTorus(i,o,40,40);
    glPopMatrix();
}

void colorRedMate(){
    GLfloat mat_ambient[] =  { 0.3, 0.0, 0.0, 1.0 };
    GLfloat mat_diffuse[] =  { 0.5, 0.1, 0.1, 1.0 };
    GLfloat mat_specular[] = { 0.1, 0.0, 0.0, 0.0 };
    GLfloat mat_shiness[] =  { 0.0 };
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shiness);
}

void colorYellowShine() {
    GLfloat shine_ambient[] =  { 0.75, 0.75, 0.0 };
    GLfloat shine_diffuse[] =  { 0.75, 0.75, 0.0 };
    GLfloat shine_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat shine_shiness[] =  { 0.8f * 128 };
    glMaterialfv(GL_FRONT, GL_SPECULAR, shine_specular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, shine_diffuse);
    glMaterialfv(GL_FRONT, GL_AMBIENT, shine_ambient);
    glMaterialfv(GL_FRONT, GL_SHININESS, shine_shiness);
}

void light2(){
    GLfloat light_position[] = { 50.0, 0.0, 0.0, 1};
    GLfloat light_color[] = { 0.3, 0.1, 0.1 };
    GLint direction[] = { 1, 0, 1 };
    glLightfv(GL_LIGHT2, GL_POSITION, light_position);
    glLightfv(GL_LIGHT2, GL_AMBIENT, light_color);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light_color);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light_color);
    glLightiv(GL_LIGHT2, GL_SPOT_DIRECTION, direction);
}

void light1(){
    GLfloat lightColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_position[] = { 33.0, 33.0, 33.0, 1 };
    GLfloat cutoff[] = { 180 };
    
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, cutoff);
}

void mainReflector() {
    GLfloat lightpos[] = { 0.0, 10.0, 30.0, 1 };
    GLint direction[] = { 0,0,5 };
  
    GLfloat light1_diffuse[] =  { 0.5, 0.1, 0.1, 1.0 };
    GLint light1_spot_exponent = 100;
    GLint light1_spot_cutoff = 180;
    
    glLightfv(GL_LIGHT1, GL_POSITION, lightpos);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightiv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, light1_spot_exponent);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, light1_spot_cutoff);
}

void setCamera() {
    float camX = odleglosc * sin(katynaradiany(katX)) * cos(katynaradiany(katY));
    float camY = odleglosc * sin((katynaradiany(katY)));
    float camZ = odleglosc * cos((katynaradiany(katX))) * cos((katynaradiany(katY)));
    float upX = odleglosc * sin(katynaradiany(katX)) * cos(katynaradiany(katY + 90));
    float upY = odleglosc * sin(katynaradiany(katY + 90));
    float upZ = odleglosc * cos((katynaradiany(katX))) * cos(katynaradiany(katY + 90));
    gluLookAt(camX, camY, camZ, 0.0, 0.0, 0.0, upX, upY, upZ);
}


void display() {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glEnable(GL_LIGHTING);
    gluPerspective(80.0, 1.0, 0.1, 50.0);
    setCamera();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor (0.0, 0.0, 0.0, 0.0);
    
    light1();
    light2();
    mainReflector();
    
    colorRedMate();
    drawCone(0, 0, 0, 8, 20);
    
    colorYellowShine();
    drawTorus(0, 10, 0, 4, 10);
    
    glFlush();
    
}

void klaw0(unsigned char key, int x, int y) {
    if (key == '1'){
       glEnable(GL_LIGHT1);
    } if (key == '2'){
        glDisable(GL_LIGHT1);
    } if (key == '3'){
        glEnable(GL_LIGHT0);
    } if (key == '4'){
        glDisable(GL_LIGHT0);
    } if (key == '5'){
        glEnable(GL_LIGHT2);
    } if (key == '6'){
        glDisable(GL_LIGHT2);
    }
    if (key == '+') odleglosc -= 0.5;
    else if (key == '-') odleglosc += 0.5;
    
    display();
}

void setTransformPosition(int key, int x, int y) {
    if (key == GLUT_KEY_UP) katY = (float)((360 + (int)katY + 5) % 360);
    else if (key == GLUT_KEY_DOWN) katY = (float)((360 + (int)katY - 5) % 360);
    else if (key == GLUT_KEY_LEFT) katX = (float)((360 + (int)katX + 5) % 360);
    else if (key == GLUT_KEY_RIGHT) katX = (float)((360 + (int)katX - 5) % 360);
    display();
}

void setDistancePosition(unsigned char key, int x, int y) {
    if (key == '-') {
        odleglosc += 0.1;
    } else if (key == '+') {
        odleglosc -= 0.1;
    }
    display();
}


void initGL() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    
}

void przerysuj(int s, int w) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, s, w);
    gluOrtho2D(0, s, w, 0);
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Damian Lasecki");
    glutDisplayFunc(display);
    glutKeyboardFunc(klaw0);
    glutSpecialFunc(setTransformPosition);
    
    glutReshapeFunc(przerysuj);
    initGL();
    glutMainLoop();
    
    return 0;
}
