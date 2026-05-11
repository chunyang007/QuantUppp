#include "BlackScholesEuropean.hpp"
#include <iostream>

/* 
	b = r		Black-Scholes stock option model
	b = r - q	Merton stock option model with continuous dividend yield
	b = 0		Black futures option model
	b = r - rf	Garman and Kohlhagen currency option model, rf = 'foreign' interest rate
*/

int main()
{
	// Call option on a stock (b = r by default)
	BlackScholesEuropean callOption(typeCall);
	cout << "S: "; 
	double S; 
	cin >> S;
	cout << "Option on a stock: " << callOption.Price(S) << endl;

	// Option on a stock index
	BlackScholesEuropean indexOption(typeCall);
	indexOption.K = 70.0;
	indexOption.T = 0.75;
	indexOption.r = 0.10;
	indexOption.sig = 0.28;

	double q = 0.0;		// Dividend yield
	indexOption.b = indexOption.r - q;

	double C = indexOption.Price(S);
	cout << (indexOption.optType == typeCall ? "Call" : "Put") << " option on an index: " << C << endl;

	indexOption.ChangeTo(typePut);

	double P = indexOption.Price(S);
	cout << (indexOption.optType == typeCall ? "Call" : "Put") << " option on an index: " << P << endl;

	indexOption.PutCallParity(S, C, P);

	// Options on a future
	BlackScholesEuropean futureOption(typePut);
	futureOption.K = 20.0;
	futureOption.T = 0.75;
	futureOption.r = 0.10;
	futureOption.sig = 0.28;

	futureOption.b = 0.0;

	cout << "Put option on a future: " << futureOption.Price(20.0) << endl;

	// Now change over to a call on the option
	futureOption.ChangeTo(typeCall);
	cout << "Call option on a future: " << futureOption.Price(20.0) << endl;


	// Call option on currency
	BlackScholesEuropean currencyOption(typeCall);
	currencyOption.K = 1.60;
	currencyOption.T = 0.5;
	currencyOption.r = 0.06;
	currencyOption.sig = 0.12;

	double rf = 0.08;		// risk-free rate of foreign currency
	currencyOption.b = currencyOption.r - rf;

	cout << "Call option on a currency: " << currencyOption.Price(1.56) << endl;

	// Call and put options on a future: Delta and Elasticity
	BlackScholesEuropean futureOption2(typePut);
	futureOption2.K = 100.0;
	futureOption2.T = 0.5;
	futureOption2.r = 0.10;
	futureOption2.sig = 0.36;

	futureOption2.b = 0.0;

	cout << "Delta on a put future: " << futureOption2.Delta(105.0) << endl;

	// Now change over to a call on the option
	futureOption2.ChangeTo(typeCall);
	cout << "Delta on a call future: " << futureOption2.Delta(105.0) << endl;
	
	// Some more data for testing; Calcuate price and delta a
	BlackScholesEuropean stockOption(typeCall);
	stockOption.K = 60.0;
	stockOption.T = 0.75;
	stockOption.r = 0.10;
	stockOption.sig = 0.30;

	stockOption.b = stockOption.r;


	// Calculating theta of a European stock index
	BlackScholesEuropean indexOption2(typePut);
	indexOption2.K = 405.0;
	indexOption2.T = 0.0833;	// One month expiration
	indexOption2.r = 0.07;
	indexOption2.sig = 0.20;

	double divYield = 0.05;		// Dividend yield, 5% per annum
	indexOption2.b = indexOption2.r - divYield;


	// Stock Option: Rho
	BlackScholesEuropean stockOption2(typeCall);
	stockOption2.K = 75.0;
	stockOption2.T = 1.0;
	stockOption2.r = 0.09;
	stockOption2.sig = 0.19;

	stockOption2.b = stockOption2.r;


	// Calculating Cost of Carry of a European stock index
	BlackScholesEuropean indexOption3(typePut);
	indexOption3.K = 490.0;
	indexOption3.T = 0.222225;
	indexOption3.r = 0.08;
	indexOption3.sig = 0.15;

	double divYield3 = 0.05;		// Dividend yield, 5% per annum
	indexOption3.b = indexOption3.r - divYield3 ;
	/*
	*/
	return 0;
}
