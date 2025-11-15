//Jordan Liu - definition of Greek derived class of EuroOption (for getting option sensitivities)

#include "Greek.h"


Greek::Greek() : BlackScholes(105, 100, 0.5, 0.1, 0.36, 0) {} //default constructor, automatically sets values for batch 5 
Greek::Greek(double S1, double K1, double T1, double r1, double sig1, double b1) : BlackScholes(S1, K1, T1, r1, sig1, b1) {} //constructor with all 6 arguments
Greek::Greek(double S1, double K1, double T1, double r1, double sig1) : BlackScholes(S1, K1, T1, r1, sig1, r1) {} //constructor with 5 arguments (assumes b = r)
Greek::~Greek() {} //destructor

double Greek::callPrice() const { //returns Euro call and put prices
	double S = getS(), K = getK(), T = getT(), r = getR(), b = getB();
	return S * exp((b - r) * T) * N(d1()) - K * exp(-r * T) * N(d2());
}
double Greek::putPrice() const { //these are needed so Greek doesn't become an abstract class
	double S = getS(), K = getK(), T = getT(), r = getR(), b = getB();
	return K * exp(-r * T) * N(-d2()) - S * exp((b - r) * T) * N(-d1());
}

double Greek::callDelta() const { //calculate Delta - option value change with the asset price
	double b = getB(), r = getR(), T = getT();
	return exp((b - r) * T) * N(d1());
}

double Greek::putDelta() const { //it's almost the same as callDelta but with a -1 at the end
	double b = getB(), r = getR(), T = getT();
	return exp((b - r) * T) * (N(d1()) - 1);
}

double Greek::gamma() const { //gamma - Delta's sensitivity to asset price changes, same for calls and puts
	double b = getB(), r = getR(), T = getT(), S = getS(), sig = getSig();
	return (n(d1()) * exp((b - r) * T)) / (S * sig * sqrt(T));
}

double Greek::vega() const { //vega - sensitivity to implied volatility, same for calls and puts
	double S = getS(), T = getT(), b = getB(), r = getR();
	return S * sqrt(T) * exp((b - r) * T) * n(d1());
}

double Greek::callTheta() const { //theta - the effect time will have on an option’s value
	//first term = -(S*sig*exp((b-r)*T)*n(d1()))/(2*sqrt(T))
	//second term = -(b-r)*S*exp((b-r)*T)*N(d1())
	//third term = - r*K*exp(-r*T)*N(d2())
	double S = getS(), K = getK(), T = getT(), r = getR(), sig = getSig(), b = getB();
	return -(S * sig * exp((b - r) * T) * n(d1())) / (2 * sqrt(T)) - (b - r) * S * exp((b - r) * T) * N(d1()) - r * K * exp(-r * T) * N(d2());
}

double Greek::putTheta() const { //very similar to callTheta except some minus signs are plus signs or vice versa
	//first term = -(S*sig*exp((b-r)*T)*n(d1()))/(2*sqrt(T))
	//second term = + (b-r)*S*exp((b-r)*T)*N(-d1())
	//third term = + r*K*exp(-r*T)*N(-d2())
	double S = getS(), K = getK(), T = getT(), r = getR(), sig = getSig(), b = getB();
	return -(S * sig * exp((b - r) * T) * n(d1())) / (2 * sqrt(T)) + (b - r) * S * exp((b - r) * T) * N(-d1()) + r * K * exp(-r * T) * N(-d2());
}

//functions that accept a vector of S values argument and return a vector of deltas
//very similar to the vector version of callPrice, except we use callDelta() instead of callPrice()
vector<double> Greek::callDelta(const vector<double>& S_values) {
	vector<double> call_prices; //create vector of call prices
	call_prices.reserve(S_values.size()); //reserve the same size as the number of S values
	const double save_S = getS(); //save the original value of S data member

	for (int i = 0; i < S_values.size(); ++i) {
		setS(S_values[i]); //assign S value in vector to S data member
		call_prices.push_back(callDelta()); //so we can use callPrice() and push it into price vector
	}
	setS(save_S); //restore original value of S
	return call_prices;
}

