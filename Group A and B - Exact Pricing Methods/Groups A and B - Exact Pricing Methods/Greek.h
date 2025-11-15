//Jordan Liu - declaration of Greek derived class of BlackScholes (for getting option sensitivities)

#ifndef GREEK_H
#define GREEK_H

#include "EuroOption.h"

class Greek : public BlackScholes {
public:
	Greek(); //default constructor, automatically sets values for batch 5 
	Greek(double S1, double K1, double T1, double r1, double sig1, double b1); //constructor with all 6 arguments
	Greek(double S1, double K1, double T1, double r1, double sig1); //constructor with 5 arguments (assumes b = r)
	~Greek() override; //destructor

	double callPrice() const override; //returns Euro call and put prices
	double putPrice() const override; //these are needed so Greek doesn't become an abstract class

	double callDelta() const override; //calculate Delta - option value change with the asset price
	double putDelta() const override;

	double gamma() const override; //gamma - Delta's sensitivity to asset price changes, same for calls and puts
	double vega() const; //vega - sensitivity to implied volatility, same for calls and puts

	double callTheta() const; //theta - the effect time will have on an option’s value
	double putTheta() const;

	vector<double> callDelta(const vector<double>& S_values); //accepts a vector of S values argument and returns a vector of deltas
	vector<double> putDelta(const vector<double>& S_values);

	double callDelta(double h); //use divided difference (DD) to get call delta
	double putDelta(double h);
	double gamma(double h); //same for call and put

	vector<double> callDelta(const vector<double>& S_values, double h); //DD version of taking S vector and returning delta vector
	vector<double> putDelta(const vector<double>& S_values, double h);
	vector<double> gamma(const vector<double>& S_values, double h); //DD gammas
	vector<double> gamma(const vector<double>& S_values); //exact gammas
};



#endif