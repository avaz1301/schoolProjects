3dobject v1
PROJECT# 3


#include<glut.h>
#include<string>
#include<iostream>
using namespace std;

GLfloat pos[] = { -2, 4, 5, 1 },
amb[] = { 0.3, 0.3, 0.3, 1.0 };

GLfloat front_amb_diff[] = { 0.2, 0.2, 1.0, 1.0 };//blue
GLfloat front_amb_diff1[] = { 1.0, 0.2, 0.2, 1.0 };//red
GLfloat front_amb_diff2[] = { 1.0, 1.0, 1.0, 1.0 };//whit
GLfloat front_amb_diff3[] = { 0.5, 0.5, 0.5, 1.0 };//grey


GLfloat back_amb_diff[] = { 0.7, 0.5, 0.1, 1.0 };
GLfloat spe[] = { 0.25, 0.25, 0.25, 1.0 };
GLfloat dt = 0.1, axes[3][3] = { {1,0,0},{0,1,0},{0,0,1} };
GLfloat theta = 0;
float pan = 0;
int axis = 0;
float y_mov =-8.0;
bool  move_up = false;
//float base = 0.5;
//float height = 5;
//float radius = 1.0f;

void display(void) {
	if (y_mov >= -3.9 && !move_up) {
		cout << "check" << endl;
		move_up = true;
	}
	if (y_mov <= -7.9 && move_up) {
		move_up = false;
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, front_amb_diff3);
	glPushMatrix();//push1
	glRotatef(pan, 0.0f, 1.0f, 0.0f);
	
	////////////////////////////////////////////////////////////////////////////
	glBegin(GL_LINES);
	for (int i = -10; i < 11; i++) {
		if (i == 0) {
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, front_amb_diff2);
		}
		else {
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, front_amb_diff);
		}
		glVertex3f(i, 0.0, -10);
		glVertex3f(i, 0.0, 10);
		glVertex3f(10, 0.0, i);
		glVertex3f(-10, 0.0, i);
	}
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, front_amb_diff1);
	glVertex3f(0.0f, 10.0f, 0.0f);
	glVertex3f(0.0f, -10.0f, 0.0f);
	glEnd();

	//////////////////////////////////////////////////////////////////////////////
	

