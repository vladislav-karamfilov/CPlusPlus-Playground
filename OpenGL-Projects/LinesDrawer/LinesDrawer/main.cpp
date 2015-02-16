#include <iostream>
#include <stdlib.h>
#include <vector>
#include <GL/glut.h>

#include "Line.h"

using namespace std;
using namespace LinesDrawer;

const int WINDOW_WIDTH = 700, WINDOW_HEIGHT = 500;
const int INITIAL_WINDOW_POSITION_X = 100, INITIAL_WINDOW_POSITION_Y = 100;
const int MOVE_STEP = 3;
const int MIN_LINE_WIDTH = 1;
const float ROTATE_ANGLE = 10;

static bool isDrawing;
static int lineWidth;
static Color currentColor;
static LineStyle currentLineStyle;
static vector<Line> lines;

void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
	glColor3f(1.0f, 1.0f, 1.0f); // White color

	isDrawing = false;
	lineWidth = MIN_LINE_WIDTH;
	currentColor = Color();
	currentLineStyle = LineStyle::NORMAL;
	lines = vector <Line>();
}

void drawLine(Line line) {
	Color color = line.CurrentColor;

	glColor3d(color.Red, color.Green, color.Blue);

	switch (line.Style)
	{
	case LineStyle::NORMAL:
		glDisable(GL_LINE_STIPPLE);
		break;
	case LineStyle::STIPPLED:
		glLineStipple(1, 0x00FF);
		glEnable(GL_LINE_STIPPLE);
		break;
	default:
		throw "Invalid line style!";
	}

	Point firstPoint = line.FirstPoint;
	Point lastPoint = line.LastPoint;

	if (firstPoint == lastPoint)
	{
		glPointSize(lineWidth);

		glBegin(GL_POINTS);
		glVertex2i(firstPoint.X, firstPoint.Y);
	}
	else
	{
		glLineWidth(lineWidth);

		glBegin(GL_LINES);
		glVertex2i(firstPoint.X, firstPoint.Y);
		glVertex2i(lastPoint.X, lastPoint.Y);
	}

	glEnd();
}

void drawLines() {
	glClear(GL_COLOR_BUFFER_BIT);

	for (size_t i = 0; i < lines.size(); i++)
	{
		drawLine(lines[i]);
	}

	glutSwapBuffers();
}

void keyPressed(unsigned char key, int x, int y) {
	switch (key) {
	case '+':
		++lineWidth;
		break;

	case '-':
		if (lineWidth > MIN_LINE_WIDTH) {
			--lineWidth;
		}

		break;

	case 'a':
	case 'A':
		glTranslatef(-MOVE_STEP, 0, 0);
		break;

	case 'd':
	case 'D':
		glTranslatef(MOVE_STEP, 0, 0);
		break;

	case 'w':
	case 'W':
		glTranslatef(0, MOVE_STEP, 0);
		break;

	case 's':
	case 'S':
		glTranslatef(0, -MOVE_STEP, 0);
		break;

	case 'r':
		glTranslatef(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0);
		glRotatef(ROTATE_ANGLE, 0, 0, 0.5);
		glTranslatef(-WINDOW_WIDTH / 2, -WINDOW_HEIGHT / 2, 0);

		break;

	case 'R':
		glTranslatef(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0);
		glRotatef(-ROTATE_ANGLE, 0, 0, 0.5);
		glTranslatef(-WINDOW_WIDTH / 2, -WINDOW_HEIGHT / 2, 0);

		break;

	case 27:
	case 'q':
	case 'Q':
		exit(0);
		return;

	default:
		return;
	}

	glutPostRedisplay();
}

void mouseButtonPressed(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN && !isDrawing) {
			lines.push_back(Line(Point(x, WINDOW_HEIGHT - y), Point(), currentColor, currentLineStyle));

			isDrawing = true;
		}
		else if (state == GLUT_UP && isDrawing) {
			lines[lines.size() - 1].LastPoint = Point(x, WINDOW_HEIGHT - y);
			isDrawing = false;

			glutPostRedisplay();
		}
	}
}

void motion(int x, int y) {
	if (isDrawing) {
		lines[lines.size() - 1].LastPoint.X = x;
		lines[lines.size() - 1].LastPoint.Y = WINDOW_HEIGHT - y;

		glutPostRedisplay();
	}
}

void menu(int menuItem) {
	switch (menuItem) {
	case 1:
		currentColor = Color(1, 0, 0);
		break;
	case 2:
		currentColor = Color(0, 1, 0);
		break;
	case 3:
		currentColor = Color(0, 0, 1);
		break;
	case 4:
		currentColor = Color(1, 1, 1);
		break;
	case 5:
		currentLineStyle = LineStyle::STIPPLED;
		break;
	case 6:
		currentLineStyle = LineStyle::NORMAL;
		break;
	case 7:
		exit(0);
		return;
	default:
		return;
	}

	glutPostRedisplay();
}

void addMenuItems() {
	glutAddMenuEntry("---Colors---", INT_MAX);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("White", 4);
	glutAddMenuEntry("---Styles---", INT_MAX);
	glutAddMenuEntry("Stippled line", 5);
	glutAddMenuEntry("Simple line", 6);
	glutAddMenuEntry("---Other---", INT_MAX);
	glutAddMenuEntry("Quit", 7);
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(INITIAL_WINDOW_POSITION_X, INITIAL_WINDOW_POSITION_Y);
	glutCreateWindow("Lines Drawer");

	init();
	glutDisplayFunc(drawLines);
	glutKeyboardFunc(keyPressed);
	glutMouseFunc(mouseButtonPressed);
	glutMotionFunc(motion);

	glutCreateMenu(menu);
	addMenuItems();
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
}
