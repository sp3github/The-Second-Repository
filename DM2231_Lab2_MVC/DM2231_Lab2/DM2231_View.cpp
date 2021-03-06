#include "DM2231_View.h"

//FROM NEHE
GLvoid DM2231_View::BuildFont(GLvoid)								// Build Our Bitmap Font
{
	HFONT	font;										// Windows Font ID
	HFONT	oldfont;									// Used For Good House Keeping

	base = glGenLists(96);								// Storage For 96 Characters

	font = CreateFont(-24,							// Height Of Font
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
		FF_DONTCARE | DEFAULT_PITCH,		// Family And Pitch
		(LPCSTR)"Courier New");					// Font Name

	oldfont = (HFONT)SelectObject(hDC, font);           // Selects The Font We Want
	wglUseFontBitmaps(hDC, 32, 96, base);				// Builds 96 Characters Starting At Character 32
	SelectObject(hDC, oldfont);							// Selects The Font We Want
	DeleteObject(font);									// Delete The Font
}

GLvoid DM2231_View::KillFont(GLvoid)									// Delete The Font List
{
	glDeleteLists(base, 96);							// Delete All 96 Characters
}

GLvoid DM2231_View::glPrint(const char *fmt, ...)					// Custom GL "Print" Routine
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
//END FROM NEHE

DM2231_View::DM2231_View(DM2231_Model* theModel)
{
	this->theModel = theModel;

	theModel->theMouseInfo.Init();
	m_iWindows_Width = 1; 
	m_iWindows_Height = 1;

	m_bActive = true; // Window Active Flag Set To TRUE By Default
	m_bFullScreen = false; // Fullscreen Flag Set To Fullscreen Mode By Default

	hDC=NULL;
	hRC=NULL;
	hWnd=NULL;

	for (int i=0; i<256; i++)
	{
		keys[i] = false;
	}

	LMKeyDown = false;
}

DM2231_View::~DM2231_View(void)
{
	this->theModel = NULL;
	KillFont();
}

// Draw the view
BOOL DM2231_View::Draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Screen And Depth Buffer
	glLoadIdentity(); // Reset The Current Modelview Matrix

	theModel->theOrtho2DSetUp.SetHUD(true);

	switch(theModel->theState.theState)
	{
	case(theModel->theState.State::EnterName):
	{
		theModel->theUI.RenderUI(theUI->ENTERNAME, base);
		glRasterPos3f (250,300,1);
		glPrint(theModel->theHero->playername.c_str());
		break;
	}
	case(theModel->theState.State::storyins):
		{
			theModel->theUI.RenderUI(theUI->STORYIN, base);
			break;
		}
	case (theModel->theState.State::menu):
		{
			theModel->theUI.RenderUI(theUI->STARTSCREEN, base);

			break;
		}
	case (theModel->theState.State::level) :
		{
			theModel->theHero->GetBase(base);
			theModel->TestMap.RenderTileMap();

			for(auto it = theModel->ArrayofEntities.begin(); it != theModel->ArrayofEntities.end(); it++)
			{
				(*it)->render(theModel->TestMap.mapOffset_x, theModel->TestMap.mapOffset_y);
			}
			theModel->thegun.render();
			theModel->theUI.RenderUI(theUI->LEVEL, base);
			break;
		}
	case(theModel->theState.State::PageToLearnShop):
		{
			theModel->theUI.RenderUI(theUI->SUBSHOP, base);
			break;
		}
	case (theModel->theState.State::shop) :
		{

			theModel->theUI.RenderUI(theUI->SHOP, base);
			theModel->theUI.RenderUI(theUI->LEVEL,base);
			break;
		}
	case (theModel->theState.State::credit) :
		{
			// Credit page -> Menu
			theModel->theUI.RenderUI(theUI->CREDIT, base);
			// Input Timer here

			break;
		}
	case (theModel->theState.State::win) :
		{
			theModel->theUI.RenderUI(theUI->WIN, base);
			// Input Timer here

			break;
		}
	case (theModel->theState.State::defeat) :
		{
			theModel->theUI.RenderUI(theUI->DEFEAT, base);
			// Input Timer here

			break;
		}
	case(theModel->theState.State::subpagelevel) :
		{
			theModel->theUI.RenderUI(theUI->SUBPAGE, base);
		}
		break;
	case (theModel->theState.State::ins):
		{
			theModel->theUI.RenderUI(theUI->INS,base);
			break;
		}
	}

	theModel->theOrtho2DSetUp.SetHUD(false);

	SwapBuffers(hDC); // Swap Buffers (Double Buffering)
	Sleep(0);
	

	return TRUE; // Keep Going
}

