#include <iostream>
#include <GL/freeglut.h>

float xrot = 0;
float yrot = 0;
float xdiff = 0;
float ydiff = 0;
bool mousedown = false;
bool is_roof_open = false;

void idle() {
	if (!mousedown) {
		xrot += 0.4f;
		yrot += 0.4f;
	}

	glutPostRedisplay();
}

void handleMouseButton(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		mousedown = true;
		xdiff = x - yrot;
		ydiff = -y + xrot;
	} else {
		mousedown = false;
	}

	glutPostRedisplay();
}

void handleMouseMove(int x, int y) {
	if (mousedown) {
		yrot = x - xdiff;
		xrot = y + ydiff;

		glutPostRedisplay();
	}
}

void handleKeyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 'a':
		case 'A':
			// bergeser ke kiri
			glTranslatef(-1.0, 0.0, 0.0);
			break;
		case 'd':
		case 'D':
			// bergeser ke kanan
			glTranslatef(1.0, 0.0, 0.0);
			break;
		case 'w':
		case 'W':
			// bergeser ke atas
			glTranslatef(0.0, 1.0, 0.0);
			break;
		case 's':
		case 'S':
			// bergeser ke bawah
			glTranslatef(0.0, -1.0, 0.0);
			break;
		case 'z':
		case 'Z':
			// bergeser ke depan
			glTranslatef(0.0, 0.0, 1.0);
			break;
		case 'x':
		case 'X':
			// bergeser ke belakang
			glTranslatef(0.0, 0.0, -1.0);
			break;
		case 'e':
		case 'E':
			// berotasi ke kanan
			glRotatef(1.0, 0.0, 0.0, -5.0);
			break;
		case 'q':
		case 'Q':
			// berotasi ke kiri
			glRotatef(1.0, 0.0, 0.0, 5.0);
			break;
		case 'o':
		case 'O':
			// membuka atap rumah
			is_roof_open = true;
			break;
		case 'c':
		case 'C':
			// menutup atap rumah
			is_roof_open = false;
			break;
	}

	glutPostRedisplay();
}

void reshape(int w, int h) {
	if (h == 0) h = 1;

	GLfloat aspect = (GLfloat)w / (GLfloat)h;
	glViewport(0, 25, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, aspect, 0.1f, -1.0f);
}

void boxFrontBack(float x1, float x2, float y1, float y2, float z1) {
	glBegin(GL_QUADS);
		glVertex3f(x1, y1, z1);
		glVertex3f(x2, y1, z1);
		glVertex3f(x2, y2, z1);
		glVertex3f(x1, y2, z1);
	glEnd();
}

void boxLeftRight(float x1, float x2, float y1, float y2, float z1, float z2) {
	glBegin(GL_QUADS);
		glVertex3f(x1, y1, z1);
		glVertex3f(x2, y1, z2);
		glVertex3f(x2, y2, z2);
		glVertex3f(x1, y2, z1);
	glEnd();
}

void boxThick(float x1, float x2, float y1, float y2, float z1, float z2) {
	// sisi atas
	glBegin(GL_QUADS);
		glVertex3f(x1, y1, z2);
		glVertex3f(x2, y1, z2);
		glVertex3f(x2, y1, z1);
		glVertex3f(x1, y1, z1);
	glEnd();

	// sisi bawah
	glBegin(GL_QUADS);
		glVertex3f(x1, y2, z2);
		glVertex3f(x2, y2, z2);
		glVertex3f(x2, y2, z1);
		glVertex3f(x1, y2, z1);
	glEnd();

	// sisi depan
	glBegin(GL_QUADS);
		glVertex3f(x1, y1, z1);
		glVertex3f(x2, y1, z1);
		glVertex3f(x2, y2, z1);
		glVertex3f(x1, y2, z1);
	glEnd();

	// sisi belakang
	glBegin(GL_QUADS);
		glVertex3f(x1, y1, z2);
		glVertex3f(x2, y1, z2);
		glVertex3f(x2, y2, z2);
		glVertex3f(x1, y2, z2);
	glEnd();

	// sisi kiri
	glBegin(GL_QUADS);
		glVertex3f(x1, y1, z2);
		glVertex3f(x1, y1, z1);
		glVertex3f(x1, y2, z1);
		glVertex3f(x1, y2, z2);
	glEnd();

	// sisi kanan
	glBegin(GL_QUADS);
		glVertex3f(x2, y1, z1);
		glVertex3f(x2, y1, z2);
		glVertex3f(x2, y2, z2);
		glVertex3f(x2, y2, z1);
	glEnd();
}

