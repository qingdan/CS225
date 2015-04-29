/**
 * @file graph.cpp
 * Graph Library Implementation
 *
 * Written for CS 225 Spring 2011
 * @author Sean Massung
 */

#include "graph.h"

/**
 * Constructor to create an empty graph.
 * @param isWeighted - specifies whether the graph is a weighted graph or not  
 */
Graph::Graph(bool isWeighted) :
    graph(VertexMap()), vertexLabels(VertexLabelMap()),
    random(47), weighted(isWeighted), vertexCounter(0) { /* nothing */ }

/**
 * Constructor to create a random, connected graph.
 * @param isWeighted - specifies whether the graph is a weighted graph or not
 * @param numVertices - the number of vertices the graph will have
 * @param seed - a random seed to create the graph with
 */
Graph::Graph(bool isWeighted, int numVertices, unsigned long seed) :
    graph(VertexMap()), vertexLabels(VertexLabelMap()),
    random(Random(seed)), weighted(isWeighted), vertexCounter(0)
{
    if(numVertices < 2)
        error("numVertices too low");

    vector<Vertex> vertices;
    for(int i = 0; i < numVertices; ++i)
    {
        Vertex next = insertVertex();
        vertices.push_back(next);
    }

    // make sure all vertices are connected
    random.shuffle(vertices);
    Vertex cur = vertices[0];
    for(size_t i = 0; i < vertices.size() - 1; ++i)
    {
        Vertex next = vertices[i + 1];
        insertEdge(cur, next);
        if(weighted)
        {
            int weight = random.nextInt();
            setEdgeWeight(cur, next, weight);
        }
        cur = next;
    }
    
    // keep the graph from being overpopulated with edges,
    //  while still maintaining a little randomness
    int numFailures = 0;
    int idx = 0;
    random.shuffle(vertices);
    while(numFailures < 2)
    {
        if( !insertEdge(vertices[idx], vertices[idx + 1]) )
        {
            ++numFailures;
        }
        else
        {
            // if insertEdge() succeeded...
            if(isWeighted)
                setEdgeWeight(vertices[idx], vertices[idx + 1], random.nextInt());
            ++idx;
            if(idx >= numVertices - 2)
            {
                idx = 0;
                random.shuffle(vertices);
            }
        }
    }
}

/**
 * Gets all adjacent vertices to the parameter vertex.
 * @param v - the vertex to get neighbors from
 * @return a vector of vertices
 */
vector<Vertex> Graph::getAdjacent(Vertex v) const
{
    assertExists(v, "getAdjacent");

    vector<Vertex> ret;
    EdgeMap edges = graph.at(v);
    EdgeMap::iterator it;
    for(it = edges.begin(); it != edges.end(); ++it)
        ret.push_back(it->second.dest);

    return ret;
}

/**
 * Returns one vertex in the graph. This function can be used
 *  to find a random vertex with which to start a traversal.
 * @return a vertex from the graph
 */
Vertex Graph::getStartingVertex() const
{
    return graph.begin()->first;
}

/**
 * Gets all the edges in the graph.
 * @return a vector of all the edges in the graph
 */
vector<Edge> Graph::getEdges() const
{
    if(graph.empty())
        return vector<Edge>();

    vector<Edge> ret;
    set< pair<Vertex, Vertex> > seen;
    VertexMap::const_iterator it;
    
    for(it = graph.begin(); it != graph.end(); ++it)
    {
        Vertex u = it->first;
        vector<Vertex> adj = getAdjacent(u);
        for(size_t i = 0; i < adj.size(); ++i)
        {
            Vertex v = adj[i];
            if(seen.find(make_pair(u, v)) == seen.end())
            {
                ret.push_back(getEdge(u, v));
                seen.insert(make_pair(u, v));
                seen.insert(make_pair(v, u));
            }
        }
    }
    
    return ret;
}

/**
 * Gets an edge between two vertices.
 * @param u - one vertex the edge is connected to
 * @param v - the other vertex the edge is connected to
 * @return the edge between u and v
 */
Edge Graph::getEdge(Vertex u, Vertex v) const
{
    assertExists(u, __func__);
    assertExists(v, __func__);
    assertConnected(u, v, __func__);
    return graph.at(u).at(v);
}

/**
 * Gets all vertices in the graph.
 * @return a vector of all vertex labels in the graph
 */
vector<Vertex> Graph::getVertices() const
{
    vector<Vertex> ret;
    VertexMap::const_iterator it;
    for(it = graph.begin(); it != graph.end(); ++it)
        ret.push_back(it->first);
    return ret;
}

/**
 * Labels a vertex with a string.
 * This is a method.
 * @param v - the vertex to label
 * @param label - label of the vertex to change
 */
void Graph::setVertexLabel(Vertex v, string label)
{    
    assertExists(v, __func__);
    vertexLabels[v] = label;
}

/**
 * Gets the label of a vertex.
 * @param v - vertex to get label from
 * @return the vertex label
 */
string Graph::getVertexLabel(Vertex v) const
{
    assertExists(v, __func__);
    return vertexLabels.at(v);
}

