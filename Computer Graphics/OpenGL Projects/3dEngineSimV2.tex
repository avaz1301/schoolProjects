//Angelo Zamudio
//CS 368 SUMMER 2015
//Project 3: 3D OBJECT
//3D SIMPLE ENGINE SIMULATOR

#include<glut.h>
#include<string>
#include<iostream>
#include <math.h>
using namespace std;

GLfloat pos[] = { -2, 4, 5, 1 },
amb[] = { 0.3, 0.3, 0.3, 1.0 };
GLfloat blue_diff[] = { 0.2, 0.2, 1.0, 1.0 };//blue
GLfloat front_amb_diff1[] = { 0.7, 0.7, 0.1, 1.0 };//grey
GLfloat grey_diff[] = { 0.5, 0.5, 0.5, 1.0 };//grey
GLfloat back_amb_diff[] = { 0.7, 0.5, 0.1, 1.0 };
GLfloat spe[] = { 0.5, 0.5, 0.5, 1.0 };

GLfloat dt = 0.01;
GLfloat theta = 0;
GLfloat theta2 = 0;
GLfloat dt2 = 0.6;
GLfloat theta3 = 0;
GLfloat dt3 = 1.0;

float cyl_height = 0.01;
float pan = 0;
int axis = 0;
float y_cyl =8.0;
float y_cyl2 = 4.9;
bool  move_up = false;
bool move_up2 = false;
GLfloat feild = -20;
int deg1 = 30, deg2 = -30;


void create_cyl(int degree, float y_mov, float depth) {
	int offset = 1;
	if (degree < 0) {
		offset = -1;
	}
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue_diff);
	GLUquadricObj * quadObj;
	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj, GL_FILL);

	glRotated(degree, 0.0, 0.0, 1.0);

	glPushMatrix();//push
	glTranslated(0.0, y_mov, depth);
	glRotatef(90, 1.0f, 0.0f, 0.0f);//cylinder head
	gluCylinder(quadObj, 2.0, 2.0, 1.5, 20, 30);
	glPopMatrix();//pop
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, grey_diff);
	glBegin(GL_QUADS);//cylinder arm
		glVertex3f(0.0, y_mov, depth);
		glVertex3f(offset*0.5, y_mov, depth);
		glVertex3f(offset*0.5+cos(theta), sin(theta), depth);//allows for rotation 
		glVertex3f(cos(theta), sin(theta), depth);			//with the crank shaft
	glEnd();	

	quadObj = gluNewQuadric();//cylinder head inner pin
	gluQuadricDrawStyle(quadObj, GL_FILL);
	
	glPushMatrix();//push
	glTranslated(0.0, y_mov-0.75, depth-2.1);
	gluCylinder(quadObj, 0.5, 0.5, 4.2, 20, 30);
	glPopMatrix();//pop

	quadObj = gluNewQuadric();//top cover of cylinder
	gluQuadricDrawStyle(quadObj, GL_FILL);
	glPushMatrix();//push
	glTranslated(0.0, y_mov, depth);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	gluDisk(quadObj,0.0,2.0,20,30);
	glPopMatrix();//pop

	glRotatef(theta2, 0, 0, 1);
	quadObj = gluNewQuadric();//cylinder crank connector
	gluQuadricDrawStyle(quadObj, GL_FILL);
	glPushMatrix();//push
	glTranslated(0.0, 0.0, depth);
	gluDisk(quadObj, 0.0, 1.5, 20, 30);
	glPopMatrix();//pop
}//create_cyl

