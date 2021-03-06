
#include <windows.h>		// Header File For Windows
#include <stdio.h>			// Header File For Standard Input/Output
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <iostream> 
using namespace std;


#include "Model.h"

#include "audiere.h"
#include "resource.h"
using namespace audiere;


#ifdef _MSC_VER                         // Check if MS Visual C compiler
	#pragma comment( lib, "opengl32.lib" )				// Search For OpenGL32.lib While Linking 
	#pragma comment( lib, "glu32.lib" )						// Search For GLu32.lib While Linking			
#endif
//#pragma comment( lib, "winmm.lib" )						// Search For WinMM Library While Linking

class MyModel Data;

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc

///////////////////////////////////////////////////////////
//  kill the window
GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (Data.fullscreen){									// Are We In Fullscreen Mode?
		ChangeDisplaySettings(NULL,0);			// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (Data.hRC){											// Do We Have A Rendering Context?	
		if (!wglMakeCurrent(NULL,NULL))	{				// Are We Able To Release The DC And RC Contexts?
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
  	
		if (!wglDeleteContext(Data.hRC)) {			// Are We Able To Delete The RC?
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		Data.hRC=NULL;										// Set RC To NULL
	}

	if (Data.hDC && !ReleaseDC(Data.hWnd,Data.hDC)) {		// Are We Able To Release The DC
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		Data.hDC=NULL;										// Set DC To NULL
	}

	if (Data.hWnd && !DestroyWindow(Data.hWnd)) {			// Are We Able To Destroy The Window?
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		Data.hWnd=NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("Basic2D",Data.hInstance)) {		// Are We Able To Unregister Class
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		Data.hInstance=NULL;									// Set hInstance To NULL
	}
}
///////////////////////////////////////////////////////////
//  create the window
/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *	title			- Title To Appear At The Top Of The Window				*
 *	width			- Width Of The GL Window Or Fullscreen Mode				*
 *	height			- Height Of The GL Window Or Fullscreen Mode			*
 *	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
 *	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/
 
BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)width;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height

	Data.fullscreen=fullscreenflag;			// Set The Global Fullscreen Flag

	Data.hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= Data.hInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= "Basic2D";								// Set The Class Name

	if (!RegisterClass(&wc)) {									// Attempt To Register The Window Class
	
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}
	
	if (Data.fullscreen){												// Attempt Fullscreen Mode?
	
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL){
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES){
				Data.fullscreen=FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (Data.fullscreen) {												// Are We Still In Fullscreen Mode?
		dwExStyle=WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle=WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(Data.hWnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
								"Basic2D",							// Class Name
								title,								// Window Title
								dwStyle |							// Defined Window Style
								WS_CLIPSIBLINGS |					// Required Window Style
								WS_CLIPCHILDREN,					// Required Window Style
								0, 0,								// Window Position
								WindowRect.right-WindowRect.left,	// Calculate Window Width
								WindowRect.bottom-WindowRect.top,	// Calculate Window Height
								NULL,								// No Parent Window
								NULL,								// No Menu
								Data.hInstance,							// Instance
								NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};
	
	if (!(Data.hDC=GetDC(Data.hWnd))) {				// Did We Get A Device Context?
	
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(Data.hDC,&pfd))) {	// Did Windows Find A Matching Pixel Format?
	
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!SetPixelFormat(Data.hDC,PixelFormat,&pfd)) {		// Are We Able To Set The Pixel Format?
	
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(Data.hRC=wglCreateContext(Data.hDC))) {				// Are We Able To Get A Rendering Context?
	
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!wglMakeCurrent(Data.hDC,Data.hRC)) {					// Try To Activate The Rendering Context
	
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(Data.hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(Data.hWnd);						// Slightly Higher Priority
	SetFocus(Data.hWnd);									// Sets Keyboard Focus To The Window
	Data.ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!Data.InitGL()) {								// Initialize Our Newly Created GL Window
	
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Initialization Failed OpenGL.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}


// CALLBACK FUNCTION
LRESULT CALLBACK WndProc(HWND hWnd, UINT	uMsg, WPARAM	wParam,	LPARAM	lParam)			
{
	switch (uMsg) {									// Check For Windows Messages

		case WM_ACTIVATE: {		
			// TODO premere invio se giococ in pausa per riprenderlo
			Data.setPacmanCanMove(true);
			// Watch For Window Activate Message
			if (!HIWORD(wParam)) { 					// Check Minimization State
				Data.active = TRUE;
			}					// Program Is Active
			else {
				Data.active = FALSE;
			}		// Program Is No Longer Active
			return 0;								      // Return To The Message Loop
		}

						  // mouse move
		case WM_MOUSEMOVE: {
			POINTS p;
			p = MAKEPOINTS(lParam);
			Data.cx = p.x; Data.cy = p.y;
			break;
		}

		case WM_LBUTTONDOWN: {

			Data.keys[WM_LBUTTONDOWN] = true;
			POINTS ppo = MAKEPOINTS(lParam);


			RECT rect;
			GetWindowRect(hWnd, &rect);
			double width = rect.right - rect.left;
			double height = rect.bottom - rect.top;

			Data.cx = ((double)ppo.x * 2.028) / width - 1;
			Data.cy = (((double)ppo.y * 2.11) / height - 1)*(-1);

			Data.mouseleft = true;
			//	Cattura il mouse, usare l'help per capire perch� serve.
			//	Ricordarsi sempre di liberarlo all'UP !
			//	Capture of the mouse. Use the help to understand why is required.
			//	You must release the mouse on the UP message!
			SetCapture(hWnd);
			return 0;
			
		}


		case WM_LBUTTONUP: {
			Data.mouseAlreadyPressed = false;
			if (Data.mouseleft) {
				Data.keys[WM_LBUTTONDOWN] = false;
				Data.keys[WM_LBUTTONUP] = true;
				Data.mouseleft = false;

				//	Always release the mouse after a SetCapture !
				//	Try to comment the following line: you cannot kill the program!
				ReleaseCapture();
			}
			return 0;
		}


			
		case WM_SYSCOMMAND: {							// Intercept System Commands
		
			switch (wParam) {							// Check System Calls
				case SC_SCREENSAVE:					// Screensaver Trying To Start?
				case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
					return 0;							// Prevent From Happening
			}
			break;									// Exit
		}

		case WM_CLOSE: {								// Did We Receive A Close Message?
			PostQuitMessage(0);					// Send A Quit Message
			return 0;								    // Jump Back
		}

		case WM_KEYDOWN: {					
			// set key button true
			Data.keys[wParam] = TRUE;		
			return 0;								
		}

		case WM_KEYUP: {								
			// relase button
			Data.keys[wParam] = FALSE;	
			return 0;								
		}

		case WM_SIZE: {
			// LoWord=Width, HiWord=Height
			Data.ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  
			return 0;
		}
		
		case WM_KILLFOCUS: {
			//TODO
			// lost focus try to set game in pause
			Data.keys[VK_LEFT] = false;
			Data.keys[VK_UP] = false;
			Data.keys[VK_RIGHT] = false;
			Data.keys[VK_DOWN] = false;
			Data.setPacmanCanMove(false);

			return 0;
		}
	}

	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

//  Main program
int WINAPI WinMain(	HINSTANCE	hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	MSG		msg;									// Windows Message Structure
	BOOL	done=FALSE;								// Bool Variable To Exit Loop

	// Ask The User Which Screen Mode They Prefer
	// Init of the default button depending on Data.fullscreen
	unsigned long Def = MB_DEFBUTTON1;
	if( !Data.fullscreen ) 
		Def = MB_DEFBUTTON2;
	/*
	if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?",
	"Start FullScreen?",MB_YESNO|MB_ICONQUESTION | Def) == IDNO)
	{
		Data.fullscreen=FALSE;							// Windowed Mode
	}
	*/
	Data.fullscreen=false;  // removed the boring request...

	// Create Our OpenGL Window --> dimensione 640 480
	if (!CreateGLWindow("Killer Pacman", 1280, 720, 16,Data.fullscreen)){
		return 0;									// Quit If Window Was Not Created
	}

	//  AUDIO device start
	AudioDevicePtr device(OpenDevice());
	if (!device) {
		return 0;         // failure
	}

	OutputStreamPtr stream(OpenSound(device, "Data/superMario_sound.mp3", true));
	if (!stream) {
		return 0;         // failure
	}
	// jump mario
	

	// music in sottofondo
	stream->setRepeat(true);
	stream->setVolume(0.5f); // 50% volume
	stream->play();
	/*
	OutputStreamPtr explosion(OpenSound(device, "Data/explosion.wav", false));
	OutputStreamPtr bell(OpenSound(device, "Data/bell.wav", false));
	OutputStreamPtr stupid(OpenSound(device, "Data/stupid.wav", false));
	*/
	OutputStreamPtr dead(OpenSound(device, "Data/PacManGameOver.mp3", false));
	if (!dead) {
		return 0;         // failure
	}
	OutputStreamPtr jumpSound(OpenSound(device, "Data/Mario_jump_sound.mp3", true));
	if (!jumpSound) {
		return 0;         // failure
	}
	
	OutputStreamPtr winSound(OpenSound(device,"Data/WeAreTheChampions.mp3"));
	if (!winSound) {
		return 0;
	}

	OutputStreamPtr stageClear(OpenSound(device, "Data/smb_stage_clear.wav"));
	if (!stageClear) {
		return 0;
	}

	// loop main principale
	while(!done) {

		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE)) {	
	
			if (msg.message==WM_QUIT) {				
				done=TRUE;							
			}else { 
				TranslateMessage(&msg);	
				DispatchMessage(&msg);			
			}
		}else{
			
			// press esc key and drawGLScene() --> code che aaggiorna la pagina
			if ((Data.active && !Data.DrawGLScene(dead,jumpSound,winSound,stream)) || Data.keys[VK_ESCAPE]) {
				done=TRUE;							
			}else{ 
				SwapBuffers(Data.hDC);					// Swap Buffers (Double Buffering)
			}

		}
	}

	// Shutdown
	KillGLWindow();									
	return (msg.wParam);							
}
