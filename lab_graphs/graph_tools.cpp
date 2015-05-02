/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph & graph, Vertex start, Vertex end)
{
	vector <Vertex> vertices = graph.getVertices();
	for(size_t i = 0; i < vertices.size(); i++)
		graph.setVertexLabel(vertices[i], "UNEXPLORED");
	vector <Edge> edges = graph.getEdges();
	for(size_t i = 0; i < edges.size(); i++)
	{	Vertex u = edges[i].source;
		Vertex w = edges[i].dest;
		graph.setEdgeLabel(u, w, "UNEXPLORED");
	}
	queue <Vertex> q;
	unordered_map <Vertex, Vertex> parent;
	q.push(start);
	graph.setVertexLabel(start, "VISITED");	
	while(!q.empty())
	{
		Vertex w = q.front();
		q.pop();
		vector <Vertex> adjacent = graph.getAdjacent(w);
		for(size_t i = 0; i < adjacent.size(); i++)
		{
			if(graph.getVertexLabel(adjacent[i]) == "UNEXPLORED")
			{
				graph.setEdgeLabel(w, adjacent[i], "DISCOVERY");
				graph.setVertexLabel(adjacent[i], "VISITED");
				pair <Vertex, Vertex> pairVertex (adjacent[i], w);
				parent.insert(pairVertex);
				q.push(adjacent[i]); 
			}
			else if(graph.getEdgeLabel(w, adjacent[i]) == "UNEXPLORED")
			{
				graph.setEdgeLabel(w, adjacent[i], "CORSS");
			}
		}
	}
	int distance = 0;
	while(end != start)
	{
		graph.setEdgeLabel(end, parent[end], "MINPATH");
		end = parent[end];
		distance ++;
	}
	return distance;	
}

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph & graph)
{
	vector <Vertex> vertices = graph.getVertices();
	for(size_t i = 0; i < vertices.size(); i++)
		graph.setVertexLabel(vertices[i], "UNEXPLORED");
	vector <Edge> edges = graph.getEdges();
	for(size_t i = 0; i < edges.size(); i++)
	{	Vertex u = edges[i].source;
		Vertex w = edges[i].dest;
		graph.setEdgeLabel(u, w, "UNEXPLORED");
	}
	queue <Vertex> q;
	q.push(vertices[0]);
	graph.setVertexLabel(vertices[0], "VISITED");	
	Vertex startDest = (graph.getAdjacent(vertices[0]))[0];
	int minWeight = graph.getEdgeWeight(vertices[0], startDest);
	Vertex min1 = vertices[0];
	Vertex min2 = startDest;
	while(!q.empty())
	{
		Vertex w = q.front();
		q.pop();
		vector <Vertex> adjacent = graph.getAdjacent(w);
		for(size_t i = 0; i < adjacent.size(); i++)
		{
			if(graph.getVertexLabel(adjacent[i]) == "UNEXPLORED")
			{
				graph.setEdgeLabel(w, adjacent[i], "DISCOVERY");
				graph.setVertexLabel(adjacent[i], "VISITED");
				int currWeight = graph.getEdgeWeight(adjacent[i], w);
				if(currWeight < minWeight)
				{
					minWeight = currWeight;
					min1 = w;
					min2 = adjacent[i];
				}
				q.push(adjacent[i]); 
			}
			else if(graph.getEdgeLabel(w, adjacent[i]) == "UNEXPLORED")
			{
				graph.setEdgeLabel(w, adjacent[i], "CORSS");
				int currWeight = graph.getEdgeWeight(adjacent[i], w);
				if(currWeight < minWeight)
				{
					minWeight = currWeight;
					min1 = w;
					min2 = adjacent[i];
				}
			}
		}
	}
	
	graph.setEdgeLabel(min1, min2, "MIN");
	return minWeight;
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort (http://www.cplusplus.com/reference/algorithm/sort/)
 *  instead of creating a priority queue.
 */
void GraphTools::findMST(Graph & graph)
{
	vector< Vertex > vertices = graph.getVertices();
	int numOfVertex = vertices.size();
	DisjointSets setVertices;
	setVertices.addelements(numOfVertex);

	int count = 0;

	vector< Edge > edges = graph.getEdges();
	int numEdges = edges.size();
	std::sort(edges.begin(), edges.end(), sort_edge);

	for(int i = 0; i < numEdges && count < numOfVertex - 1; i++)
	{
		Vertex u = edges[i].source;
		Vertex v = edges[i].dest;
		if(setVertices.find(u) != setVertices.find(v))
		{
			setVertices.setunion(u, v);
			graph.setEdgeLabel(u, v, "MST");
			count++;
		}
	}


}

bool GraphTools::sort_edge (Edge u, Edge v) {
    return (u.weight < v.weight);
}