/**
 * Sets the edge label of an edge between vertices u and v.
 * @param u - one vertex the edge is connected to
 * @param v - the other vertex the edge is connected to
 */
void Graph::setEdgeLabel(Vertex u, Vertex v, string label)
{
    assertExists(u, __func__);
    assertExists(v, __func__);
    assertConnected(u, v, __func__);
    graph[u][v].label = label;
    graph[v][u].label = label;
}

/**
 * Gets the edge label of an edge between vertices u and v.
 * @param u - one vertex the edge is connected to
 * @param v - the other vertex the edge is connected to
 * @return the edge label between u and v
 */
string Graph::getEdgeLabel(Vertex u, Vertex v) const
{
    assertExists(u, __func__);
    assertExists(v, __func__);
    assertConnected(u, v, __func__);
    return graph.at(u).at(v).label;
}

/**
 * Gets the weight of an edge between two vertices.
 * @param u - one vertex the edge is connected to
 * @param v - the other vertex the edge is connected to
 * @return the weight of the edge
 */
int Graph::getEdgeWeight(Vertex u, Vertex v) const
{
    if(!weighted)
        error("can't get edge weights on non-weighted graphs!");

    assertExists(u, __func__);
    assertExists(v, __func__);
    assertConnected(u, v, __func__);
    return graph.at(u).at(v).weight;
}

/**
 * Inserts a new vertex into the graph and labels it.
 * @param label the label for the vertex
 * @return a copy of the vertex that was inserted
 */
Vertex Graph::insertVertex(string label /* = "" */)
{
    Vertex vertex = nextVertex();
    graph.insert(make_pair(vertex, EdgeMap()));
    vertexLabels.insert(make_pair(vertex, label));
    return vertex;
}

/**
 * Removes a given vertex from the graph.
 * @param v - the vertex to remove
 */
void Graph::removeVertex(Vertex v)
{    
    assertExists(v, __func__);
   
    // first, remove all references to the vertex in every other edge list
    // luckily, we can call getAdjacent and work backwards 
    //  instead of traversing the whole hash table
    vector<Vertex> adjacent = getAdjacent(v);
    vector<Vertex>::iterator it;
    for(it = adjacent.begin(); it != adjacent.end(); ++it)
        removeEdge(*it, v);
    
    // now that all references are gone, we can delete the vertex
    graph.erase(v);
    vertexLabels.erase(v);
}

/**
 * Inserts an edge between two vertices.
 * A boolean is returned for use with the random graph generation.
 * Hence, an error is not thrown when it fails to insert an edge.
 * @param u - one vertex the edge is connected to
 * @param v - the other vertex the edge is connected to
 * @return whether inserting the edge was successful
 */
bool Graph::insertEdge(Vertex u, Vertex v)
{   
    assertExists(u, __func__);
    assertExists(v, __func__);

    EdgeMap uEdges = graph[u];

    // "fail" silently for random graph generation
    if(uEdges.find(v) != uEdges.end())
        return false;

    Edge uEdge(u, v, -1, "");
    graph[u].insert(make_pair(v, uEdge));
 
    Edge vEdge(v, u, -1, "");
    graph[v].insert(make_pair(u, vEdge));

    return true;
}

/**
 * Removes an edge between two vertices.
 * @param u - one vertex the edge is connected to
 * @param v - the other vertex the edge is connected to
 */
void Graph::removeEdge(Vertex u, Vertex v)
{
    assertExists(u, __func__);
    assertExists(v, __func__);
    assertConnected(u, v, __func__);
    graph[u].erase(graph[u].find(v));
    graph[v].erase(graph[v].find(u));
}

/**
 * Sets the weight of an edge between two vertices.
 * @param u - one vertex the edge is connected to
 * @param v - the other vertex the edge is connected to
 * @param weight - the weight to set the edge
 */
void Graph::setEdgeWeight(Vertex u, Vertex v, int weight)
{
    assertExists(u, __func__);
    assertExists(v, __func__);
    assertConnected(u, v, __func__);
    graph[u][v].weight = weight;
    graph[v][u].weight = weight;
}

/**
 * Returns whether a given vertex exists in the graph.
 * @param v - the vertex to check
 * @param functionName - the name of the calling function to return
 *  in the event of an error
 */
void Graph::assertExists(Vertex v, string functionName) const
{
    if(graph.find(v) == graph.end())
        error(functionName + " called on nonexistent vertices");
}

/**
 * Returns whether two vertices are connected in the graph.
 * @param u - one vertex
 * @param v - another vertex
 * @param functionName - the name of the calling function to return
 *  in the event of an error
 */
void Graph::assertConnected(Vertex u, Vertex v, string functionName) const
{
    EdgeMap uEdges = graph.at(u);
    if(uEdges.find(v) == uEdges.end())
        error(functionName + " called on unconnected vertices");

    EdgeMap vEdges = graph.at(v);
    if(vEdges.find(u) == vEdges.end())
        error(functionName + " called on unconnected vertices");
}

/**
 * Creates a new vertex an inserts it into the graph.
 * @return a copy of the inserted vertex
 */