int DM2231_View::InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	glShadeModel(GL_SMOOTH); // Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f); // Black Background
	glClearDepth(1.0f); // Depth Buffer Setup
	glEnable(GL_DEPTH_TEST); // Enables Depth Testing
	glDepthFunc(GL_LEQUAL); // The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Really Nice Perspective Calculations
	BuildFont();
	return TRUE; // Initialization Went OK
}

GLvoid DM2231_View::ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height==0) // Prevent A Divide By Zero By
	{
		height=1; // Making Height Equal One
	}

	m_iWindows_Width = width; 
	m_iWindows_Height = height;

	glViewport(0,0,width,height); // Reset The Current Viewport

	glMatrixMode(GL_PROJECTION); // Select The Projection Matrix
	glLoadIdentity(); // Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW); // Select The Modelview Matrix
	glLoadIdentity(); // Reset The Modelview Matrix
}

GLvoid DM2231_View::KillGLWindow(GLvoid) // Properly Kill The Window
{
	if (m_bFullScreen) // Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL,0); // If So Switch Back To The Desktop
		ShowCursor(TRUE); // Show Mouse Pointer
	}

	if (hRC) // Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL)) // Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,(LPCSTR)"Release Of DC And RC Failed.",(LPCSTR)"SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC)) // Are We Able To Delete The RC?
		{
			MessageBox(NULL,(LPCSTR)"Release Rendering Context Failed.",(LPCSTR)"SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL; // Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC)) // Are We Able To Release The DC
	{
		MessageBox(NULL,(LPCSTR)"Release Device Context Failed.",(LPCSTR)"SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL; // Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd)) // Are We Able To Destroy The Window?
	{
		MessageBox(NULL,(LPCSTR)"Could Not Release hWnd.",(LPCSTR)"SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL; // Set hWnd To NULL
	}
	if (!UnregisterClass((LPCSTR)"OpenGL",hInstance)) // Are We Able To Unregister Class
	{
		MessageBox(NULL,(LPCSTR)"Could Not Unregister Class.",(LPCSTR)"SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL; // Set hInstance To NULL
	}
}

/* This Code Creates Our OpenGL Window. Parameters Are: *
* title - Title To Appear At The Top Of The Window *
* width - Width Of The GL Window Or Fullscreen Mode *
* height - Height Of The GL Window Or Fullscreen Mode *
* bits - Number Of Bits To Use For Color (8/16/24/32) *
* fullscreenflag - Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE) */

BOOL DM2231_View::CreateGLWindow(char* title, int width, int height, int bits)
{
	GLuint PixelFormat; // Holds The Results After Searching For A Match
	WNDCLASS wc; // Windows Class Structure
	DWORD dwExStyle; // Window Extended Style
	DWORD dwStyle; // Window Style
	RECT WindowRect; // Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0; // Set Left Value To 0
	WindowRect.right=(long)width; // Set Right Value To Requested Width
	WindowRect.top=(long)0; // Set Top Value To 0
	WindowRect.bottom=(long)height; // Set Bottom Value To Requested Height

	hInstance = GetModuleHandle(NULL); // Grab An Instance For Our Window
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; // Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc = (WNDPROC) WndProc; // WndProc Handles Messages
	wc.cbClsExtra = 0; // No Extra Window Data
	wc.cbWndExtra = 0; // No Extra Window Data
	wc.hInstance = hInstance; // Set The Instance
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO); // Load The Default Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // Load The Arrow Pointer
	wc.hbrBackground = NULL; // No Background Required For GL
	wc.lpszMenuName = NULL; // We Don't Want A Menu
	wc.lpszClassName = (LPCSTR)"OpenGL"; // Set The Class Name

	if (!RegisterClass(&wc)) // Attempt To Register The Window Class
	{
		MessageBox(NULL,(LPCSTR)"Failed To Register The Window Class.",(LPCSTR)"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE; // Return FALSE
	}

	if (m_bFullScreen) // Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings; // Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings)); // Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings); // Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth = width; // Selected Screen Width
		dmScreenSettings.dmPelsHeight = height; // Selected Screen Height
		dmScreenSettings.dmBitsPerPel = bits; // Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results. NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options. Quit Or Use Windowed Mode.
			if (MessageBox(NULL,(LPCSTR)"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?",(LPCSTR)"NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				m_bFullScreen=false; // Windowed Mode Selected. Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL,(LPCSTR)"Program Will Now Close.",(LPCSTR)"ERROR",MB_OK|MB_ICONSTOP);
				return FALSE; // Return FALSE
			}
		}
	}

	if (m_bFullScreen) // Are We Still In Fullscreen Mode?
	{
		dwExStyle=WS_EX_APPWINDOW; // Window Extended Style
		dwStyle=WS_POPUP; // Windows Style
		ShowCursor(FALSE); // Hide Mouse Pointer
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE; // Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW; // Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle); // Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd=CreateWindowEx( dwExStyle, // Extended Style For The Window
		(LPCSTR)"OpenGL", // Class Name
		(LPCSTR)title, // Window Title
		dwStyle | // Defined Window Style
		WS_CLIPSIBLINGS | // Required Window Style
		WS_CLIPCHILDREN, // Required Window Style
		0, 0, // Window Position
		WindowRect.right-WindowRect.left, // Calculate Window Width
		WindowRect.bottom-WindowRect.top, // Calculate Window Height
		NULL, // No Parent Window
		NULL, // No Menu
		hInstance, // Instance
		NULL))) // Dont Pass Anything To WM_CREATE
	{
		KillGLWindow(); // Reset The Display
		MessageBox(NULL,(LPCSTR)"Window Creation Error.",(LPCSTR)"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE; // Return FALSE
	}

	static PIXELFORMATDESCRIPTOR pfd= // pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR), // Size Of This Pixel Format Descriptor
		1, // Version Number
		PFD_DRAW_TO_WINDOW | // Format Must Support Window
		PFD_SUPPORT_OPENGL | // Format Must Support OpenGL
		PFD_DOUBLEBUFFER, // Must Support Double Buffering
		PFD_TYPE_RGBA, // Request An RGBA Format
		bits, // Select Our Color Depth
		0, 0, 0, 0, 0, 0, // Color Bits Ignored
		0, // No Alpha Buffer
		0, // Shift Bit Ignored
		0, // No Accumulation Buffer
		0, 0, 0, 0, // Accumulation Bits Ignored
		16, // 16Bit Z-Buffer (Depth Buffer)
		0, // No Stencil Buffer
		0, // No Auxiliary Buffer
		PFD_MAIN_PLANE, // Main Drawing Layer
		0, // Reserved
		0, 0, 0 // Layer Masks Ignored
	};

	if (!(hDC=GetDC(hWnd))) // Did We Get A Device Context?
	{
		KillGLWindow(); // Reset The Display
		MessageBox(NULL,(LPCSTR)"Can't Create A GL Device Context.",(LPCSTR)"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE; // Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd))) // Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow(); // Reset The Display
		MessageBox(NULL,(LPCSTR)"Can't Find A Suitable PixelFormat.",(LPCSTR)"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE; // Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd)) // Are We Able To Set The Pixel Format?
	{
		KillGLWindow(); // Reset The Display
		MessageBox(NULL,(LPCSTR)"Can't Set The PixelFormat.",(LPCSTR)"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE; // Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC))) // Are We Able To Get A Rendering Context?
	{
		KillGLWindow(); // Reset The Display
		MessageBox(NULL,(LPCSTR)"Can't Create A GL Rendering Context.",(LPCSTR)"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE; // Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC)) // Try To Activate The Rendering Context
	{
		KillGLWindow(); // Reset The Display
		MessageBox(NULL,(LPCSTR)"Can't Activate The GL Rendering Context.",(LPCSTR)"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE; // Return FALSE
	}

	SetWindowLongPtr(hWnd, GWLP_USERDATA, (long)this);

	ShowWindow(hWnd,SW_SHOW); // Show The Window
	UpdateWindow(hWnd);
	SetForegroundWindow(hWnd); // Slightly Higher Priority
	SetFocus(hWnd); // Sets Keyboard Focus To The Window

	
	ReSizeGLScene(width, height); // Set Up Our Perspective GL Screen

	if (!InitGL()) // Initialize Our Newly Created GL Window
	{
		KillGLWindow(); // Reset The Display
		MessageBox(NULL,(LPCSTR)"Initialization Failed.",(LPCSTR)"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE; // Return FALSE
	}

	// Store the width and height
	m_iWindows_Width = width; 
	m_iWindows_Height = height;

	if (!theModel->theUI.theTexture.LoadTGA(&theModel->theUI.theTexture.menuTexture[0],"Images/Menu.tga"))
		return false;
	if (!theModel->theUI.theTexture.LoadTGA(&theModel->theUI.theTexture.levelTexture[0], "Images/Level.tga"))
		return false;
	if (!theModel->theUI.theTexture.LoadTGA(&theModel->theUI.theTexture.subpageTexture[0], "Images/Subpage.tga"))
		return false;
	if (!theModel->theUI.theTexture.LoadTGA(&theModel->theUI.theTexture.shopTexture[0], "Images/Shop.tga"))
		return false;
	if (!theModel->theUI.theTexture.LoadTGA(&theModel->theUI.theTexture.creditTexture[0], "Images/Credit.tga"))
		return false;
	if (!theModel->theUI.theTexture.LoadTGA(&theModel->theUI.theTexture.winTexture[0], "Images/Win.tga"))
		return false;
	if (!theModel->theUI.theTexture.LoadTGA(&theModel->theUI.theTexture.defeatTexture[0], "Images/Defeat.tga"))
		return false;

	if (!theModel->theUI.theTexture.LoadTGA(&theModel->theUI.theTexture.nameTexture[0], "Images/EnterName.tga"))
		return false;
	if (!theModel->theUI.theTexture.LoadTGA(&theModel->theUI.theTexture.storyTexture[0], "Images/StoryInst.tga"))
		return false;
	if (!theModel->theUI.theTexture.LoadTGA(&theModel->theHero->heroTexture[0], "Images/Hero.tga"))
		return false;
	if (!theModel->theUI.theTexture.LoadTGA(&theModel->dummyZombie.tex, "Images/Zombie.tga"))
		return false;
	if (!theModel->theUI.theTexture.LoadTGA(&theModel->theUI.theTexture.gambledTexture[0], "Images/Gambled.tga"))
		return false;
	if (!theModel->theUI.theTexture.LoadTGA(&theModel->dummyHP.tex, "Images/Health.tga"))
		return false;
	if (!theModel->theUI.theTexture.LoadTGA(&theModel->dummySlow.tex, "Images/Speedup.tga"))
		return false;
	if (!theModel->theUI.theTexture.LoadTGA(&theModel->theUI.theTexture.insTexture[0], "Images/Inst.tga"))
		return false;

	for(int i = 0; i < theModel->ArrayofEntities.size(); i++)
	{
		if(theModel->ArrayofEntities[i]->ID == Entity::ZOMBIE)
			theModel->ArrayofEntities[i]->tex = theModel->dummyZombie.tex;
		else if(theModel->ArrayofEntities[i]->ID == Entity::SLOWDOWN)
			theModel->ArrayofEntities[i]->tex = theModel->dummySlow.tex;
		else if(theModel->ArrayofEntities[i]->ID == Entity::HEALTH)
			theModel->ArrayofEntities[i]->tex = theModel->dummyHP.tex;
	}

	return TRUE; // Success
}

LRESULT CALLBACK DM2231_View::MsgProc( HWND hWnd, // Handle For This Window
									  UINT uMsg, // Message For This Window
									  WPARAM wParam, // Additional Message Information
									  LPARAM lParam) // Additional Message Information
{
	switch (uMsg) // Check For Windows Messages
	{
	case WM_ACTIVATE: // Watch For Window Activate Message
		{
			if (!HIWORD(wParam)) // Check Minimization State
			{
				m_bActive=TRUE; // Program Is Active
			}
			else
			{
				m_bActive=FALSE; // Program Is No Longer Active
			}

			return 1; // Return To The Message Loop
		}

	case WM_SYSCOMMAND: // Intercept System Commands
		{
			switch (wParam) // Check System Calls
			{
			case SC_SCREENSAVE: // Screensaver Trying To Start?
			case SC_MONITORPOWER: // Monitor Trying To Enter Powersave?
				return 1; // Prevent From Happening
			}
			break; // Exit
		}

	case WM_CLOSE: // Did We Receive A Close Message?
		{
			PostQuitMessage(0); // Send A Quit Message
			return 1; // Jump Back
		}

	case WM_KEYDOWN: // Is A Key Being Held Down?
		{
			keys[wParam] = TRUE; // If So, Mark It As TRUE
			return 1; // Jump Back
		}

	case WM_KEYUP: // Has A Key Been Released?
		{
			keys[wParam] = FALSE; // If So, Mark It As FALSE
			return 1; // Jump Back
		}

	case WM_SIZE: // Resize The OpenGL Window
		{
			// ReSizeGLScene(LOWORD(lParam),HIWORD(lParam)); // LoWord=Width, HiWord=Height
			return 1; // Jump Back
		}
	case WM_MOUSEMOVE:
		{
			theModel->theMouseInfo.SetMousePos( LOWORD(lParam), HIWORD(lParam) );
			int diffX = theModel->theMouseInfo.GetDiff_X();
			int diffY = theModel->theMouseInfo.GetDiff_Y();
			cout<<theModel->theMouseInfo.MousePos.x / theModel->Wratio<<" : "<<theModel->theMouseInfo.MousePos.y / theModel->Hratio<<endl;

			RECT WindowRect;
			GetWindowRect( hWnd, &WindowRect);
			ClipCursor( &WindowRect );
			return 1;
		}
	case WM_LBUTTONDOWN:
		{
			LMKeyDown = true;
			return 1;
		}
	case WM_LBUTTONUP:
		{
			LMKeyDown = false;
			return 1;
		}
	case WM_MOUSEWHEEL:
		{
			 return 1;
		}

	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}


LRESULT CALLBACK DM2231_View::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	// Recover the pointer to our class, don't forget to type cast it back

	DM2231_View* winptr = (DM2231_View*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	// Check if the pointer is NULL and call the Default WndProc

	if (winptr == NULL)
	{
		return DefWindowProc(hwnd, message, wParam, lParam);
	} else
	{
		// Call the Message Handler for my class (MsgProc in my case)
		return winptr->MsgProc(hwnd, message, wParam, lParam);
	}
}
// Check if the player wants to quit the game
bool DM2231_View::isQuitGame(void)
{
	if (keys[VK_ESCAPE])				// Was ESC Pressed?
		return true;
	else
		return false;
}

// Check if the player wants to play the game in Full Screen
bool DM2231_View::runFullScreen(void)
{
	if (keys[VK_F1])
		return true;
	else
		return false;
}

// Toggle the game to be fullscreen or otherwise
bool DM2231_View::toggleFullScreen(void)
{
	keys[VK_F1]=FALSE;					// If So Make Key FALSE
	m_bFullScreen=!m_bFullScreen;				// Toggle Fullscreen / Windowed Mode

	KillGLWindow();						// Kill Our Current Window
	// Recreate Our OpenGL Window
	if (!CreateGLWindow("OpenGL GAME",1040,780,16))
	{
		return false;						// Quit If Window Was Not Created
	}

	return true;
}

// Set the fullscreen display status
void DM2231_View::setFullScreen(bool m_bFullScreen)
{
	this->m_bFullScreen = m_bFullScreen;
}

bool DM2231_View::GetKeys(char s)
{
	if(keys[s] || keys[s - 32])
		return true;
	else 
		return false;
}

void DM2231_View::SetKeys(char g)
{
	keys[g] = false;
	keys[g-32] = false;
}	

bool DM2231_View::GetBackspace()
{
	if(keys[0x08])
		return true;
	else 
		return false;
}

void DM2231_View::SetBackspace(bool set)
{
	keys[0x08] = set;
}

bool DM2231_View::GetEnter()
{
	if(keys[0x0D])
		return true;
	else 
		return false;
}

void DM2231_View::SetEnter(bool set)
{
	keys[0x0D] = set;
}
