#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <glut.h>
#include<glaux.h>
#include<math.h>
#include <iostream>
//////////////////////////////////////////////////////////////////////////////// 
#define PI 3.1416
float spin = 0.0;
float legLeft =0.0;
float legRight=0.0;
float zz=-10.0;
GLuint  texname;
//íÊã æÖÚ ãáÝ ÇáÕæÑÉ Ðæ ÇááÇÍÞÉ bmp
//  Ýí ãÌáÏ Çá debug 
// ÇáÎÇÕ ÈÇáãÔÑæÚ 
void LoadTexture(char *FileName ,  GLuint *ID)
	{

	AUX_RGBImageRec *TextureImage=new AUX_RGBImageRec();      
	memset(TextureImage,0,sizeof(void *)*1);            
	TextureImage = auxDIBImageLoad(FileName);

	glGenTextures(1, ID);      
	glBindTexture(GL_TEXTURE_2D,*ID);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA , TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);


	free(TextureImage->data);	
	free(TextureImage);  

	}
void init()
{
	glClearColor(1.0,1.0,1.0,1);
	glEnable(GL_DEPTH_TEST);
		LoadTexture("image.bmp" ,&texname);

		glutFullScreen();

}
void cordinate(GLfloat x,GLfloat y,GLfloat z)
{
	glPushMatrix();	
	glTranslatef(x, y, z);
	glBegin(GL_LINES); // CORDINATES
	glColor3f(1.0, 0.0, 0.0);
	//x
	glVertex3f(-5.0, 0.0, 0.0);
	glVertex3f(5.0, 0.0, 0.0);
	//y
	glColor3f(0.0, 1.0, 0.0);

	glVertex3f(0.0, -5.0, 0.0);
	glVertex3f(0.0, 5.0, 0.0);
	//z
	glColor3f(0.0, 0.0, 1.0);

	glVertex3f(0.0, 0.0, 5.0);
	glVertex3f(0.0, 0.0, -5.0);
	glEnd();
	glPopMatrix();
}
void circle(GLdouble rad)
{
	GLint points = 50;
	GLdouble delTheta = (2.0 * PI) / (GLdouble)points;
	GLdouble theta = 0.0;
	glBegin(GL_POLYGON);
	{
		for (int i = 0; i <= 50; i++, theta += delTheta)
		{
			glVertex2f(rad * cos(theta), rad * sin(theta));
		}
	}
	glEnd();
	//glutSolidSphere(rad, 100, 100);
}
void cloud(GLfloat x,GLfloat y,GLfloat z) {
	glColor3f(1.0, 1.0, 1.0);
	///Top_Left
	glPushMatrix();
	glTranslatef(x-2, y+2.5, z);
	circle(3);
	glPopMatrix();
	///Top_Right
	glPushMatrix();
	glTranslatef(x+2, y+2.5, z);
	circle(3);
	glPopMatrix();
	///Bottom_lift
	glPushMatrix();
	glTranslatef(x-4.0, y-1.0, z);
	circle(3);
	glPopMatrix();
	///Bottom_middle
	glPushMatrix();
	glTranslatef(x, y-1.5, z);
	circle(3);
	glPopMatrix();
	//Bottom_right
	glPushMatrix();
	glTranslatef(x+4.0, y-1.0, z);
	circle(3);
	glPopMatrix();
}
void sun(GLfloat x,GLfloat y,GLfloat z)
{
	glPushMatrix();
	glTranslatef(x,y,z);
	glColor3f(1.0,1.0,0.0);
	glutSolidSphere(5.0,100,100);
	glPopMatrix();
}
void rectangle(GLfloat x, GLfloat y, GLfloat z, GLfloat hight, GLfloat width, GLfloat depth)
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glBegin(GL_QUADS);
	//green color
	glColor3f(0.0, 1.0, 0.0);
	//front
	glVertex3f(width / 2.0, hight / 2.0, depth / 2.0);
	glVertex3f(-width / 2.0, hight / 2.0, depth / 2.0);
	glVertex3f(-width / 2.0, -hight / 2.0, depth / 2.0);
	glVertex3f(width / 2.0, -hight / 2.0, depth / 2.0);
	//back
	glVertex3f(width / 2.0, hight / 2.0, -depth / 2.0);
	glVertex3f(-width / 2.0, hight / 2.0, -depth / 2.0);
	glVertex3f(-width / 2.0, -hight / 2.0, -depth / 2.0);
	glVertex3f(width / 2.0, -hight / 2.0, -depth / 2.0);
	//right
	glVertex3f(width / 2.0, hight / 2.0, depth / 2.0);
	glVertex3f(width / 2.0, hight / 2.0, -depth / 2.0);
	glVertex3f(width / 2.0, -hight / 2.0, -depth / 2.0);
	glVertex3f(width / 2.0, -hight / 2.0, depth / 2.0);
	//left
	glVertex3f(-width / 2.0, hight / 2.0, depth / 2.0);
	glVertex3f(-width / 2.0, hight / 2.0, -depth / 2.0);
	glVertex3f(-width / 2.0, -hight / 2.0, -depth / 2.0);
	glVertex3f(-width / 2.0, -hight / 2.0, depth / 2.0);
	//top
	glVertex3f(width / 2.0, hight / 2.0, depth / 2.0);
	glVertex3f(width / 2.0, hight / 2.0, -depth / 2.0);
	glVertex3f(-width / 2.0, hight / 2.0, -depth / 2.0);
	glVertex3f(-width / 2.0, hight / 2.0, depth / 2.0);
	//bottom
	glVertex3f(width / 2.0, -hight / 2.0, depth / 2.0);
	glVertex3f(width / 2.0, -hight / 2.0, -depth / 2.0);
	glVertex3f(-width / 2.0, -hight / 2.0, -depth / 2.0);
	glVertex3f(-width / 2.0, -hight / 2.0, depth / 2.0);
	glEnd();
	glPopMatrix();
}
void cactuses(GLfloat x, GLfloat y, GLfloat z)
{
	glPushMatrix();
	glTranslatef(x, y, z);
	rectangle(x - 1.0, y, z, 6.0, 1.0, 1.0);
	rectangle(x, y, z, 1.0, 3.0, 1.0);
	rectangle(x + 1.0, y + 0.75, z, 2.0, 1.0, 1.0);
	glPopMatrix();
}
void cactuses1(GLfloat x, GLfloat y, GLfloat z)
{
	glPushMatrix();
	glTranslatef(x, y, z);
	rectangle(x, y, z, 6.0, 1.0, 1.0);
	rectangle(x, y, z, 1.0, 4.0, 1.0);
	rectangle(x + 1.50, y + 0.75, z, 1.50, 1.0, 1.0);
	rectangle(x - 1.750, y + 0.75, z, 2.50, 1.0, 1.0);
	glPopMatrix();
}
void Enviroment(GLfloat width,GLfloat hight,GLfloat depth)
{
	glPushMatrix();
	glTranslatef(0.0,0.0,0.0);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, texname);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0, 0.0); glVertex3f(-width,0.0, depth);
	glTexCoord2f(10.0, 0.0); glVertex3f(width, 0.0, depth);
	glTexCoord2f(10.0, 1.0); glVertex3f(width, 0.0, -depth);
	glTexCoord2f(0.0, 1.0); glVertex3f(-width,0.0, -depth);
	
	
	glEnd();
			glDisable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	//sky color
	glColor3f(51.0/255.0,204.0/255.0,1.0);
	//front
	glVertex3f(width, hight, depth);
	glVertex3f(-width, hight, depth);
	glVertex3f(-width, -hight, depth);
	glVertex3f(width, -hight, depth);
	//back
	glVertex3f(width, hight, -depth);
	glVertex3f(-width, hight, -depth);
	glVertex3f(-width, -hight, -depth);
	glVertex3f(width, -hight, -depth);
	//right