//	glRotatef(theta, 0, 0, 1);

	//glPushMatrix();
	//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, front_amb_diff3);
	////glRotatef(90.0f, 1, 0, 0);
	//glutSolidTorus(.2, 1.0, 48, 96);
	//glPopMatrix();
	
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, front_amb_diff);
	GLUquadricObj * quadObj;
	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj, GL_FILL);
	

	glRotatef(90, 1.0f, 0.0f, 0.0f);//bouncing cylinder
	glPushMatrix();//push 2
	glRotatef(-30, 0.0, 1.0, 0.0);/////////////////////
	glTranslated(0.0, 0.0, y_mov);
	gluCylinder(quadObj, 2.0, 2.0,1.5,20,30);
	glPopMatrix();//pop2


	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, front_amb_diff3);
	quadObj = gluNewQuadric();//bouncing cylinder inner pin
	gluQuadricDrawStyle(quadObj, GL_FILL);
	glRotatef(-30, 0.0, 1.0, 0.0);/////////////////////
	glPushMatrix();//push3
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	glTranslated(0.0, y_mov+0.75, -2.1);
	gluCylinder(quadObj, 0.5, 0.5, 4.2, 20, 30);
	glPopMatrix();//pop3

	//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, front_amb_diff3);
	//quadObj = gluNewQuadric();//bouncing cylinder inner pin
	//gluQuadricDrawStyle(quadObj, GL_FILL);
	//glPushMatrix();
	//glRotatef(90, 1.0f, 0.0f, 0.0f);
	//glTranslated(0.0, y_mov + 0.75, -2.1);
	//gluCylinder(quadObj, 0.5, 0.5, 4.2, 20, 30);
	//glPopMatrix();

	quadObj = gluNewQuadric();//top cover of cylinder
	gluQuadricDrawStyle(quadObj, GL_FILL);
	glRotatef(180, 1.0f, 0.0f, 0.0f);
	glPushMatrix();//push4
	glTranslated(0.0, 0.0, (-y_mov));
	gluDisk(quadObj,0.0,2.0,20,30);
	glPopMatrix();//pop4

	quadObj = gluNewQuadric();//bottom cover of cylinder
	gluQuadricDrawStyle(quadObj, GL_FILL);
	glRotatef(180, 1.0f, 0.0f, 0.0f);
	glPushMatrix();//push5
	glTranslated(0.0, 0.0, (y_mov+1.5));
	gluDisk(quadObj, 0.0, 2.0, 20, 30);
	glPopMatrix();//pop5

	
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, front_amb_diff3);//grey
	quadObj = gluNewQuadric();//cylinder arm
	gluQuadricDrawStyle(quadObj, GL_FILL);
	glPushMatrix();//push6
	glRotatef(-30, 0.0f, 1.0f, 0.0f);
	glTranslated(0.0, 0.0, y_mov);
	gluCylinder(quadObj, 0.5, 0.5, 7.0, 20, 30);
	glPopMatrix();//pop6

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, front_amb_diff);//blue
	quadObj = gluNewQuadric();//cylinder at origin
	gluQuadricDrawStyle(quadObj, GL_FILL);
	glPushMatrix();//push7
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	glTranslated(0.0, 0.0, -0.75);
	gluCylinder(quadObj, 0.8, 0.8, 1.5, 20, 30);
	glPopMatrix();//pop7

	


	//glPushMatrix();//push2
	//glTranslated(0.0, 2.0, 0.0);
	//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, front_amb_diff1);
	//glPushMatrix();//push torus
	//glRotatef(theta, 1.0f, 0.0f, 0.0f);
	//glutSolidTorus(0.1, 1.0, 48, 96);
	//glPopMatrix();//pop torus
	//
	//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, front_amb_diff);
	///*GLUquadricObj * quadObj;
	//quadObj = gluNewQuadric();*/
	//gluQuadricDrawStyle(quadObj, GL_FILL);

	//glPushMatrix();//push icosa
	//glRotatef(-theta, 0.0f, 1.0f, 0.0f);
	//glutSolidIcosahedron();
	//glPopMatrix();//pop icosa

	//gluSphere(quadObj, 1.0, 12, 10);
	
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, front_amb_diff3);
	glutSolidTorus(.2, 1.0, 48, 96);

	///////////////////////////////////////////////////////////////////////////

	glPopMatrix();//pop1
	glutSwapBuffers();
}

void keyboard(int key, int x, int y) {
	if (GLUT_KEY_DOWN) {
		switch (key) {
			//"r" pressed:sets color for right of interpolation window to current slider RGB value
		case GLUT_KEY_LEFT:
			pan +=5;
			//cout << theta << endl;

			break;
			//"l" pressed: sets color for left of interpolation window to current slider RGB value
		case GLUT_KEY_RIGHT:
			pan -= 5;
			cout << theta << endl;
			break;

		case GLUT_KEY_DOWN:
			y_mov -= 0.1;
			break;

		case GLUT_KEY_UP:
			y_mov += 0.1;
			cout << theta << endl;
			break;
		}//switch
	}
	glutPostRedisplay();
}//keyboard

void idle(void) {

	if (theta >= 360) {
		axis = (axis + 1) % 2;
	}
	theta = (theta < 360) ? theta + dt : dt;

	if (move_up) {
		y_mov -= 0.01;
	}
	else {
		y_mov += 0.01;
	}
		
	
	//move_up = true;
	glutPostRedisplay();
}//idle

void main(int argc, char * * argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("GLUT_ Objects");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, front_amb_diff);
	glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, back_amb_diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 75);

	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(100, 1, 2, 30);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -10.0f);
	
	//glTranslatef(0.0f, 0.0f, 10.0f);
	glRotatef(30.0f, 1.0f, 0.0f, 0.0f);

	//glRotatef((float)theta, 0.0f, 1.0f, 0.0f);
	//glTranslated(0, 0, -15);

	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glutDisplayFunc(display);
	glutSpecialFunc(keyboard);
	glutIdleFunc(idle);
	glutMainLoop();
}//main

