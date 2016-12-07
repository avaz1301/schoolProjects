#include<glut.h>
#include<math.h>

void hermann(void) {	//650*650 window created
	int x = 25;
	int y = 25;
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_QUADS);		//function call to draw GL_QUADS, draws 
							//quadrilaterals connecting 4 specified coordinates
	glColor3f(0.0, 0.0, 0.0);  //color is set to black
	for (int i = 0; i <= 5; i++) {   //for loop for the # of rows
		for (int j = 0;j <= 650; j += 125) {	//for loop to properly space the 5 square in each row
			glVertex2i(x + j, y);		//draw a 100*100 square ..... offset x by j; 
			glVertex2i(x + 100 + j, y);	//x shifted right by 100+j
			glVertex2i(x + 100 + j, y + 100);//x shifted by 100+j, y shifted by 100
			glVertex2i(x + j, y + 100);//x shifted by j...y shifted by 100;
		}//for j
		y += 125;  //after each row y pointer is moved up by 125 to start new row
	}//for i
	glEnd();	//glEnd() is called to finish close the glBeigin call;
	glFlush();	//glFlush is called to force all remaining instructions to be executed.
}//HERMANN
void main(int argc, char** argv) {
	int width = 650;
	int height = 650;
	glutInit(&argc, argv); //initialize the  GLUT library
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//allows for display on single buffer window
												//glut_rgb shows colors red blue green and an alpha
	glutInitWindowSize(width, height);		//function call that sets the window size using (x,y)
	glutInitWindowPosition(200, 100);		//function call that sets the position of the window on the screen
											//this case position 200(X-AXIS) and 100(Y-AXIS)
	glutCreateWindow("Hermann Illusion");	//function call to set title of the widow
	
	glClearColor(1.0, 1.0, 1.0, 0.0);	//white
	gluOrtho2D(0.0, width, 0.0, height);
	glutDisplayFunc(hermann);	//function call to display the hermann display function.
	glutMainLoop();	//glut event processing loop
}//main
//ANGELO ZAMUDIO CS 368 SUMMER 2015