#include "QuadTree.h"


QuadTree::QuadTree(void)
{
	int MAX_OBJECTS = 10;
	int MAX_LEVELS = 5;
}

QuadTree::QuadTree(int pLevel, rect pBounds)
{
	level = pLevel;
	bounds = pBounds;
	nodes[4] = new QuadTree;
}

QuadTree::~QuadTree(void)
{
}

void QuadTree::clear()
{
	objects.clear();

	for (int i = 0; i < 4; i++) {
		if (nodes[i] != NULL)
		{
			nodes[i]->clear();
			nodes[i] = NULL;
		}
	}
}

void QuadTree::Split()
{
	int subWidth = (int)(bounds.width / 2);
	int subHeight = (int)(bounds.height / 2);
	int x = (int)bounds.x;
	int y = (int)bounds.y;

	nodes[0] =  new QuadTree(level+1, rect(x + subWidth, y, subWidth, subHeight));
	nodes[1] =  new QuadTree(level+1,  rect(x, y, subWidth, subHeight));
	nodes[2] =  new QuadTree(level+1, rect(x, y + subHeight, subWidth, subHeight));
	nodes[3] =  new QuadTree(level+1,  rect(x + subWidth, y + subHeight, subWidth, subHeight));
}

int QuadTree::GetIndex(rect pRect)
{
	int index = -1;
	double verticalMidpoint = bounds.x + (bounds.width / 2);
	double horizontalMidpoint = bounds.y + (bounds.height / 2);

	// Object can completely fit within the top quadrants
	bool topQuadrant = (pRect.y < horizontalMidpoint && pRect.y + pRect.height < horizontalMidpoint);
	// Object can completely fit within the bottom quadrants
	bool bottomQuadrant = (pRect.y > horizontalMidpoint);

	// Object can completely fit within the left quadrants
	if (pRect.x < verticalMidpoint && pRect.x + pRect.width < verticalMidpoint) {
		if (topQuadrant) {
			index = 1;
		}
		else if (bottomQuadrant) {
			index = 2;
		}
	}
	// Object can completely fit within the right quadrants
	else if (pRect.x > verticalMidpoint) {
		if (topQuadrant) {
			index = 0;
		}
		else if (bottomQuadrant) {
			index = 3;
		}
	}
	//Basically cut two lines in a cross and get the index value of which rect it is act.
	return index;
}

void QuadTree::insert(rect pRect)
{
	if (nodes[0] != NULL)
	{
		int index = GetIndex(pRect);

		if (index != -1)
		{
			nodes[index]->insert(pRect);

			return;
		}
	}
	//The method first determines whether the node has any child nodes and tries to add the object there.
	

	objects.push_back(pRect);
//If there are no child nodes or the object doesn’t fit in a child node, it adds the object to the parent node.

	if (objects.size() > MAX_OBJECTS && level < MAX_LEVELS)
	{
		if (nodes[0] == NULL)
		{
			Split();
		}

		auto i = objects.begin();
		int counter;
		for(i = objects.begin(), counter = 0; i != objects.end(); counter++)
		{
			int index = GetIndex(objects.at(counter));
			if(index != -1)
			{
				nodes[index]->insert(objects.at(counter));
				objects.erase(i);
			}
		}
	}
	//Once the object is added, it determines whether the node needs to split by checking if the current number of objects exceeds the max allowed objects.
	//Splitting will cause the node to insert any object that can fit in a child node to be added to the child node; otherwise the object will stay in the parent node.
}

vector<QuadTree::rect> QuadTree::retrive(vector<rect> returnObjects, rect pRect)
{
	int index = GetIndex(pRect);
	if (index != -1 && nodes[0] != NULL)
	{
		nodes[index]->retrive(returnObjects, pRect);
	}

	returnObjects.insert(returnObjects.end(),objects.begin(),objects.end());

	return returnObjects;
}