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
#include "EnemyPacman.h"
#include "EnemySimple.h"
#include "Sky.h"
#include "audiere.h"
#include "Ostacolo.h"
#include "CollisionSystem.h"
#include "Level.h"

using namespace std;

// x iniziale, y iniziale, spessore e altezza personaggio e nemico
//PC mario(-0.2, -0.6, 0.05, 0.1);
PC mario(0.2, -0.6, 0.05, 0.1);
EnemyPacman pacman(-0.9,-0.6, 0.055, 0.1);

EnemySimple enemy(0.0, -0.6, 0.05, 0.1);
//Sky Cloud1(-0.4, 0.7, 0.18, 0.15);
//Sky Cloud2(0.7, 0.6, 0.15, 0.12);
//Sky Mountain(0.55, -0.58, 0.2, 0.12);

Sky Cloud1(-1, 0.51, 1.02, 0.5);
Sky Cloud2(1.01, 0.51, 1.02, 0.5);
Sky Mountain1(-1.9, -0.35, 1.01, 0.4);
Sky Mountain2(0.105, -0.35, 1.01, 0.4);


Level *levA; // make level


CollisionSystem *collisionSystem; // System to handle collision


double posSchermoX = 0;
bool pacmanCanMove = false;
double xStartEnemy = 0.0;