//	glColor3f(1.0 , 204.0 / 255.0, 1.0);
	glVertex3f(width, hight, depth);
	glVertex3f(width, hight, -depth);
	glVertex3f(width, -hight, -depth);
	glVertex3f(width, -hight, depth);
	//left
//	glColor3f(0.7 , 204.0 / 255.0, 1.0);
	glVertex3f(-width, hight, depth);
	glVertex3f(-width, hight, -depth);
	glVertex3f(-width, -hight, -depth);
	glVertex3f(-width, -hight, depth);
	//top
//	glColor3f(0.4, 204.0 / 255.0, 1.0);
	glVertex3f(width, hight, depth);
	glVertex3f(width, hight, -depth);
	glVertex3f(-width, hight, -depth);
	glVertex3f(-width, hight, depth);
	// desert color
	glColor3f(241.0/255.0,190.0/255.0,108.0/255.0);
	//bottom
	glEnd();
		
	

	glPopMatrix();
//////////////////////////////////////////
	// the sun 
	sun(0.0, hight/1.0 , -depth);
//////////////////////////////////////////
	//cloud back
	cloud(-width /1.25, hight / 1.5, -depth+1);
	cloud(-width / 2.25, hight / 3.0, -depth + 1);
	cloud(width / 1.25, hight / 1.5, -depth + 1);
	cloud(0 , hight / 1.75, -depth + 1);
	cloud(width / 2.25, hight / 3.0, -depth + 1);
