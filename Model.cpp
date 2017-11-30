///////////////////////////////////////////////////////////////////
//  A basic skeleton for 2D like game developpers.
//
//  model data
///////////////////////////////////////////////////////////////////

#include <windows.h>		// Header File For Windows
#include <stdio.h>			// Header File For Standard Input/Output
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library

#include "Model.h"
#include "SOIL.h"


#include "PC.h"

PC mario(-0.65, -0.6, 0.05, 0.1);



// All Setup For OpenGL Goes Here
bool MyModel::InitGL(void)
{
	if (!this->LoadGLTextures())				// Jump To Texture Loading Routine
  {	return false; }							// If Texture Didn't Load Return FALSE


	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
  this->BuildFont();

  // eye    (0,0,0)
  // center (0,0,-1)
  // up     (0,1,0)
	
  gluLookAt(0.0,0.0,0.0, 0.0,0.0,-1.0, 0.0,1.0,0.0);

  return true;										// Initialization Went OK
}


void MyModel::ReSizeGLScene(int width, int height)
{
	if (height==0) 
		height=1;					// Prevent A Divide By Zero By
	if (width==0) 
		width=1;					// Prevent A Divide By Zero By

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// orthographic projection
	// background in [-1, 1] on both x and y
	// fill th background according to the window aspect ratio
	// void WINAPI glOrtho( GLdouble left,   GLdouble right,
	//                      GLdouble bottom, GLdouble top,
	//                      GLdouble zNear,  GLdouble zFar );
	if( width >= height ) 
	{
		this->plx = 1.0;
		this->ply = 1.0;
	} 
	else 
	{
		this->plx = (double) width /(double) height;
		this->ply = 1.0;
	}
	glOrtho(-this->plx, this->plx, -this->ply, this->ply, 1, 5.1);
  
	//  saving the window width and height in pixels
	this->Wheight = height;
	this->Wwidth = width;

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}



// Load Bitmaps And Convert To Textures
bool MyModel::LoadGLTextures(void)
{
	//load an image file directly as a new OpenGL texture */
	texture[0] = SOIL_load_OGL_texture( "Data/media/baseWall.png",SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y );
	if(texture[0] == 0) 
		return false;

	texture[1] = SOIL_load_OGL_texture("Data/media/mario_test_1.png",SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[1] == 0) 
		return false;

	
	//  Load 19 pacman textures (front and back)
	char ll[200];
	for(int i=1; i < 19; i++) {
	sprintf(ll,"Data/PacmanSprite/pacman%01d.png",i+1);
	this->texture[i+1] = SOIL_load_OGL_texture (ll,	SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,	SOIL_FLAG_INVERT_Y);
		if(texture[i+1] == 0)
			return false;
	}

	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	return true;										// Return Success
}


void MyModel::updateWorld(){
	//se è premuto il pulsante ->
	if (this->keys[39])
		mario.addVelX(1);
	else{
		//se è premuto il pulsante <-
		if (this->keys[37])
			mario.addVelX(-1);
		else
			mario.stopX();
	}

	//BUG!! Il salto funziona solo se mi sto muovendo verso destra!!

	if (this->keys[38]){
		mario.jump();
	}

	//aggiorno la posizione del pc
	mario.update();

	//NOTA: DA CANCELLARE IN FUTURO
	//NOTA: simili controlli vanno fatti dove si ha un FPS maggiore.
	//qui dovrebbe esserci codice relativo alla velocità utente, non collisioni o altro.
	if (mario.getDown() < -0.7)
		mario.stopY();
}


