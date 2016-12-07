#include<glut.h>
#include<math.h>

void hering(void) {		//600*300 window created
	int tleft = -100;		//integer variables holding starting values of 
	int bright = 700;		//the line on he x-axis.
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);	//sets the starting drawing colour to blue.
	glBegin(GL_LINES);		// call to function glBegin calling GL_LINES as argument.
	glVertex2i(tleft, 300);	//set first point from which line will drawn at topmost pixel 100 pixels 
							//to the left of the viewing window.
	glVertex2i(bright, 1);	//set first end point to be at the bottom most pixel 100 pixels 
							//to the right of the viewing window.
	for (int i = 0;i <= 16;i++) {  //for loop that is set to draw 16 evenly spaced intersecting lines
		glVertex2i(tleft, 300);		
		glVertex2i(bright, 1);
		tleft += 50;		//after each line drawn we then shift the left starting point 50 pixels to the right 
		bright -= 50;		//the right pointer is shifted to the left 50 pixel
	}
	glColor3f(0.0, 0.0, 0.0);	//after intersecting lines are drawn color is changed to black
	glVertex2i(1, 90);			//two horizontal lines are then drawn at an equal distance 
	glVertex2i(599, 90);		//above and below the middle one at y=90 the other at y=210
	glVertex2i(1, 210);
	glVertex2i(599, 210);
	glEnd();					//glEnd() is called to finish close the glBeigin call;
	glFlush();					//glFlush is called to force all remaining instructions to be executed.
}//HERING
void main(int argc, char** argv) {
	int width = 600;			
	int height = 300;
	glutInit(&argc, argv); //initialize the  GLUT library
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//allows for display on single buffer window
												//glut_rgb shows colors red blue green and an alpha
	glutInitWindowSize(width, height);		//function call that sets the window size using (x,y)
	glutInitWindowPosition(200, 100);		//function call that sets the position of the window on the screen
											//this case position 200(X-AXIS) and 100(Y-AXIS)
	glutCreateWindow("Window of Illusions");	//function call to set title of the widow
	glClearColor(1.0, 1.0, 1.0, 0.0);	//Sets the background colour to white
	gluOrtho2D(0.0, width, 0.0, height);	//function call to set our display window size
											//want it to be the same as the window size, but not always the case.
	glutDisplayFunc(hering);	//function call to display the hering display function.
	glutMainLoop(); //glut event processing loop	
}//main
//ANGELO ZAMUDIO CS 368 SUMMER 2015