void boxFloatLeftRight(float x1, float x2, float x3, float y1, float y2, float z1, float z2) {
	// sisi kiri
	glBegin(GL_QUADS);
		glVertex3f(x2, y1, z2);
		glVertex3f(x2, y1, z1);
		glVertex3f(x1, y2, z1);
		glVertex3f(x1, y2, z2);
	glEnd();

	// sisi kanan
	glBegin(GL_QUADS);
		glVertex3f(x2, y1, z1);
		glVertex3f(x2, y1, z2);
		glVertex3f(x3, y2, z2);
		glVertex3f(x3, y2, z1);
	glEnd();
}

void triangleThick(float x1, float x2, float x3, float y1, float y2, float z1, float z2) {
	// sisi depan
	glBegin(GL_TRIANGLES);
		glVertex3f(x1, y2, z1);
		glVertex3f(x2, y1, z1);
		glVertex3f(x3, y2, z1);
	glEnd();

	// sisi belakang
	glBegin(GL_TRIANGLES);
		glVertex3f(x1, y2, z2);
		glVertex3f(x2, y1, z2);
		glVertex3f(x3, y2, z2);
	glEnd();

	// sisi kiri
	glBegin(GL_QUADS);
		glVertex3f(x2, y1, z2);
		glVertex3f(x2, y1, z1);
		glVertex3f(x1, y2, z1);
		glVertex3f(x1, y2, z2);
	glEnd();

	// sisi kanan
	glBegin(GL_QUADS);
		glVertex3f(x2, y1, z1);
		glVertex3f(x2, y1, z2);
		glVertex3f(x3, y2, z2);
		glVertex3f(x3, y2, z1);
	glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	gluLookAt(0, 0, 470, 0, 0, 0, 0, 1, 0);
	glRotatef(xrot, 1, 0, 0);
	glRotatef(yrot, 0, 1, 0);

	glColor3ub(255, 139, 61);
	boxFrontBack(-89.5, -65.8, 2.3, -54.7, -250.7); // tembok belakang kanan pojok
	boxFrontBack(67.7, 92.1, 2.3, -54.7, -250.7); // tembok belakang kiri pojok
	boxFrontBack(-65.8, 67.7, 2.3, -7.5, -250.7); // tembok belakang atas tengah
	boxFrontBack(-20.8, 22.9, -7.5, -25.0, -250.7); // tembok belakang tengah tengah
	boxFrontBack(-65.8, 67.7, -25.0, -54.7, -250.7); // tembok belakang bawah tengah

	glColor3ub(179, 205, 224);
	boxFrontBack(-65.8, -20.8, -7.5, -25.0, -250.7); // jendela belakang kanan
	boxFrontBack(22.9, 67.7, -7.5, -25.0, -250.7); // jendela belakang kiri

	glColor3ub(255, 139, 61);
	boxFrontBack(-89.5, -68.2, 2.3, -54.7, 8.7); // tembok depan kiri pojok
	boxFrontBack(74.1, 92.1, 2.3, -54.7, 8.7); // tembok depan kanan pojok
	boxFrontBack(-68.2, 74.1, 2.3, -3.7, 8.7); // tembok depan atas tengah
	boxFrontBack(-29.5, 35.4, -3.7, -23.6, 8.7); // tembok depan tengah tengah
	boxFrontBack(-68.2, -7.5, -23.6, -54.7, 8.7); // tembok depan bawah kiri
	boxFrontBack(14.5, 74.1, -23.6, -54.7, 8.7); // tembok depan bawah kanan

	glColor3ub(179, 205, 224);
	boxFrontBack(-68.2, -29.5, -3.7, -23.6, 8.7); // jendela depan kiri
	boxFrontBack(35.4, 74.1, -3.7, -23.6, 8.7); // jendela depan kanan

	glColor3ub(154, 88, 40);
	boxFrontBack(-7.5, 14.5, -23.6, -54.7, 8.7); // pintu depan

	glColor3ub(219, 205, 173);
	boxFrontBack(11.1, 13.3, -36.4, -39.9, 8.8); // gagang pintu depan depan
	boxFrontBack(11.1, 13.3, -36.4, -39.9, 8.6); // gagang pintu depan belakang

	glColor3ub(255, 139, 61);
	boxLeftRight(-89.5, -89.5, 2.3, -54.7, -250.7, -228.8); // tembok kiri kiri pojok
	boxLeftRight(-89.5, -89.5, 2.3, -54.7, -11.3, 8.7); // tembok kiri kanan pojok
	boxLeftRight(-89.5, -89.5, 2.3, -7.0, -228.8, 8.7); // tembok kiri tengah atas
	boxLeftRight(-89.5, -89.5, -7.0, -27.8, -162.8, -77.6); // tembok kiri tengah tengah
	boxLeftRight(-89.5, -89.5, -27.8, -54.7, -228.8, 8.7); // tembok kiri tengah bawah

	glColor3ub(179, 205, 224);
	boxLeftRight(-89.5, -89.5, -7.0, -27.8, -228.8, -162.8); // jendela kiri kiri
	boxLeftRight(-89.5, -89.5, -7.0, -27.8, -77.6, -11.3); // jendela kiri kanan

	glColor3ub(255, 139, 61);
	boxLeftRight(92.1, 92.1, 2.3, -54.7, 8.7, -16.6); // tembok kanan kiri pojok
	boxLeftRight(92.1, 92.1, 2.3, -54.7, -222.6, -250.7); // tembok kanan kanan pojok
	boxLeftRight(92.1, 92.1, 2.3, -7.9, -16.6, -222.6); // tembok kanan tengah atas
	boxLeftRight(92.1, 92.1, -7.9, -29.5, -76.9, -162.3); // tembok kanan tengah tengah
	boxLeftRight(92.1, 92.1, -29.5, -54.7, -16.6, -222.6); // tembok kanan tengah bawah

	glColor3ub(179, 205, 224);
	boxLeftRight(92.1, 92.1, -7.9, -29.5, -16.6, -76.9); // jendela kanan kiri
	boxLeftRight(92.1, 92.1, -7.9, -29.5, -162.3, -222.6); // jendela kanan kanan

	glColor3ub(219, 205, 173);
	boxThick(-109.9, 118.4, -54.7, -65.0, 34.7, -278.1); // lantai

	glColor3ub(189, 126, 74);
	boxThick(-80.6, -63.4, -2.2, -54.7, -197.1, -242.7); // lemari

	glColor3ub(150, 97, 61);
	boxLeftRight(-63.3, -63.3, -7.0, -47.2, -202.8, -218.9); // pintu lemari kiri
	boxLeftRight(-63.3, -63.3, -7.0, -47.2, -220.6, -236.7); // pintu lemari kanan

	glColor3ub(219, 205, 173);
	boxLeftRight(-63.2, -63.2, -20.1, -27.0, -213.3, -216.6); // gagang pintu lemari kiri
	boxLeftRight(-63.2, -63.2, -20.1, -27.0, -222.5, -225.8); // gagang pintu lemari kanan

	glColor3ub(237, 163, 35);
	boxThick(-80.6, -67.0, -21.3, -54.7, -28.5, -143.0); // sofa kiri belakang

	glColor3ub(244, 205, 42);
	boxThick(-67.0, -51.2, -37.0, -54.7, -28.5, -143.0); // sofa kiri depan

	glColor3ub(237, 163, 35);
	boxThick(69.2, 79.5, -21.3, -54.7, -10.0, -64.3); // sofa kanan belakang

	glColor3ub(244, 205, 42);
	boxThick(52.2, 69.2, -37.0, -54.7, -10.0, -64.3); // sofa kanan depan

	glColor3ub(154, 154, 154);
	boxThick(52.2, 83.0, -37.0, -54.7, -80.9, -126.4); // alas tv

	glColor3ub(112, 112, 112);
	boxThick(62.2, 73.0, -34.0, -37.0, -95.9, -108.4); // alas kaki tv

	glColor3ub(69, 69, 69);
	boxThick(66.2, 69.0, -29.0, -34.0, -100.9, -103.4); // kaki tv
	boxThick(66.2, 69.0, -14.0, -29.0, -85.9, -118.4); // tv

	glColor3ub(46, 133, 110);
	boxThick(19.2, 79.5, -37.0, -54.7, -156.4, -242.7); // tempat tidur
	boxThick(19.2, 79.5, -17.0, -37.0, -237.7, -242.7); // sandaran tempat tidur

	glColor3ub(219, 205, 173);
	boxThick(19.2, 79.5, -35.0, -37.0, -156.4, -236.7); // alas tempat tidur

	glColor3ub(237, 163, 35);
	boxThick(34.2, 64.5, -30.0, -35.0, -227.7, -210.7); // bantal

	if (!is_roof_open) {
		glColor3ub(219, 205, 173);
		triangleThick(-89.5, 2.0, 92.1, 45.0, 2.3, 8.7, -250.7); // atap rumah

		glColor3ub(154, 88, 40);
		boxFloatLeftRight(-90.5, 2.0, 93.1, 46.0, 2.3, 20.7, -262.7); // seng rumah
	}

	glPopMatrix();
	glutSwapBuffers();
}

void initGL() {
	glClearColor(0, 0, 0, 0);
	glLineWidth(2);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glMatrixMode(GL_PROJECTION);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000, 600);
	glutCreateWindow("Dewi Winarsih - 672018402");
	initGL();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(handleKeyboard);
	glutMouseFunc(handleMouseButton);
	glutMotionFunc(handleMouseMove);
	glutIdleFunc(display);

	glutMainLoop();
	return 0;
}
