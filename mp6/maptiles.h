/**
 * @file maptiles.h
 *	 			
 * mapTiles() function.
 * Developed for CS225 PhotoMosaic MP
 *
 * @author Jack Toole
 * @date Fall 2011
 */
	 			
#ifndef MAPTILES_H
#define MAPTILES_H
	 			
#include <map>
#include <vector>
#include "png.h"
#include "kdtree.h"
#include "mosaiccanvas.h"
#include "sourceimage.h"
#include "tileimage.h"

using namespace std;

/**
 * Map the image tiles into a mosaic canvas which closely
 * matches the input image.
 *
 * @todo This function is required for MP 6.2.
 * @param theSource The input image to construct a photomosaic of
 * @param theTiles The tiles image to use in the mosaic
 */
MosaicCanvas * mapTiles(SourceImage const & theSource, vector<TileImage> const & theTiles);

#endif // MAPTILES_H
