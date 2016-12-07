#include<glut.h>
#include<math.h>

void cafe(void) {	// 	800*510 window created
	int x = 15;
	int y = 0;
	int t;		//temporary integer to hold value of x;
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_QUADS);		//function call to draw GL_QUADS, draws 
							//quadrilaterals connecting 4 specified coordinates
	for (int i = 0; i < 10; i++){ //for loop initiated for the #of squares in a column
		t = x;
		if (i % 5 < 2) {//first 3 squares are shifted left 20 pixels each
			x += 20;
		}
		else {//the next 3 are shifted right 20 pixels each
			x -= 20;		//alternates until all rows have been drawn
		}	
		for (int j = 0;j < 50; j++) { //for loop initiated for the # squares in a row
			glColor3f(0.0, 0.0, 0.0);//color is set to black black
			glVertex2i(t + j, y); 	//coordinates of the square to be drawn with the x_axis
									//offset by j;
			glVertex2i(t + 50 + j, y); //next x is offset by 50 +j;
			glVertex2i(t + 50 + j, y + 50);//next y offset by 50;
			glVertex2i(t + j, y + 50);//last x offset by j and y offset by 50
			t += 100;  //t is shifted over by 100 pixels leaving a white square
					   //between each black square
		}//for j
		y += 50; //y coordinated shifted up by 50 pixels after each row
		glColor3f(0.5, 0.5, 0.5);//color is now set to grey;
		glVertex2i(0, y);	//grey line is created (800 x 2) simulating "mortar"
		glVertex2i(800, y);
		glVertex2i(800, y+2);
		glVertex2i(0, y+2);
		y += 2;		
	}//for i
	glEnd();					//glEnd() is called to finish close the glBeigin call;
	glFlush();					//glFlush is called to force all remaining instructions to be executed.
}//CAFE_WALL


void main(int argc, char** argv) {
	int width = 800;						
	int height = 510;
	glutInit(&argc, argv); //initialize the  GLUT library
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//allows for display on single buffer window
												//glut_rgb shows colors red blue green and an alpha
	glutInitWindowSize(width, height);		//function call that sets the window size using (x,y)
	glutInitWindowPosition(200, 100);		//function call that sets the position of the window on the screen
											//this case position 200(X-AXIS) and 100(Y-AXIS)
	glutCreateWindow("Cafe Wall Illusion");	//function call to set title of the widow
	
	glClearColor(1.0, 1.0, 1.0, 0.0);	//grey--->CAFE WALL
	gluOrtho2D(0.0, width, 0.0, height);
	glutDisplayFunc(cafe);	//function call to display the cafe display function.
	glutMainLoop();		//glut event processing loop

}//main

//ANGELO ZAMUDIO CS 368 SUMMER 2015