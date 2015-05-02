/* Your code here! */
#ifndef DSETS_H
#define DSETS_H
#include <vector>

using std::vector;
class DisjointSets
{
public:
void addelements (int num);
int find (int elem);
void setunion (int a, int b);

private:
vector <int > sets;

};

#endif
