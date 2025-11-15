//Jordan Liu - definition of EuroOption derived class of BlackScholes

#include "EuroOption.h"


EuroOption::EuroOption() : BlackScholes() {} //default constructor (automatically sets batch 1 values)
EuroOption::EuroOption(double S1, double K1, double T1, double r1, double sig1, double b1) : BlackScholes(S1, K1, T1, r1, sig1, b1) {} //constructor with 6 arguments (when b=/= r)
EuroOption::EuroOption(double S1, double K1, double T1, double r1, double sig1) : BlackScholes(S1, K1, T1, r1, sig1, r1) {} //constructor with 5 arguments (assumes b=r)
EuroOption::~EuroOption() {} //destructor with override


double EuroOption::callPrice() const { //get call price, with exp being 'e to the power of'
	double S = getS(), K = getK(), T = getT(), r = getR(), b = getB();
	return S * exp((b - r) * T) * N(d1()) - K * exp(-r * T) * N(d2());
}

double EuroOption::putPrice() const { //get put price
	double S = getS(), K = getK(), T = getT(), r = getR(), b = getB();
	return K * exp(-r * T) * N(-d2()) - S * exp((b - r) * T) * N(-d1());
}

double EuroOption::callDelta() const {//get deltas and gamma (necessary so EuroOption doesn't become abstract)
	double b = getB(), r = getR(), T = getT();
	return exp((b - r) * T) * N(d1());
}
double EuroOption::putDelta() const {
	double b = getB(), r = getR(), T = getT();
	return exp((b - r) * T) * (N(d1()) - 1);
}

double EuroOption::gamma() const {
	double b = getB(), r = getR(), T = getT(), S = getS(), sig = getSig();
	return (n(d1()) * exp((b - r) * T)) / (S * sig * sqrt(T));
}

//put-call parity formula is: call + K*exp(-r*T) = put + S
double EuroOption::callPrice(double put) const { //get call price from put price using put-call parity
	double S = getS(), K = getK(), r = getR(), T = getT();
	return put + S - K * exp(-r * T);
}

double EuroOption::putPrice(double call) const { //get put price from call price using put-call parity
	double K = getK(), r = getR(), T = getT(), S = getS();
	return call + K * exp(-r * T) - S;
}

double EuroOption::verifyParity(double call, double put) const { //verify wheter given call and put prices satisfy put-call parity 
	double K = getK(), r = getR(), T = getT(), S = getS();
	double left_side = call + K * exp(-r * T);
	double right_side = put + S;
	return fabs(left_side - right_side) < 0.00001;
}

vector<double> EuroOption::callPrice(const vector<double>& S_values) { //get call prices for a mesh array of S values
	vector<double> call_prices; //create vector of call prices
	call_prices.reserve(S_values.size()); //reserve the same size as the number of S values
	const double save_S = getS(); //save the original value of S data member

	for (int i = 0; i < S_values.size(); ++i) {
		setS(S_values[i]); //assign S value in vector to S data member
		call_prices.push_back(callPrice()); //so we can use callPrice() and push it into price vector
	}
	setS(save_S); //restore original value of S
	return call_prices;
}

vector<double> EuroOption::putPrice(const vector<double>& S_values) { //get put prices for a mesh array of S values
	vector<double> put_prices; //create vector of put prices
	put_prices.reserve(S_values.size()); //reserve the same size as the number of S values
	double save_S = getS(); //save the original value of S data member

	for (int i = 0; i < S_values.size(); ++i) {
		setS(S_values[i]); //assign S value in vector to S data member
		put_prices.push_back(putPrice()); //so we can use putPrice() and push it into price vector
	}
	setS(save_S); //restore original value of S
	return put_prices;
}