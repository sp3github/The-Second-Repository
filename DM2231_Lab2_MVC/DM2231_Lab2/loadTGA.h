#pragma once
#include "Header.h"

class loadTGA
{
public:
	bool LoadTGA(TextureImage *texture, char *filename);

	TextureImage menuTexture[1];
	TextureImage levelTexture[1];
	TextureImage scoreTexture[1];
	TextureImage subpageTexture[1];
	TextureImage shopTexture[1];

	loadTGA(void);
	~loadTGA(void);
};