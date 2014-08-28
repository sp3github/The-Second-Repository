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
}

DM2231_Controller::~DM2231_Controller(void)
{
	this->theView = NULL;
	this->theModel = NULL;
}

bool DM2231_Controller::Init(void)
{
	// Ask The User Which Screen Mode They Prefer
	if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
		theView->setFullScreen( false );
	else
		theView->setFullScreen( true );


	theModel->TestMap.LoadLevel(1);
	theModel->ArrayofEntities.push_back(theModel->theEntityFactory.Create(PLAYER));
	theModel->ArrayofEntities.back()->SetPos(100,200);

	
	theModel->theHeroEntity = theModel->ArrayofEntities.back();
	theModel->theHero = (dynamic_cast<CPlayerInfo*>(theModel->theHeroEntity));

	theModel->ArrayofEntities.push_back(theModel->theEntityFactory.Create(HEALTH));
	theModel->ArrayofEntities.back()->SetPos(100,300);

	
	for(int zombiecount = 0; zombiecount < 1;  zombiecount++)
	{
		theModel->ArrayofEntities.push_back(theModel->theEntityFactory.Create(ZOMBIE));
		cout <<"CONTROLLER:" << zombiecount << endl;
	}
	
	theModel->ArrayofEntities.push_back(theModel->theEntityFactory.Create(OBSTACLE));
	theModel->ArrayofEntities.back()->SetPos(400,150);

	return true;
}


// Get the status of the stop game boolean flag
BOOL DM2231_Controller::RunMainLoop(void)
{

	MSG msg; // Windows Message Structure
	BOOL done=FALSE; // Bool Variable To Exit Loop

	// Create Our OpenGL Window
	if (!theView->CreateGLWindow("OPENGL GAME",800,600,16))
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
	case (theModel->theState.states::level):
		{
			if (theView->GetKeys('w'))
			{
				if(theModel->theCollision.CheckCollision(theModel->theHeroEntity,NULL,true))
					theModel->theHero->moveMeUpDown(true, 1.0f, theModel->theHero->movementspeed);
			}
			if (theView->GetKeys('s'))
			{
				if(theModel->theCollision.CheckCollision(theModel->theHeroEntity,NULL,false,true))
					theModel->theHero->moveMeUpDown(false, 1.0f, theModel->theHero->movementspeed);
			}
			if (theView->GetKeys('a'))
			{
				if(theModel->theCollision.CheckCollision(theModel->theHeroEntity,NULL,false,false,true))
					theModel->theHero->moveMeLeftRight(true,1.0f,theModel->theHero->movementspeed);
			}
			if (theView->GetKeys('d'))
			{
				if(theModel->theCollision.CheckCollision(theModel->theHeroEntity,NULL,false,false,false,true))
					theModel->theHero->moveMeLeftRight(false, 1.0f, theModel->theHero->movementspeed);
			}
			if(theView->LMKeyDown)
			{
				cout<<"FIRE"<<endl;
				theView->LMKeyDown = false; //Uncomment this if you want to fire while holding down
				theModel->theBullet.Draw();
				//theModel->theBullet.FireBullet();
			}
			break;
		}
	case (theModel->theState.states::menu):
		{
			if(theView->LMKeyDown)
			{
				if(theModel->theMouseInfo.MousePos.x >= 350 && theModel->theMouseInfo.MousePos.x <= 450 && theModel->theMouseInfo.MousePos.y >= 220 && theModel->theMouseInfo.MousePos.y <= 260)
				{
					theModel->theState.theState = theModel->theState.level;
				}
				if(theModel->theMouseInfo.MousePos.x >= 350 && theModel->theMouseInfo.MousePos.x <= 450 && theModel->theMouseInfo.MousePos.y >= 270 && theModel->theMouseInfo.MousePos.y <= 310)
				{
					m_bContinueLoop=false;
					return false;
				}
				theView->LMKeyDown = false;
			}
			break;
		}
	case (theModel->theState.states::shop) :
	{

											   break;

	}
	case (theModel->theState.states::bet) :
	{

											  break;
	}
	case (theModel->theState.states::message) :
	{

												  break;

	}
	case (theModel->theState.states::credit) :
	{

												 break;

	}
	case (theModel->theState.states::win) :
	{

											  break;
	}
	case (theModel->theState.states::defeat) :
	{
												 break;
	}

	}

	return true;
}
