#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

#include <random>
//From JacobB/prog1
//Returns vector of all strings in <str> between <delim>s.
//Returns an empty string ("") between consecutive occurences of <delim>.
std::vector<std::string> split( std::string& str, char delim );


//random
int random_int(int min, int max);


#endif // UTILS_H
