/* NO EDITS NEEDED IN THIS FILE. YOU MAY ADD HELPERS METHODS HERE IF YOU WOULD LIKE.

	Vertex Class Declaration

	The Vertex class is responsible for:
		- Keeping track of all the data for an individual "cell" in the grid.
*/

#pragma once
class Vertex
{
public:
	// A bool to keep track of if this vertex is a wall or not.
	bool isWall = false;

	// The position of this vertex in the grid.
	int xPos = -1;
	int yPos = -1;

	// Some methods to expose our costs and parent publicly.
	int GetFCost(); // YOU NEED TO FILL THIS OUT IN Vertex.cpp.

	int GetGCost();
	int GetHCost();
	Vertex* GetParent();

	// A method for setting the heuristic. YOU NEED TO FILL THIS OUT IN Vertex.cpp.
	void SetHCost(int _endX, int _endY);

	// A method for determining if we should change this vertex's parent.
	// YOU WILL NEED TO FILL THIS OUT IN Vertex.cpp.
	bool SetParentIfCheaper(Vertex * _possibleParent);

private:
	// Our h and g cost, as well as our parent.
	int hCost = 0;
	int gCost = 0;
	Vertex* parent = nullptr;
};

