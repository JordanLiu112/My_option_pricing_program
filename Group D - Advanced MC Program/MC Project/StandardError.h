///Jordan Liu - declaration of standard error and standard deviation functions

#ifndef STANDARD_ERROR_H
#define STANDARD_ERROR_H

#include <vector>
using namespace std;

//function to get standard deviation - need all the payoffs from the simulations, and r and T so we can discount the payoffs
double SD(const vector<double>& payoffs, double r, double T);
//get standard error - we just need the standard deviation and M = number of simulations
double SE(double SD1, long M); 

#endif