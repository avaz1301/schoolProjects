#include<glut.h>
#include<math.h>

void pyramid(void) {		// 	500*500 window created
	int max = 500;
	float  rate_change = 0.002;
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_QUADS);		//function call to draw GL_QUADS, draws 
							//quadrilaterals connecting 4 specified coordinates
	for (int i = 0; i <= 250;i++) { //for loop set to draw the square until middle of window is reached
		glColor3f(rate_change - .2, rate_change - .2, rate_change); 
		//color is initialized at (.002,.002,.002) and decreased by .2 for each square creating effect
		glVertex2i(i, i);	//square is then drawn starting out at max x and max y
							//each following square is then deceased by one pixel until x=250,y=250
		glVertex2i(max - i, i);
		glVertex2i(max - i, max - i);
		glVertex2i(i, max - i);
		rate_change += 0.002; //rate of color change increased by .002
	}//for
	glEnd();		//glEnd() is called to finish close the glBeigin call;
	glFlush();		//glFlush is called to force all remaining instructions to be executed.
}//PYRAMID

void main(int argc, char** argv) {
	int width = 500;
	int height = 500;
	glutInit(&argc, argv); //initialize the  GLUT library
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//allows for display on single buffer window
												//glut_rgb shows colors red blue green and an alpha
	glutInitWindowSize(width, height);		//function call that sets the window size using (x,y)
	glutInitWindowPosition(200, 100);		//function call that sets the position of the window on the screen
											//this case position 200(X-AXIS) and 100(Y-AXIS)
	glutCreateWindow("Pyramid Illusion");	//function call to set title of the widow	
	glClearColor(1.0, 0.0, 0.0, 0.0);	
	gluOrtho2D(0.0, width, 0.0, height);
	glutDisplayFunc(pyramid);	//function call to display the pyramid display function.
	glutMainLoop();	//glut event processing loop
}//main
//ANGELO ZAMUDIO CS 368 SUMMER 2015