#pragma once

#include "UI.h"
#include "DM2231_Model.h"
#include "Mouse.h"


class DM2231_View
{
public:
	DM2231_View(DM2231_Model* theModel);
	~DM2231_View(void);
	// Draw the view
	BOOL Draw(void);

	int InitGL(GLvoid);										// All Setup For OpenGL Goes Here
	BOOL CreateGLWindow(char* title, int width, int height, int bits);
	GLvoid ReSizeGLScene(GLsizei width, GLsizei height);		// Resize And Initialize The GL Window
	GLvoid KillGLWindow(GLvoid);

private:
	DM2231_Model* theModel;
	UI* theUI;
	HDC hDC; // Private GDI Device Context
	HGLRC hRC; // Permanent Rendering Context
	HWND hWnd; // Holds Our Window Handle
	HINSTANCE hInstance; // Holds The Instance Of The Application

	bool m_bActive; // Window Active Flag Set To TRUE By Default
	bool m_bFullScreen; // Fullscreen Flag Set To Fullscreen Mode By Default
	bool keys[256]; // Array Used For The Keyboard Routine
	int m_iWindows_Width, m_iWindows_Height;

	GLfloat rtri; // Angle For The Triangle ( NEW )
	GLfloat rquad; // Angle For The Quad ( NEW )

	virtual LRESULT CALLBACK MsgProc(HWND, UINT, WPARAM, LPARAM); // Declaration For WndProc
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); // Declaration For WndProc


	GLuint	base;				// Base Display List For The Font Set
	GLvoid BuildFont(GLvoid);
	GLvoid KillFont(GLvoid);
	GLvoid glPrint(const char *fmt, ...);

public:
	// Check if the player wants to quit the game
	bool isQuitGame(void);
	// Check if the player wants to play the game in Full Screen
	bool runFullScreen(void);
	// Toggle the game to be fullscreen or otherwise
	bool toggleFullScreen(void);
	// Set the fullscreen display status
	void setFullScreen(bool m_bFullScreen);

	bool GetKeys(char s);
	void SetKeys(char g);

	bool GetBackspace();
	void SetBackspace(bool set);

	bool GetEnter();
	void SetEnter(bool set);

	bool LMKeyDown;
	bool RMKeyDown;

	//name
	void PrintName(float x, float y, float z, const GLuint &base, char *fmt, ...);
};
