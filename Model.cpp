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
	if (!this->LoadGLTextures()){
		// Jump To Texture Loading Routine
  		
		return false; 
	}							// If Texture Didn't Load Return FALSE


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
	
	gluLookAt(0.0,0.0,0.0, 0.0,0.0,1.0,  0.0,1.0,0.0);



  return true;										// Initialization Went OK
}

// resize window
void MyModel::ReSizeGLScene(int width, int height)
{
	if (height == 0) 
		height = 1;					// Prevent A Divide By Zero By
	if (width == 0) 
		width = 1;					// Prevent A Divide By Zero By

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	if( width >= height ) {
		this->plx = 1.0;
		this->ply = 1.0;
	} 
	else {
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

	
	// ToDo Naturalmente devono essere una serie di texture mario si deve muovere 
	// texture for mario 
	char marioName[200];
	for (int i = 0; i < 8; i++) {
		sprintf(marioName, "../Data/media/mario_test_%d.png", i + 1);
		this->marioTexture[i] = SOIL_load_OGL_texture(marioName, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
		if (marioTexture[i] == 0) {
			return false;
		}
	}
	
	
	//  Load 19 pacman textures (front and back)
	char pacman[200];
	for(int i=0; i < 18; i++) {
		sprintf(pacman,"../Data/PacmanSprite/pacman%01d.png",i+1);
		this->pacmanTexture[i] = SOIL_load_OGL_texture (pacman,	SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,	SOIL_FLAG_INVERT_Y);
			if(pacmanTexture[i] == 0)
				return false;
	}
	this->pacmanTexture[18] = SOIL_load_OGL_texture("../Data/PacmanSprite/pacman_evil_new.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (pacmanTexture[18] == 0)
		return false;

	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	return true;										// Return Success
}


void MyModel::updateWorld(){

	if (this->keys[39])
		// mario si deve spostare a destra
		mario.addVelX(1);
	else{

		if (this->keys[37])
			// mario si deve spostare a sinistra
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


// call every time in MainProcm
bool MyModel::DrawGLScene(void){


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
	/*
	glMatrixMode(GL_MODELVIEW);				
	glLoadIdentity();*/
	
	// muove il mondo insieme a mario
	glMatrixMode(GL_MODELVIEW);				
	glLoadIdentity(); // per muovere il mondo insieme a mario						
	glTranslatef(-(float)mario.getLeft(), 0, 0);

	//  TIMING - start
	clock_t t = clock();
	// elapsed time in seconds from the last draw
	double elapsed = double (t - Tstamp) /  (double) CLOCKS_PER_SEC;
	// elapsed time in milliseconds from the last draw
	int ms_elapsed = (int) (t - Tstamp);
	// elapsed time in seconds from the beginning of the program
	this->fullElapsed = double (t - Tstart) /  (double) CLOCKS_PER_SEC;
	this->frameTime += double (t - Tstamp) /  (double) CLOCKS_PER_SEC;
	this->Tstamp = t;
	//  TIMING - end
	
	//aggiorno la posizione del gioco ogni 10ms 
	if (fullElapsed - LastUpdateTime > 0.01){
		this->LastUpdateTime = fullElapsed;
		updateWorld();
	}
	
	
	// può essere disegnato una sola volta non tutte le volte
	//Background cielo celeste
	buildSky();
	
	glEnable(GL_TEXTURE_2D);
	//disegna la texture subito dopo
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	//"pulisco" il colore base"
	glColor3f(1.0, 1.0, 1.0);
	// draw floor
	this->buildFloor();
	
	//PC add alpha channel
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);
	int marioId = (int(fullElapsed * 19) % 8);
	if (marioId > 7) {
		marioId = 0;
	}

	// only first now 
	marioId = 0;
	
	glBindTexture(GL_TEXTURE_2D, marioTexture[marioId]);
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


	//Pacman texture
	int pacmanId = (int(fullElapsed * 19) % 18)  ;
	if (pacmanId > 18) {
		pacmanId = 0;
	}

  
	// PACMAN PRINT
	glBindTexture(GL_TEXTURE_2D, pacmanTexture[pacmanId]);
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
		glVertex3f(-0.8, -0.7, Background[0].z);
		
		//alto destra
		glTexCoord2f(Background[2].u-0.38, Background[2].v-0.33);
		glVertex3f(-0.8, -0.45, Background[0].z);

		//alto sinistra
		glTexCoord2f(Background[3].u+0.39, Background[3].v-0.33);
		glVertex3f(-1, -0.45, Background[0].z);
	glEnd();
 	glTranslatef(ClientX2World(cx), ClientY2World(cy), 0);
	
	// proportional scaling (fixed percentual of window dimension)
	// if(1) proportional, if(0) fixed
	if (1) {
		glScalef(0.10f, 0.10f, 1);
	}
	//  Fixed scaling, alwais 100 pixels width/height
	else {
		float dx = PixToCoord_X(100);
		float dy = PixToCoord_Y(100);
		glScalef(dx/2, dy/2,1);
	}

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
	glRasterPos3f(- (float) plx + PixToCoord_X(10), (float) ply - PixToCoord_Y(21), -4);

	// compute fps and write text
	this->frames++;
	if( this->frames > 18 ) {
		this->fps = frames / frameTime;
		this->frames = 0; 
		this->frameTime = 0;
	}
	
	// to fix --> see mario.getLeft() per riuscire a capire quando mario va via dalla schermata
	this->glPrint("Elapsed time: %6.2f sec.  -  Fps %6.2f - PositionMario x = %6.2f, y = %6.2f", fullElapsed, fps, mario.getLeft(), mario.getDown());
	
	if(this->fullElapsed < 6) {
		glRasterPos3f(- (float) plx + PixToCoord_X(10), (float) -ply+PixToCoord_Y(21),-4);
		this->glPrint("...F2/F3/F4 for sounds");
	}

	glRasterPos3f(- (float) plx + PixToCoord_X(10), (float) -ply+PixToCoord_Y(61),-4);
	this->glPrint("%1d %1d  %s",cx,cy, captured ? "captured" : "Not captured" );
	
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	return true;

}

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

void MyModel::buildFloor() {

	// Terreno
	float blockFloorLength = 0.2;
	int nBlockFloor = 2 / blockFloorLength;
	//float lengthGame = 8.5; // lunghezza che vogliamo dare al mondo
	// 2.5 vertice x fino al quale disegnare il background
	for (float i = this->xStartGame; i < this->xEndGame; i += blockFloorLength) {
		glBegin(GL_QUADS);

		//basso sinistra
		glTexCoord2f(Background[0].u, Background[0].v);
		glVertex3f(i, Background[0].y, Background[0].z);

		//basso destra
		glTexCoord2f(Background[1].u, Background[1].v);
		glVertex3f(i + blockFloorLength, Background[1].y, Background[0].z);

		//alto destra
		glTexCoord2f(Background[2].u, Background[2].v);
		glVertex3f(i + blockFloorLength, Background[1].y + 0.3, Background[0].z);

		//alto sinistra
		glTexCoord2f(Background[3].u, Background[3].v);
		glVertex3f(i, Background[0].y + 0.3, Background[0].z);

		glEnd();
	}
}

void MyModel::buildSky() {
		glDisable(GL_TEXTURE_2D);
		glPushMatrix();
		// può essere disegnato una sola volta non tutte le volte
		//Background cielo celeste
		glBegin(GL_QUADS);
			// colore da disegnare
			glColor3f(0.35, 0.57, 0.984);
			// vertice in basso a sinistra
			glVertex3f(Background[0].x +this->xStartGame, Background[0].y, Background[0].z);
			// in basso  a destra
			glVertex3f(Background[1].x + this->xEndGame, Background[1].y, Background[1].z);
			// in alto a destra
			glVertex3f(Background[2].x + this->xEndGame, Background[2].y, Background[2].z);
			// in basso  a sinistra
			glVertex3f(Background[3].x + this->xStartGame, Background[3].y, Background[3].z);
		glEnd();

}

