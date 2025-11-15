///Jordan Liu - definition of the BlackScholes base class

#include "BlackScholes.h"

BlackScholes::BlackScholes() : S(60), K(65), T(0.25), r(0.08), sig(0.30), b(0.08) {} //default constructor (assigns values from Batch 1)
BlackScholes::BlackScholes(double S1, double K1, double T1, double r1, double sig1, double b1) : S(S1), K(K1), T(T1), r(r1), sig(sig1), b(b1) {}
BlackScholes::~BlackScholes() {} //destructor

void BlackScholes::checkParam(const string& name, double value) { //for checking the string in the matrix input and assigning the value to the right parameter
	if (name == "K") K = value; //check name of the parameter before assigning value from other vector to data member
	else if (name == "T") T = value;
	else if (name == "r") r = value;
	else if (name == "sig") sig = value;
	else if (name == "b") b = value;
	else S = value; //assign value to S by default
}

double BlackScholes::d1() const { //calculate d1 according to formula provided
	return (log(S / K) + (b + sig * sig / 2) * T) / (sig * sqrt(T));
}
double BlackScholes::d2() const { //calculate d2
	return d1() - sig * sqrt(T); //we can use the easier formula by calling d1()
}

double BlackScholes::N(double x) const { //standard cumulative Normal distribution
	boost::math::normal_distribution<> normal(0.0, 1.0); //create standard normal distribution
	return cdf(normal, x); //return standard Normal cdf
}

double BlackScholes::n(double x) const { //standard Normal pdf for option sensitivities calculations
	boost::math::normal_distribution<> normal(0.0, 1.0); //create standard normal distribution
	return pdf(normal, x); //return standard Normal pdf
}

double BlackScholes::y1() const { //calculate y1 for US perpetual options
	return 0.5 - b / (sig * sig) + sqrt((b / (sig * sig) - 0.5) * (b / (sig * sig) - 0.5) + ((2 * r) / (sig * sig)));
}

double BlackScholes::y2() const { //calculate y2 for US perpetual options
	return 0.5 - b / (sig * sig) - sqrt((b / (sig * sig) - 0.5) * (b / (sig * sig) - 0.5) + ((2 * r) / (sig * sig)));
}















