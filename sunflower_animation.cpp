#include<stdio.h>
#include<stdlib.h>
#include<glut.h>
#include<GL/glu.h>
#include<GL/gl.h>
#define SUNFLOWER 1
#define SUNFLOWER_STEM_WITH_LEAVES 2

/*This is the new line inserted*/
/*This is the second line */
int n;
int paused = 0;//initially don't pause.
short int direction = 1;//0 - clockwise, 1 - anti-clockwise.
static float year=0.0f;
//static int rotateAngle = 0;
//int light = 1;
#define MAX_SUN_ROTATION_ANGLE 150
//#define FIRST_QUARTER (1/4)
#define SUN_MORNING_QUARTER ((1.0/4.0)*MAX_SUN_ROTATION_ANGLE)
#define SUN_EVENING_QUARTER ((1-(1.0/4.0))*MAX_SUN_ROTATION_ANGLE)
//GLfloat position[]={-2.0,-2.0,-2.0,1.0};
GLfloat scalex = 0.0,scaley = 0.0, scalez = 0.0;
float sunRotSpeed = 0.1;
//float sunRotSpeed = 1;
float sunflower_max_scale_factor = 2.5;
float ortho2d_x_left = -7.0, ortho2d_x_right = 7.0;
float ortho2d_y_bottom = -7.0, ortho2d_y_top = 7.0;

int mainWindowId, helpWindowId;

void idle(void)
{
	//year=(year-1)%150;
	//year = year - 0.25;
	if(! paused)
	{
		if(direction)
		{
			if(-year >= MAX_SUN_ROTATION_ANGLE)
				year = 0;//Start the SUN from original position, after rotating it by 150 degrees..

			//year = year - 0.005;//This is negative for anti-clockwise rotation of SUN
			year = year - sunRotSpeed;//This is negative for anti-clockwise rotation of SUN
			//rotateAngle = (int)(year)%MAX_SUN_ROTATION_ANGLE;//This is negative for anti-clockwise rotation of SUN
		}
		else
		{
			if(year >= 0)
				year = -MAX_SUN_ROTATION_ANGLE;//Start the SUN from original position, after rotating it by 150 degrees..

			//year = year - 0.005;//This is negative for clockwise rotation of SUN
			year = year + sunRotSpeed;//This is negative for clockwise rotation of SUN
			//rotateAngle = (int)(year)%MAX_SUN_ROTATION_ANGLE;//This is negative for anti-clockwise rotation of SUN
		}
	}
	glutPostRedisplay();
}


void draw_sun()
{
	//to rotate the solid sphere sun
	//glColor3ub(255,255,0);	
	glColor3ub(255,40,40);
	glPushMatrix();
	glScalef(1,1,0);
    glRotatef((GLfloat)year,0.0,0.0,1.0);
	//glRotatef((GLfloat)rotateAngle,0.0,0.0,1.0);
	glTranslatef(ortho2d_x_left,1.5,0.0);	
	glutSolidSphere(0.3,30,8);

	//for light radiation effect of sun..
	float angle=360.0/9;
	glColor3ub(255,255,0);
	//glColor3ub(255,40,40);

	int i = 0;
	for(i = 0;i<9;i++)
	{
		//For inner triangles..
		glPushMatrix();//current status saving
		glRotatef((360.0/9)*i,0.0,0.0,1.0);
		glTranslatef(0.05,0.0,0.0);
		glBegin(GL_TRIANGLES);
	   // glBegin(GL_LINE_LOOP);
		glVertex2f(0.0,0.05);
		//glVertex2f(1,0.0);
		glVertex2f(0.5,0.0);
		glVertex2f(0.0,-0.05);
		glEnd();
		glPopMatrix();
		//glFlush();
	}

	glPopMatrix();

	//glFlush();
}


