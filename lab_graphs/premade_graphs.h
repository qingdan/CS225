/**
 * @file premade_graphs.h
 * 
 * This file builds three example graphs with the Graph library.
 * The examples have real weights between cities in miles.
 * Unfortunately, graphviz draws the nodes with a best-fit algorithm,
 *  so relative locations of cities are wrong.
 * These graphs are also used in *_test.cpp.
 * Updated by Sean Massung for Spring 2012
 *
 * @author Sean Massung
 * @date Spring 2011
 */

#ifndef _PREMADE_GRAPHS_
#define _PREMADE_GRAPHS_

/**
 * This namespace contains code that builds three example graphs
 *  with the Graph library. The examples have real weights between
 *  cities in miles. Unfortunately, graphviz draws the nodes with a
 *  best-fit algorithm, so relative locations of cities are wrong.
 */
namespace PremadeGraphs
{
    /**
     * Returns a starting vertex for a path algorithm.
     * @param mapType - determines which map to get a starting vertex
     *  from. Possible values are "us", "europe", and "japan"
     * @return the starting vertex for a particular graph
     */
    Vertex getStartVertex(string mapType);

    /**
     * Returns a ending vertex for a path algorithm.
     * @param mapType - determines which map to get a ending vertex
     *  from. Possible values are "us", "europe", and "japan"
     * @return the ending vertex for a particular graph
     */
    Vertex getEndVertex(string mapType);

    /**
     * Creates a map of some US cities.
     * @param isWeighted - whether to show distance between
     *  cities in miles.
     * @return the graph of a few cities in the United States
     */
    Graph createUSMap(bool isWeighted);

    /**
     * Creates a map of some European cities.
     * @param isWeighted - whether to show distance between
     *  cities in miles.
     * @return the graph of a few cities in Europe
     */
    Graph createEuropeMap(bool isWeighted);

    /**
     * Creates a map of some Japanese cities.
     * @param isWeighted - whether to show distance between
     *  cities in miles.
     * @return the graph of a few cities in Japan
     */
    Graph createJapanMap(bool isWeighted);
}

#endif
