#pragma once

#include <string>
using namespace std;

enum OptionType 
{ 
	typeCall, 
	typePut 
};

class BlackScholesEuropean
{
private:		
	void copy(const BlackScholesEuropean& o2);

	// functions option calculations
	double CallPrice(const double S) const;
	double PutPrice(const double S) const;
	double CallDelta(const double S) const;
	double PutDelta(const double S) const;
	
	double n(double x) const; // PDF
	double N(double x) const; // CDF


public:

	double r;		// risk free interest rate
	double sig;		// volatility
	double K;		// strike price
	double T;		// maturity time, time left to expiry (years)

	/*
	Cost of carry
	b = r		Black-Scholes stock option model
	b = r - q	Merton stock option model with continuous dividend yield
	b = 0		Black futures option model
	b = r - rf	Garman and Kohlhagen currency option model, rf = 'foreign' interest rate
	*/
	double b;		

	

	OptionType optType;	// (call, put)
	string unam;	// Name of underlying asset


public:	// Public functions
	//EuropeanOption();
	BlackScholesEuropean(const BlackScholesEuropean& option2);	// Copy constructor
	BlackScholesEuropean(const OptionType& optionType);	// Constructor with option type
	virtual ~BlackScholesEuropean();	

	BlackScholesEuropean& operator = (const BlackScholesEuropean& option2);

	// Functions that calculate option price and sensitivities
	double Price(const double S) const;
	double Delta(const double S) const; // sensitivity to underlying price, "speed" of stock price
	
	double CallGamma(const double S) const; // sensitivity to Delta, "acceleration" of stock price
	double CallVega(const double S) const;  // sensitivity to volatility
	double CallTheta(const double S) const; // sensitivity to time decay
	
	void ChangeTo(const OptionType& optionType);
	bool PutCallParity(const double& S, const double& C, const double& P) const;
};
