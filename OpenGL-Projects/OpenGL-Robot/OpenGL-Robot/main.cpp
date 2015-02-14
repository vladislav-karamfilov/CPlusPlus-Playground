#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GL/glut.h>

#include "RotatingPart.h"

using namespace OpenGlRobot;

const int WINDOW_WIDTH = 700, WINDOW_HEIGHT = 500;
const float ROTATE_STEP = 5.0f;

static float rotateX = 0;
static float rotateY = 0;
static float rotateZ = 0;
static float rotateHeadY = 0;
static float rotateLeftArmX = 0;
static float rotateRightArmX = 0;

static RotatingPart currentRotatingPart = RotatingPart::WHOLE_ROBOT;

void init() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(-3.0f, 3.0, -3.0f, 3.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0.2f, 0.0f, 0.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 1.0f);
}

void displayRobotLeftArm() {
	glPushMatrix();
	glRotatef(rotateLeftArmX, 1.0, 0.0, 0.0);
	glTranslatef(-1.0f, 0.1f, 0.0f);
	glScalef(1.0f, 0.2f, 0.2f);
	glutWireCube(1.0);
	glPopMatrix();
}

void displayRobotRightArm() {
	glPushMatrix();
	glRotatef(rotateRightArmX, 1.0, 0.0, 0.0);
	glTranslatef(1.0f, 0.1f, 0.0f);
	glScalef(1.0f, 0.2f, 0.2f);
	glutWireCube(1.0);
	glPopMatrix();
}

void displayRobotLeftLeg() {
	glPushMatrix();
	glTranslatef(-0.75, -0.5, 0.0);
	glScalef(0.5f, 0.5f, 0.5f);
	glutWireCube(1.0);
	glPopMatrix();
}

void displayRobotRightLeg() {
	glPushMatrix();
	glTranslatef(0.75, -0.5, 0.0);
	glScalef(0.5f, 0.5f, 0.5f);
	glutWireCube(1.0);
	glPopMatrix();
}

void displayRobotBody() {
	glPushMatrix();
	glutWireCube(1.0);
	glPopMatrix();
}

void displayRobootHead() {
	glPushMatrix();
	glRotatef(rotateHeadY, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 0.75, 0.0);
	glScalef(1.5f, 0.5f, 1.0f);
	glutWireSphere(0.75, 50, 50);
	glScalef(1.0f, 2.0f, 1.0f);
	glPopMatrix();
}

void displayRobot() {
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	glTranslatef(0.5f, 0.5f, 0.0f);

	glRotatef(rotateX, 1.0f, 0.0f, 0.0f);
	glRotatef(rotateY, 0.0f, 1.0f, 0.0f);
	glRotatef(rotateZ, 0.0f, 0.0f, 1.0f);

	glScalef(1.0f, 2.0f, 1.0f);

	displayRobootHead();
	displayRobotBody();
	displayRobotLeftArm();
	displayRobotRightArm();
	displayRobotLeftLeg();
	displayRobotRightLeg();

	glutSwapBuffers();
}

void onKeyPressed(unsigned char key, int x, int y) {
	switch (key) {
	case 'X':
		if (currentRotatingPart == RotatingPart::LEFT_ARM)
		{
			rotateLeftArmX += ROTATE_STEP;
		}
		else if (currentRotatingPart == RotatingPart::RIGHT_ARM)
		{
			rotateRightArmX += ROTATE_STEP;
		}
		else
		{
			rotateX += ROTATE_STEP;
		}

		break;

	case 'x':
		if (currentRotatingPart == RotatingPart::LEFT_ARM)
		{
			rotateLeftArmX -= ROTATE_STEP;
		}
		else if (currentRotatingPart == RotatingPart::RIGHT_ARM)
		{
			rotateRightArmX -= ROTATE_STEP;
		}
		else
		{
			rotateX -= ROTATE_STEP;
		}

		break;

	case 'Y':
		if (currentRotatingPart == RotatingPart::HEAD)
		{
			rotateHeadY += ROTATE_STEP;
		}
		else
		{
			rotateY += ROTATE_STEP;
		}

		break;

	case 'y':
		if (currentRotatingPart == RotatingPart::HEAD)
		{
			rotateHeadY -= ROTATE_STEP;
		}
		else
		{
			rotateY -= ROTATE_STEP;
		}

		break;

	case 'Z':
		rotateZ += ROTATE_STEP;
		break;

	case 'z':
		rotateZ -= ROTATE_STEP;
		break;

	case 27: // ESC
		exit(0);
		return;

	default:
		return;
	}

	glutPostRedisplay();
}

void resize(int width, int height) {
	double aspect = WINDOW_WIDTH / WINDOW_HEIGHT;
	if (aspect > (double) width / height) {
		glViewport(0, 0, width, width / aspect);
	}
	else {
		glViewport(0, 0, height * aspect, height);
	}
}

void menu(int menuItem) {
	switch (menuItem) {
	case 0:
		currentRotatingPart = RotatingPart::WHOLE_ROBOT;
		break;
	case 1:
		currentRotatingPart = RotatingPart::HEAD;
		break;
	case 2:
		currentRotatingPart = RotatingPart::LEFT_ARM;
		break;
	case 3:
		currentRotatingPart = RotatingPart::RIGHT_ARM;
		break;
	case 4:
		exit(0);
		return;
	default:
		return;
	}

	glutPostRedisplay();
}

void addMenuItems() {
	glutAddMenuEntry("---Select current moving part---", INT_MAX);
	glutAddMenuEntry("Whole robot", 0);
	glutAddMenuEntry("Head", 1);
	glutAddMenuEntry("Left arm", 2);
	glutAddMenuEntry("Right arm", 3);
	glutAddMenuEntry("---Others---", INT_MAX);
	glutAddMenuEntry("Quit", 4);
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("OpenGL Robot");

	init();
	glutDisplayFunc(displayRobot);
	glutKeyboardFunc(onKeyPressed);
	glutReshapeFunc(resize);

	glutCreateMenu(menu);
	addMenuItems();
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
}
