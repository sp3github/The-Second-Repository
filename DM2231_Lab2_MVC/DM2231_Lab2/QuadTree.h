#pragma once
#include "Entity.h"
#include <vector>

struct rect
{
	int x;
	int y;
	int height;
	int width;
	CEntity * theEntity;
	rect(int x, int y, int width, int height, CEntity * theEntity = NULL)
	{
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
		this->theEntity = theEntity;
	}
	rect()
	{

	};
};

class QuadTree
{
private :


	int MAX_OBJECTS;
	int MAX_LEVELS;

	int level;
	vector<rect> objects;
	rect bounds;
	QuadTree * nodes[];


public:

	QuadTree(void);
	QuadTree(int pLevel, rect pBounds);
	~QuadTree(void);

	void clear();	//clear the quadtree
	void Split();	//split the quadtree
	int GetIndex(rect pRect);	//Determine Location in quadtree -1 means object cannot completely fit within a child node and is part of the parent node
	void insert(rect pRect);
	vector<rect> retrive(vector<rect> &returnObjects, rect pRect);


};

