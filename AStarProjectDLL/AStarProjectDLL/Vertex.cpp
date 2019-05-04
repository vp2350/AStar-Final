#include "stdafx.h"
#include "Vertex.h"
#include <cstdlib>



/*
Helpful references:

CELL ANATOMY--
# = Cell Number
g = Movement cost from start through parent tree
h = Estimate of distance to finish
f = Weighted distance (f = g + h)

Open List: All cells we have reached, but not checked around.
Closed List: All cells we have reached AND checked around.
Parent: Previous cell in the optimal path back to the start. Each cell keeps track of its parent, and each cell's parent is null until the cell is added to the open list.
Movement cost = cost of moving from once cell to another. We can just use 1 for all of them.
g cost = parent.g + movementCost. The cost of moving from the start to this current cell.

If you encounter a cell that's already on the open list:
Check if said cell would have a lower g cost coming from the cell the program is currently at than it does from it's own parent.
If it does, reparent it to the cell the program is currently at, change g cost accordingly, and recalculate its f cost.

If the end destination cell has been added to the open list, parent it to the current cell and traverse back up the parent tree to the start. We're done.
*/

// !-------- TO DO ----------!
// CALCULATE THE F COST HERE AND RETURN IT
int Vertex::GetFCost()
{
	int fCost = GetGCost() + GetHCost();
	return fCost;
}

// !-------------DO NOT EDIT THIS--------------!
// This method simply exposes the vertex's gCost publicly.
int Vertex::GetGCost()
{
	return gCost;
}

// !-------------DO NOT EDIT THIS--------------!
// This method simply exposes the vertex's hCost publicly.
int Vertex::GetHCost()
{
	return hCost;
}

// !-------------DO NOT EDIT THIS--------------!
// This method simply exposes the vertex's parent publicly.
Vertex * Vertex::GetParent()
{
	return parent;
}

/* !-------- TO DO ----------!
	CALCULATE THE HEURISTIC COST FOR THIS VERTEX TO THE END USING
	THE MANHATTAN DISTANCE FORMULA. STORE THE RESULTS IN hCost
*/
void Vertex::SetHCost(int _endX, int _endY)
{

	//h = Estimate of distance to finish.
	//Manhattan Distance is when you can only move in a cardinal direction, no diagonals.
	//In which case h = abs(x1-x2) + abs(y1 - y2) where x1, y1, x2, and y2 refer to the coordinates of the start and end destinations respectively.
	//Due to how the grid is set up, we need to multiply the result of Manhattan Distance. At least, that's what the slides seem to imply.

	//NOTE: Apparently, according to someone on the discord, there's constant variables for the values of the starting cell. "Look through the top of the files."
	//I THINK they're referring to the "GetStart" method in the Graph code, but I'm not sure how to access it at this time since VS complains about it not being a static method.
	
	hCost = abs(_endX-xPos) + abs(_endY-yPos);
	hCost *= 2;
}

/* !-------- TO DO ----------!
	THIS METHOD IS USED TO INTELLIGENTLY SWAP THE VERTEX'S PARENT
	IF NEED BE. CHECK TO SEE IF THE PARENT SHOULD BE SWAPPED WITH
	THE ONE PASSED IN. IF A SWAP OCCURS (OR IF YOU ARE SETTING THE
	PARENT FOR THE FIRST TIME), RETURN TRUE. OTHERWISE RETURN FALSE.
*/
bool Vertex::SetParentIfCheaper(Vertex* _possibleParent)
{
	/*
	If you encounter a cell that's already on the open list:
	Check if said cell would have a lower g cost coming from the cell the program is currently at than it does from it's own parent.
	If it does, reparent it to the cell the program is currently at, change g cost accordingly, and recalculate its f cost.

	If the end destination cell has been added to the open list, parent it to the current cell and traverse back up the parent tree to the start. We're done.
	*/

	if (_possibleParent->GetGCost() < this->GetGCost() || this->parent == NULL)
	{
		//Reparent it.
		this->parent = _possibleParent;

		//Change g cost.
		gCost = (_possibleParent->GetGCost()) + 1;

		//Recalculate f cost.
		GetFCost();

		return true;
	}

	return false;
}
