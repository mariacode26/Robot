#define _CRT_SECURE_NO_WARNINGS
#define PI 3.141592654

#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include "RgbImage.h"
#include <cmath>


using namespace std;

char* filenameTexMetal1 = "metalTexture1.bmp";

GLuint _textureIdMetal1;
GLuint _textureIdSphere;
GLuint _textureIdCylinder;
GLUquadric *quadSphere;
GLUquadric *quadCylinder;

bool textureOn = true;

float diameterCylinder = 0.2;
float diameterCylinder_x = 0.6;
float diameterSphere = 0.4;
float sizeArm = 4.5;
float sizeArm_x = 5.5;
float sizeForearm = 2.0;
//float sizeHand = 2.0;
//float sizeClampPart = 1.0;
float diameterBase = 2.0;
float heightBase = 0.5;

float sizeHand = 2.0;
float sizeClampPart = 1.0;
float angleHand = 10.0;
float angleHand_L = 10.0;

float eyeDistance = 20.0;
float eyeX;
float eyeY;
float eyeZ;
float viewAngleX = 0.0;
float viewAngleZ = 15.0;

float angleArm = 90.0;
float angleArm_L = 90.0;
float angleForearm = 120.0;
float angleForearm_L = 120.0;
//float angleHand = 0.0;
float angleClampZ = 0.0;
float angleClampY = 0.0;
float angleHead = 0.0;
float angleH = 0.0;
float eY = 0.0;

GLfloat luz_p[4] = { 0.0f, 25.0f, 0.0f, 0.0f };
GLfloat luz[4] = { 0.25, 0.25, 0.25, 0.5 };

void iluminacao(void)
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glShadeModel(GL_SMOOTH);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luz);

	glLightfv(GL_LIGHT0, GL_AMBIENT, luz);
	glLightfv(GL_LIGHT0, GL_POSITION, luz_p);

	glEnable(GL_COLOR_MATERIAL);
}

//makes the image into a texture, and returns the id of the texture
GLuint loadTexture(char *filename) {
	GLuint textureId;

	RgbImage theTexMap(filename); //Image with texture

	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId);	//Tell OpenGL which texture to edit
												//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,	//Always GL_TEXTURE_2D
		0,						//0 for now
		GL_RGB,					//Format OpenGL uses for image
		theTexMap.GetNumCols(),	//Width
		theTexMap.GetNumRows(),	//Height
		0,						//The border of the image
		GL_RGB,					//GL_RGB, because pixels are stored in RGB format
		GL_UNSIGNED_BYTE,		//GL_UNSIGNED_BYTE, because pixels are stored as unsigned numbers
		theTexMap.ImageData());	//The actual pixel data
	return textureId; //Returns the id of the texture
}

