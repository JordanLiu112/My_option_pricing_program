///declaration of US_Perpetual derived class of BlackScholes

#ifndef US_PERPETUAL_H
#define US_PERPETUAL_H

#include "BlackScholes.h"

class US_Perpetual : public BlackScholes {
public:
	US_Perpetual(); //default constructor, automatically sets values of batch6
	US_Perpetual(double S1, double K1, double r1, double sig1, double b1); //5-argument constructor, assumes T = 0
	~US_Perpetual() override; //destructor with override

	double callPrice() const override; //get US perpetual call and put prices
	double putPrice() const override;

	double callDelta() const override { return 0; }; //need these to avoid US_Perpetual being an abstract class
	double putDelta() const override { return 0; }; //with T = 0, all these are technically undefined since they involve dividing by 0
	double gamma() const override { return 0; }; //but these must return a double, so for now, they are to return 0. 

	vector<double> callPrice(const vector<double>& S_values); //input vector of S values, return vector of call or put prices
	vector<double> putPrice(const vector<double>& S_values);

};


#endif