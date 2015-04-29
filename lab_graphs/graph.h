/**
 * @file graph.h
 * Graph Library Declarations
 *
 * Written for CS 225 Spring 2011
 * @author Sean Massung
 *
 * Updated Spring 2012 by Sean Massung
 *  - Added doxygen comments
 *  - Created better error handling
 *  - More encapsulated and object-oriented
 */

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "lab_graphs_random.h"
#include "edge.h"

typedef std::unordered_map<Vertex, Edge> EdgeMap;
typedef std::unordered_map<Vertex, EdgeMap> VertexMap;
typedef std::unordered_map<Vertex, std::string> VertexLabelMap;
typedef std::unordered_map<Vertex, std::string> VertexNameMap;

using std::cerr;
using std::cout;
using std::endl;
using std::vector;
using std::set;
using std::string;
using std::vector;
using std::pair;
using std::make_pair;

/**
 * Represents a graph of vertices and edges and allows basic operations to be performed on it.
 */
class Graph
{
    public:
        /**
         * Constructor to create an empty graph.
         * @param isWeighted - specifies whether the graph is a weighted graph or not  
         */
        Graph(bool isWeighted);

        /**
         * Constructor to create a random, connected graph.
         * @param isWeighted - specifies whether the graph is a weighted graph or not
         * @param numVertices - the number of vertices the graph will have
         * @param seed - a random seed to create the graph with
         */
        Graph(bool isWeighted, int numVertices, unsigned long seed);
        
        /**
         * Gets all adjacent vertices to the parameter vertex.
         * @param v - the vertex to get neighbors from
         * @return a vector of vertices
         */
        vector<Vertex> getAdjacent(Vertex v) const;

        /**
         * Returns one vertex in the graph. This function can be used
         *  to find a random vertex with which to start a traversal.
         * @return a vertex from the graph
         */
        Vertex getStartingVertex() const;
        
        /**
         * Gets all vertices in the graph.
         * @return a vector of all vertex labels in the graph
         */
        vector<Vertex> getVertices() const;
        
        /**
         * Gets an edge between two vertices.
         * @param u - one vertex the edge is connected to
         * @param v - the other vertex the edge is connected to
         * @return the edge between u and v
         */
        Edge getEdge(Vertex u, Vertex v) const;

        /**
         * Gets all the edges in the graph.
         * @return a vector of all the edges in the graph
         */
        vector<Edge> getEdges() const;

        /**
         * Creates a name for a vertex. This is *NOT* for marking as
         *  unvisited, cross, etc. Use setVertexLabel instead for that.
         * This is only really used for the premade graphs where particular
         *  nodes have fun names, such as cities.
         * @param v - the vertex to label
         * @param label - label of the vertex to change
         */
        void setVertexName(Vertex v, string name);

        /**
         * Gets the name of a vertex.
         * This is only really used for the premade graphs where particular
         *  nodes have fun names, such as cities.
         * @param v - vertex to get the name from
         * @return the vertex name
         */
        string getVertexName(Vertex v) const;

        /**
         * Labels a vertex with a string.
         * This is a method.
         * @param v - the vertex to label
         * @param label - label of the vertex to change
         */
        void setVertexLabel(Vertex v, string label);

        /**
         * Gets the label of a vertex.
         * @param v - vertex to get label from
         * @return the vertex label
         */
        string getVertexLabel(Vertex v) const;
        
        /**
         * Sets the edge label of an edge between vertices u and v.
         * @param u - one vertex the edge is connected to
         * @param v - the other vertex the edge is connected to
         */
        void setEdgeLabel(Vertex u, Vertex v, string label);

        /**
         * Gets the edge label of an edge between vertices u and v.
         * @param u - one vertex the edge is connected to
         * @param v - the other vertex the edge is connected to
         * @return the edge label between u and v
         */
        string getEdgeLabel(Vertex u, Vertex v) const;

        /**
         * Gets the weight of an edge between two vertices.
         * @param u - one vertex the edge is connected to
         * @param v - the other vertex the edge is connected to
         * @return the weight of the edge
         */
        int getEdgeWeight(Vertex u, Vertex v) const;
        
        /**
         * Inserts a new vertex into the graph and labels it.
         * @param label the label for the vertex
         * @return a copy of the vertex that was inserted
         */
        Vertex insertVertex(string label = "");

        /**
         * Removes a given vertex from the graph.
         * @param v - the vertex to remove
         */
        void removeVertex(Vertex v);
        
        /**
         * Inserts an edge between two vertices.
         * A boolean is returned for use with the random graph generation.
         * Hence, an error is not thrown when it fails to insert an edge.
         * @param u - one vertex the edge is connected to
         * @param v - the other vertex the edge is connected to
         * @return whether inserting the edge was successful
         */
        bool insertEdge(Vertex u, Vertex v);

        /**
         * Removes an edge between two vertices.
         * @param u - one vertex the edge is connected to
         * @param v - the other vertex the edge is connected to
         */
        void removeEdge(Vertex u, Vertex v);
        
        /**
         * Sets the weight of an edge between two vertices.
         * @param u - one vertex the edge is connected to
         * @param v - the other vertex the edge is connected to
         * @param weight - the weight to set the edge
         */
        void setEdgeWeight(Vertex u, Vertex v, int weight);

        /**
         * Creates a name for snapshots of the graph.
         * @param title - the name to save the snapshots as
         */
        void initSnapshot(string title);

        /**
         * Saves a snapshot of the graph to file.
         * initSnapshot() must be run first.
         */
        void snapshot();

        /**
         * Prints the graph to stdout.
         */
        void print() const;

        /**
         * Saves the graph as a PNG image.
         * @param title - the filename of the PNG image
         */
        void savePNG(string title) const;
        
    private:

        /** a mapping of vertices to edge lists */
        VertexMap graph;

        /** a mapping of vertices to their labels */
        VertexLabelMap vertexLabels;

        /** a mapping of vertices to their names */
        VertexNameMap vertexNames;

        /** a random number generator */
        Random random;

        bool weighted;
        int picNum;
        string picName;
        size_t vertexCounter;

        /**
         * Creates a new vertex an inserts it into the graph.
         * @return a copy of the inserted vertex
         */
        Vertex nextVertex();

        /**
         * Returns whether a given vertex exists in the graph.
         * @param v - the vertex to check
         * @param functionName - the name of the calling function to return
         *  in the event of an error
         */
        void assertExists(Vertex v, string functionName) const;

        /**
         * Returns whether two vertices are connected in the graph.
         * @param u - one vertex
         * @param v - another vertex
         * @param functionName - the name of the calling function to return
         *  in the event of an error
         */
        void assertConnected(Vertex u, Vertex v, string functionName) const;

        /**
         * Prints a graph error and quits the program.
         * The program is exited with a segfault to provide a stack trace.
         * @param message - the error message that is printed
         */
        void error(string message) const;
};

#endif