void initRendering(void) {
	quadSphere = gluNewQuadric();
	quadCylinder = gluNewQuadric();
	_textureIdMetal1 = loadTexture(filenameTexMetal1);
	_textureIdCylinder = _textureIdMetal1;
	_textureIdSphere = _textureIdMetal1;
}
void Timer(int value){


    angleForearm_L-=1;
    angleHand_L=-120;
   if (angleForearm_L < 90)
        angleForearm_L=120;
        angleForearm_L-=3;

    angleHand=120;
    angleForearm+=1;
   if (angleForearm > 100)
        angleForearm=80;


    glutPostRedisplay();
    glutTimerFunc(100, Timer, 0);
}
void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
	case 27: //Escape key
		exit(0);
	case 'w': //Increase view angle z axis
		if (viewAngleZ < 180) viewAngleZ += 3;
		glutPostRedisplay();
		break;
	case 'z': //Decrease view angle z axis
		if (viewAngleZ > 0) viewAngleZ -= 3;
		glutPostRedisplay();
		break;
	case 'a': //Decrease view angle x axis
		if (viewAngleX > 0) viewAngleX -= 3;
		glutPostRedisplay();
		break;
	case 's': //Increase view angle x axis
		if (viewAngleX < 180) viewAngleX += 3;
		glutPostRedisplay();
		break;
	case 't': //Use texture or not
		textureOn = !textureOn;
		glutPostRedisplay();
		break;
	case '1': //Increase arm angle
		angleArm += 3;
		if (angleArm >= 360) angleArm = 0;
		glutPostRedisplay();
		break;
	case '2': //Decrease arm angle
		angleArm -= 3;
		if (angleArm <= 0) angleArm = 360;
		glutPostRedisplay();
		break;
	case '3': //Abaixa o braço
		if (angleForearm < 120) angleForearm += 3;
		glutPostRedisplay();
		break;
	case '4': //Levanta o braço
		if (angleForearm > -90) angleForearm -= 3;
		glutPostRedisplay();
		break;
    case '5': //Decrease hand angle
		if (angleHand > -90) angleHand -= 3;
		glutPostRedisplay();
		break;
	case '6': //Increase hand angle
		if (angleHand < 90) angleHand += 3;
		glutPostRedisplay();
		break;
    case 'c': //abre o braço esquerdo
		angleArm_L += 3;
		if (angleArm_L >= 360) angleArm_L = 0;
		glutPostRedisplay();
		break;
	case 'v': //fecha o braço esquerdo
		angleArm_L -= 3;
		if (angleArm_L <= 0) angleArm_L = 360;
		glutPostRedisplay();
		break;
	case 'b': //Abaixa o braço esquerdo
		if (angleForearm_L < 120) angleForearm_L += 3;
		glutPostRedisplay();
		break;
	case 'n': //Levanta o braço esquerdo
		if (angleForearm_L > -90) angleForearm_L -= 3;
		glutPostRedisplay();
		break;
    case 'l': //move o antebraço para baixo
		if (angleHand_L > -90) angleHand_L -= 3;
		glutPostRedisplay();
		break;
	case 'm': //move o antebraço para cima
		if (angleHand_L < 90) angleHand_L += 3;
		glutPostRedisplay();
		break;
	case '7': //Increase clamp angle y axis
		if (angleClampY < 60) angleClampY += 3;
		glutPostRedisplay();
		break;
	case '8': //Decrease clamp angle y axis
		if (angleClampY > 0) angleClampY -= 3;
		glutPostRedisplay();
		break;
    case '9': //Move cabeca pra esquerda
		if (angleHead < 70)
            angleH=-0.2;
		glutPostRedisplay();
		break;
      case 'h': //Move cabeca pra direita
		if (angleHead < 70)
            angleH=0.2;
		glutPostRedisplay();
		break;
       case 'j': //Move cabeca pra posicao inicial
		if (angleHead < 70)
            angleH=0.0;
		glutPostRedisplay();
		break;
		 case 'd': //Danca do gira braco
            if (angleForearm_L > -90)
                //angleHand_L -= 3;
                glutTimerFunc(100, Timer, 0);
            glutPostRedisplay();
		break;
	}
}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (float)w / (float)h, 1.0, 50.0);
}

void drawCylinder(float diameter, float lenght) {
	if (textureOn) {
		glBindTexture(GL_TEXTURE_2D, _textureIdCylinder);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		gluQuadricTexture(quadCylinder, 1);
	}
	else
		gluQuadricTexture(quadCylinder, 0);
	gluCylinder(quadCylinder, diameter, diameter, lenght, 40.0, lenght*30.0);
}
void drawCylinder_l(float diameter, float lenght) {
	if (textureOn) {
		glBindTexture(GL_TEXTURE_2D, _textureIdCylinder);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		gluQuadricTexture(quadCylinder, 1);
	}
	else
		gluQuadricTexture(quadCylinder, 0);
	gluCylinder(quadCylinder, diameter, diameter, lenght, 40.0, lenght*30.0);
}
void drawCone(float diameter, float lenght) {
	if (textureOn) {
		glBindTexture(GL_TEXTURE_2D, _textureIdCylinder);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		gluQuadricTexture(quadCylinder, 1);
	}
	else
		gluQuadricTexture(quadCylinder, 0);
	gluCylinder(quadCylinder, diameter, 0, lenght, 40.0, lenght*30.0);
}

void drawDisk(float diameterInner, float diameterOuter) {
	if (textureOn) {
		glBindTexture(GL_TEXTURE_2D, _textureIdCylinder);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		gluQuadricTexture(quadCylinder, 1);
	}
	else
		gluQuadricTexture(quadCylinder, 0);
	gluDisk(quadCylinder, diameterInner, diameterOuter, 40.0, 30.0);

}

void drawSphere(float diameter) {
	if (textureOn) {
		glBindTexture(GL_TEXTURE_2D, _textureIdSphere);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		gluQuadricTexture(quadSphere, 1);
	}
	else
		gluQuadricTexture(quadSphere, 0);
	gluSphere(quadSphere, diameter, 40.0, 40.0);
	//gluSphere(quadSphere, diameter, 10.0, 10.0);
}

