#include "DM2231_Controller.h"

#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library


HDC			hDC=NULL;		// Private GDI Device Context
HGLRC		hRC=NULL;		// Permanent Rendering Context
HWND		hWnd=NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application

DM2231_Controller::DM2231_Controller(DM2231_Model* theModel, DM2231_View* theView)
: theModel(NULL)
, theView(NULL)
, m_bContinueLoop(false)
{

	this->theModel = theModel;
	this->theView = theView;
	Init();
	timer = mvcTime::getInstance();
}

DM2231_Controller::~DM2231_Controller(void)
{
	this->theView = NULL;
	this->theModel = NULL;
}

bool DM2231_Controller::Init(void)
{
	srand(time(NULL));

	// Ask The User Which Screen Mode They Prefer
	if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
		theView->setFullScreen( false );
	else
		theView->setFullScreen( true );

	theModel->SetStart(1);


	return true;
}


// Get the status of the stop game boolean flag
BOOL DM2231_Controller::RunMainLoop(void)
{

	MSG msg; // Windows Message Structure
	BOOL done=FALSE; // Bool Variable To Exit Loop

	// Create Our OpenGL Window
	int theMonWidth = GetSystemMetrics(SM_CXFULLSCREEN) - 0.01 * GetSystemMetrics(SM_CXFULLSCREEN);
	int theMonHeight = GetSystemMetrics(SM_CYFULLSCREEN) - 0.01 * GetSystemMetrics(SM_CYFULLSCREEN);

	if (!theView->CreateGLWindow("OPENGL GAME",theMonWidth,theMonHeight,16))
	{
		return false;									// Quit If Window Was Not Created
	}

	while(!done) // Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE)) // Is There A Message Waiting?
		{
			if (msg.message==WM_QUIT) // Have We Received A Quit Message?
			{
				done=TRUE; // If So done=TRUE
			}
			else // If Not, Deal With Window Messages
			{
				TranslateMessage(&msg); // Translate The Message
				DispatchMessage(&msg); // Dispatch The Message
			}
		}
		else // If There Are No Messages
		{
			if (ProcessInput())
			{
				timer->updateTime();
				theModel->Update();
				theView->Draw();
			}
			else
			{
				done=TRUE; // ESC or DrawGLScene Signalled A Quit
			}
		}
	}

	// Shutdown
	theView->KillGLWindow(); // Kill The Window
	return (msg.wParam); // Exit The Program
}

// Process input from I/O devices
bool DM2231_Controller::ProcessInput(void)
{
	// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
	if (theView->isQuitGame())				// Was ESC Pressed?
	{
		m_bContinueLoop=false;						// ESC Signalled A Quit
		return false;
	}

	if (theView->runFullScreen())						// Is F1 Being Pressed?
	{
		if (theView->toggleFullScreen() == false)
		{
			m_bContinueLoop=false;						// ESC Signalled A Quit
			return false;
		}
	}

	switch (theModel->theState.theState)
	{
	case (theModel->theState.State::EnterName):
		{
			for(int i = 65; i < 90; i++)
			{
				if(theView->GetKeys(i))
				{	
					theModel->theHero->playername.push_back(i);
					theView->SetKeys(i);
				}

				if (theView->GetBackspace())
				{
					if(theModel->theHero->playername.size() != 0)
					{
						theModel->theHero->playername.pop_back();
						theView->SetBackspace(false);
					}
				}
			}
			if(theView->GetEnter())
			{
				if(theModel->theHero->playername.size() != 0)
				{
					theModel->theState.theState = theModel->theState.State::menu;
					theView->SetEnter(false);
				}
			}
			break;
		}
	case (theModel->theState.State::menu):
		{
			if(theView->LMKeyDown)
			{
				//PLAY BUTTON
				if(theModel->theMouseInfo.MousePos.x >= 835 && theModel->theMouseInfo.MousePos.x <= 1070 && theModel->theMouseInfo.MousePos.y >= 370 && theModel->theMouseInfo.MousePos.y <= 430)
				{
					theModel->theState.theState = theModel->theState.storyins;
				}
				//EXIT BUTTON
				if(theModel->theMouseInfo.MousePos.x >= 835 && theModel->theMouseInfo.MousePos.x <= 1070 && theModel->theMouseInfo.MousePos.y >= 450 && theModel->theMouseInfo.MousePos.y <= 520)
				{
					m_bContinueLoop=false;
					return false;
				}
				theView->LMKeyDown = false;
			}
		}
	case (theModel->theState.State::level):
		{
			//INPUT CONTROLS
			if (theView->GetKeys('w'))
			{
				if(theModel->theCollision.CheckCollision(theModel->theHeroEntity,NULL,true))
					theModel->theHero->moveMeUpDown(true, 1.0f, static_cast<float>(theModel->theHero->movementspeed));
			}
			if (theView->GetKeys('s'))
			{
				if(theModel->theCollision.CheckCollision(theModel->theHeroEntity,NULL,false,true))
					theModel->theHero->moveMeUpDown(false, 1.0f, static_cast<float>(theModel->theHero->movementspeed));
			}
			if (theView->GetKeys('a'))
			{
				if(theModel->theCollision.CheckCollision(theModel->theHeroEntity,NULL,false,false,true))
					theModel->theHero->moveMeLeftRight(true,1.0f,static_cast<float>(theModel->theHero->movementspeed));
			}
			if (theView->GetKeys('d'))
			{
				if(theModel->theCollision.CheckCollision(theModel->theHeroEntity,NULL,false,false,false,true))
					theModel->theHero->moveMeLeftRight(false, 1.0f, static_cast<float>(theModel->theHero->movementspeed));
			}
			if (theView->GetKeys('1'))
			{
			}
			if (theView->GetKeys('2'))
			{
			}
			if (theView->GetKeys('3'))
			{
			}
			if(theView->LMKeyDown)
			{
				theModel->thegun.FireGun();
				theSound.RenderSound(Sound::PISTOL);
			}
			break;
		}
	case (theModel->theState.State::storyins):
		{
			break;
		}
	case (theModel->theState.State::shop) :
		{
			if(theView->GetKeys('1'))
				theModel->theState.theState = theModel->theState.level;
			break;
		}
	case (theModel->theState.State::PageToLearnShop):
		{
			break;
		}
	case (theModel->theState.State::credit) :
		{
			break;
		}
	case (theModel->theState.State::win) :
		{
			break;
		}
	case (theModel->theState.State::defeat) :
		{
			break;
		}
	case (theModel->theState.State::subpagelevel) :
		{
			break;
		}
	}

	return true;
}