vector<double> Greek::putDelta(const vector<double>& S_values) {
	vector<double> put_prices; //create vector of put prices
	put_prices.reserve(S_values.size()); //reserve the same size as the number of S values
	const double save_S = getS(); //save the original value of S data member

	for (int i = 0; i < S_values.size(); ++i) {
		setS(S_values[i]); //assign S value in vector to S data member
		put_prices.push_back(putDelta()); //so we can use putPrice() and push it into price vector
	}
	setS(save_S); //restore original value of S
	return put_prices;
}

double Greek::callDelta(double h) { //use divided difference (DD) to get call delta
	const double save_S = getS(); //save original value of S
	setS(save_S + h); //assign S+h to S data member
	double V_plus = callPrice(); //get V(S+h) i.e. solution with S+h
	setS(save_S - h); //assign S-h to S data member
	double V_minus = callPrice(); //get V(S-h)
	setS(save_S); //restore original value of S
	return (V_plus - V_minus) / (2 * h); //get divided difference (DD) delta
}

double Greek::putDelta(double h) { //same as callDelta but we use putPrice instead
	const double save_S = getS(); //save original value of S
	setS(save_S + h); //assign S+h to S data member
	double V_plus = putPrice(); //get V(S+h) i.e. solution with S+h
	setS(save_S - h); //assign S-h to S data member
	double V_minus = putPrice(); //get V(S-h)
	setS(save_S); //restore original value of S
	return (V_plus - V_minus) / (2 * h); //get divided difference (DD) delta
}

double Greek::gamma(double h) { //same for call and put
	const double save_S = getS(); //save original value of S
	double V = callPrice(); //get V(S)
	setS(save_S + h); //assign S+h to S data member
	double V_plus = callPrice(); //get V(S+h) i.e. solution with S+h
	setS(save_S - h); //assign S-h to S data member
	double V_minus = callPrice(); //get V(S-h)
	setS(save_S); //restore original value of S
	return (V_plus - 2 * V + V_minus) / (h * h); //get divided difference (DD) gamma
}

//DD version of taking S vector and returning delta vector
//code is basically the same as non-DD version but callPrice accepts an 'h' now
vector<double> Greek::callDelta(const vector<double>& S_values, double h) {
	vector<double> call_prices; //create vector of call prices
	call_prices.reserve(S_values.size()); //reserve the same size as the number of S values
	const double save_S = getS(); //save the original value of S data member

	for (int i = 0; i < S_values.size(); ++i) {
		setS(S_values[i]); //assign S value in vector to S data member
		call_prices.push_back(callDelta(h)); //so we can use DD callPrice() and push it into price vector
	}
	setS(save_S); //restore original value of S
	return call_prices;
}

vector<double> Greek::putDelta(const vector<double>& S_values, double h) {
	vector<double> put_prices; //create vector of put prices
	put_prices.reserve(S_values.size()); //reserve the same size as the number of S values
	double save_S = getS(); //save the original value of S data member

	for (int i = 0; i < S_values.size(); ++i) {
		setS(S_values[i]); //assign S value in vector to S data member
		put_prices.push_back(putDelta(h)); //so we can use DD putPrice() and push it into price vector
	}
	setS(save_S); //restore original value of S
	return put_prices;
}

vector<double> Greek::gamma(const vector<double>& S_values, double h) {
	vector<double> gammas; //create vector of gammas
	gammas.reserve(S_values.size()); //reserve the same size as the number of S values
	double save_S = getS(); //save the original value of S data member

	for (int i = 0; i < S_values.size(); ++i) {
		setS(S_values[i]); //assign S value in vector to S data member
		gammas.push_back(gamma(h)); //so we can use DD gamma() and push it into gamma vector
	}
	setS(save_S); //restore original value of S
	return gammas;
}

vector<double> Greek::gamma(const vector<double>& S_values) {
	vector<double> gammas; //create vector of gammas
	gammas.reserve(S_values.size()); //reserve the same size as the number of S values
	double save_S = getS(); //save the original value of S data member

	for (int i = 0; i < S_values.size(); ++i) {
		setS(S_values[i]); //assign S value in vector to S data member
		gammas.push_back(gamma()); //so we can use DD gamma() and push it into gamma vector
	}
	setS(save_S); //restore original value of S
	return gammas;
}