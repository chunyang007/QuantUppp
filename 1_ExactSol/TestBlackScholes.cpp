#include "BlackScholesEuropean.hpp"
#include <iostream>

int main()
{
	// Call option using default values
	BlackScholesEuropean option1(typeCall);
	cout << "S: "; 
	double S; 
	cin >> S;
	cout << "Call Option on a stock: " << option1.Price(S) << endl;

	////////////////////////////////////////////////////////////////
	
	// call option with modified values + dividend yield
	BlackScholesEuropean option2(typeCall);
	option2.K = 70.0;
	option2.T = 0.75;
	option2.r = 0.10;
	option2.sig = 0.28;

	double q = 0.0;				// !! Dividend yield TO STOCK HOLDERS, not to options holders
								// percentage in annum, continuous compounding
	double C = 0.0, P = 0.0;	// call/put option price

	q = 0.0;
	option2.b = option2.r - q;
	C = option2.Price(S);
	cout << "Call option on a stock with DY = " << q << " : " << C << endl;

	q = 0.05;
	option2.b = option2.r - q;
	C = option2.Price(S);
	cout << "Call option on a stock with DY = " << q << " : " << C << endl;

	option2.ChangeTo(typePut);

	P = option2.Price(S);
	cout << "Put  option on a stock with DY = " << q << " : " << P << endl;

	cout << "Parity check: " << option2.PutCallParity(S, C, P) << endl;

	////////////////////////////////////////////////////////////////

	// calculate delta (sensitivity), call and put options on a future
	BlackScholesEuropean futureOption(typePut);
	futureOption.K = 100.0;
	futureOption.T = 0.5;
	futureOption.r = 0.10;
	futureOption.sig = 0.36;
	futureOption.b = 0.0;

	cout << "Delta on put  future: " << futureOption.Delta(105.0) << endl;

	futureOption.ChangeTo(typeCall);
	cout << "Delta on call future: " << futureOption.Delta(105.0) << endl;
	
	////////////////////////////////////////////////////////////////

	// calcuate price and delta
	BlackScholesEuropean stockOption(typeCall);
	stockOption.K = 60.0;
	stockOption.T = 0.75;
	stockOption.r = 0.10;
	stockOption.sig = 0.30;
	stockOption.b = stockOption.r;

	// Calculating theta of a European stock index
	BlackScholesEuropean indexOption2(typePut);
	indexOption2.K = 405.0;
	indexOption2.T = 0.0833;
	indexOption2.r = 0.07;
	indexOption2.sig = 0.20;

	double q = 0.05;		// Dividend yield, 5% annually
	indexOption2.b = indexOption2.r - q;


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
