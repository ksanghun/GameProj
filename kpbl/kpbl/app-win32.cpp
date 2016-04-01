/******************************************************************************
Andoid Jni-OpenLG Tester by Sanghun Kim
3/23/16
******************************************************************************/
#include <stdio.h>
#include <windows.h>
#include <TCHAR.h>


#include "egl.h"
#include "glext.h"

#include "../jni_tester/Game2048.h"


/******************************************************************************
Defines
*****************************************************************************/
// Width and height of the window
#define WINDOW_WIDTH	480
#define WINDOW_HEIGHT	800
#define WINDOW_BPP		16
//#define	WINDOW_CLASS _T("GO_KPBL")
#define TRANSPARENT_COLOR RGB(16, 16, 0)

/******************************************************************************
Global variables
******************************************************************************/
int gAppAlive = 1;
kpbl::CGame2048* pGame = nullptr;

//static HINSTANCE sInstance;
static const _TCHAR sAppName[] =
_T("Android LIB Test (by KPBL)");
static HWND sWnd;
static int sWindowWidth = WINDOW_WIDTH;
static int sWindowHeight = WINDOW_HEIGHT;
static EGLDisplay sEglDisplay = EGL_NO_DISPLAY;
static EGLConfig sEglConfig;
static EGLContext sEglContext = EGL_NO_CONTEXT;
static EGLSurface sEglSurface = EGL_NO_SURFACE;


static void checkEGLError()
{
	EGLint error = eglGetError();
	if (error != EGL_SUCCESS)
	{
		_TCHAR errorString[32];
		_stprintf(errorString, _T("0x%04x"), error);
		MessageBox(NULL, errorString, _T("EGL Initialization Error"), MB_OK);
	}
}

/***** Callback *****/
void RTestSwapBuffer()
{	
	eglSwapBuffers(sEglDisplay, sEglSurface);
	checkEGLError();
}


static BOOL initEGL(HWND wnd)
{
	EGLint				pi32ConfigAttribs[128];
	int i = 0;
	pi32ConfigAttribs[i++] = EGL_RED_SIZE;
	pi32ConfigAttribs[i++] = 5;
	pi32ConfigAttribs[i++] = EGL_GREEN_SIZE;
	pi32ConfigAttribs[i++] = 6;
	pi32ConfigAttribs[i++] = EGL_BLUE_SIZE;
	pi32ConfigAttribs[i++] = 5;
	pi32ConfigAttribs[i++] = EGL_ALPHA_SIZE;
	pi32ConfigAttribs[i++] = 0;
	pi32ConfigAttribs[i++] = EGL_SURFACE_TYPE;
	pi32ConfigAttribs[i++] = EGL_WINDOW_BIT;
	pi32ConfigAttribs[i++] = EGL_DEPTH_SIZE;
	pi32ConfigAttribs[i++] = 16;
	pi32ConfigAttribs[i++] = EGL_SAMPLE_BUFFERS;
	pi32ConfigAttribs[i++] = 1;
	pi32ConfigAttribs[i++] = EGL_SAMPLES;
	pi32ConfigAttribs[i++] = 4;
	pi32ConfigAttribs[i++] = EGL_NONE;

	HDC	hDC		= 0;
	EGLBoolean success;
	int iConfigs;
	hDC = GetDC(wnd);
	sEglDisplay = eglGetDisplay((NativeDisplayType) hDC);
	if(sEglDisplay == EGL_NO_DISPLAY)
		sEglDisplay = eglGetDisplay((NativeDisplayType) EGL_DEFAULT_DISPLAY);

	EGLint iMajorVersion, iMinorVersion;
	success = eglInitialize(sEglDisplay, &iMajorVersion, &iMinorVersion);
	if(success!=EGL_FALSE)
		success = eglChooseConfig(sEglDisplay, pi32ConfigAttribs, &sEglConfig, 1, &iConfigs);
	if(success!=EGL_FALSE){
		sEglSurface = eglCreateWindowSurface(sEglDisplay, sEglConfig, wnd, NULL);
		if(sEglSurface == EGL_NO_SURFACE)
			success =EGL_FALSE;
	}
	if(success!=EGL_FALSE){
		sEglContext = eglCreateContext(sEglDisplay, sEglConfig, NULL, NULL);
		if(sEglContext==EGL_NO_CONTEXT)
			success = EGL_FALSE;
	}
	if(success!=EGL_FALSE)
		success = eglMakeCurrent(sEglDisplay, sEglSurface, sEglSurface, sEglContext);

	if(success==EGL_FALSE)
		checkEGLError();	

	return TRUE;
}

static void deinitEGL()
{
	if(pGame) 
		delete pGame;
}

//void RenderScene(int w, int h)
//void RenderScene(int w, int h)
//{
//	pGame->RenderReady();
//
//	eglSwapBuffers(sEglDisplay, sEglSurface);
//	checkEGLError();
//
//}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT rc;
	int useDefWindowProc=0;

	switch (message)
	{
		// Handles the close message when a user clicks the quit icon of the window
	case WM_CLOSE:
		DestroyWindow(hWnd);
		gAppAlive = 0;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		gAppAlive = 0;
		break;
	case WM_SIZE:
		GetClientRect(sWnd, &rc);
		sWindowWidth = rc.right;
		sWindowHeight = rc.bottom;
		break;

	case WM_LBUTTONDOWN:
		{		
      POINT pt;
			pt.x=(long)LOWORD(lParam);
			pt.y=(long)HIWORD(lParam);		
      pGame->setStartPosition(pt.x, pt.y);
		}
		break;

	case WM_LBUTTONUP:
		{
      POINT pt;
			pt.x = (long)LOWORD(lParam);
			pt.y = (long)HIWORD(lParam);	
      pGame->makeMove(pt.x, pt.y);
		}
		break;
    
	case WM_MOUSEMOVE:
		{			
		}
		break;

	case WM_RBUTTONDOWN:
		{
		}
		break;

	case WM_KEYDOWN:
		{
		}

	default:
		useDefWindowProc =1;
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);;
}

//******************************************************************************
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	MSG msg;
	WNDCLASS wc;
	DWORD windowStyle;
	int windowX, windowY;

	// Register the windows class
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = 0;
	wc.hCursor = 0;
	wc.lpszMenuName = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = sAppName;

	if(!RegisterClass(&wc))
		return FALSE;

	windowStyle = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VISIBLE;
	windowStyle |= WS_OVERLAPPEDWINDOW;
	windowX = CW_USEDEFAULT;
	windowY = 0;
	sWnd = CreateWindow(sAppName, sAppName, windowStyle, windowX, windowY,sWindowWidth, sWindowHeight,	NULL, NULL, hInstance, NULL);

	if(!sWnd)		
		return FALSE;

	ShowWindow(sWnd, nCmdShow);
	UpdateWindow(sWnd);


	// EGL initialization //
	if (!initEGL(sWnd)){
		return FALSE;
	}


	//=================Creage GL View===============================//
	pGame = new kpbl::CGame2048;
	kpbl::FnTestCallback pFn = RTestSwapBuffer;	
	if (pGame->Initialize(pFn) == false){
		MessageBox(NULL, NULL, _T("EGL Initialization Error"), MB_OK);
		return FALSE;
	}
	pGame->RenderReady();
	//================================================================//

	while(gAppAlive){
		while(PeekMessage(&msg, sWnd, 0,0,PM_NOREMOVE)){
			if(GetMessage(&msg, sWnd, 0,0)){
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
				gAppAlive = 0;
		}

		
		if(gAppAlive){		
			pGame->Render();			
			Sleep(200);
		}
	}

	return 0;	
}