void create_crank(void) {
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue_diff);
	GLUquadricObj * quadObj;
	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj, GL_FILL);

	glRotatef(theta, 0, 0, 1);//main crank shaft
	glPushMatrix();//push1
	glTranslated(0.0, 0.0, -10.0);
	gluCylinder(quadObj, 0.5, 0.5, 20.0, 20, 30);
	glPopMatrix();//pop1

	glPushMatrix();//rotating torus base
	glTranslated(0.0, 0.0, -10.0);
	glutSolidTorus(0.5,1.0,48,60);
	glEnd();

	quadObj = gluNewQuadric();//front cover of crank shaft
	gluQuadricDrawStyle(quadObj, GL_FILL);
	glPushMatrix();//push2
	glTranslated(0.0, 0.0, 10.0);	
	gluDisk(quadObj, 0.0, 0.5, 20, 30);
	glPopMatrix();//pop2

	quadObj = gluNewQuadric();//back cover of crank shaft
	gluQuadricDrawStyle(quadObj, GL_FILL);
	glPushMatrix();//push3
	glTranslated(0.0, 0.0, -10.0);
	gluDisk(quadObj, 0.0, 0.5, -20, 30);
	glPopMatrix();//pop3

	glRotatef(theta2, 0, 0, 1);//propeller crank shaft
	glPushMatrix();//push1
	glTranslated(0.0, 0.0, 3.0);
	gluCylinder(quadObj, 0.3, 0.3, 8.0, 20, 30);
	glPopMatrix();//pop1
}//create_crank

void create_prop(void) {
	glRotatef(theta3, 0, 0, 1);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, grey_diff);
	
	glPushMatrix();//prop blade1
	glTranslated(0.0, 8.0, 11.0);
	glScalef(1.0f, 3.5f, 0.25f);
	glutSolidSphere(1.0, 20, 30);
	glPopMatrix();

	glPushMatrix();//prop blade2
	glTranslated(0.0, -8.0, 11.0);
	glScalef(1.0f, 3.5f, 0.25f);
	glutSolidSphere(1.0, 20, 30);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue_diff);
	GLUquadricObj * quadObj;
	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj, GL_FILL);

	glPushMatrix();//prop shaft 1
	glRotated(-90, 1.0, 0.0, 0.0);
	glTranslated(0.0, -11, 0.0);
	gluCylinder(quadObj, 0.25, 0.25, 5.0, 20, 30);
	glPopMatrix();

	glPushMatrix();//prop shaft 2
	glRotated(90, 1.0, 0.0, 0.0);
	glTranslated(0.0, 11, 0.0);
	gluCylinder(quadObj, 0.25, 0.25, 5.0, 20, 30);
	glPopMatrix();

	glPushMatrix();//prop pivot	
	glTranslated(0.0, 0.0, 11.0);
	glutSolidSphere(0.5,20,30);
	glPopMatrix();

}

void keyboard(int key, int x, int y) {
	if (GLUT_KEY_DOWN) {
		switch (key) {		
		case GLUT_KEY_LEFT://pan view left
			pan -=5;
			break;
		case GLUT_KEY_RIGHT://pan view right
			pan += 5;
			break;

		case GLUT_KEY_DOWN://zoom out
			if (feild >= -25) {
				feild -= 1.0;
			}
			break;

		case GLUT_KEY_UP://zoom in
			feild += 1.0;
			cout << feild << endl;
			break;
		}//switch
	}
	glutPostRedisplay();
}//keyboard

void keyboard1(unsigned char key, int x, int y) {
	if (GLUT_KEY_DOWN) {
		switch (key) {
		case 'f':		//increase engine speed
			dt += 0.01;
			dt2 += 0.1;
			dt3 += 0.6;
			cyl_height += 0.01;
			break;
		case 's':  //decrease engine speed
			if (theta >= 0 && cyl_height >= 0.01) {
				dt -= 0.01;
				dt2 -= 0.1;
				dt3 -= 0.6;
				cyl_height -= 0.01;
			}

			break;
		case 'x': //stop/kill engine
			dt = 0;
			dt2 = 0;
			dt3 = 0;
			cyl_height = 0;
			break;
		}
	}
	glutPostRedisplay();
}//keyboard1

