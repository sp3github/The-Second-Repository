#pragma once
#include <vector>
#include <string>
#include <stdio.h>

using namespace std;
class LoadResources
{
public:
	LoadResources(void);
	LoadResources(string thedirectory);
	~LoadResources(void);

	FILE *theFILE;
	void LoadInfo(string thedirectory);
	vector<string> buffer;
};

