#pragma once
#include "Header.h"

class loadTGA
{
public:
	bool LoadTGA(TextureImage *texture, char *filename);

	TextureImage nameTexture[1];
	TextureImage storyTexture[1];
	TextureImage menuTexture[1];
	TextureImage levelTexture[1];
	TextureImage subshopTexture[1];
	TextureImage shopTexture[1];
	TextureImage creditTexture[1];
	TextureImage winTexture[1];
	TextureImage defeatTexture[1];
	TextureImage subpageTexture[1];

	loadTGA(void);
	~loadTGA(void);
};