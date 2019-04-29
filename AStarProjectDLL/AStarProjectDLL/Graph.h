/* NO EDITS NEEDED IN THIS FILE. YOU MAY ADD HELPERS METHODS HERE IF YOU WOULD LIKE.

	Graph Class Declaration

	The Graph class is responsible for:
		- Keeping track of our logical "grid", in which we can navigate.
		- Calculating paths within that grid (using your A* code).
*/

#pragma once
#include "Vertex.h"
#include <stack>
class Graph
{
public:
	// Constructors and Destructor
	Graph();
	Graph(const int** _mazeData, int _mazeWidth, int _mazeHeight);
	~Graph();

	// A few methods for setting the start and end positions
	bool SetStart(int _startX, int _startY);
	bool SetEnd(int _endX, int _endY);

	// A few methods that expose data publicly
	int GetWidth();
	int GetHeight();
	Vertex GetStart();
	Vertex GetEnd();
	int** GetRawMazeData();

	// Returns true if a path between the start and end has been determined to exist.
	bool PathExists();

	// Returns the next point to move the character on the way to the end.
	// Will try to calculate a path if one does not currently exist.
	Vertex NextPosition();

	// Will try to calculate a path if one has not already been calculated.
	void FindPathIfNeeded();

private:
	// A bunch of data regarding the "maze" world.
	const int** rawMazeData;
	int mazeWidth;
	int mazeHeight;
	int startX;
	int startY;
	int endX;
	int endY;

	// The logical "maze" of walls and floor spaces which will be used to
	// calculate the path using the A* Pathfinding Algorithm.
	Vertex** vertexGraph;

	// A bool for keeping track of if any data has been changed since the
	// path was determined (aka the start or end point changed).
	bool pathMatchesInput;

	// A method for calculating each vertices' heuristic cost.
	void CalculateHCosts();

	// The method that holds our A* algorithm. This is where you will be
	// programming everything.
	void FindPath();

	// The stack that will be used to hold our determined path.
	std::stack<Vertex> path;
};

