///Jordan Liu - definition of standard error and standard deviation functions

#include "StandardError.h"

//function to get standard deviation 
double SD(const vector<double>& payoffs, double r, double T) {
	double sum = 0, sumSquares = 0;
	const long M = payoffs.size(); //get M = number of simulations
	for (long i = 0; i < M; ++i) {
		sum += payoffs[i]; //get the sum of all call/put output prices from all simulations
		sumSquares += payoffs[i] * payoffs[i]; //get squared sum
	}
	return sqrt((sumSquares - sum * sum / M) / (M - 1)) * exp(-r * T); //SD formula
}


//get standard error - we just need the standard deviation and M = number of simulations
double SE(double SD1, long M) {
	return SD1 / sqrt(M);
}