bool MyModel::DrawGLScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
	glMatrixMode(GL_MODELVIEW);				// Select The Modelview Matrix
	glLoadIdentity();									// Reset The View

	//  TIMING - start
	clock_t t = clock();
	// elapsed time in seconds from the last draw
	double elapsed = double (t - Tstamp) /  (double) CLOCKS_PER_SEC;
	// elapsed time in milliseconds from the last draw
	int ms_elapsed = (int) (t - Tstamp);
	// elapsed time in seconds from the beginning of the program
	this->Full_elapsed = double (t - Tstart) /  (double) CLOCKS_PER_SEC;
	this->frameTime += double (t - Tstamp) /  (double) CLOCKS_PER_SEC;

	this->Tstamp = t;
	//  TIMING - end
	


	//aggiorno la posizione del gioco ogni 10ms (aka lavoro a 120 frame/sec).
	if (Full_elapsed - LastUpdateTime > 0.01){
		this->LastUpdateTime = Full_elapsed;
		updateWorld();
	}
		


	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	
	//glBindTexture(GL_TEXTURE_2D, texture[0]);
	//  Background cielo celeste
  glBegin(GL_QUADS);
		glColor3f(0.35, 0.57, 0.984);
		glVertex3f(Background[0].x, Background[0].y, Background[0].z);
		glVertex3f(Background[1].x, Background[1].y, Background[1].z);
		glVertex3f(Background[2].x, Background[2].y, Background[2].z);
		glVertex3f(Background[3].x, Background[3].y, Background[3].z);
  glEnd();

  //glMatrixMode(GL_MODELVIEW);
  //glLoadIdentity();

  glEnable(GL_TEXTURE_2D);
  //disegna la texture subito dopo
  
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, texture[0]);

  //"pulisco" il colore base"
  glColor3f(1.0, 1.0, 1.0);
  // Terreno

  float blockFloorLength = 0.2;
  int nBlockFloor = 2 / blockFloorLength;

  for (float i = -1; i < 2.5; i += blockFloorLength){
	  glBegin(GL_QUADS);
			//basso sinistra
		  glTexCoord2f(Background[0].u, Background[0].v);
		  glVertex3f(i, Background[0].y, Background[0].z);
		  //basso destra
		  glTexCoord2f(Background[1].u, Background[1].v);
		  glVertex3f(i + blockFloorLength, Background[1].y, Background[1].z);
		  //alto destra
		  glTexCoord2f(Background[2].u, Background[2].v);
		  glVertex3f(i + blockFloorLength, Background[1].y + 0.3, Background[0].z);
		  //alto sinistra
		  glTexCoord2f(Background[3].u, Background[3].v);
		  glVertex3f(i, Background[0].y + 0.3, Background[0].z);

	  glEnd();
  }


 //PC add alpha channel
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_ALPHA_TEST);
  glAlphaFunc(GL_GREATER, 0);

  





  glBindTexture(GL_TEXTURE_2D, texture[1]);
  glBegin(GL_QUADS);

	  //basso sinistra
	  glTexCoord2f(Background[0].u, Background[0].v);
	  glVertex3f(mario.getLeft(), mario.getDown(), Background[0].z);
	  //basso destra
	  glTexCoord2f(Background[1].u, Background[1].v);
	  glVertex3f(mario.getRight(), mario.getDown(), Background[1].z);
	  //alto destra
	  glTexCoord2f(Background[2].u, Background[2].v);
	  glVertex3f(mario.getRight(), mario.getUp(), Background[0].z);
	  //alto sinistra
	  glTexCoord2f(Background[3].u, Background[3].v);
	  glVertex3f(mario.getLeft(), mario.getUp(), Background[0].z);

  glEnd();
  glDisable(GL_BLEND);
  glDisable(GL_ALPHA_TEST);


  //Pacman

  //  Texture for the pacman, Full_elapsed * 19 -> change image every 1/19 sec.
  //										% 11 -> pacman is contained between f[2] and f[11]
									//				(9 image + returning back)

  int texF = (int(Full_elapsed * 19) % 19) + 2  ;
  if (texF > 19) {
	  texF = 2;
  }

  
  glBindTexture(GL_TEXTURE_2D, texture[texF]);
  
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_ALPHA_TEST);
  glAlphaFunc(GL_GREATER, 0);
  glBegin(GL_QUADS);

	  //basso sinistra
	  glTexCoord2f(Background[0].u+0.39, Background[0].v+0.34);
	  glVertex3f(-1, -0.7, Background[0].z);
	  //basso destra
	  glTexCoord2f(Background[1].u-0.38, Background[1].v+0.34);
	  glVertex3f(-0.7, -0.7, Background[1].z);
	  //alto destra
	  glTexCoord2f(Background[2].u-0.38, Background[2].v-0.33);
	  glVertex3f(-0.7, -0.3, Background[0].z);
	  //alto sinistra
	  glTexCoord2f(Background[3].u+0.39, Background[3].v-0.33);
	  glVertex3f(-1, -0.3, Background[0].z);

  glEnd();
 
  /*
  //  Texture for the fire, change every 1/19 sec.
  int texF2 = 2 + ((int( (Full_elapsed*19) )) %26 );
  glBindTexture(GL_TEXTURE_2D, texture[texF]);

  //  fire geometrical trasformations
  glMatrixMode(GL_MODELVIEW);				// Select The Modelview Matrix
	glLoadIdentity();									// Reset The View

  //  circular path from window center. Radious and angular velocity
  //  in radians as follows
  double radious = 0.5;
  double omega = PI / 27.0;  // PI/8 each second
  double px, py;
  px = radious * cos(omega * Full_elapsed);
  py = radious * sin(omega * Full_elapsed);
  glTranslatef((float) px, (float) py, 0);
  glScalef(0.30f,0.5f,1);    // 1- scale the fire

  //  fire
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_ALPHA_TEST);
  glAlphaFunc(GL_GREATER, 0);

  glBegin(GL_QUADS);
  for(int i = 0; i < 4; i++) {
		glTexCoord2f(fire[i].u, fire[i].v);
    glVertex3f(fire[i].x, fire[i].y,  fire[i].z);
  }
  glEnd();

  glDisable(GL_BLEND);
  glDisable(GL_ALPHA_TEST);
  */
  

  //  Floating cursor - start
  /*
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_ALPHA_TEST);
  glAlphaFunc(GL_GREATER, 0);
  glMatrixMode(GL_MODELVIEW);				// Select The Modelview Matrix
	glLoadIdentity();									// Reset The View
	*/
  //  Disable texture to see the rectangle size
  //  The cursor "hot spot" is the center of the rectangle
  // glDisable(GL_TEXTURE_2D);
 

	glTranslatef(ClientX2World(cx), ClientY2World(cy), 0);
	// proportional scaling (fixed percentual of window dimension)
	// if(1) proportional, if(0) fixed
	if (1) 
	{
		glScalef(0.10f, 0.10f, 1);
	}
	//  Fixed scaling, alwais 100 pixels width/height
	else 
	{
		float dx = PixToCoord_X(100);
		float dy = PixToCoord_Y(100);
		glScalef(dx/2, dy/2,1);
	}

	/*
	glBegin(GL_QUADS);
	for(int i = 0; i < 4; i++) {
		glTexCoord2f(curs[i].u, curs[i].v);
	glVertex3f(curs[i].x, fire[i].y,  curs[i].z);
	}
	glEnd();
	*/

	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	//  Floating cursor - end

	//  Some text
	glMatrixMode(GL_MODELVIEW);				// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Current Modelview Matrix
	glDisable(GL_TEXTURE_2D);

	// Color
	glColor3f(1.0f,1.0f,1.0f);

	// Position The Text On The Screen
	glRasterPos3f(- (float) plx + PixToCoord_X(10), (float) ply-PixToCoord_Y(21),-4);

	// compute fps and write text
	this->frames++;
	if( this->frames > 18 ) {
		this->fps = frames / frameTime;
		this->frames = 0; this->frameTime = 0;
	}
	this->glPrint("Elapsed time: %6.2f sec.  -  Fps %6.2f", Full_elapsed, fps);
	
	if(this->Full_elapsed < 6) {
		glRasterPos3f(- (float) plx + PixToCoord_X(10), (float) -ply+PixToCoord_Y(21),-4);
		this->glPrint("...F2/F3/F4 for sounds");
	}

	{
		glRasterPos3f(- (float) plx + PixToCoord_X(10), (float) -ply+PixToCoord_Y(61),-4);
		this->glPrint("%1d %1d  %s",cx,cy, captured ? "captured" : "Not captured" );
	}

	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	return true;
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//  bitmap fonts
void MyModel::BuildFont(void)								// Build Our Bitmap Font
{
	HFONT	font;										// Windows Font ID
	HFONT	oldfont;									// Used For Good House Keeping

	base = glGenLists(96);								// Storage For 96 Characters

	font = CreateFont(	-20,							// Height Of Font
						0,								// Width Of Font
						0,								// Angle Of Escapement
						0,								// Orientation Angle
						FW_BOLD,						// Font Weight
						FALSE,							// Italic
						FALSE,							// Underline
						FALSE,							// Strikeout
						ANSI_CHARSET,					// Character Set Identifier
						OUT_TT_PRECIS,					// Output Precision
						CLIP_DEFAULT_PRECIS,			// Clipping Precision
						ANTIALIASED_QUALITY,			// Output Quality
						FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
						"Courier New");					// Font Name

	oldfont = (HFONT)SelectObject(hDC, font);           // Selects The Font We Want
	wglUseFontBitmaps(hDC, 32, 96, base);				// Builds 96 Characters Starting At Character 32
	SelectObject(hDC, oldfont);							// Selects The Font We Want
	DeleteObject(font);									// Delete The Font
}

void MyModel::KillFont(void)									// Delete The Font List
{
	glDeleteLists(base, 96);							// Delete All 96 Characters
}

void MyModel::glPrint(const char *fmt, ...)					// Custom GL "Print" Routine
{
	char		text[256];								// Holds Our String
	va_list		ap;										// Pointer To List Of Arguments

	if (fmt == NULL)									// If There's No Text
		return;											// Do Nothing

	va_start(ap, fmt);									// Parses The String For Variables
	    vsprintf(text, fmt, ap);						// And Converts Symbols To Actual Numbers
	va_end(ap);											// Results Are Stored In Text

	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(base - 32);								// Sets The Base Character to 32
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
	glPopAttrib();										// Pops The Display List Bits
}
