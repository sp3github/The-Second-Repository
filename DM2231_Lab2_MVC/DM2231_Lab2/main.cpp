#pragma once
#include <stdio.h>

#include "DM2231_Model.h"
#include "DM2231_View.h"
#include "DM2231_Controller.h"


int main( int argc, char **args )
{
	glutInit(&argc, args);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,600);
	DM2231_Model* theModel = new DM2231_Model();
	DM2231_View* theView = new DM2231_View( theModel );
	DM2231_Controller* theController = new DM2231_Controller( theModel, theView );

	theController->RunMainLoop();

	if ( theController != NULL)
	{
		delete theController;
		theController = NULL;
	}
	if ( theView != NULL)
	{
		delete theView;
		theView = NULL;
	}
	if ( theModel != NULL)
	{
		delete theModel;
		theModel = NULL;
	}
	return 0;
}