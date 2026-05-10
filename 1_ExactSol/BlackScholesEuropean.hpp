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

	double r;		// Risk free interest rate
	double sig;		// Volatility
	double K;		// Strike price
	double T;		// Maturity time in years
	double b;		// Cost of carry

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
	double Delta(const double S) const;

	void ChangeTo(const OptionType& optionType);
};