//////////////////////////////////////////
	// the cactuses (ÇáÕÈÇÑÉ )
	cactuses1(-20.0, 1.0, -25.0);
	cactuses(20.0, 1.0, -25.0);
	cactuses1(-20.0, 1.0, 25.0);
	cactuses(20.0, 1.0, 25.0);
	cactuses1(+15.0, 1.0, -15.0);
	cactuses(-15.0, 1.0, -15.0);
	cactuses1(+15.0, 1.0, 15.0);
	cactuses(-15.0, 1.0, 15.0);
}
void rectangle2(GLfloat x, GLfloat y, GLfloat z, GLfloat hight, GLfloat width, GLfloat depth)
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glBegin(GL_QUADS);
	//white color
		glColor3f(244.0/255.0, 244.0/255.0, 244.0/255.0);
	//front
	glVertex3f(width / 2.0, 0.0 , depth / 2.0);
	glVertex3f(-width / 2.0,0.0, depth / 2.0);
	glVertex3f(-width / 2.0, -hight , depth / 2.0);
	glVertex3f(width / 2.0, -hight , depth / 2.0);
	
	//gray color
		glColor3f(200.0/255.0, 200.0/255.0, 200.0/255.0);

	//back
	glVertex3f(width / 2.0,0.0, -depth / 2.0);
	glVertex3f(-width / 2.0, 0.0, -depth / 2.0);
	glVertex3f(-width / 2.0, -hight , -depth / 2.0);
	glVertex3f(width / 2.0, -hight , -depth / 2.0);
	//right
	glVertex3f(width / 2.0, 0.0, depth / 2.0);
	glVertex3f(width / 2.0, -hight , depth / 2.0);
	glVertex3f(width / 2.0, -hight , -depth / 2.0);
	glVertex3f(width / 2.0, 0.0, -depth / 2.0);
	//left
	glVertex3f(-width / 2.0, 0.0, depth / 2.0);
	glVertex3f(-width / 2.0, -hight , depth / 2.0);
	glVertex3f(-width / 2.0, -hight , -depth / 2.0);
	glVertex3f(-width / 2.0, 0.0, -depth / 2.0);
	//top
	glVertex3f(width / 2.0,0.0, depth / 2.0);
	glVertex3f(width / 2.0, 0.0, -depth / 2.0);
	glVertex3f(-width / 2.0, 0.0, -depth / 2.0);
	glVertex3f(-width / 2.0, 0.0, depth / 2.0);
	//bottom
	glVertex3f(width / 2.0, -hight , depth / 2.0);
	glVertex3f(width / 2.0, -hight , -depth / 2.0);
	glVertex3f(-width / 2.0, -hight , -depth / 2.0);
	glVertex3f(-width / 2.0, -hight , depth / 2.0);
	glEnd();
	glPopMatrix();
}
void robotEyes(GLfloat x, GLfloat y, GLfloat z){

	glPushMatrix();
	glTranslatef(x, y, z);
	glutSolidSphere(0.20, 100, 100);
	glPopMatrix();
}
//void robotMouth(GLfloat x, GLfloat y, GLfloat z) {
//	glPushMatrix();
//	glTranslatef(x, y, z);
//	glutSolidCube(0.4);
//	glPopMatrix();
//}
void robotHead(GLfloat x, GLfloat y, GLfloat z)
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(spin, 0.0, 1.0, 0.0);

	rectangle2(x,y,z,1.0,2.0,1.0);//head
	glColor3f(0.0, 0.0, 0.0);
	robotEyes(x+0.5,y-0.250,z+0.5);
	robotEyes(x-0.5,y- 0.25,z+0.5);
	//mouth
	glLineWidth(1.0);
	glBegin(GL_LINES);
	glVertex3f(x-0.5, y-0.7, z+1.0);
	glVertex3f(x+0.5,y -0.7,z+ 1.0);
	glEnd();
	glLineWidth(1.0);

	// neck
	rectangle2(x,y-1.0,z,0.5,1.0,1.0);
	glPopMatrix();
}
void robotBody(GLfloat x, GLfloat y, GLfloat z)
{
	glPushMatrix();
	glTranslatef(x, y, z);
	rectangle2(x,y,z,4.0,4.0,2.0);
	glPopMatrix();
}
void robotLeg(GLfloat x, GLfloat y, GLfloat z ,GLfloat theta)
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(theta,1.0,0.0,0.0);
	glColor3f(0.0, 0.5, 0.0);
	rectangle2(x,y,z,3.0,1.0,1.0);
	glPopMatrix();
}
void robotHand(GLfloat x, GLfloat y, GLfloat z ,GLfloat theta )
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(theta, 0.0, 0.0, 1.0);
	glColor3f(0.0, 0.5, 0.0);
	rectangle2(x,y,z,3.0,1.0,1.0);
	glPopMatrix();
}
void robot(GLfloat x, GLfloat y, GLfloat z)
{
	glPushMatrix();
	glTranslatef(x, y, z);

	glLoadIdentity();
	glTranslatef(x, y, zz);


	//cordinate(x,y,zz);

	robotHand(x-1.60,y-1.150,z,-30); // right
	robotHand(x+1.60,y-1.150,z,+30); // left 
	robotHead(x,y,z); // the head in Center top ( we start to draw robot from this point) 
	robotBody(x,y- 0.75, z);
	robotLeg(x+0.5,y-2.75,z,legLeft);
	robotLeg(x-0.5,y-2.75,z,legRight);
	glPopMatrix();
}
void RotateRobotHeadR(void)
{
spin =-60.0;
glutPostRedisplay();
}
void RotateRobotHeadL(void)
{
spin=60.0;
glutPostRedisplay();
}
void RotateRobotHeadRest(void){
	spin=0.0;
	glutPostRedisplay();

}
void MoveRobotUP(void)
{
	if( legLeft==0.0 && legRight==0.0)
	{
	legRight=45.0;
	}
	else if(legRight==45.0 )
	{
	legLeft=45.0;
	legRight=0.0;
	}
	else if(legLeft==45.0 )
	{
	legLeft=0.0;
	legRight=45.0;
	}
	zz+=0.5;
	if(zz>45)
		zz=45;
	
glutPostRedisplay();
glutIdleFunc(NULL);
}
void MoveRobotDown(void)
{
	if( legLeft==0.0 && legRight==0.0)
	{
	legRight=45.0;
	}
	else if(legRight==45.0 )
	{
	legLeft=45.0;
	legRight=0.0;
	}
	else if(legLeft==45.0 )
	{
	legLeft=0.0;
	legRight=45.0;
	}
	zz-=0.5;
	if(zz<-45)
		zz=-45;
glutPostRedisplay();
glutIdleFunc(NULL);
}

