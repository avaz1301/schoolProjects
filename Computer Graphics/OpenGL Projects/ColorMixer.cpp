//Angelo Zamudio
//CS 368 SUMMER 2015
//Project 2: Color Mixer

#include<glut.h>
#include<string>
#include<iostream>
using namespace std;
//NOTE: Throughout my project, the variables shade are meant to represent the 
//		current "SHADE" of RGB that a variable may represent
class SliderTab {
	public:
		int x;			//intial x
		int y;			//inital y
		char tab_color;			//char either r, g or b
		bool engaged = false;	//bool to check if SliderTab is active

		/*Constructor for SliderTab takes in and sets inital postion x,y
		and sets character representing color*/ 
		SliderTab(int pos_x, int pos_y, char color) {
			x = pos_x;
			y = pos_y;
			tab_color = color;
		}
		/*This function creates the SliderTab object checks char color
		then sets verticies for tab based on the x and y passed in.
		SliderTab is 30 x 20*/
		void create() {
			if (engaged) {
				glColor3f(0.5, 0.5, 0.5);
			}else if (tab_color=='r') {
				glColor3f(1.0, 0.0, 0.0);
			}else if (tab_color == 'g') {
				glColor3f(0.0, 1.0, 0.0);
			}
			else if (tab_color == 'b') {
				glColor3f(0.0, 0.0, 1.0);
			}
			glBegin(GL_QUADS);
			glVertex2i(x, y);
			glVertex2i(x+30, y);
			glVertex2i(x+30, y+20);
			glVertex2i(x, y+20);
			glEnd();
		}		
};//SliderTab

//This function displays the value for R, G,and B from 0-255
//float colr: incoming float value for red green or blue.
//int pos: initial x position for number to be printed.
void colorNumDisplay(float colr, int pos) {
	int temp = colr * 255;
	string current_value = to_string(temp);
	for (int i = 0; i < current_value.length(); i++) {
		glRasterPos2i(pos, 560);    //function call sets initial raster position.
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, current_value.at(i)); //pulls char from string at position i
		pos += 12;  //shifts next initial position over by 12.
	}
};//ColorValue

SliderTab r1(85, 262, 'r');
SliderTab g1(185, 262, 'g');
SliderTab b1(285, 262, 'b');
int width = 800.f, height = 800.f;			//window dimensions
float shade_r = 0.0f, shade_g = 0.0f, shade_b = 0.0f; //slider values for RED, BLUE, GREEN
float inter_l1 = 0.0f, inter_l2 = 0.0f, inter_l3 = 0.0f;// values for left side of interpolation box
float inter_r1 = 0.0f, inter_r2 = 0.0f, inter_r3 = 0.0f;// values for right of interpolation box
float color_array[3]; //float array to hold RGB values from readPixel function.

//This function sets up the contents of the display window properly to the user.
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);//set red line length 256
	glVertex2i(100, 272);
	glVertex2i(100, 528);

	glColor3f(0.0, 1.0, 0.0);//set green line length 256
	glVertex2i(200, 272);
	glVertex2i(200, 528);

	glColor3f(0.0, 0.0, 1.0);//set blue line length 256
	glVertex2i(300, 272);
	glVertex2i(300, 528);
	glEnd();

	glBegin(GL_QUADS);
	//sets viewing window color based on RGB SliderTab position
	glColor3f(shade_r, shade_g, shade_b);
	glVertex2i(400, 700);//sets size for color mixer viewing window
	glVertex2i(700, 700);//300 x 300
	glVertex2i(700, 400);
	glVertex2i(400, 400);
	//Creates color interpolation window 300 x 75
	glColor3f(inter_l1, inter_l2, inter_l3);//sets RGB for left
	glVertex2i(400, 300);
	glVertex2i(400, 225);
	glColor3f(inter_r1, inter_r2, inter_r3);//sets RGB for right
	glVertex2i(700, 225);
	glVertex2i(700, 300);
	glEnd();
	//RGB SliderTabs creates after so they lay on top on their respective lines.
	r1.create();
	g1.create();
	b1.create();

	glColor3f(1.0, 1.0, 1.0);//sets color FOR R G B characters to white
	glRasterPos2i(92,230);//initial position for 'R'
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'R');

	glRasterPos2i(192,230);//initial position for 'G' 
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'G');
	
	glRasterPos2i(292,230);//initial position for 'B'
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'B');
	//calls colorNumDisplay passing in current R G or B float value and 
	//initial position for the number display.
	colorNumDisplay(shade_r,89);
	colorNumDisplay(shade_g,189);
	colorNumDisplay(shade_b,289);
	glutSwapBuffers();
}//display

//This function checks for activity from the keyboard defining a specific 
//action to be preformed depending on key that is pushed.
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		//"r" pressed:sets color for right of interpolation window to current slider RGB value
		case 'r':
			inter_r1 = shade_r;
			inter_r2 = shade_g;
			inter_r3 = shade_b;
			break;
		//"l" pressed: sets color for left of interpolation window to current slider RGB value
		case 'l':
			inter_l1 = shade_r;
			inter_l2 = shade_g;
			inter_l3 = shade_b;
			break;	
	}//switch
	glutPostRedisplay();
}//keyboard

