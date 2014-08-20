#pragma once
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#include <iostream>
#include <stdio.h>
#include <windows.h> // Header File For Windows

#include <gl\GL.h>
#include <gl\GLU.h>

#define TILE_SIZE 25

using namespace std;

typedef struct												// Create A Structure
{
	GLubyte	*imageData;										// Image Data (Up To 32 Bits)
	GLuint	bpp;											// Image Color Depth In Bits Per Pixel.
	GLuint	width;											// Image Width
	GLuint	height;											// Image Height
	GLuint	texID;											// Texture ID Used To Select A Texture
} TextureImage;												// Structure Name