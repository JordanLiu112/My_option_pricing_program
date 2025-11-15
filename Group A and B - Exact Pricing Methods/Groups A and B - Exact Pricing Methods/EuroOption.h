///Jordan Liu - declaration of Euro option derived class of BlackScholes

#ifndef EURO_OPTION_H
#define EURO_OPTION_H

#include "BlackScholes.h"

class EuroOption : public BlackScholes {
public:
	EuroOption(); //default constructor (automatically sets batch 1 values)
	EuroOption(double S1, double K1, double T1, double r1, double sig1, double b1); //constructor with 6 arguments (when b=/= r)
	EuroOption(double S1, double K1, double T1, double r1, double sig1); //constructor with 5 arguments (assumes b=r)
	~EuroOption() override; //destructor with override

	double callPrice() const override; //get Euro call and put prices
	double putPrice() const override; 

	double callDelta() const override; //get deltas and gamma (necessary so EuroOption doesn't become abstract)
	double putDelta() const override;
	double gamma() const override;

	double callPrice(double put) const; //get call price from put price using put-call parity
	double putPrice(double call) const; //get put price from call price using put-call parity
	double verifyParity(double call, double put) const; //verify wheter given call and put prices satisfy put-call parity

	vector<double> callPrice(const vector<double>& S_values); //input vector of S values, return vector of call or put prices
	vector<double> putPrice(const vector<double>& S_values);

};


#endif