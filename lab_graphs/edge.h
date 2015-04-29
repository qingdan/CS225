/**
 * @file edge.h
 * Definition and (minimal) implementation of an edge class.
 */

#ifndef _EDGE_H_
#define _EDGE_H_

#include <string>
#include <limits.h>

using std::string;

typedef size_t Vertex;

/**
 * Represents an edge in a graph; used by the Graph class.
 *
 * @author Sean Massung
 * @date Spring 2012
 */
class Edge
{
    public:

        Vertex source;
        Vertex dest;
        int weight;
        string label;

        /**
         * Parameter constructor for unweighted graphs.
         * @param u - one vertex the edge is connected to
         * @param v - the other vertex it is connected to
         * @param lbl - the edge label
         */
        Edge(Vertex u, Vertex v, string lbl) :
            source(u), dest(v), weight(-1), label(lbl) { /* nothing */ }

        /**
         * Parameter constructor for weighted graphs.
         * @param u - one vertex the edge is connected to
         * @param v - the other vertex it is connected to
         * @param w - the weight of the edge
         * @param lbl - the edge label
         */
        Edge(Vertex u, Vertex v, int w, string lbl) :
            source(u), dest(v), weight(w), label(lbl) { /* nothing */ }

        /**
         * Default constructor.
         */
        Edge() :
            source(-1), dest(-1), weight(-1), label("") { /* nothing */ }

        /**
         * Compares two Edges.
         * operator< is defined so Edges can be sorted with std::sort.
         * @param other - the edge to compare with
         * @return whether the current edge is less than the parameter 
         */
        bool operator<(const Edge & other) const
        {
            return weight < other.weight;
        }
};

#endif