void drawBase(){
    // draws the base

	drawCylinder(diameterBase, heightBase);
	glTranslatef(0.0f, 0.0f, heightBase);
	drawDisk(diameterCylinder, diameterBase);
	drawCylinder(diameterCylinder, sizeArm); //tronco

}

void drawRightArm(){

     glPushMatrix();

    	// move to arm referential
	glRotatef(angleArm, 0.0f, 0.0f, 1.0f);

	glRotatef(angleForearm, 0.0f, 1.0f, 0.0f);

	glTranslatef(0.1f, 0.0f, 1.0f);

	//draws the forearm
	drawSphere(diameterSphere);
	glTranslatef(0.0f, .0f, diameterSphere / 5);

	drawCylinder(diameterCylinder, sizeForearm);

	 //move to hand referential
	glTranslatef(0.0f, 0.0f, 2.0 + diameterSphere / 5);
	glRotatef(angleHand, 0.0f, 1.0f, 0.0f);//move o antebraço

	//draws the hand
	drawSphere(diameterSphere);
	glTranslatef(0.0f, 0.0f, diameterSphere / 5);
	drawCylinder(diameterCylinder, sizeHand);

	//move to clamp referential
	glTranslatef(0.0f, 0.0f, sizeHand + diameterSphere / 5);
	glRotatef(angleClampZ, 0.0f, 0.0f, 1.0f);

	//draws the clamp sphere
	drawSphere(diameterSphere);
	glTranslatef(0.0f, 0.0f, diameterSphere / 2);

	glPushMatrix();

	//draws top part of clamp
	glRotatef(angleClampY + 60, 0.0f, 1.0f, 0.0f);

	drawCylinder(diameterCylinder / 3, sizeClampPart);
	glTranslatef(0.0f, 0.0f, sizeClampPart + diameterSphere / 15);
	drawSphere(diameterSphere / 3);

	glTranslatef(0.0f, 0.0f, diameterSphere / 15);
	glRotatef(-60, 0.0f, 1.0f, 0.0f);

	drawCylinder(diameterCylinder / 3, sizeClampPart);
	glTranslatef(0.0f, 0.0f, sizeClampPart + diameterSphere / 15);
	drawSphere(diameterSphere / 3);

	glTranslatef(0.0f, 0.0f, diameterSphere / 15);
	glRotatef(-60, 0.0f, 1.0f, 0.0f);
	drawCone(diameterCylinder / 3, sizeClampPart);

	glPopMatrix();
	glPushMatrix();

	//draws bottom part of clamp
	glRotatef(-angleClampY - 60, 0.0f, 1.0f, 0.0f);

	drawCylinder(diameterCylinder / 3, sizeClampPart);
	glTranslatef(0.0f, 0.0f, sizeClampPart + diameterSphere / 15);
	drawSphere(diameterSphere / 3);

	glTranslatef(0.0f, 0.0f, diameterSphere / 15);
	glRotatef(60, 0.0f, 1.0f, 0.0f);

	drawCylinder(diameterCylinder / 3, sizeClampPart);
	glTranslatef(0.0f, 0.0f, sizeClampPart + diameterSphere / 15);
	drawSphere(diameterSphere / 3);

	glTranslatef(0.0f, 0.0f, diameterSphere / 15);
	glRotatef(60, 0.0f, 1.0f, 0.0f);
	drawCone(diameterCylinder / 3, sizeClampPart);

	glPopMatrix();
	glPopMatrix();
}


