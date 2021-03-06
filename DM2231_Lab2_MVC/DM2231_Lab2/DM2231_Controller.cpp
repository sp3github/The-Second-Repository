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
	timer = mvcTime::getInstance();
	timer->init();
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
	srand(time(NULL));

	// Ask The User Which Screen Mode They Prefer
	if (MessageBox(NULL,(LPCSTR)"Would You Like To Run In Fullscreen Mode?",(LPCSTR) "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
		theView->setFullScreen( false );
	else
		theView->setFullScreen( true );


	//for (int i = 0; i < theModel->ArrayofEntities.size(); i++)
	//{
	//	theModel->quad->insert(rect(theModel->ArrayofEntities[i]->GetX(), theModel->ArrayofEntities[i]->GetY(), theModel->ArrayofEntities[i]->tile_size, theModel->ArrayofEntities[i]->tile_size, theModel->ArrayofEntities[i]));
	//	//INSERT EVERYTHING INTO QUAD TREE
	//}
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
				//cout<<"FPS: "<<timer->getFPS()<<endl;
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
				if((theModel->theMouseInfo.MousePos.x >= 350 * theModel->Wratio) && (theModel->theMouseInfo.MousePos.x <= 450 * theModel->Wratio)
					&& (theModel->theMouseInfo.MousePos.y >= 220 * theModel->Hratio )&& (theModel->theMouseInfo.MousePos.y <= 260 * theModel->Hratio))
				{
					theModel->theState.theState = theModel->theState.storyins;
				}
				//EXIT BUTTON
				if((theModel->theMouseInfo.MousePos.x >= 350 * theModel->Wratio)&& (theModel->theMouseInfo.MousePos.x <= 450 * theModel->Wratio)
					&& (theModel->theMouseInfo.MousePos.y >= 270 * theModel->Hratio ) &&( theModel->theMouseInfo.MousePos.y <= 308 * theModel->Hratio ))
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
				theModel->thegun.changestate(GunStates::pistol);
			}
			if (theView->GetKeys('2'))
			{
				theModel->thegun.changestate(GunStates::uzi);
			}
			if (theView->GetKeys('3'))
			{
				theModel->thegun.changestate(GunStates::shotgun);
			}
			if(theView->LMKeyDown)
			{
				theModel->thegun.FireGun();
				if(theModel->thegun.StateNow == GunStates::pistol && theModel->thegun.currentBullet[0] != 0)
					theSound.RenderSound(Sound::PISTOL);
				else if(theModel->thegun.StateNow == GunStates::uzi&& theModel->thegun.currentBullet[1] != 0)
					theSound.RenderSound(Sound::UZI);
				else if(theModel->thegun.StateNow == GunStates::shotgun&& theModel->thegun.currentBullet[2] != 0)
					theSound.RenderSound(Sound::SHOTGUN);
			}
			break;
		}
	case (theModel->theState.State::storyins):
		{
			break;
		}
	case (theModel->theState.State::shop) :
		{
			if(theView->GetKeys('q'))//EXIT THE SHOP
			{
				if(theModel->theBet.firstbet)
					theModel->theState.theState = theModel->theState.level;
				else
					theModel->theState.theState = theModel->theState.subpagelevel;
			}

			if(theView->LMKeyDown)
			{
				//BUY PISTOL AMMO
				if((theModel->theMouseInfo.MousePos.x >= 47  * theModel->Wratio) && ( theModel->theMouseInfo.MousePos.x <= 166  * theModel->Wratio)
					&& (theModel->theMouseInfo.MousePos.y >= 224  * theModel->Hratio) && (theModel->theMouseInfo.MousePos.y <= 294  * theModel->Hratio))
				{
					if((theModel->theHero->money.playerMoney - 10) >= 0)
					{
						theModel->theHero->money.AddMoney(-10);
						theModel->thegun.currentBullet[0] += 10;
					}
				}
				//BUY UZI AMMO
				if((theModel->theMouseInfo.MousePos.x >= 191  * theModel->Wratio) && ( theModel->theMouseInfo.MousePos.x <= 312  * theModel->Wratio)
					&& (theModel->theMouseInfo.MousePos.y >= 224  * theModel->Hratio) && (theModel->theMouseInfo.MousePos.y <= 294  * theModel->Hratio))
				{
					if((theModel->theHero->money.playerMoney - 20) >= 0)
					{
						theModel->theHero->money.AddMoney(-20);
						theModel->thegun.currentBullet[1] += 10;
					}
				}
				//BUY SHOTGUN AMMO
				if((theModel->theMouseInfo.MousePos.x >= 338  * theModel->Wratio) && ( theModel->theMouseInfo.MousePos.x <= 457  * theModel->Wratio)
					&& (theModel->theMouseInfo.MousePos.y >= 224  * theModel->Hratio) && (theModel->theMouseInfo.MousePos.y <= 294  * theModel->Hratio))
				{
					if((theModel->theHero->money.playerMoney - 30) >= 0)
					{
						theModel->theHero->money.AddMoney(-30);
						theModel->thegun.currentBullet[2] += 10;
					}
				}
				theView->LMKeyDown = false;
			}

			for(int i = 0x30; i < 0x3A; i++)
			{
				if(theView->GetKeys(i))
				{	
					theModel->theBet.AmounttoBet.push_back(i);
					theView->SetKeys(i);
				}

				if (theView->GetBackspace())
				{
					if(theModel->theBet.AmounttoBet.size() != 0)
					{
						theModel->theBet.AmounttoBet.pop_back();
						theView->SetBackspace(false);
					}
				}
			}
			if(theView->GetEnter())
			{
				if(atoi(theModel->theBet.AmounttoBet.c_str()) <= theModel->theHero->money.playerMoney)
				{
					theModel->theHero->money.playerMoney += theModel->theBet.BetEvent(atoi(theModel->theBet.AmounttoBet.c_str()));
				}
				theView->SetEnter(false);
			}

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
