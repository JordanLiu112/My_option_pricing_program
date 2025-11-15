//Jordan Liu - definition of US_Perpetual derived class of BlackScholes

#include "US_Perpetual.h"


US_Perpetual::US_Perpetual() : BlackScholes(110, 100, 0, 0.1, 0.1, 0.02) {} //default constructor, automatically sets values of batch 6
US_Perpetual::US_Perpetual(double S1, double K1, double r1, double sig1, double b1) : BlackScholes(S1, K1, 0, r1, sig1, b1) {}
US_Perpetual::~US_Perpetual() {} //destructor



double US_Perpetual::callPrice() const { //get US perpetual call price
	double S = getS(), K = getK(), T = getT(), r = getR(), sig = getSig(), b = getB();
	if (b >= r) return S * exp((b - r) * T) * N(d1()) - K * exp(-r * T) * N(d2()); //when cost of carry (b) exceeds rate of return (r), it is better to hold the asset than exercise early, so the US call price = Euro price
	return (K / (y1() - 1)) * pow((((y1() - 1) / y1()) * (S / K)), y1());
}

double US_Perpetual::putPrice() const { //get US perpetual put price
	double S = getS(), K = getK();
	return (K / (1 - y2())) * pow((((y2() - 1) / y2()) * (S / K)), y2());
}

vector<double> US_Perpetual::callPrice(const vector<double>& S_values) { //get vector of US perpetual call prices
	vector<double> call_prices; //create vector of call prices
	call_prices.reserve(S_values.size()); //reserve the same size as the number of S values
	const double save_S = getS(); //save the original value of S data member

	for (int i = 0; i < S_values.size(); ++i) {
		setS(S_values[i]); //assign S value in vector to S data member
		call_prices.push_back(callPrice()); //so we can use US callPrice() and push it into price vector
	}
	setS(save_S); //restore original value of S
	return call_prices;
}


vector<double> US_Perpetual::putPrice(const vector<double>& S_values) { //get vector of US perpetual put prices
	vector<double> put_prices; //create vector of put prices
	put_prices.reserve(S_values.size()); //reserve the same size as the number of S values
	double save_S = getS(); //save the original value of S data member

	for (int i = 0; i < S_values.size(); ++i) {
		setS(S_values[i]); //assign S value in vector to S data member
		put_prices.push_back(putPrice()); //so we can use US putPrice() and push it into price vector
	}
	setS(save_S); //restore original value of S
	return put_prices;
}