void draw_sunflowers()
{
		//To draw sunflower...
	
	//list which draws leaves and stem..
	if(! paused)
	{
		//if(-rotateAngle<=(SUN_MORNING_QUARTER))
		if(-year<=(SUN_MORNING_QUARTER))
		{
			//glColor3ub(255,40,40);
			if(direction)
			{
				scalex += (sunflower_max_scale_factor /(SUN_MORNING_QUARTER/sunRotSpeed));
				scaley += (sunflower_max_scale_factor /(SUN_MORNING_QUARTER/sunRotSpeed));
			}
			else
			{
				scalex -= (sunflower_max_scale_factor /(SUN_MORNING_QUARTER/sunRotSpeed));
				scaley -= (sunflower_max_scale_factor /(SUN_MORNING_QUARTER/sunRotSpeed));
			}
			//scalez = 0.1;
		}
		//else if(-rotateAngle>(SUN_MORNING_QUARTER ) && -rotateAngle<(SUN_EVENING_QUARTER ))
		else if(-year>(SUN_MORNING_QUARTER ) && -year<(SUN_EVENING_QUARTER ))
		{
			scalex = sunflower_max_scale_factor;
			scaley = sunflower_max_scale_factor;
			//glColor3ub(240,31,9);
		}
		//else if(-rotateAngle>(SUN_EVENING_QUARTER ))
		else if(-year>(SUN_EVENING_QUARTER ))
		{
			if(direction)
			{
				scalex -= (sunflower_max_scale_factor /(SUN_MORNING_QUARTER/sunRotSpeed));
				scaley -= (sunflower_max_scale_factor /(SUN_MORNING_QUARTER/sunRotSpeed));
			}
			else
			{
				scalex += (sunflower_max_scale_factor /(SUN_MORNING_QUARTER/sunRotSpeed));
				scaley += (sunflower_max_scale_factor /(SUN_MORNING_QUARTER/sunRotSpeed));
			}
			//glColor3ub(215,65,28);
		}
	}//if not paused.

	//To draw 5 sunflowers
	int sunflowers_loc = 0;
	for(sunflowers_loc=ortho2d_x_left; sunflowers_loc<=ortho2d_x_right; sunflowers_loc+=1)
	{
		glPushMatrix();
		glTranslatef(sunflowers_loc,(sunflowers_loc%2)?-3:0,0);
		glScalef(scalex,scaley,0.0);
		glCallList(SUNFLOWER_STEM_WITH_LEAVES);
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(sunflowers_loc,(sunflowers_loc%2)?-3:0,0);
		glRotatef((GLfloat)year,0.0,1.0,1.0);
		//glRotatef((GLfloat)rotateAngle,0.0,1.0,1.0);
		//glTranslatef(0,0,0);

		glRotatef(-90,0,01,0);
		glScalef(scalex,scaley,0.0);
		//To draw center of sunflower..
		glCallList(SUNFLOWER);
		glPopMatrix();
		//glFlush();
	}//end of for loop...

}


