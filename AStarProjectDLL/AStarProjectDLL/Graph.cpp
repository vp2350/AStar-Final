/*
	Graph Class Definitions

	DO NOT edit any methods in this file EXCEPT FindPath().
	Editing other methods will cause the program to become non-functional,
	and you will need to revert your changes to restore functionality to the
	program. This DLL is built to a very specific specification.
*/

#include "stdafx.h"
#include "Graph.h"
using namespace std;


// !-------------DO NOT EDIT THIS--------------!
Graph::Graph()
{
}

// !-------------DO NOT EDIT THIS--------------!
/* This constructor takes in the maze data sent by the test app and constructs
	a logical version of that data as a 2D array of vertices.
*/
Graph::Graph(const int ** _mazeData, int _mazeWidth, int _mazeHeight)
{
	pathMatchesInput = false;
	mazeWidth = _mazeWidth;
	mazeHeight = _mazeHeight;
	rawMazeData = _mazeData;

	vertexGraph = new Vertex*[mazeWidth];

	for (int x = 0; x < mazeWidth; x++)
	{
		vertexGraph[x] = new Vertex[mazeHeight];
		for (int y = 0; y < mazeHeight; y++)
		{
			vertexGraph[x][y] = Vertex();
			vertexGraph[x][y].xPos = x;
			vertexGraph[x][y].yPos = y;

			if (_mazeData[x][y] == 0)
			{
				vertexGraph[x][y].isWall = true;
			}
		}
	}
}

// !-------------DO NOT EDIT THIS--------------!
/* This destructor is responsible for cleaning up the maze data
	once we are done using it. NOTE: This program will likely
	display memory leaks because of the way this DLL is handled
	by the Test App. Ignore those memory leaks.
*/
Graph::~Graph()
{
	for (int x = 0; x < mazeWidth; x++)
	{
		delete[] vertexGraph[x];
		vertexGraph[x] = nullptr;
	}
	delete[] vertexGraph;
	vertexGraph = nullptr;
}

// !-------------DO NOT EDIT THIS--------------!
/* This method for setting the start is necessary so that we can update the
	"pathMatchesInput" bool whenever we change them. We use this bool to ensure
	that we have calculated the path before returning any points if the start 
	or end points have changed.
*/
bool Graph::SetStart(int _startX, int _startY)
{
	if (_startX < 0 && _startX >= mazeWidth && _startY < 0 && _startY >= mazeHeight)
	{
		return false;
	}

	pathMatchesInput = false;
	startX = _startX;
	startY = _startY;

	return true;
}

// !-------------DO NOT EDIT THIS--------------!
/* This method for setting the end is necessary so that we can update the
	"pathMatchesInput" bool whenever we change them. We use this bool to ensure
	that we have calculated the path before returning any points if the start 
	or end points have changed.
*/
bool Graph::SetEnd(int _endX, int _endY)
{
	if (_endX < 0 && _endX >= mazeWidth && _endY < 0 && _endY >= mazeHeight)
	{
		return false;
	}

	pathMatchesInput = false;
	endX = _endX;
	endY = _endY;

	return true;
}

// !-------------DO NOT EDIT THIS--------------!
// This helper function will return true of a path exists at present.
bool Graph::PathExists()
{
	if (path.size() > 0)
	{
		return true;
	}
	return false;
}

// !-------------DO NOT EDIT THIS--------------!
/* NextPosition will return the next point in the path. Before returning
	anything, it ensures our path is up to date using FindPathIfNeeded(),
	which will find a new path if any part of the graph has changed since
	we last calculated the path.
*/
Vertex Graph::NextPosition()
{
	FindPathIfNeeded();

	Vertex nextPoint = path.top();
	path.pop();

	return nextPoint;
}

// !-------------DO NOT EDIT THIS--------------!
// This method returns our private mazeWidth.
int Graph::GetWidth()
{
	return mazeWidth;
}

// !-------------DO NOT EDIT THIS--------------!
// This method returns our private mazeHeight.
int Graph::GetHeight()
{
	return mazeHeight;
}

// !-------------DO NOT EDIT THIS--------------!
// This method returns our start point as a vertex.
Vertex Graph::GetStart()
{
	Vertex start = Vertex();
	start.xPos = startX;
	start.yPos = startY;
	return start;
}

// !-------------DO NOT EDIT THIS--------------!
// This mhod returns our end point as a vertex.
Vertex Graph::GetEnd()
{
	Vertex end = Vertex();
	end.xPos = endX;
	end.yPos = endY;
	return end;
}

// !-------------DO NOT EDIT THIS--------------!
// This method returns our raw maze data.
int ** Graph::GetRawMazeData()
{
	return (int**)rawMazeData;
}

// !-------------DO NOT EDIT THIS--------------!
/* This helper method determines if our path is up to date. If any
	part of our graph has changed since we last determined the path,
	it will update the graph and find a path from the new start to the
	new end point.
*/
void Graph::FindPathIfNeeded()
{
	if (!pathMatchesInput)
	{
		CalculateHCosts();
		FindPath();
	}
}

// !-------------DO NOT EDIT THIS--------------!
/* This method loops through the graph and sets up the heuristic costs
	for all of the vertices. You will need to fill in the Vertex::SetHCost()
	method in Vertex.cpp for this to work.
*/
void Graph::CalculateHCosts()
{
	for (int x = 0; x < mazeWidth; x++)
	{
		for (int y = 0; y < mazeHeight; y++)
		{
			vertexGraph[x][y].SetHCost(endX, endY);
		}
	}
}




void Graph::FindPath()
{
	// !-------- TO DO ----------!
	/* PERFORM THE ENTIRE A* ALGORITHM HERE.

	   CALCULATE THE PATH BETWEEN THE START POINT (startX, startY), AND
	   THE END POINT (endX, endY). ONCE YOU HAVE DETERMINED THE PATH, PUSH
	   IT TO THE "path" STACK. YOU SHOULD PUSH ELEMENTS TO THE STACK STARTING
	   AT THE END AND CONTINUING UNTIL YOU MAKE IT TO THE STARTING VERTEX.

	   READ THROUGH THIS GRAPH CLASS, THE VERTEX CLASS, AND THE ASTARPROJECTDLL.CPP
	   TO GET AN IDEA OF HOW EVERYTHING TIES TOGETHER. BELOW IS A LIST OF IMPORTANT
	   INFORMATION/VARIABLES YOU'LL NEED TO KNOW TO BE SUCCESSFUL.

		- The Vertex class is used to keep track of one specific "cell" in the grid.

		- vertexGraph is a 2D array of Vertex data. You can index into this array
			like this: vertexGraph[x][y].
			- Each vertex in this 2D array is already set up with the following:
				- Each knows if it is a wall or not.
				- Each knows its x and y position.
				- The vertex position in the vertexGraph mirrors its position in the
					grid. AKA: vertexGraph[x][y] is at position (x,y).

		- YOU MUST DO THE FOLLOWING:
			- Complete the SetParentIfCheaper() and SetHCost() methods in the Vertex class.
			- Empty out the path at the start of the method.
			- Push the final path to the path stack.
			- Set pathMatchesInput to true once you have either determined the path or
				determined that there is no path.
			- Only check UP DOWN LEFT AND RIGHT. Do NOT program diagonal movement.

		Feel free to create helper methods within this Graph class to compartmentalize
		any code you would like.

		Also, a reminder that this algorithm is NOT called each time the player moves.
		It will ONLY be called once to determine the path. The player will then move
		along the predetermined path.
	*/

	path.empty();

	// Your A* code goes here.
}