int debug = 0;



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
	//texture[0] = SOIL_load_OGL_texture( "Data/media/baseWall.png",SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y );
	texture[0] = SOIL_load_OGL_texture("Data/media/Terrain.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if(texture[0] == 0) 
		return false;

	// SFONDO-NUVOLE-
	texture[1] = SOIL_load_OGL_texture("Data/media/nuvole_trasparenti.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[1] == 0)
		return false;

	// SFONDO-MONTAGNE-
	texture[2] = SOIL_load_OGL_texture("Data/media/mountain2_trasparenti.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[2] == 0)
		return false;


	// -OSTACOLO PROVA
	texture[3] = SOIL_load_OGL_texture("Data/media/baseWall.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[3] == 0)
		return false;

	
	// ToDo Naturalmente devono essere una serie di texture mario si deve muovere 
	// texture for mario 
	char marioName[200];
	for (int i = 0; i < 8; i++) {
		sprintf(marioName, "Data/media/mario_test_%d.png", i + 1);
		this->marioTexture[i] = SOIL_load_OGL_texture(marioName, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
		if (marioTexture[i] == 0) {
			return false;
		}
	}

	// GAME INIT
	char backgroundFile[100];
	sprintf(backgroundFile,"Data/backgroundImageStart_3_rotate.png" );

	backgroundtexture = SOIL_load_OGL_texture(backgroundFile, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (this->backgroundtexture == 0)
		return false;

	// GAME OVER TEXTURE
	char endgameoverfile[100];
	sprintf(endgameoverfile, "Data/Game_over4.png");
	this->gameovertexture = SOIL_load_OGL_texture(endgameoverfile, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (this->gameovertexture == 0)
		return false;

	char wingameoverfile[100];
	sprintf(wingameoverfile, "Data/YouWIn.png");
	this->wintexture = SOIL_load_OGL_texture(wingameoverfile, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (this->wintexture == 0)
		return false;

	
	//  Load 19 pacman textures (front and back)
	char pacman[200];
	int numeroTexture = 2;
	// int numeroTexture = 18;

	for(int i=0; i < numeroTexture; i++) {
		sprintf(pacman,"Data/PacmanSprite/pacman_new_%01d.png",i+1);
		this->pacmanTexture[i] = SOIL_load_OGL_texture (pacman,	SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,	SOIL_FLAG_INVERT_Y);
			if(pacmanTexture[i] == 0)
				return false;
	}

	char newgamebutton[200];
	int numero_button = 2;

	for (int i = 0; i < numero_button; i++) {
		sprintf(newgamebutton, "Data/button_new-game_%01d.png", i + 1);
		this->newGame[i] = SOIL_load_OGL_texture(newgamebutton, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
		if (newGame[i] == 0)
			return false;
	}
	char exitgamebutton[200];
	for (int i = 0; i < numero_button; i++) {
		sprintf(exitgamebutton, "Data/button_exit-game_%01d.png", i + 1);
		this->exitGame[i] = SOIL_load_OGL_texture(exitgamebutton, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
		if (exitGame[i] == 0)
			return false;
	}
	
	char enemytexturename[200];
	int numero_texture_enemy = 3;
	for (int i = 0; i < numero_texture_enemy; i++) {
		sprintf(enemytexturename, "Data/media/sheet_hero_walk_%01d.png", i + 1);
		this->enemyTexture[i] = SOIL_load_OGL_texture(enemytexturename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
		if (enemyTexture[i] == 0)
			return false;
	}
	
		// Typical Texture Generation Using Data From The Bitmap
	//glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	return true;										// Return Success
}

// call every time in MainProc
bool MyModel::DrawGLScene(audiere::OutputStreamPtr dead, audiere::OutputStreamPtr jump, audiere::OutputStreamPtr winSound, audiere::OutputStreamPtr soundBase) {

	// usato per caricare schermate diverse
	// 0 schermata iniziale
	// 1 schermata di gioco principale

	switch (this->screenPlay) {
	case 0:
		this->drawInitGame();
		break;
	case 1:
		//inizializzazione delle variabili per il mondo di gioco
		// se suono win stop
		if (winSound->isPlaying())
			winSound->stop();
		if (dead->isPlaying())
			dead->stop();
		this->screenPlay = 3;

		//cancello le tracce dei livelli precedenti
		//nuovo livello
		//gli passo la larghezza di mario*3
		collisionSystem = new CollisionSystem(mario.getWidth()*3);		
		levA = new Level();
		levA->fillCollisionSystemA(collisionSystem); // add level A
		levA->fillCollisionSystemB(collisionSystem); // add level B
		levA->fillCollisionSystemC(collisionSystem);
		xStartEnemy = levA->getStartA() + 9.0;
		//enemy = new EnemySimple(xStartEnemy, -0.6, 0.1, 0.1);
		enemy.setX(xStartEnemy);
		enemy.addVelX("right");
		//schermata di gioco
		drawGamePrincipale(dead, jump);
		break;

	case 2:
		this->drawGameOver(soundBase);
		break;
	case 3:
		//mondo di gioco con variabili inizializzate
		if (winSound->isPlaying())
			winSound->stop();
		if (dead->isPlaying())
			dead->stop();
		
		drawGamePrincipale(dead, jump);
		break;
	case 4:
		// win
		winSound->play();
		drawWinGame(soundBase);
		break;

	default:
		return true;

	}

}

void MyModel::drawInitGame() {

	double x_init = 0.5;
	double x_end = 0.8;
	double y_init = 0.1;
	double y_end = 0.3;
	double fattore_y = 0.4;

	if (this->keys[VK_UP]) {
		this->select = 0;	
	}

	if (this->keys[VK_DOWN]) {
			this->select = 1;
	}


	//  TIMING - start
	clock_t t = clock();
	// elapsed time in seconds from the last draw
	double elapsed = double(t - Tstamp) / (double)CLOCKS_PER_SEC;
	// elapsed time in milliseconds from the last draw
	int ms_elapsed = (int)(t - Tstamp);
	// elapsed time in seconds from the beginning of the program
	this->fullElapsed = double(t - Tstart) / (double)CLOCKS_PER_SEC;
	this->frameTime += double(t - Tstamp) / (double)CLOCKS_PER_SEC;
	this->Tstamp = t;
	
	// background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glAlphaFunc(GL_GREATER, 0);
	glBindTexture(GL_TEXTURE_2D, backgroundtexture);
	glPushMatrix();
	glBegin(GL_QUADS);

		// b-s
		glTexCoord2f(Background[0].u, Background[0].v);
		glVertex3f(Background[0].x, Background[0].y, Background[0].z );
		
		//b-d
		glTexCoord2f(Background[1].u, Background[1].v);
		glVertex3f(Background[1].x, Background[1].y, Background[0].z );

		//a-d
		glTexCoord2f(Background[2].u, Background[2].v);
		glVertex3f(Background[2].x, Background[2].y, Background[0].z );

		//a-s
		glTexCoord2f(Background[3].u, Background[3].v);
		glVertex3f(Background[3].x, Background[3].y, Background[0].z );
	
	glEnd();

	// NEW GAME BUTTON
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	int newgamebutton = (sizeof(newGame) / sizeof(*newGame));
	// new game
	
	int buttonId = (int(fullElapsed * 5) % newgamebutton);
	if (buttonId > newgamebutton) {
		buttonId = 0;
	}

	// se ho selezionato exit game lampeggia solo quello
	if (this->select != 0) {
		buttonId = 0;
	}
	glBindTexture(GL_TEXTURE_2D, newGame[buttonId]);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPushMatrix();
		glBegin(GL_QUADS);
		// b-s
		glTexCoord2f(Background[0].u, Background[0].v);
		glVertex3f(x_init, y_init, Background[0].z);
		//b-d
		glTexCoord2f(Background[1].u, Background[1].v);
		glVertex3f(x_end, y_init, Background[0].z);
		//a-d
		glTexCoord2f(Background[2].u, Background[2].v);
		glVertex3f(x_end, y_end, Background[0].z);
		//a-s
		glTexCoord2f(Background[3].u, Background[3].v);
		glVertex3f(x_init, y_end, Background[0].z);
	glEnd();

	// EXIT BUTTON
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	int buttonexitId = (int(fullElapsed * 5) % newgamebutton);
	if (buttonexitId > newgamebutton) {
		buttonexitId = 0;
	}
	// se ho selezionato new game lampeggia solo quello
	if (this->select != 1) {
		buttonexitId = 0;
	}

	glBindTexture(GL_TEXTURE_2D, exitGame[buttonexitId]);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPushMatrix();
	glBegin(GL_QUADS);
	
		// b-s
		glTexCoord2f(Background[0].u, Background[0].v);
		glVertex3f(x_init, y_init-fattore_y, Background[0].z);

		//b-d
		glTexCoord2f(Background[1].u, Background[1].v);
		glVertex3f(x_end, y_init - fattore_y, Background[0].z);

		//a-d
		glTexCoord2f(Background[2].u, Background[2].v);
		glVertex3f(x_end, y_end - fattore_y, Background[0].z);

		//a-s
		glTexCoord2f(Background[3].u, Background[3].v);
		glVertex3f(x_init, y_end - fattore_y, Background[0].z);

	glEnd();
	glDisable(GL_TEXTURE_2D);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//this->glPrint("Killer Pacman: Only One Rule : RUN Press Enter to Start!");

	if (this->keys[WM_LBUTTONDOWN]) {

		

		if (Data.mouseleft && !Data.mouseAlreadyPressed) {

			Data.mouseAlreadyPressed = true;
			double x = Data.cx;
			double y = Data.cy;

			if (x > x_init && x < x_end && y > y_init && y < y_end) {
				this->screenPlay = 1;

				/*char out[100];
				sprintf(out, "%lf", Data.cy);
				OutputDebugString(out);
				OutputDebugString("\n");*/
				
			}

			if (x > x_init && x < x_end && y > y_init - fattore_y && y < y_end - fattore_y)
				this->keys[VK_ESCAPE] = true;
		}
	}
	
	if (this->keys[VK_RETURN]) {
		if(this->select == 0)
			this->screenPlay = 1;
		else {
			this->keys[VK_ESCAPE] = true;
		}
	}
	// reset color
	glColor3f(1.0, 1.0, 1.0);

}

void MyModel::updateWorld(audiere::OutputStreamPtr jump, audiere::OutputStreamPtr dead) {

	if (abs(enemy.getX() - xStartEnemy) >= 0.5) {
		// change direction before update
		if (enemy.getX() > xStartEnemy) {
			// devo tornare a sinistra
			enemy.addVelX("left");
		}
		else {
			enemy.addVelX("right");
		}
	}
	enemy.update();

	// update pacman
	if (pacmanCanMove) {
		// check pacman jump con end floor 
		if (this->pacmanMustJump(pacman,levA)) {
			pacman.jump();
		}
		if (mario.getVelX() == 0.0 && this->checkX(mario, pacman)) {
			pacman.stopX();
			if (!this->checkY(mario, pacman)) {
				pacman.jump(); // aggiungere che si raggiunge il salto al valore x
			}
		}
		else {
			if (pacman.getX() > mario.getX()) {
				pacman.addVelX("left");
			}
			else {
				pacman.addVelX("right");
			}
		}
		pacman.update();
		if (pacman.getDown() < -0.7) {
			pacman.stopY();
		}
	}

	// update mario
	if (this->keys[VK_RIGHT]) {
		pacmanCanMove = true ;
		// mario si deve spostare a destra
		mario.addVelX("right");
	}else {
		if (this->keys[VK_LEFT]) {
			// mario si deve spostare a sinistra
			if (mario.getLeft() > posSchermoX - 1)
				mario.addVelX("left");
			else
				mario.stopX();
		}
		else
			mario.stopX();
	}

	if (this->keys[VK_UP]) {
		//se non sta saltando
		mario.jump(jump);
	}

	
	if(!mario.getIsInHole()){
		// update mario position
		mario.update();
		if (mario.getDown() < -1.1) {
			this->screenPlay = 2;
			dead->play();
			mario.setDead(true);
		}
	}

	// cheat ahahah
	if (this->keys[VK_F11] && this->keys[VK_F12]) {
		mario.setVelMaxX(mario.getVelMaxX() * 2);
	}

	// reset cheat ahah
	if (this->keys[VK_F1] && this->keys[VK_F2]) {
		mario.setVelMaxX(0.0015);
	}

	if (this->keys[VK_F8]) {
		// update vel max pacman
		pacman.setVelMaxX(pacman.getVelMaxX() * 2);
	}

	if (this->keys[VK_F9]) {
		// update vel max pacman
		pacman.setVelMaxX(0.0015);
	}

}

// schermata di gioco
void MyModel::drawGamePrincipale(audiere::OutputStreamPtr dead, audiere::OutputStreamPtr jump) {

	collisionSystem->physics(&mario);
	
	collisionSystem->physics(&pacman);
	

	// DA DECOMENT
	if (mario.getX() >= this->xEndGame) {
		this->screenPlay = 4;
		return;
	}
	// same function per pacman
	// DECOMENNT
	/*
	if (this->checkDead(mario, pacman) ||  mario.getDead()) {
		dead->play();
		this->screenPlay = 2;
		return;
	}
	*/
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//per muovere il mondo insieme a mario		
	glTranslatef(-(float)posSchermoX, 0, 0);
	if (mario.getLeft() > posSchermoX + 0.0001) {
		posSchermoX = mario.getLeft();
		Cloud1.move(-mario.getVelX()*0.6, posSchermoX - 1, posSchermoX + 1);
		Cloud2.move(-mario.getVelX()*0.6, posSchermoX - 1, posSchermoX + 1);
		Mountain1.move(-mario.getVelX()*0.35, posSchermoX - 1, posSchermoX + 1);
		Mountain2.move(-mario.getVelX()*0.35, posSchermoX - 1, posSchermoX + 1);
	}

	//  TIMING - start
	clock_t t = clock();
	// elapsed time in seconds from the last draw
	double elapsed = double(t - Tstamp) / (double)CLOCKS_PER_SEC;
	// elapsed time in milliseconds from the last draw
	int ms_elapsed = (int)(t - Tstamp);
	// elapsed time in seconds from the beginning of the program
	this->fullElapsed = double(t - Tstart) / (double)CLOCKS_PER_SEC;
	this->frameTime += double(t - Tstamp) / (double)CLOCKS_PER_SEC;
	this->Tstamp = t;
	//  TIMING - end

	//aggiorno la posizione del gioco ogni 1ms per prevenire il tremolio --> riduco la valocità massima  
	// se minore di 0.0008 --> potremmmo non disegno niente
	if (fullElapsed - LastUpdateTime > 0.0008) {
		this->LastUpdateTime = fullElapsed;
		updateWorld(jump,dead);
	}

	// ogni 10 minuti aumento la velocità di pacman
	if (fullElapsed > 300 * lastTimeChangeVelocityPacman) {
		pacman.setVelMaxX(pacman.getVelMaxX() + 0.0002);
	}

	// può essere disegnato una sola volta non tutte le volte
	//Background cielo celeste
	buildSky();
	glEnable(GL_TEXTURE_2D);
	//disegna la texture subito dopo
	glColor3f(1.0, 1.0, 1.0);
	// Draw the landscape
	this->buildLandscape();

	// draw floor
	this->buildFloor(-1, 0.7);
	//ostacolo
	this->drawLevel();
	this->buildEnemy();

	// draw mario
	this->buildMario();

	// draw pacman
	this->buildPacman();
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping

}

void MyModel::drawWinGame(audiere::OutputStreamPtr soundBase) {

	double x_init = 0.5;
	double x_end = 0.8;
	double y_init = 0.1;
	double y_end = 0.3;
	double fattore_y = 0.4;

	if (this->keys[VK_UP]) {
		this->select = 0;
	}

	if (this->keys[VK_DOWN]) {
		this->select = 1;
	}


	//  TIMING - start
	clock_t t = clock();
	// elapsed time in seconds from the last draw
	double elapsed = double(t - Tstamp) / (double)CLOCKS_PER_SEC;
	// elapsed time in milliseconds from the last draw
	int ms_elapsed = (int)(t - Tstamp);
	// elapsed time in seconds from the beginning of the program
	this->fullElapsed = double(t - Tstart) / (double)CLOCKS_PER_SEC;
	this->frameTime += double(t - Tstamp) / (double)CLOCKS_PER_SEC;
	this->Tstamp = t;

	pacmanCanMove = false;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glAlphaFunc(GL_GREATER, 0);
	glLoadIdentity();
	glBindTexture(GL_TEXTURE_2D, this->wintexture);
	glBegin(GL_QUADS);
		double resize = 0.0;
		// b-s
		glTexCoord2f(Background[0].u, Background[0].v);
		glVertex3f(Background[0].x, Background[0].y, Background[0].z);
		//b-d
		glTexCoord2f(Background[1].u, Background[1].v);
		glVertex3f(Background[1].x, Background[1].y, Background[1].z);

		//a-d
		glTexCoord2f(Background[2].u, Background[2].v);
		glVertex3f(Background[2].x, Background[2].y, Background[2].z);

		//a-s
		glTexCoord2f(Background[3].u, Background[3].v);
		glVertex3f(Background[3].x, Background[3].y, Background[3].z);

	glEnd();
	
	// NEW GAME BUTTON
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	int newgamebutton = (sizeof(newGame) / sizeof(*newGame));
	// new game

	int buttonId = (int(fullElapsed * 5) % newgamebutton);
	if (buttonId > newgamebutton) {
		buttonId = 0;
	}

	// se ho selezionato exit game lampeggia solo quello
	if (this->select != 0) {
		buttonId = 0;
	}
	glBindTexture(GL_TEXTURE_2D, newGame[buttonId]);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPushMatrix();
	glBegin(GL_QUADS);
	// b-s
	glTexCoord2f(Background[0].u, Background[0].v);
	glVertex3f(x_init, y_init, Background[0].z);
	//b-d
	glTexCoord2f(Background[1].u, Background[1].v);
	glVertex3f(x_end, y_init, Background[0].z);
	//a-d
	glTexCoord2f(Background[2].u, Background[2].v);
	glVertex3f(x_end, y_end, Background[0].z);
	//a-s
	glTexCoord2f(Background[3].u, Background[3].v);
	glVertex3f(x_init, y_end, Background[0].z);
	glEnd();

	// EXIT BUTTON
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	int buttonexitId = (int(fullElapsed * 5) % newgamebutton);
	if (buttonexitId > newgamebutton) {
		buttonexitId = 0;
	}
	// se ho selezionato new game lampeggia solo quello
	if (this->select != 1) {
		buttonexitId = 0;
	}

	glBindTexture(GL_TEXTURE_2D, exitGame[buttonexitId]);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPushMatrix();
	glBegin(GL_QUADS);

	// b-s
	glTexCoord2f(Background[0].u, Background[0].v);
	glVertex3f(x_init, y_init - fattore_y, Background[0].z);

	//b-d
	glTexCoord2f(Background[1].u, Background[1].v);
	glVertex3f(x_end, y_init - fattore_y, Background[0].z);

	//a-d
	glTexCoord2f(Background[2].u, Background[2].v);
	glVertex3f(x_end, y_end - fattore_y, Background[0].z);

	//a-s
	glTexCoord2f(Background[3].u, Background[3].v);
	glVertex3f(x_init, y_end - fattore_y, Background[0].z);

	glEnd();
	glDisable(GL_TEXTURE_2D);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//this->glPrint("Killer Pacman: Only One Rule : RUN Press Enter to Start!");

	if (this->keys[WM_LBUTTONDOWN]) {



		if (Data.mouseleft && !Data.mouseAlreadyPressed) {

			Data.mouseAlreadyPressed = true;
			double x = Data.cx;
			double y = Data.cy;

			if (x > x_init && x < x_end && y > y_init && y < y_end) {
				this->screenPlay = 1;
				this->resetGame();
				/*char out[100];
				sprintf(out, "%lf", Data.cy);
				OutputDebugString(out);
				OutputDebugString("\n");*/

			}

			if (x > x_init && x < x_end && y > y_init - fattore_y && y < y_end - fattore_y)
				this->keys[VK_ESCAPE] = true;
		}
	}

	if (this->keys[VK_RETURN]) {
		if (this->select == 0){
			this->screenPlay = 1;
			this->resetGame();
		}
		else {
			this->keys[VK_ESCAPE] = true;
		}
	}
	// reset color
	if (this->screenPlay == 1) {
		soundBase->reset();
	}

	glColor3f(1.0, 1.0, 1.0);


}

void MyModel::drawGameOver(audiere::OutputStreamPtr soundBase) {
	pacmanCanMove = false;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glAlphaFunc(GL_GREATER, 0);

	glLoadIdentity();
	glBindTexture(GL_TEXTURE_2D, this->gameovertexture);

	double x_init = 0.5;
	double x_end = 0.8;
	double y_init = 0.1;
	double y_end = 0.3;
	double fattore_y = 0.4;

	if (this->keys[VK_UP]) {
		this->select = 0;
	}

	if (this->keys[VK_DOWN]) {
		this->select = 1;
	}

	//  TIMING - start
	clock_t t = clock();
	// elapsed time in seconds from the last draw
	double elapsed = double(t - Tstamp) / (double)CLOCKS_PER_SEC;
	// elapsed time in milliseconds from the last draw
	int ms_elapsed = (int)(t - Tstamp);
	// elapsed time in seconds from the beginning of the program
	this->fullElapsed = double(t - Tstart) / (double)CLOCKS_PER_SEC;
	this->frameTime += double(t - Tstamp) / (double)CLOCKS_PER_SEC;
	this->Tstamp = t;

	glBegin(GL_QUADS);
		// b-s
		glTexCoord2f(Background[0].u, Background[0].v);
		glVertex3f(Background[0].x, Background[0].y, Background[0].z);

		//b-d
		glTexCoord2f(Background[1].u, Background[1].v);
		glVertex3f(Background[1].x, Background[1].y, Background[0].z);

		//a-d
		glTexCoord2f(Background[2].u, Background[2].v);
		glVertex3f(Background[2].x, Background[2].y, Background[0].z);

		//a-s
		glTexCoord2f(Background[3].u, Background[3].v);
		glVertex3f(Background[3].x, Background[3].y, Background[0].z);

	glEnd();

	// NEW GAME BUTTON
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	int newgamebutton = (sizeof(newGame) / sizeof(*newGame));
	// new game

	int buttonId = (int(fullElapsed * 5) % newgamebutton);
	if (buttonId > newgamebutton) {
		buttonId = 0;
	}

	// se ho selezionato exit game lampeggia solo quello
	if (this->select != 0) {
		buttonId = 0;
	}
	glBindTexture(GL_TEXTURE_2D, newGame[buttonId]);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPushMatrix();
	glBegin(GL_QUADS);
		// b-s
		glTexCoord2f(Background[0].u, Background[0].v);
		glVertex3f(x_init, y_init, Background[0].z);
		//b-d
		glTexCoord2f(Background[1].u, Background[1].v);
		glVertex3f(x_end, y_init, Background[0].z);
		//a-d
		glTexCoord2f(Background[2].u, Background[2].v);
		glVertex3f(x_end, y_end, Background[0].z);
		//a-s
		glTexCoord2f(Background[3].u, Background[3].v);
		glVertex3f(x_init, y_end, Background[0].z);
	glEnd();


	// EXIT BUTTON
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	int buttonexitId = (int(fullElapsed * 5) % newgamebutton);
	if (buttonexitId > newgamebutton) {
		buttonexitId = 0;
	}
	// se ho selezionato new game lampeggia solo quello
	if (this->select != 1) {
		buttonexitId = 0;
	}

	glBindTexture(GL_TEXTURE_2D, exitGame[buttonexitId]);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPushMatrix();
	glBegin(GL_QUADS);

		// b-s
		glTexCoord2f(Background[0].u, Background[0].v);
		glVertex3f(x_init, y_init - fattore_y, Background[0].z);

		//b-d
		glTexCoord2f(Background[1].u, Background[1].v);
		glVertex3f(x_end, y_init - fattore_y, Background[0].z);

		//a-d
		glTexCoord2f(Background[2].u, Background[2].v);
		glVertex3f(x_end, y_end - fattore_y, Background[0].z);

		//a-s
		glTexCoord2f(Background[3].u, Background[3].v);
		glVertex3f(x_init, y_end - fattore_y, Background[0].z);

	glEnd();
	glDisable(GL_TEXTURE_2D);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//this->glPrint("Killer Pacman: Only One Rule : RUN Press Enter to Start!");

	if (this->keys[WM_LBUTTONDOWN]) {

		if (Data.mouseleft && !Data.mouseAlreadyPressed) {

			Data.mouseAlreadyPressed = true;
			double x = Data.cx;
			double y = Data.cy;

			if (x > x_init && x < x_end && y > y_init && y < y_end) {
				this->screenPlay = 1;
				this->resetGame();

			}

			if (x > x_init && x < x_end && y > y_init - fattore_y && y < y_end - fattore_y)
				this->keys[VK_ESCAPE] = true;
		}
	}

	if (this->keys[VK_RETURN]) {
		if (this->select == 0) {
			this->screenPlay = 1;
			this->resetGame();
		}
		else {
			this->keys[VK_ESCAPE] = true;
		}
	}

	if (this->screenPlay == 1) {
		soundBase->reset();
	}
	// reset color
	glColor3f(1.0, 1.0, 1.0);
}


void MyModel::resetGame() {
	this->screenPlay = 1;
	delete(collisionSystem);
	delete(levA);
	mario = PC(0.2, -0.6, 0.05, 0.1);
	pacman = EnemyPacman(-0.9, -0.6, 0.055, 0.1);
	Cloud1 = Sky(-1, 0.51, 1.02, 0.5);
	Cloud2 = Sky(1.01, 0.51, 1.02, 0.5);
	Mountain1 = Sky(-1.9, -0.35, 1.01, 0.4);
	Mountain2 = Sky(0.105, -0.35, 1.01, 0.4);
	posSchermoX = 0;
}

//  bitmap fonts
void MyModel::BuildFont(void){								// Build Our Bitmap Font
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
	try {
		vsprintf(text, fmt, ap);						// And Converts Symbols To Actual Number
	}
	catch (int e) {
		char out[100];
		sprintf(out, "error2");
		OutputDebugString(out);
		OutputDebugString("\n");
	}
	va_end(ap);											// Results Are Stored In Text

	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(base - 32);								// Sets The Base Character to 32
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
	glPopAttrib();										// Pops The Display List Bits
}

bool MyModel::checkX(PC mario, EnemyPacman pacman) {
	bool x = false;
	if ((mario.getX() <= pacman.getRight()) && mario.getX() >= pacman.getLeft()) {
		x = true;
	}
	return x;
}

bool MyModel::checkY(PC mario, EnemyPacman pacman) {
	bool y = false;
	// se la cordinata x del centro di mario è compresa fra gli estremi di pacman

	// stessa cosa per la y
	if ((mario.getY() <= pacman.getUp()) && mario.getY() >= pacman.getDown()) {
		y = true;
	}
	return y;
}

// controlla se mario è stato mangiato da pacman
bool MyModel::checkDead(PC mario, EnemyPacman pacman) {

	return this->checkX(mario, pacman) && this->checkY(mario, pacman);
}

// if pacman must jump
bool MyModel::pacmanMustJump(EnemyPacman pacman, Level* level) {
	double startA = level->getStartA();
	double endA = level->getEndA();
	double startB = level->getStartB();
	double endB = level->getEndB();
	double startC = level->getStartC();
	double endC = level->getEndC();
	
	if (startA <= pacman.getX() && pacman.getX() < endA) {
		// check only obs A
		vector<Ostacolo> floor = level->getFloorVectorA();
		vector<Ostacolo> obs = level->getObstacleVectorA();
		return searchEndOstacolo(pacman, floor, obs);

	}
	else if (startB <= pacman.getX() && pacman.getX() < endB) {
		// check only obs B

		vector<Ostacolo> floor = level->getFloorVectorB();
		vector<Ostacolo> obs = level->getObstacleVectorB();		
		return searchEndOstacolo(pacman, floor, obs);

	}
	else {
		// check only obs C
		vector<Ostacolo> floor = level->getFloorVectorC();
		vector<Ostacolo> obs = level->getObstacleVectorC();
		return searchEndOstacolo(pacman, floor, obs);

	}

}
bool MyModel::searchEndOstacolo(EnemyPacman pacman, vector<Ostacolo> floor, vector<Ostacolo> obs) {
	for (vector<Ostacolo>::iterator it = floor.begin(); it != floor.end(); ++it) {
		if (this->checkEndOstacolo(pacman, *it)) {
			return true;
		}
	}
	for (vector<Ostacolo>::iterator it = obs.begin(); it != obs.end(); ++it) {
		if (this->checkEndOstacolo(pacman, *it)) {
			return true;
		}
	}
	return false;
}
bool MyModel::checkEndOstacolo(EnemyPacman pacman, Ostacolo ostacolo) {

	if (ostacolo.getXFin() - 0.05 <= pacman.getX() && pacman.getX() <= ostacolo.getXFin() + 0.05){
	//if (ostacolo.getXFin() - 0.04 <= pacman.getX()) {
		return true;
	}
	/*else if(pacman.getY() > ostacolo.getYInit() && pacman.getY() < ostacolo.getYFin() && pacman.getX() >= ostacolo.getXInit() - 0.05)  {
		return true;
	}*/
	return false;
}

// Build texture pacman
void MyModel::buildPacman() {
	// se carico l'immagine evil pacman
	//int lengthPacman = (sizeof(pacmanTexture) / sizeof(*pacmanTexture))-1;

	int lengthPacman = (sizeof(pacmanTexture) / sizeof(*pacmanTexture)) ;
	//Pacman texture
	int pacmanId = (int(fullElapsed * 7) % lengthPacman);
	if (pacmanId > lengthPacman) {
		pacmanId = 0;
	}

	//pacmanId = 18;
	// PACMAN PRINT
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping

	glBindTexture(GL_TEXTURE_2D, pacmanTexture[pacmanId]);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);
	// original 0.38 e 0.34
	double resize_width = 0.33;
	double resize_height = 0.30;
	glBegin(GL_QUADS);
	if (std::strcmp(pacman.getState().c_str(), "left") == 0
		|| std::strcmp(pacman.getState().c_str(), "stopLeft") == 0
		|| std::strcmp(pacman.getState().c_str(), "upLeft") == 0 ) {
		//basso destra
		glTexCoord2f(Background[1].u - resize_width, Background[1].v + resize_height);
		glVertex3f(pacman.getLeft(), pacman.getDown(), Background[0].z);

		//basso sinistra
		glTexCoord2f(Background[0].u + resize_width, Background[0].v + resize_height);
		glVertex3f(pacman.getRight(), pacman.getDown(), Background[0].z);
		
		//alto sinistra
		glTexCoord2f(Background[3].u + resize_width, Background[3].v - resize_height);
		glVertex3f(pacman.getRight(), pacman.getUp(), Background[0].z);


		//alto destra
		glTexCoord2f(Background[2].u - resize_width, Background[2].v - resize_height);
		glVertex3f(pacman.getLeft(), pacman.getUp(), Background[0].z);

	}
	else {
		//basso sinistra
		glTexCoord2f(Background[0].u + resize_width, Background[0].v + resize_height);

		//glTexCoord2f(Background[0].u, Background[0].v);
		//glVertex3f(-1, -0.7, Background[0].z);
		glVertex3f(pacman.getLeft(), pacman.getDown(), Background[0].z);

		//basso destra
		glTexCoord2f(Background[1].u - resize_width, Background[1].v + resize_height);
		//glTexCoord2f(Background[1].u, Background[1].v);
		//glVertex3f(-0.8, -0.7, Background[0].z);
		glVertex3f(pacman.getRight(), pacman.getDown(), Background[0].z);


		//alto destra
		glTexCoord2f(Background[2].u - resize_width, Background[2].v - resize_height);
		//glTexCoord2f(Background[2].u, Background[2].v);
		//glVertex3f(-0.8, -0.45, Background[0].z);
		glVertex3f(pacman.getRight(), pacman.getUp(), Background[0].z);

		//alto sinistra
		glTexCoord2f(Background[3].u + resize_width, Background[3].v - resize_height);
		//glTexCoord2f(Background[3].u, Background[3].v);
		//glVertex3f(-1, -0.45, Background[0].z);
		glVertex3f(pacman.getLeft(), pacman.getUp(), Background[0].z);
	}
	glEnd();

	//glTranslatef(ClientX2World(cx), ClientY2World(cy), 0);

	// proportional scaling (fixed percentual of window dimension)
	// if(1) proportional, if(0) fixed
	//if (1) {
	//	glScalef(0.10f, 0.10f, 1);
	//}
	////  Fixed scaling, alwais 100 pixels width/height
	//else {
	//	float dx = PixToCoord_X(100);
	//	float dy = PixToCoord_Y(100);
	//	glScalef(dx / 2, dy / 2, 1);
	//}

	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);


}

// set pacman can move (pause game)
void MyModel::setPacmanCanMove(bool move) {
	pacmanCanMove = move;
}

// build mario texture
void MyModel::buildMario() {
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);

	int marioId = 0 ;

	// mario stop image blocked
	if (std::strcmp(mario.getState().c_str(), "stopLeft") == 0
		|| std::strcmp(mario.getState().c_str(), "stopRight") == 0 && !mario.getFalling()) {
		marioId = 0;
	// mario move
	}else if ((std::strcmp(mario.getState().c_str(), "left") == 0
		|| std::strcmp(mario.getState().c_str(), "right") == 0) && !mario.getFalling()) {
		int lengthMarioTexture = 2;
		marioId = (int(fullElapsed * 7) % lengthMarioTexture);
		if (marioId > lengthMarioTexture) {
			marioId = 0;
		}
	} else {
		// mario jump
		marioId = 3;
	}

	glBindTexture(GL_TEXTURE_2D, marioTexture[marioId]);

	glBegin(GL_QUADS);
	if (std::strcmp(mario.getState().c_str(), "left") == 0
		|| std::strcmp(mario.getState().c_str(), "stopLeft") == 0
		|| std::strcmp(mario.getState().c_str(), "upLeft") == 0) {
		// cambio i punti di ancoraggio della texture cosi facendo la ruoto

		//basso destra
		glTexCoord2f(Background[1].u, Background[1].v);
		glVertex3f(mario.getLeft(), mario.getDown(), Background[1].z);

		//basso sinistra
		glTexCoord2f(Background[0].u, Background[0].v);
		glVertex3f(mario.getRight(), mario.getDown(), Background[1].z);

		//alto sinistra
		glTexCoord2f(Background[3].u, Background[3].v);
		glVertex3f(mario.getRight(), mario.getUp(), Background[1].z);

		//alto destra
		glTexCoord2f(Background[2].u, Background[2].v);
		glVertex3f(mario.getLeft(), mario.getUp(), Background[1].z);
	}
	else {

		//basso sinistra
		glTexCoord2f(Background[0].u, Background[0].v);
		glVertex3f(mario.getLeft(), mario.getDown(), Background[1].z);

		//basso destra
		glTexCoord2f(Background[1].u, Background[1].v);
		glVertex3f(mario.getRight(), mario.getDown(), Background[1].z);

		//alto destra
		glTexCoord2f(Background[2].u, Background[2].v);
		glVertex3f(mario.getRight(), mario.getUp(), Background[1].z);

		//alto sinistra
		glTexCoord2f(Background[3].u, Background[3].v);
		glVertex3f(mario.getLeft(), mario.getUp(), Background[1].z);
	}


	glEnd();
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
}

// build floor texture
void MyModel::buildFloor(double start, double end) {
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	//"pulisco" il colore base"// Enable Texture Mapping

	// Terreno
	float blockFloorLength = 0.1;
	//float lengthGame = 8.5; // lunghezza che vogliamo dare al mondo
	// 2.5 vertice x fino al quale disegnare il background
	for (float i = start; i < end; i += blockFloorLength) {
		
		glBegin(GL_QUADS);

		//fattore di correzione x (per evitare bordi tra texture sovrapposizionate
		float x = 0.01;

		//basso sinistra
		glTexCoord2f(Background[0].u + x, Background[0].v + x);
		glVertex3f(i, Background[0].y, Background[0].z );

		//basso destra
		glTexCoord2f(Background[1].u - x, Background[1].v + x);
		glVertex3f(i + blockFloorLength, Background[1].y, Background[0].z );

		//alto destra
		glTexCoord2f(Background[2].u - x, Background[2].v);
		glVertex3f(i + blockFloorLength, Background[1].y + 0.3, Background[0].z );

		//alto sinistra
		glTexCoord2f(Background[3].u + x, Background[3].v);
		glVertex3f(i, Background[0].y + 0.3, Background[0].z );

		glEnd();
		
	}
	glDisable(GL_TEXTURE_2D);
}

// build sky texture
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

void MyModel::buildEnemy() {
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);

	int lengthEnemy = (sizeof(enemyTexture) / sizeof(*enemyTexture));
	//Pacman texture
	int enemyId = (int(fullElapsed * 7) % lengthEnemy);
	if (enemyId > lengthEnemy) {
		enemyId = 0;
	}

	//pacmanId = 18;
	// PACMAN PRINT

	glBindTexture(GL_TEXTURE_2D, enemyTexture[enemyId]);


	// original 0.38 e 0.34
	double resize_width = 0.0;
	double resize_height = 0.0;
	glBegin(GL_QUADS);
	OutputDebugString(enemy.getState().c_str());
	char stringdebug[200];
	sprintf(stringdebug, "Enemy l: %f, r:%f, u:%f, d:%f \n", enemy.getLeft(), enemy.getRight(), enemy.getUp(), enemy.getDown());
	OutputDebugString(stringdebug);


	if (std::strcmp(enemy.getState().c_str(), "left") == 0
		|| std::strcmp(enemy.getState().c_str(), "stopLeft") == 0
		|| std::strcmp(enemy.getState().c_str(), "upLeft") == 0) {
		//basso destra
		glTexCoord2f(Background[1].u - resize_width, Background[1].v + resize_height);
		glVertex3f(enemy.getLeft(), enemy.getDown(), Background[0].z);

		//basso sinistra
		glTexCoord2f(Background[0].u + resize_width, Background[0].v + resize_height);
		glVertex3f(enemy.getRight(), enemy.getDown(), Background[0].z);

		//alto sinistra
		glTexCoord2f(Background[3].u + resize_width, Background[3].v - resize_height);
		glVertex3f(enemy.getRight(), enemy.getUp(), Background[0].z);


		//alto destra
		glTexCoord2f(Background[2].u - resize_width, Background[2].v - resize_height);
		glVertex3f(enemy.getLeft(), enemy.getUp(), Background[0].z);

	}
	else {
		//basso sinistra
		glTexCoord2f(Background[0].u + resize_width, Background[0].v + resize_height);
		//glTexCoord2f(Background[0].u, Background[0].v);
		//glVertex3f(-1, -0.7, Background[0].z);
		glVertex3f(enemy.getLeft(), enemy.getDown(), Background[0].z);

		//basso destra
		glTexCoord2f(Background[1].u - resize_width, Background[1].v + resize_height);
		//glTexCoord2f(Background[1].u, Background[1].v);
		//glVertex3f(-0.8, -0.7, Background[0].z);
		glVertex3f(enemy.getRight(), enemy.getDown(), Background[0].z);


		//alto destra
		glTexCoord2f(Background[2].u - resize_width, Background[2].v - resize_height);
		//glTexCoord2f(Background[2].u, Background[2].v);
		//glVertex3f(-0.8, -0.45, Background[0].z);
		glVertex3f(enemy.getRight(), enemy.getUp(), Background[0].z);

		//alto sinistra
		glTexCoord2f(Background[3].u + resize_width, Background[3].v - resize_height);
		//glTexCoord2f(Background[3].u, Background[3].v);
		//glVertex3f(-1, -0.45, Background[0].z);
		glVertex3f(enemy.getLeft(), enemy.getUp(), Background[0].z);
	}
	glEnd();

	//glTranslatef(ClientX2World(cx), ClientY2World(cy), 0);

	// proportional scaling (fixed percentual of window dimension)
	// if(1) proportional, if(0) fixed

	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);


}

// build montain, cloud
void MyModel::buildLandscape(){
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);

	//fattore di correzione x
	float x = 0.003;
	
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	

		//basso sinistra
		glTexCoord2f(Background[0].u + x, Background[0].v + x);
		glVertex3f(Cloud1.getLeft(), Cloud1.getDown(), Background[1].z);

		//basso destra
		glTexCoord2f(Background[1].u - x, Background[1].v + x);
		glVertex3f(Cloud1.getRight(), Cloud1.getDown(), Background[1].z);

		//alto destra
		glTexCoord2f(Background[2].u - x, Background[2].v);
		glVertex3f(Cloud1.getRight(), Cloud1.getUp(), Background[1].z);

		//alto sinistra
		glTexCoord2f(Background[3].u + x, Background[3].v);
		glVertex3f(Cloud1.getLeft(), Cloud1.getUp(), Background[1].z);
	

	glEnd();

	glBegin(GL_QUADS);


	//basso sinistra
	glTexCoord2f(Background[0].u + x, Background[0].v + x);
	glVertex3f(Cloud2.getLeft(), Cloud2.getDown(), Background[1].z);

	//basso destra
	glTexCoord2f(Background[1].u - x, Background[1].v + x);
	glVertex3f(Cloud2.getRight(), Cloud2.getDown(), Background[1].z);

	//alto destra
	glTexCoord2f(Background[2].u - x, Background[2].v);
	glVertex3f(Cloud2.getRight(), Cloud2.getUp(), Background[1].z);

	//alto sinistra
	glTexCoord2f(Background[3].u + x, Background[3].v);
	glVertex3f(Cloud2.getLeft(), Cloud2.getUp(), Background[1].z);


	glEnd();


	glBindTexture(GL_TEXTURE_2D, texture[2]);

	glBegin(GL_QUADS);
	//basso sinistra
		glTexCoord2f(Background[0].u + x, Background[0].v);
		glVertex3f(Mountain1.getLeft(), Mountain1.getDown(), Background[1].z);

		//basso destra
		glTexCoord2f(Background[1].u - x, Background[1].v);
		glVertex3f(Mountain1.getRight(), Mountain1.getDown(), Background[1].z);

		//alto destra
		glTexCoord2f(Background[2].u - x, Background[2].v - x);
		glVertex3f(Mountain1.getRight(), Mountain1.getUp(), Background[1].z);

		//alto sinistra
		glTexCoord2f(Background[3].u + x, Background[3].v - x);
		glVertex3f(Mountain1.getLeft(), Mountain1.getUp(), Background[1].z);
	glEnd();

	glBegin(GL_QUADS);
		//basso sinistra
		glTexCoord2f(Background[0].u + x, Background[0].v);
		glVertex3f(Mountain2.getLeft(), Mountain2.getDown(), Background[1].z);

		//basso destra
		glTexCoord2f(Background[1].u - x, Background[1].v);
		glVertex3f(Mountain2.getRight(), Mountain2.getDown(), Background[1].z);

		//alto destra
		glTexCoord2f(Background[2].u - x, Background[2].v - x);
		glVertex3f(Mountain2.getRight(), Mountain2.getUp(), Background[1].z);

		//alto sinistra
		glTexCoord2f(Background[3].u + x, Background[3].v - x);
		glVertex3f(Mountain2.getLeft(), Mountain2.getUp(), Background[1].z);
	glEnd();

	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);


}

// draw obs
void MyModel::drawLevel() {

	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);

	//fattore di correzione x
	float x = 0;
	// può essere disegnato una sola volta non tutte le volte

	glBindTexture(GL_TEXTURE_2D, texture[3]);
	vector<Ostacolo> obstacleList = levA->getObstacleVectorA();

	for (vector<Ostacolo>::iterator it = obstacleList.begin(); it != obstacleList.end(); ++it) {
		
		glBegin(GL_QUADS);


		//basso sinistra
		glTexCoord2f(Background[0].u + x, Background[0].v + x);
		glVertex3f(it->getXInit(), it->getYInit(), Background[1].z);

		//basso destra
		glTexCoord2f(Background[1].u - x, Background[1].v + x);
		glVertex3f(it->getXFin(), it->getYInit(), Background[1].z);

		//alto destra
		glTexCoord2f(Background[2].u - x, Background[2].v);
		glVertex3f(it->getXFin(), it->getYFin(), Background[1].z);

		//alto sinistra
		glTexCoord2f(Background[3].u + x, Background[3].v);
		glVertex3f(it->getXInit(), it->getYFin(), Background[1].z);


		glEnd();
	
	}

	obstacleList = levA->getObstacleVectorB();
	for (vector<Ostacolo>::iterator it = obstacleList.begin(); it != obstacleList.end(); ++it) {

		glBegin(GL_QUADS);

		//basso sinistra
		glTexCoord2f(Background[0].u + x, Background[0].v + x);
		glVertex3f(it->getXInit(), it->getYInit(), Background[1].z);

		//basso destra
		glTexCoord2f(Background[1].u - x, Background[1].v + x);
		glVertex3f(it->getXFin(), it->getYInit(), Background[1].z);

		//alto destra
		glTexCoord2f(Background[2].u - x, Background[2].v);
		glVertex3f(it->getXFin(), it->getYFin(), Background[1].z);

		//alto sinistra
		glTexCoord2f(Background[3].u + x, Background[3].v);
		glVertex3f(it->getXInit(), it->getYFin(), Background[1].z);


		glEnd();
	}


	obstacleList = levA->getObstacleVectorC();
	for (vector<Ostacolo>::iterator it = obstacleList.begin(); it != obstacleList.end(); ++it) {

		glBegin(GL_QUADS);

		//basso sinistra
		glTexCoord2f(Background[0].u + x, Background[0].v + x);
		glVertex3f(it->getXInit(), it->getYInit(), Background[1].z);

		//basso destra
		glTexCoord2f(Background[1].u - x, Background[1].v + x);
		glVertex3f(it->getXFin(), it->getYInit(), Background[1].z);

		//alto destra
		glTexCoord2f(Background[2].u - x, Background[2].v);
		glVertex3f(it->getXFin(), it->getYFin(), Background[1].z);

		//alto sinistra
		glTexCoord2f(Background[3].u + x, Background[3].v);
		glVertex3f(it->getXInit(), it->getYFin(), Background[1].z);


		glEnd();
	}

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	//costruisco il pavimento
	vector<Ostacolo> groundList = levA->getFloorVectorA();
	for (vector<Ostacolo>::iterator it = groundList.begin(); it != groundList.end(); ++it) {

		float blockFloorLength = 0.1;
		for (float i = it->getXInit(); i < it->getXFin(); i += blockFloorLength) {

			glBegin(GL_QUADS);

			//fattore di correzione x (per evitare bordi tra texture sovrapposizionate
			float x = 0.01;

			//basso sinistra
			glTexCoord2f(Background[0].u + x, Background[0].v + x);
			glVertex3f(i, Background[0].y, Background[0].z);

			//basso destra
			glTexCoord2f(Background[1].u - x, Background[1].v + x);
			glVertex3f(i + blockFloorLength, Background[1].y, Background[0].z);

			//alto destra
			glTexCoord2f(Background[2].u - x, Background[2].v);
			glVertex3f(i + blockFloorLength, Background[1].y + 0.3, Background[0].z);

			//alto sinistra
			glTexCoord2f(Background[3].u + x, Background[3].v);
			glVertex3f(i, Background[0].y + 0.3, Background[0].z);

			glEnd();

		}
	}
		
	groundList = levA->getFloorVectorB();
	for (vector<Ostacolo>::iterator it = groundList.begin(); it != groundList.end(); ++it) {

		float blockFloorLength = 0.1;
		for (float i = it->getXInit(); i < it->getXFin(); i += blockFloorLength) {

			glBegin(GL_QUADS);

			//fattore di correzione x (per evitare bordi tra texture sovrapposizionate
			float x = 0.01;

			//basso sinistra
			glTexCoord2f(Background[0].u + x, Background[0].v + x);
			glVertex3f(i, Background[0].y, Background[0].z);

			//basso destra
			glTexCoord2f(Background[1].u - x, Background[1].v + x);
			glVertex3f(i + blockFloorLength, Background[1].y, Background[0].z);

			//alto destra
			glTexCoord2f(Background[2].u - x, Background[2].v);
			glVertex3f(i + blockFloorLength, Background[1].y + 0.3, Background[0].z);

			//alto sinistra
			glTexCoord2f(Background[3].u + x, Background[3].v);
			glVertex3f(i, Background[0].y + 0.3, Background[0].z);

			glEnd();

		}


	}
	
	groundList = levA->getFloorVectorC();
	for (vector<Ostacolo>::iterator it = groundList.begin(); it != groundList.end(); ++it) {

		float blockFloorLength = 0.1;
		for (float i = it->getXInit(); i < it->getXFin(); i += blockFloorLength) {

			glBegin(GL_QUADS);

			//fattore di correzione x (per evitare bordi tra texture sovrapposizionate
			float x = 0.01;

			//basso sinistra
			glTexCoord2f(Background[0].u + x, Background[0].v + x);
			glVertex3f(i, Background[0].y, Background[0].z);

			//basso destra
			glTexCoord2f(Background[1].u - x, Background[1].v + x);
			glVertex3f(i + blockFloorLength, Background[1].y, Background[0].z);

			//alto destra
			glTexCoord2f(Background[2].u - x, Background[2].v);
			glVertex3f(i + blockFloorLength, Background[1].y + 0.3, Background[0].z);

			//alto sinistra
			glTexCoord2f(Background[3].u + x, Background[3].v);
			glVertex3f(i, Background[0].y + 0.3, Background[0].z);

			glEnd();

		}


	}
	glDisable(GL_TEXTURE_2D);

}