void DrawBitmapText(char *string,float x,float y,float z)
{
	char *c;
	glRasterPos3f(x,y,z);
	for(c=string;*c!=0;c++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*c);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1,0.5,1,1.0);
	//Sky
	glColor3ub(35,87,207);
	//glPointSize(50);
	glBegin(GL_POLYGON);
	glVertex2f(ortho2d_x_left,ortho2d_y_top);
	glVertex2f(ortho2d_x_right,ortho2d_y_top);
	glVertex2f(ortho2d_x_right,0);
	glVertex2f(ortho2d_x_left,0);
	//glVertex2f(0.0,0.0);
	//glVertex2f(0.0,0.5);
	glEnd();

	//Greenery
	glColor3ub(126,172,73);
	glBegin(GL_POLYGON);
	glVertex2f(ortho2d_x_left,ortho2d_y_bottom);
	glVertex2f(ortho2d_x_right,ortho2d_y_bottom);
	glVertex2f(ortho2d_x_right,0);
	glVertex2f(ortho2d_x_left,0);
	glEnd();

	draw_sunflowers();

	draw_sun();

	////To draw grass..
	glColor3ub(180,255,0);
	//for(int g=ortho2d_x_right;g>=ortho2d_x_left;g--)
	for(float g=ortho2d_x_left+0.225;g<=0;g+=1)
	{

		glPushMatrix();
        glTranslatef(g,((int)g%2)?-4:-6,0);
		//glTranslatef(ortho2d_x_left+g,0,0);

		glBegin(GL_LINES);
		glVertex2f(0.0,0.5);
		glVertex2f(0.0,0.0);
		glVertex2f(-0.5,0.25);
		glVertex2f(0.0,0.0);
		glVertex2f(0.5,0.25);
		glVertex2f(0.0,0.0);
		glVertex2f(0.0,0.5);
		glEnd();
		
		glPopMatrix();

		glPushMatrix();
        glTranslatef(abs(g),(int)g%2?-4:-6,0);
		//glTranslatef(ortho2d_x_left+g,0,0);

		glBegin(GL_LINES);
		glVertex2f(0.0,0.5);
		glVertex2f(0.0,0.0);
		glVertex2f(-0.5,0.25);
		glVertex2f(0.0,0.0);
		glVertex2f(0.5,0.25);
		glVertex2f(0.0,0.0);
		glVertex2f(0.0,0.5);
		glEnd();
		
		glPopMatrix();
	}
////to draw clouds.....
//	glColor3f(1,1,1);
//	for(int i=0;i<4;i++)
//	{
//	glPushMatrix();
//	//glRotatef(45,1,0,0);
//	glTranslatef(0.1*i,6.0,0);
//	//glRotatef(30,0,0,1);
//
//	glutSolidSphere(0.3,30,12);
//	glPopMatrix();
//	}

	glFlush();

	glutSetWindow(helpWindowId);
	glutPostRedisplay();
}//end of display()




void display1(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1,1,1,0);
	glColor3ub(126,172,73);
	int textDisplacement = 1;
	DrawBitmapText("\"Sunflower Animation\" Project Created By, ",ortho2d_x_left,ortho2d_y_top - textDisplacement,0);
	textDisplacement+=2;
	DrawBitmapText("           Sindhu Shree B.N   (1VI13CS107)   and ",ortho2d_x_left,ortho2d_y_top - textDisplacement,0);textDisplacement++;
	DrawBitmapText("           Mounika S.K          (1VI13CS084)",ortho2d_x_left,ortho2d_y_top - textDisplacement,0);

	textDisplacement+=2;
	glColor3f(0,0,1);
	if(paused)
		DrawBitmapText("Currently the Animation is PAUSED. You can resume it.",ortho2d_x_left, ortho2d_y_top - textDisplacement, 0);
	else
		DrawBitmapText("Currently the Animation is RUNNING. You can pause it",ortho2d_x_left, ortho2d_y_top - textDisplacement, 0);

	textDisplacement+=2;
	glColor3f(0,0,1);
	if(direction)
		DrawBitmapText("Currently Sun is rotating in CLOCKWISE direction",ortho2d_x_left, ortho2d_y_top - textDisplacement, 0);
	else
		DrawBitmapText("Currently Sun is rotating in ANTI-CLOCKWISE direction",ortho2d_x_left, ortho2d_y_top - textDisplacement, 0);

	textDisplacement+=2;
	glColor3f(1,0,0);
	DrawBitmapText("User Help Options.",ortho2d_x_left,ortho2d_y_top - textDisplacement,0);textDisplacement++;
	DrawBitmapText("Press \"P\" or \"p\" to Pause Animation.",ortho2d_x_left,ortho2d_y_top - textDisplacement,0);textDisplacement++;
	DrawBitmapText("Press \"R\" or \"r\" to Resume Animation.",ortho2d_x_left,ortho2d_y_top - textDisplacement,0);textDisplacement++;
	DrawBitmapText("Press \"Q\" or \"q\" to Quit Animation",ortho2d_x_left,ortho2d_y_top - textDisplacement,0);

	glFlush();
	glutSwapBuffers();

	glutSetWindow(mainWindowId);
}

