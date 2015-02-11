/*
   BlockPNG -- A Visualization for MP3
   Created by Chase Geigle for CS225, Fall 2011
*/
#include "blockpng.h"

PNG BlockPNG::genImg(vector<int> vect, int d)
{
    // error checking: we need to evenly divide the image into d by d blocks
    if( width() % d != 0 || height() % d != 0 )
	{
        cerr << "[BlockPNG]: " << d << " does not divide either width " <<
            width() << " or height " << height() << endl;
        return PNG();
    }

    // error checking: vector must be of the correct length
    if( static_cast<size_t>(( width() / d ) * ( height() / d )) != vect.size() )
        cerr << "[BlockPNG]: Vector not of correct length (" << vect.size()
            << " vs expected " << ( width() / d ) * ( height() / d ) << ")" << endl;

    PNG ret;
    ret.resize( width(), height() );

    int numWidth = width() / d;

    for( unsigned int i = 0; i < vect.size(); i++ ) {
        int idx = vect[i] % ( ( width() / d ) * ( height() / d ) + 1 );
        if( idx <= 0 )
            idx = 1;

        // if idx is different, we modified it above---alert user
        if( idx != vect[i] )
            cerr << "[BlockPNG]: Block number " << vect[i] << " not valid, "
                << "truncated to " << idx << endl;

        int x = ( (idx - 1) % numWidth ) * d;
        int oy = ( (idx - 1) / numWidth ) * d;

        int y = oy;

        int sy = y + d;

        int nx = ( i % numWidth ) * d; 
        int ny = ( i / numWidth ) * d;

        for( int j = nx; j < nx + d; j++ ) {
            for( int k = ny; k < ny + d; k++ ) {
                *ret(j,k) = *operator()(x,y);
                y++;
                if( y == sy ) {
                    y = oy; 
                    x++;
                }
            }
        }
    }

    return ret;
}