void idle(void) {
	if (theta >= 360) {//crank arm rotation
		axis = (axis + 1) % 2;
	}
	theta = (theta < 360) ? theta + dt : dt;
	if (theta2 >= 360) {//propeller crank rotation
		axis = (axis + 1) % 2;
	}
	theta2 = (theta2 < 360) ? theta2 + dt2 : dt2;
	if (theta3 >= 360) {//propeller rotation
		axis = (axis + 1) % 2;
	}
	theta3 = (theta3 < 360) ? theta3 + dt3 : dt3;
	if (move_up) {//cylinder type 1 move up
		y_cyl += cyl_height;
	}
	else {//cylinder type 1 move down
		y_cyl -= cyl_height;
	}

	if (move_up2) {//cylinder type 2 move up
		y_cyl2 += cyl_height;
	}
	else {//cylinder type 2 move down
		y_cyl2 -= cyl_height;
	}
	glutPostRedisplay();
}//idle

void display(void) {
	if (y_cyl <= 4.9 && !move_up) {//set cylinder 1 up flag true
		move_up = true;
	}
	if (y_cyl >= 7.9 && move_up) {
		move_up = false;
	}

	if (y_cyl2 <= 4.9 && !move_up2) {//set cylinder 2 up flag true
		move_up2 = true;
	}
	if (y_cyl2 >= 7.9 && move_up2) {
		move_up2 = false;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(100, 1, 2, 40);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0f, feild);//move the model veiw out by "feild" variable
	glRotatef(30.0f, 1.0f, 0.0f, 0.0f);//rotate model view 30 deg about the x-axis
	glRotatef(pan, 0.0f, 1.0f, 0.0f);//rotate model view by variable "pan" about the y-axis
	
	glPushMatrix();//push1
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, grey_diff);
	
	GLUquadricObj * quadObj1;
	quadObj1 = gluNewQuadric();
	gluQuadricDrawStyle(quadObj1, GL_FILL);
	glPushMatrix();
	glTranslatef(0.0, -10.0, 0.0);
	glRotated(90, 1.0, 0.0, 0.0);
	gluDisk(quadObj1,0.0,10.0,40,60);//display disk under engine
	glPopMatrix();
		
	create_cyl(deg1, y_cyl, 1.0);//cyl 1
	glPopMatrix();

	glPushMatrix();
	create_cyl(deg2, y_cyl2, -1.0);//cyl 2
	glPopMatrix();

	glPushMatrix();
	create_cyl(deg1, y_cyl, -4.0);//cyl 3
	glPopMatrix();

	glPushMatrix();
	create_cyl(deg2, y_cyl2, 4.0);//cyl 4
	glPopMatrix();

	glPushMatrix();
	create_cyl(deg1, y_cyl, 7.0);//cyl 5
	glPopMatrix();

	glPushMatrix();
	create_cyl(deg2, y_cyl2, -7.0);//cyl 6
	glPopMatrix();

	glPushMatrix();
	create_prop();//create the propeller
	glPopMatrix();

	glPushMatrix();
	create_crank();//creates the crank shaft

	glPopMatrix();
	glutSwapBuffers();
}//display

void main(int argc, char * * argv) {
	cout << "F - speed up engine." << endl;
	cout << "S - slow down engine. (NOTE: WHEN CYLINDERS STOP, ENGINE IS IDLE)" << endl;
	cout << "X - STOP the engine immediately." << endl;
	cout << "UP ARRROW - Zoom in." << endl;
	cout << "DOWN ARROW - Zoom out." << endl;
	cout << "LEFT ARROW - Rotate view left." << endl;
	cout << "RIGHT ARROW  - rotate view right." << endl;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(300, 200);
	glutCreateWindow("ENIGINE SIMULATOR");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue_diff);
	glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, back_amb_diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 75);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard1);
	glutSpecialFunc(keyboard);
	glutIdleFunc(idle);
	glutMainLoop();
}//main


 //ANGELO ZAMUDIOCS 368 SUMMER 15'

