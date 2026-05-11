#include "BlackScholesEuropean.hpp"
#include <cmath>
#include <iostream>
#include <numbers>

using namespace std;

BlackScholesEuropean::BlackScholesEuropean(const OptionType& optionType) : optType(optionType)
{
	//  default values
	r	= 0.05;		// risk-free interest rate
	sig = 0.2;		// volatility
	K	= 110.0;	// strike price
	T	= 0.5;		// time left to expiry
	b	= r;		// Black and Scholes stock option model (1973)
}

BlackScholesEuropean::~BlackScholesEuropean()
{
}

BlackScholesEuropean::BlackScholesEuropean(const BlackScholesEuropean& o2)
{ // Copy constructor
	copy(o2);
}

BlackScholesEuropean& BlackScholesEuropean::operator = (const BlackScholesEuropean& option2)
{ // copy assignment operator
	if (this == &option2) return *this;
	copy(option2);
	return *this;
}

void BlackScholesEuropean::copy(const BlackScholesEuropean& o2)
{
	r = o2.r;
	sig = o2.sig;
	K = o2.K;
	T = o2.T;
	b = o2.b;
	optType = o2.optType;
}

double BlackScholesEuropean::n(double x) const
{  
	// normal distrubution function (probability density function)	N'(x) = n(x)
	// assume mean = 0 and standard deviation = 1
	double sigma = 1.0;
	double mu = 0.0;
	return 1.0 / (sigma * sqrt(2.0 * numbers::pi)) * exp(-(x-mu) * (x-mu) * 0.5);
}

double BlackScholesEuropean::N(double x) const
{ // cumulative normal distribution function CDF (area under normal distribution from -inf to x)
	
	/*
	// 3 terms approximation for CDF
	double a1 = 0.4361836;
	double a2 = -0.1201676;
	double a3 = 0.9372980;
	double gamma = 0.33267;
	double k = 1.0 / (1.0 + (gamma * abs(x)));
	
	double cdf = 1.0 - n(abs(x))* (a1*k + (a2*k*k) + (a3*k*k*k));

	if (x >= 0.0) return cdf;
	else return 1.0 - cdf;
	*/

	// using std::erf function to calculate CDF
	return 0.5 * (1.0 + std::erf(x / std::sqrt(2.0)));

}


double BlackScholesEuropean::CallPrice(const double S) const
{
	double denom = sig * sqrt(T);
	double d1 = ( log(S/K) + (b + (sig*sig)/2 ) * T ) / denom;
	double d2 = d1 - denom;

	return (S * exp((b-r)*T) * N(d1)) - (K * exp(-r * T) * N(d2));
}

double BlackScholesEuropean::PutPrice(const double S) const
{
	double denom = sig * sqrt(T);
	double d1 = ( log(S/K) + (b + (sig*sig)/2 ) * T ) / denom;
	double d2 = d1 - denom;

	return (K * exp(-r * T)* N(-d2)) - (S * exp((b-r)*T) * N(-d1));
}

double BlackScholesEuropean::CallDelta(const double S) const
{
	double tmp = sig * sqrt(T);
	double d1 = ( log(S/K) + (b + (sig*sig)/2 ) * T )/ tmp;

	return exp((b-r)*T) * N(d1);
}

double BlackScholesEuropean::PutDelta(const double S) const
{
	double tmp = sig * sqrt(T);
	double d1 = ( log(S/K) + (b + (sig*sig)/2 ) * T )/ tmp;

	return -exp((b-r)*T) * N(-d1);
}

double BlackScholesEuropean::Price(const double S) const
{
	if (optType == typeCall)
		return CallPrice(S);
	else // typePut
		return PutPrice(S);
}	

double BlackScholesEuropean::Delta(const double S) const 
{
	if (optType == typeCall)
		return CallDelta(S);
	else // typePut
		return PutDelta(S);

}

void BlackScholesEuropean::ChangeTo(const OptionType& optionType)
{
	optType = optionType;
}

bool BlackScholesEuropean::PutCallParity(const double& S, const double& C, const double& P) const
{
	double Cpart = C + K * exp(-r * T);
	double Ppart = S * exp((b - r) * T) + P;
	
	// floating-point comparison
	double tolerance = 1e-7;
	bool is_equal = abs(Cpart - Ppart) < tolerance;

	if (!is_equal) {
		cout << "Parity Violation! Diff: " << abs(Cpart - Ppart) << endl;
	}

	return is_equal;
}