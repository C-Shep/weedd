// CMP201.2022 AX1.7 Pathfinding over DiGraphs
// Author William Kavanagh
// Partial Framework

#include "Graph.h"

// digraph constructor.
// initialise size and vertices (a pointer to an array of graphVertex pointers)
// set all LLs to nullptrs, then use getAdjacencyList to add each edge to the adjacency list.
Graph::Graph(graphEdge edges[], int numEdges, int numVertices)
{
	// Assessed: 1 mark
	size = numVertices;

	vertices = new graphVertex* [size]();

	for (int i=0; i < size; i++)
	{
		vertices[i] = nullptr;
	}

	for (int i=0; i < numEdges; i++)
	{
		vertices[edges[i].from] = getAdjacencyList(edges[i].to, edges[i].weight, vertices[edges[i].from]);
	}
}

// Builds a string representation of the graph showing the edges going from each vertex in the following form:
// e.g.: vertex 12 with edges to vertex 3 of weight 5 and vertex 13 of weight 1 would look like:
// "v12: 3 (w=5), 13 (w=1) 
// Notice the spaces, commas (not trailing). Also each vertex is on it's own line.
// Nothing should be printed by this method.
// hint: Use std::to_string(int val) to convert from integers to strings
std::string Graph::display()
{
	// Assessed: 1 mark
	int counter = 0;
	std::string stringaling;
	bool weed;

	for (int i = 0; i < size; i++)
	{
		graphVertex* temp = vertices[i];

		if (temp)
		{
			stringaling += "v";
			stringaling += std::to_string(i);
			stringaling += ": ";

			do {
				weed = false;

				stringaling += std::to_string(temp->to);
				stringaling += " (w=";
				stringaling += std::to_string(temp->weight);
				stringaling += ")";

				if (temp->next)
				{
					stringaling += ", ";
					temp = temp->next;
					weed = true;
				}

			} while (weed);
			stringaling += "\n";
		}

	}

	return stringaling;
}

// Use Dijkstra's algorithm to find the shortest path from start to end.
// returns a structure with the path length and a stack with all vertices on the path with the start on the top.
// You can assume all edge weights will be under 1000.
// pathInformation is defined at the top of Graph.h
// HINT:	pQueue.top() gets a reference to the first element, but does not remove it. 
//			pQueue.pop() removes the first element but does not get a reference to it.
//				.. so use both.
pathInformation Graph::dijkstra(int start, int end)
{
	// Assessed: 3 marks

	// Initial DSs, provided.
	std::map<int, int> distanceTo;	// maps from vertices to best distance found to start (start->start = 0)
	std::map<int, int> pathTaken;	// maps from vertices to last vertex visited as part of best distance found so far.
	std::map<int, bool> visited;	// maps from vertices to whether or not the vertex has been visited yet so we do not visit vertices multiple times.
	// priority queue of distances to vertices yet to visit alongside their index. DISTANCE FIRST, index second.
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> frontier;

	// TODO
	// Set initial distances to arbitrarily high value and set start distance to 0. 
	// Add start to frontier.
	for (int i = 0; i < size; i++)
	{
		distanceTo[i] = INT_MAX;
		visited[i] = false;
	}

	distanceTo[start] = 0;
	frontier.push({distanceTo[start], start});

	// TODO
	// main loop:
	// while the frontier has vertices yet to visit. 
	// get a reference to the vertex, if the vertex has been visited, continue
	// remove from frontier, set visited to true and iterate over all edges from the vertex in the adjacency list.
		// check if the distance via the visited vertex along the edge is smaller than the currently found shortest distance
			// update the distance and path maps if a new shorter path is found, add the edge vertex to the frontier with the new distance.
	while (frontier.empty() == false)
	{
		int top = frontier.top().second;
		int dist = frontier.top().first;
		bool stopFlag;

		frontier.pop();

		graphVertex* reference = vertices[top];

		if (reference)
		{
			do {
				stopFlag = false;

				if (dist + reference->weight < distanceTo[reference->to])
				{
					distanceTo[reference->to] = reference->weight + dist;
					pathTaken[reference->to] = top;
				}

				if (!visited[reference->to])
				{
					frontier.push({distanceTo[reference->to],reference->to});
				}

				if (reference->next)
				{
					reference = reference->next;
					stopFlag = true;
				}
			} while (stopFlag == true);
			visited[top] = true;
		}
	}

	// TODO
	// Create a return structure and store the length as the distance to the end.
	// Create an int stack and iterate backwards over the pathTo map, pushing onto the stack from end until start has been pushed.
	// Store the stack in the structure and return it.




	std::stack<int> stack;
	int counter = end;

	stack.push(end);

	while (counter >start)
	{
		stack.push(pathTaken[counter]);
		counter = pathTaken[counter];
	}

	pathInformation returner;

	returner.length = distanceTo[end];
	returner.path = stack;

	return returner;
	
}