void drawLeftArm(){

     glPushMatrix();

    	// move to arm referential
	glRotatef(-angleArm_L, 0.0f, 0.0f, 1.0f);
	glRotatef(angleForearm_L, 0.0f, 1.0f, 0.0f);

	glTranslatef(0.1f, 0.0f, 1.0f);

	//draws the forearm
	drawSphere(diameterSphere);
	glTranslatef(0.0f, .0f, diameterSphere / 5);
	drawCylinder(diameterCylinder, sizeForearm);

	 //move to hand referential
	glTranslatef(0.0f, 0.0f, 2.0 + diameterSphere / 5);
	glRotatef(angleHand_L, 0.0f, 1.0f, 0.0f);//move o antebraço

	//draws the hand
	drawSphere(diameterSphere);
	glTranslatef(0.0f, 0.0f, diameterSphere / 5);
	drawCylinder(diameterCylinder, sizeHand);

	//move to clamp referential
	glTranslatef(0.0f, 0.0f, sizeHand + diameterSphere / 5);
	glRotatef(angleClampZ, 0.0f, 0.0f, 1.0f);

	//draws the clamp sphere
	drawSphere(diameterSphere);
	glTranslatef(0.0f, 0.0f, diameterSphere / 2);

	glPushMatrix();

	//draws top part of clamp
	glRotatef(angleClampY + 60, 0.0f, 1.0f, 0.0f);

	drawCylinder(diameterCylinder / 3, sizeClampPart);
	glTranslatef(0.0f, 0.0f, sizeClampPart + diameterSphere / 15);
	drawSphere(diameterSphere / 3);

	glTranslatef(0.0f, 0.0f, diameterSphere / 15);
	glRotatef(-60, 0.0f, 1.0f, 0.0f);

	drawCylinder(diameterCylinder / 3, sizeClampPart);
	glTranslatef(0.0f, 0.0f, sizeClampPart + diameterSphere / 15);
	drawSphere(diameterSphere / 3);

	glTranslatef(0.0f, 0.0f, diameterSphere / 15);
	glRotatef(-60, 0.0f, 1.0f, 0.0f);
	drawCone(diameterCylinder / 3, sizeClampPart);

	glPopMatrix();
	glPushMatrix();

	//draws bottom part of clamp
	glRotatef(-angleClampY - 60, 0.0f, 1.0f, 0.0f);

	drawCylinder(diameterCylinder / 3, sizeClampPart);
	glTranslatef(0.0f, 0.0f, sizeClampPart + diameterSphere / 15);
	drawSphere(diameterSphere / 3);

	glTranslatef(0.0f, 0.0f, diameterSphere / 15);
	glRotatef(60, 0.0f, 1.0f, 0.0f);

	drawCylinder(diameterCylinder / 3, sizeClampPart);
	glTranslatef(0.0f, 0.0f, sizeClampPart + diameterSphere / 15);
	drawSphere(diameterSphere / 3);

	glTranslatef(0.0f, 0.0f, diameterSphere / 15);
	glRotatef(60, 0.0f, 1.0f, 0.0f);
	drawCone(diameterCylinder / 3, sizeClampPart);

	glPopMatrix();
	glPopMatrix();
}



void drawHead(){

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 2.0f);
    glRotatef(angleHead+70, angleH, 1.0f, 0.0f);
    glRectd(-1.0, -1.4, 1.0, 1.4);
    glPopMatrix();
    drawCylinder(0.4f, 1.2f);
}
void Eyes(){

    glPushMatrix();
    glTranslatef(1.0f, 0.8f, 2.0f);
    gluSphere(quadSphere, eY + 0.2, 40.0, 40.0);
	glPopMatrix();

    glPushMatrix();
    glTranslatef(1.0f, -0.8f, 2.0f);
    gluSphere(quadSphere, eY + 0.2, 40.0, 40.0);
	glPopMatrix();

}



void drawScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);
	//iluminacao
	//glEnable(GL_LIGHTING);
	//glEnable(GL_COLOR_MATERIAL);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	eyeX = eyeDistance * cos(viewAngleZ*PI / 180) * cos(viewAngleX*PI / 180);
	eyeY = eyeDistance * cos(viewAngleZ*PI / 180) * sin(viewAngleX*PI / 180);
	eyeZ = eyeDistance * sin(viewAngleZ*PI / 180);
	if (viewAngleZ<90)
		gluLookAt(eyeX, eyeY, eyeZ, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
	else
		gluLookAt(eyeX, eyeY, eyeZ, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);

    // drawing color
	glColor3f(1.0f, 1.0f, 1.0f);

// desenha base
	drawCylinder(diameterBase, heightBase);
	glTranslatef(0.0f, 0.0f, heightBase);
	drawDisk(diameterCylinder, diameterBase);
// Fim desenha base
//tronco
    drawCylinder(1.0, sizeArm);
// bolinha do meio
    glTranslatef(0.1f, 0.0f, sizeArm + diameterSphere / 5);
    drawHead();
    Eyes();
    drawRightArm();
    drawLeftArm();
	glutSwapBuffers();
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Garra");

    iluminacao();
	initRendering();
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);


	glutMainLoop();
	return 0;
}
