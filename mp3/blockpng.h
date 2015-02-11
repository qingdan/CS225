/*
   BlockPNG -- A Visualization for MP3
   Created by Chase Geigle for CS225, Fall 2011
*/
#include "png.h"

#include <vector>
#include <iostream>
using std::vector;
using std::cerr;
using std::endl;

class BlockPNG : public PNG {
    public:
        PNG genImg( vector<int> vect, int d );
};