Vertex Graph::nextVertex()
{
    return vertexCounter++;
}

/**
 * Prints a graph error and quits the program.
 * The program is exited with a segfault to provide a stack trace.
 * @param message - the error message that is printed
 */
void Graph::error(string message) const
{
    cerr << "\033[1;31m[Graph Error]\033[0m " + message << endl;
    int* p = NULL;
    *p = 42; // segfault!

    /* DO NOT EDIT THIS FUNCTION.
     * There is a segfault here to provide a stack trace so
     *  you can determine where your error *really* is.
     * Most likely, the error is actually in graph_tools.cpp, where
     *  an assumption was made about the graph which was untrue.
     */
}

/**
 * Creates a name for snapshots of the graph.
 * @param title - the name to save the snapshots as
 */
void Graph::initSnapshot(string title)
{
    picNum  = 0;
    picName = title;
}

/**
 * Saves a snapshot of the graph to file.
 * initSnapshot() must be run first.
 */
void Graph::snapshot()
{
    std::stringstream ss;
    ss << picNum;
    string newName = picName + ss.str();
    savePNG(newName);
    ++picNum;
}

/**
 * Prints the graph to stdout.
 */
void Graph::print() const
{    
    VertexMap::const_iterator it;
    for(it = graph.begin(); it != graph.end(); ++it)
    {
        cout << it->first
             << getVertexName(it->first)
             << endl;
        EdgeMap::const_iterator git;
        for(git = it->second.begin(); git != it->second.end(); ++git)
        {
            std::stringstream ss;
            ss << git->second.dest;
            string vertexColumn = "    => " + ss.str();
            vertexColumn += " " + getVertexName(git->first);
            cout << std::left << std::setw(26) << vertexColumn;
            string edgeColumn = "edge label = \"" + git->second.label + "\"";
            cout << std::left << std::setw(26) << edgeColumn;
            if(weighted)
                cout << "weight = " << git->second.weight;
            cout << endl;
        }
        cout << endl;
    }
}

/**
 * Saves the graph as a PNG image.
 * @param title - the filename of the PNG image
 */
void Graph::savePNG(string title) const
{
    std::ofstream neatoFile;
    string filename = "images/" + title + ".dot";
    neatoFile.open(filename.c_str());

    if(!neatoFile.good())
        error("couldn't create " + filename + ".dot");

    neatoFile << "strict graph G {\n"
              << "\toverlap=\"false\";\n"
              << "\tdpi=\"160\";\n"
              << "\tsep=\"1.5\";\n"
              << "\tnode [fixedsize=\"true\", shape=\"circle\", fontsize=\"6.0\"];\n"
              << "\tedge [penwidth=\"1.5\", fontsize=\"6.0\"];\n";
              
    VertexMap::const_iterator it;
    for(it = graph.begin(); it != graph.end(); ++it)
    {
        EdgeMap::const_iterator git;
        for(git = it->second.begin(); git != it->second.end(); ++git)
        {
            string vertex1Text = getVertexName(it->first);
            string vertex2Text = getVertexName(git->first);

            neatoFile << "\t\"" << it->first;
            neatoFile << vertex1Text;
            neatoFile << "\" -- \"" << git->first;
            neatoFile << vertex2Text;
            neatoFile << "\"";

            string edgeLabel = git->second.label;
            if(edgeLabel == "MST" || edgeLabel == "MIN" || edgeLabel == "MINPATH")
                neatoFile << "[color=\"blue\"]";
            else if(edgeLabel == "CROSS")
                neatoFile << "[color=\"red\"]";
            else if(edgeLabel == "DISCOVERY")
                neatoFile << "[color=\"green\"]";
            else if(edgeLabel == "VISITED")
                neatoFile << "[color=\"grey\"]";
            if(weighted && git->second.weight != -1)
                neatoFile << "[label=\"" << git->second.weight << "\"]";
            neatoFile << ";\n";
        }
    }
    
    neatoFile << "}";
    neatoFile.close();
    string command = "neato -Tpng " + filename + " -o " + "images/" + title + ".png 2> /dev/null";
    system(command.c_str());
    string rmCommand = "rm -f " + filename + " 2> /dev/null";
    system(rmCommand.c_str());
}

/**
 * Creates a name for a vertex. This is *NOT* for marking as
 *  unvisited, cross, etc. Use setVertexLabel instead for that.
 * This is only really used for the premade graphs where particular
 *  nodes have fun names, such as cities.
 * @param v - the vertex to label
 * @param label - label of the vertex to change
 */
void Graph::setVertexName(Vertex v, string name)
{
    vertexNames.insert(make_pair(v, name));
}

/**
 * Gets the name of a vertex.
 * This is only really used for the premade graphs where particular
 *  nodes have fun names, such as cities.
 * @param v - vertex to get the name from
 * @return the vertex name
 */
string Graph::getVertexName(Vertex v) const
{
    if(vertexNames.find(v) != vertexNames.end())
        return " (" + vertexNames.at(v) + ")";
    if(vertexLabels.find(v) != vertexLabels.end())
        return " (" + vertexLabels.at(v) + ")";
    return "";
}