void initialize()
{
glNewList(SUNFLOWER_STEM_WITH_LEAVES,GL_COMPILE_AND_EXECUTE);
	//to draw stem...
	glColor3f(0.0,1.0,0.0);
	glPushMatrix();
	glRotatef(90,1.0,0.0,0.0);
	glutSolidCone(0.05,1,30,12);
	glPopMatrix();

	
	//to draw right leaf....
	//glColor3f(0.0,64,0.0);
	glColor3ub(0.0,128,0.0);
	glPushMatrix();
	glTranslatef(0.0,-0.7,0.0);
	glRotatef(135,0.0,0.0,1.0);
	//glTranslatef(0.0,-0.2,0.0);
	glBegin(GL_POLYGON);
	//int i;
	//for( i=0 ; i<10 ; i++)
    /*glVertex2f(0.1,-0.1);
	glVertex2f(-0.1,-0.9);
	glVertex2f(0.1,-0.9);
	glVertex2f(0.2,-0.9);*/
	glVertex2f(0.03,-0.05);
	glVertex2f(-0.03,-0.45);
	glVertex2f(0.03,-0.45);
	glVertex2f(0.07,-0.45);
	//glVertex2f(0.15,-0.1);
	glEnd();
	glPopMatrix();

	//left leaf..
	glColor3ub(0,128,0);
	glPushMatrix();
	glTranslatef(0.0,-0.9,0.0);
	glRotatef(-135,0.0,0.0,1.0);
	//glTranslatef(0.0,-0.2,0.0);
	glBegin(GL_POLYGON);
	//int i;
	//for( i=0 ; i<10 ; i++)
    glVertex2f(0.03,-0.05);
	glVertex2f(-0.03,-0.45);
	glVertex2f(0.03,-0.45);
	glVertex2f(0.07,-0.45);
	//glVertex2f(0.15,-0.1);
	glEnd();
	glPopMatrix();

glEndList();


glNewList(SUNFLOWER,GL_COMPILE_AND_EXECUTE);

	//Central circle
    glColor3f(0.9,0.27,0.0);
	glutSolidSphere(0.2,30,12);
	glFlush();
    
	int i=0;

	//glColor3f(0.87,0.84,0.0);
	//glBegin(GL_TRIANGLES);
 //  // glBegin(GL_LINE_LOOP);
	//glVertex2f(0.0,0.1);
	//glVertex2f(0.1,0.0);
	//glVertex2f(0.0,-0.1);
	//glEnd();

	float angle=360.0/n;

	glColor3ub(255,140,26);
	
	//for inner petals
	for(i = 0;i<9/*no_of_petals*/;i++)
	{
		//For inner triangles..
		glPushMatrix();//current status saving
		//glTranslatef(0.2,0.0,0.0);
		glRotatef((360.0/9)*i,0.0,0.0,1.0);
		glTranslatef(0.05,0.0,0.0);
		glBegin(GL_TRIANGLES);
	   // glBegin(GL_LINE_LOOP);
		glVertex2f(0.0,0.07);
		glVertex2f(0.07,0.0);
		glVertex2f(0.0,-0.07);
		glEnd();
		glPopMatrix();
		glFlush();
	}

	glColor3ub(255,255,4);
	//For outer petals..
	for(i = 0;i<n/*no_of_petals*/;i++)
	{
		////For inner triangles..
		//glPushMatrix();//current status saving
		////glTranslatef(0.2,0.0,0.0);
		//glRotatef(angle*i,0.0,0.0,1.0);
		////glTranslatef(0.2,0.0,0.0);
		//glBegin(GL_TRIANGLES);
	 //  // glBegin(GL_LINE_LOOP);
		//glVertex2f(0.0,0.1);
		//glVertex2f(0.1,0.0);
		//glVertex2f(0.0,-0.1);
		//glEnd();

		//For outer petals
		glPushMatrix();//current status saving
		//glTranslatef(0.2,0.0,0.0);
		glRotatef(angle*i,0.0,0.0,1.0);
		glTranslatef(0.2,0.0,0.0);
		glBegin(GL_TRIANGLES);
	   // glBegin(GL_LINE_LOOP);
		glVertex2f(0.0,0.1);
		glVertex2f(0.1,0.0);
		glVertex2f(0.0,-0.1);
		glEnd();
		glPopMatrix();

    }

	//For pollen grains
	glColor3ub(255,0,0);
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex2f(0,0);
	glEnd();
	//glBegin(GL_POINTS);
	int pt_angle = 360.0 / 9;
	for(i=0;i<9;i++)
	{
		//glVertex2f(0.0,0.1*i);
		//glVertex2f(0.0,-0.1*i);
		//glVertex2f(0.1*i,0.0);
		//glVertex2f(-0.1*i,0.0);
		//glVertex2f(0.13*i,0.1);
		//glVertex2f(-0.13,0.0*i);
		glPushMatrix();//current status saving
		//glTranslatef(0.2,0.0,0.0);
		glRotatef(pt_angle *i,0.0,0.0,1.0);
		glTranslatef(0.07,0.0,0.0);
		glBegin(GL_POINTS);
		glVertex2f(0,0);
		glEnd();
		glPopMatrix();

	}
	//glEnd();
	//glFlush();

	glEndList();
}