//This function is tailored for check the y value for each occasion at which the left mouse button is pressed down.
//int x and y: position of the mouse
//SliderTab current_tab: SliderTab object that is being checked
//float shade: respective shade variable corresponding to current SliderTab
void sliderTabClick(int x, int y, SliderTab &current_tab, float &shade) {
	float current_shade = 0.f;
	//when mouse is clicked within a SliderTab then that tab is set to engaged.
	if( (height-y-1)>current_tab.y && (height-y-1)<current_tab.y+20 && x>current_tab.x && x<current_tab.x + 30  ){
		current_tab.engaged = true;
		return;
	}
	//if mouse is clicked within the color line range, tab is snapped to mouse position.
	//respective shade is set to corresponding value and tab is engaged
	else if (y > 270 && y <= 529) {
		current_tab.y = ((float)height - y - 10.f);
		current_shade = ((float)height - y - 272.f) / 256.f;
		current_tab.engaged = true;
		shade=current_shade;
	}
	//if mouse clicked in an area 10 pixels above the color line, tab is snapped to top
	//of the color line and color is set to max of color value independent of mouse position
	//tab not engaged
	else if (y < 271 && y > 260) {//TOP
		current_tab.y = ((float)height - 272.f - 10);
		current_shade = ((float)height - 271.f - 272.f) / 256.f;
		shade=current_shade;
	}//if mouse clicked in an area of 10 pixels below the color line, tab is snapped to bottom
	//and respective color set to 0 independent of mouse position
	else if (y > 529 && y <540) {//BOTTOM
		current_tab.y = ((float)height - 529.f - 10);
		current_shade = ((float)height - 529.f - 272.f) / 256.f;
		shade= current_shade;
	}//if mouse out of range of tab, tab is neither snapped or engaged.
	return;
}//sliderTabClick

//this function is called to set the color mixer window and the RGB slider tabs to the value of the 
//color that is clicked within the interpolation color window.
//takes in current mouse x and y position
void colorReset(int x, int y) { 
	glutSwapBuffers(); // buffer is swapped first to ensure that readPixel function reads the proper 
					   // buffer to return the proper desired color
	glReadPixels(x, y, 1, 1, GL_RGB,GL_FLOAT, color_array);//read the pixel at current mouse position 
	//in an area that is 1 x 1 and places RGB value into an array.
	r1.y = color_array[0] *256+272;//RGB slider tabs set to the values corresponding
	g1.y = color_array[1] *256+272;// to the color that was clicked.
	b1.y = color_array[2] *256+272;
	shade_r = color_array[0];//Color mixer window set to RGB value that was clicked.
	shade_g = color_array[1];
	shade_b = color_array[2];
}//colorReset

//This function checks for changes in the state of the mouse, change in position or button click.
void mouse(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:
		//if left mouse button is down
		if (state == GLUT_DOWN) {
			//within this x range check the red SliderTab obj.
			if (x > 84 && x < 114) {
				sliderTabClick(x, y, r1, shade_r);//calls function to determine proper action
			}
			//within this x range check the green SliderTab obj.
			else if (x > 184 && x < 214) {
				sliderTabClick(x, y, g1, shade_g);//calls function to determine proper action
			}
			//within this x range check the blue SliderTab obj.
			else if (x > 284 && x < 314) {
				sliderTabClick(x, y, b1, shade_b);//calls function to determine proper action
			}
			//if left button click within interpolation color window
			//colorReset function called passing in current mouse position
			else if (x > 400 && x < 700 && (height - y - 1)>225 && (height - y - 1) < 300) {
				colorReset(x,(height-y-1));
			}
		}
		else {//if left button is not click all tabs are set to false; not engaged.
			r1.engaged = false; b1.engaged = false; g1.engaged = false;
			//glutPostRedisplay();
		}
		break;
	}//switch
	glutPostRedisplay();
}//mouse

//this function is called to check and set the proper y positions for a specified slider tab while the 
//left mouse button is held down and in motion.
float sliderTab(int x, int y, SliderTab &current_tab) {
	float current_shade = 0.f; // hold initial slider value
	//is slider tab is engaged within the color line range then slider tab is 
	//set to the y position of the mouse as it moves and shade is set accordingly.
	if (y > 270 && y <= 529) {
		current_tab.y = ((float)height - y - 10);
		current_shade = ((float)height - y - 272.f) / 256.f;
	}
	//if slider tab is engaged and mouse moves past the max range of the color line, 
	//tab is set to max float value and max slider y position
	else if (y < 271) {
		current_tab.y = ((float)height - 272.f - 10);
		current_shade = ((float)height - 271.f - 272.f) / 256.f;
	}
	//if slider tab is engaged and mouse moves below minimum range of color line,
	//tab float value and y position are both set to zero.
	else if (y > 529) {
		current_tab.y = ((float)height - 529.f - 10);
		current_shade = ((float)height - 529.f - 272.f) / 256.f;
	}//if none of the above occurs the current shade of the slider is returned unchanged.
	return current_shade;
}//sliderTab

//THis function follows mouse movement taking in its current x and y value as it changes.
void motion(int x, int y) {
	//within this x range check the red SliderTab obj.
	if (x > 49 && x < 151 && r1.engaged) {
		shade_r = sliderTab(x, y, r1);//calls sliderTab function to set proper float value
	}
	//within this x range check the green SliderTab obj.
	else if (x > 149 && x < 251 && g1.engaged) {
		shade_g = sliderTab(x, y, g1);//calls sliderTab function to set proper float value
	}
	//within this x range check the blue SliderTab obj.
	else if (x > 149 && x < 351 && b1.engaged) {
		shade_b = sliderTab(x, y, b1);//calls sliderTab function to set proper float value
	}
	glutPostRedisplay();
}//motion

void main(int argc, char ** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(width, height);//window dimension
	glutInitWindowPosition(50, 100);  //initial window position on screen
	glutCreateWindow("COLOR MIXER");//window title
	glClearColor(0.3, 0.3, 0.3, 0.0);//window color set to grey
	glColor3f(1, 1, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, 0, height);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//following glut function call their respective/appropriate functions
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutMainLoop();
}//main

//Angelo Zamudio CS 368 Summer 15'