void mouse(int button, int state, int x, int y)
{
switch (button)
{
case GLUT_LEFT_BUTTON:
	if (state == GLUT_DOWN)
	{
	glutIdleFunc(RotateRobotHeadR);
	break;
	}
	else if (state == GLUT_UP)
	{
		glutIdleFunc(RotateRobotHeadRest);
		break;
	}
case GLUT_MIDDLE_BUTTON:
case GLUT_RIGHT_BUTTON:
	if (state == GLUT_DOWN)
	{
	glutIdleFunc(RotateRobotHeadL);
	break;
	}else if (state == GLUT_UP)
	{
		glutIdleFunc(RotateRobotHeadRest);
		break;
	}
default: break;
}
}
void keyboard(unsigned char key, int x, int y)
{
if (key == 27)
	exit(0);
else if (key=='w')
	glutIdleFunc(MoveRobotUP);
else if (key=='s')
	glutIdleFunc(MoveRobotDown);
std::cout<<key<< (int)key <<"\n";
}


void draw()
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	
//===========================================
	Enviroment(50.0,50.0,50.0);

	//robot(0.0, 1.0, 2.0);
	robot(0.0,3.0,0.0);
	//robotHand(0,0,0,-30);
glutSwapBuffers();

}

////////////////////////////////////////////////////////
void reshape(GLsizei width, GLsizei height) { 
	if (height == 0) height = 1; 
	GLfloat aspect = (GLfloat)width / (GLfloat)height;
	// Set the viewport to cover the new window
	glViewport(0, 0, width, height);
	// Set the aspect ratio of the clipping volume to match the viewport
	glMatrixMode(GL_PROJECTION); // To operate on the Projection matrix
	glLoadIdentity(); // Reset
	 // Enable perspective projection with fovy, aspect, zNear and zFar
	gluPerspective(90.0f, aspect, 0.1f, 200.0f);
	gluLookAt(0.0, 8.0, 25.0, /* eye is at (0,0,5) */
	0.0, 3.0, 0.0, /* center is at (0,0,0) */
	0.0, +3.0, 0.0); /* up is in positive Y direction */
}
//////////////////////////////////////////////////////
int main(int argc, char* argv[]) {
glutInit(&argc, argv); // Initialize GLUT
glutInitDisplayMode(GLUT_DEPTH |GLUT_RGB | GLUT_DOUBLE |GLUT_SINGLE); // Enable Depth buffered mode
glutInitWindowSize(640, 480); // Set the window's initial width & height
glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
glutCreateWindow("3D Shapes"); // Create window with the given title
glutDisplayFunc(draw); // Register callback handler for window re-paint event
glutReshapeFunc(reshape);// Register callback handler for window re-size event
glutMouseFunc(mouse);
glutKeyboardFunc(keyboard);
init(); // Our own OpenGL initialization
glutMainLoop(); // Enter the infinite event-processing loop
return 0;
}