void myKeyboard(unsigned char key,int x,int y)
{
	//if(key=='Q'||key=='q') exit(0);
	switch(key)
	{
		case 'Q':
		case 'q':
			exit(0);
			break;
		case 'P':
		case 'p':
			paused = 1;
			break;
		case 'R':
		case 'r':
			paused = 0;
		default :
			break;
	}//end of switch-case..
}
 

void demo_menu(int id)
{
	switch(id)
	{
	  case 1:exit(0);
		  break;
	  case 2:paused=1;
		   break;
	  case 3:paused=0;
		   break;
	  case 4:
		  if(direction)
			  direction = 0;
		  else
			  direction = 1;
		  break;
	}
	glutPostRedisplay();
}


int main(int argc,char **argv)
{
	//printf("enter no of petals");
	//scanf("%d",&n);
	n = 20;//No of petals..
	if(direction)//if anti-clockwise..
		year=0;
	else
		year=-MAX_SUN_ROTATION_ANGLE;

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700,700);
	glutInitWindowPosition(0,0);
	mainWindowId = glutCreateWindow("SUNFLOWER ANIMATION");
	glutDisplayFunc(display);
	glClearColor(1.0,1.0,.0,1.0);
	glutIdleFunc(idle);
	glutCreateMenu(demo_menu);
	glutAddMenuEntry("QUIT",1);
	glutAddMenuEntry("PAUSE",2);
	glutAddMenuEntry("RESTART",3);
	glutAddMenuEntry("ClockWise/Anti-ClockWise",4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutKeyboardFunc(myKeyboard);
	gluOrtho2D(ortho2d_x_left,ortho2d_x_right,ortho2d_y_bottom,ortho2d_y_top);
	initialize();

	
	glutInitWindowSize(600,300);
	glutInitWindowPosition(720,400);
	helpWindowId = glutCreateWindow("Sunflower Animation About/Help Window");
	gluOrtho2D(ortho2d_x_left,ortho2d_x_right,ortho2d_y_bottom,ortho2d_y_top);
	glClearColor(1.0,1.0,1.0,1.0);
	glutDisplayFunc(display1);


	//glutSetWindow(mainWindowId);
	glutMainLoop();
}