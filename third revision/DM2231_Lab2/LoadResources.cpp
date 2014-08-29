#include "LoadResources.h"


LoadResources::LoadResources(void)
{

}


LoadResources::~LoadResources(void)
{
	if(theFILE != NULL)
	{
		theFILE = NULL;
	}
}

LoadResources::LoadResources(string thedirectory)
{
	theFILE = fopen (thedirectory.c_str(),"r");
	if (theFILE !=NULL)
	{
		fputs ("fopen example",theFILE);
		
	}
	fclose(theFILE);
}

void LoadResources::LoadInfo(string thedirectory)
{
	theFILE = fopen (thedirectory.c_str(),"r");
	if (theFILE !=NULL)
	{
		

	}
	fclose(theFILE);
}