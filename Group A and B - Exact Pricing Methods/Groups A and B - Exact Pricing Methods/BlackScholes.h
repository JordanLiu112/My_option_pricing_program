///Jordan Liu - declaration of the BlackScholes base class

#ifndef BLACK_SCHOLES_H
#define BLACK_SCHOLES_H //prevent redefinition errors

#include <cmath>
#include <boost/math/distributions/normal.hpp> //need it for N(x) function
#include <vector>
#include <sstream>
using namespace std;

class BlackScholes {
private:
	double S; //asset price
	double K; //strike price
	double T; //exercise (maturity) date
	double r; //risk-free interest rate
	double sig; //constant volatility
	double b; //cost of carry (b = r for Black-Scholes stock option model)

public:

	BlackScholes(); //default constructor 
	BlackScholes(double S1, double K1, double T1, double r1, double sig1, double b1); //constructor with six arguments
	virtual ~BlackScholes(); // virtual destructor

	//getter functions
	double getS() const { return S; } //asset price 
	double getK() const { return K; } //strike price
	double getT() const { return T; } //exercise (maturity) date
	double getR() const { return r; } //risk-free interest rate
	double getSig() const { return sig; } //constant volatility
	double getB() const { return b; } //cost of carry (b = r for Black-Scholes stock option model)

	//setter functions
	void setS(double S1) { S = S1; } //asset price
	void setK(double K1) { K = K1; } //strike price
	void setT(double T1) { T = T1; } //exercise (maturity) date
	void setR(double r1) { r = r1; } //risk-free interest rate
	void setSig(double sig1) { sig = sig1; } //constant volatility
	void setB(double b1) { b = b1; } //cost of carry (b = r for Black-Scholes stock option model)
	//the setters and getters are necessary so we can access the data members of a BlackScholes class object input in the matrix pricer function

	//line to create a bunch of variables and assign the values of the data members to them - convenient for making formulae
	//double S = getS(), K = getK(), T = getT(), r = getR(), sig = getSig(), b = getB(); 
	
	double d1() const; //calculate d1
	double d2() const; //calculate d2
	double N(double x) const; //standard cumulative Normal distribution
	double n(double x) const; //standard Normal pdf for option sensitivities calculations

	double y1() const; //calculate y1, y2 for US perpetual options
	double y2() const;

	void checkParam(const string& name, double value); //for checking the string in the matrix input and assigning the value to the right parameter

	virtual double callPrice() const = 0; //get Euro call and put prices
	virtual double putPrice() const = 0; //pure virtual functions (this is so we we can call them in the matrix pricer)

	virtual double callDelta() const = 0; //get Euro call and put deltas
	virtual double putDelta() const = 0; //pure virtual functions
	virtual double gamma() const = 0; 

};

#endif