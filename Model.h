//  world geometry
// eye    (0,0,0)
// center (0,0,-1)
// up     (0,1,0)
// left -1, right 1
//  top & bottom centered on Y to match the window aspect ratio
// clipping planes: 1, 5.1

#pragma warning(disable: 4996)

#include <vector>
#include <time.h>
#include <math.h>
# include "Level.h"
# include "Ostacolo.h"
#include "audiere.h"
#include "PC.h"
#include "EnemyPacman.h"
#include "Ostacolo.h"
#define PI 3.141592654

// A class for storing vetices
//  Vertex
class Vertex {
	public:

		float x, y, z;     // 3d coordinate of the vertex
		float Nx, Ny, Nz;     // Normal to the surface (if present)
		float u, v;						// texture coordinates
		float r, g, b;				// Color (0.0 -  1.0)

		Vertex() {}
		Vertex(float x, float y, float z): x(x), y(y), z(z) { }
		Vertex(float x, float y, float z, float u, float v): x(x), y(y), z(z), u(u), v(v) { }
		inline void SetP(float x,float y,float z) { this->x = x; this->y = y;
		this->z = z; }
		inline void SetN(float x,float y,float z) { Nx = x; Ny = y; Nz = z; }
};


class MyModel {
	public:
		//  general data for window and input controls
		HDC			hDC;		        // Private GDI Device Context
		HGLRC		hRC;		        // Permanent Rendering Context
		HWND		hWnd;		        // Holds Our Window Handle
		HINSTANCE	hInstance;		// Holds The Instance Of The Application

		bool	keys[256];			// Array Used For The Keyboard Routine
		bool	active;		      // Window Active Flag Set To TRUE By Default
		bool cursor;          // true if visible
		bool captured;        // true if the mouse is captured
		double cx, cy;           // client position of the cursor
		bool mouseleft;
		bool	fullscreen;	    // Fullscreen Flag 
		bool mouseAlreadyPressed;

	private:
		//  projection limits in X and Y: x in [-plx, plx], y in [-ply, ply]
		double plx, ply;
		int Wheight, Wwidth;  // window dimensions in pixels

		int frames;           // n. of frames
		double frameTime;     // for fps computation
		double fps;
		double LastUpdateTime;
  
		double xStartGame; // coordinate x per l'inizio e la fine del gioco 
		double xEndGame;
		bool init;
		// per selezionare la schermata da caricare
		int screenPlay=0;

		//  model data
		std::vector<Vertex> Background;   // background
		std::vector<Vertex> fire;         // floating fire
		std::vector<Vertex> curs;         // floating cursor
		clock_t Tstamp, Tstart;
		double fullElapsed;  // elapsed time in seconds from the beginning of the program
		int lastTimeChangeVelocityPacman; // valore per aumentare progressivamente la velocità di pacman se si gioca troppo

		GLuint	texture[28];	
		// Storage For 28 Textures!
//		GLuint	pacmanTexture[19];
		GLuint	pacmanTexture[2];
		GLuint backgroundtexture;
		GLuint wintexture;
		GLuint gameovertexture;
		GLuint	marioTexture[8];
		GLuint newGame[2];
		GLuint exitGame[2];
		int select = 0;

		GLuint	base;				// Base Display List For The Font Set
	public:
		//  methods
		MyModel(): hDC(NULL), hRC (NULL), hWnd (NULL), active (true), fullscreen(true), frames(0), fps(0), cursor(true), captured(false) {
    
			Background.clear();

			Background.push_back(Vertex(-1,-1,-5,0,0));
			Background.push_back(Vertex( 1,-1,-5,1,0));
			Background.push_back(Vertex( 1, 1,-5,1,1));
			Background.push_back(Vertex(-1, 1,-5,0,1));
    
			fire.clear();
			fire.push_back(Vertex(-1,-1,-5,0,0));
			fire.push_back(Vertex( 1,-1,-5,1,0));
			fire.push_back(Vertex( 1, 1,-5,1,1));
			fire.push_back(Vertex(-1, 1,-5,0,1));

			curs.clear();
			curs.push_back(Vertex(-1,-1,-4,0,0));
			curs.push_back(Vertex( 1,-1,-4,1,0));
			curs.push_back(Vertex( 1, 1,-4,1,1));
			curs.push_back(Vertex(-1, 1,-4,0,1));

			this->Tstart = this->Tstamp = clock();
			this->fullElapsed = 0;
			this->frameTime = 0;
			this->LastUpdateTime = 0;
	
			// set x start and x end
			this->xStartGame = -1;
			this->xEndGame = 31;
			this->lastTimeChangeVelocityPacman = 1;
			// to build same thing once
			this->init = true;

		}
		~MyModel() {
			this->KillFont();
		}
	
		inline bool IsInClient(int x, int y) {
			if( x >= 0 && x < Wwidth && y >= 0 && y < Wheight ) return true;
			return false;
		}

		bool DrawGLScene(audiere::OutputStreamPtr dead, audiere::OutputStreamPtr jump, audiere::OutputStreamPtr winSound, audiere::OutputStreamPtr soundBase);
		bool InitGL(void);
		void ReSizeGLScene(int width, int height);
		void glPrint(const char *fmt, ...);			// Custom GL "Print" Routine
		void updateWorld(audiere::OutputStreamPtr jump, audiere::OutputStreamPtr dead);
		void buildFloor(double start, double end);
		void buildSky();
		void buildMario();
		//void buildLevel0();
		void buildPacman();
		void buildLandscape();
		void drawInitGame();
		void drawGameOver(audiere::OutputStreamPtr soundBase);
		void drawWinGame(audiere::OutputStreamPtr soundBase);
		void resetGame();
		bool checkX(PC mario, EnemyPacman pacman);
		bool checkY(PC mario, EnemyPacman pacman);
		bool checkDead(PC mario, EnemyPacman pacman);
		bool pcCanMove(PC mario);
		bool checkEndOstacolo(EnemyPacman pacman, Ostacolo ostacolo);
		bool searchEndOstacolo(EnemyPacman pacman, vector<Ostacolo> floor, vector<Ostacolo> obs);
		bool pacmanMustJump(EnemyPacman pacman, Level* level);
		void drawGamePrincipale(audiere::OutputStreamPtr dead, audiere::OutputStreamPtr jump);
		void drawLevel();
		void setPacmanCanMove(bool);
	private:
		bool LoadGLTextures(void);
		void BuildFont(void);
		void KillFont(void);
		//  Conversion from pixel distance to float X and Y distance
		inline float PixToCoord_X(int pix){ 
		  return ( 2.0f * (float) pix * (float) plx ) / (float) Wwidth; 
		}

		inline float PixToCoord_Y(int pix){ 
			return ( 2.0f * (float) pix * (float) ply ) / (float) Wheight; 
		}

		//  conversion from client coordinates to 3d world coordinates
		inline float ClientX2World(int x) {
			return ( (2.0f * float(plx) * float(x) / float(Wwidth)) - float(plx));
		}

		inline float ClientY2World(int y) {
			return ( float(ply) - (2.0f * float(ply) * float(y) / float(Wheight)));
		}

  

};

extern class MyModel Data;