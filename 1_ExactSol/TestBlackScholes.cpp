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

	// !! Dividend yield TO STOCK HOLDERS, not to options holders
	// percentage in annum, continuous compounding
	double q = 0.0;

	////////////////////////////////////////////////////////////////
	
	// call option with modified values + dividend yield
	BlackScholesEuropean option2(typeCall);
	option2.K = 70.0;
	option2.T = 0.75;
	option2.r = 0.10;
	option2.sig = 0.28;
	
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
	futureOption.b = 0.0; // future option, cost of carry = 0

	cout << "Delta on put  future: " << futureOption.Delta(S) << endl;

	futureOption.ChangeTo(typeCall);
	cout << "Delta on call future: " << futureOption.Delta(S) << endl;
	
	////////////////////////////////////////////////////////////////

	// Calculating theta
	BlackScholesEuropean stockOption(typeCall);
	stockOption.K = 60.0;
	stockOption.T = 0.75;
	stockOption.r = 0.10;
	stockOption.sig = 0.30;
	
	q = 0.05;		// Dividend yield, 5% annually
	stockOption.b = stockOption.r - q;
	
	cout << "Gamma on call stock option: " << stockOption.CallGamma(S) << endl;
	cout << "Vega on call stock option: " << stockOption.CallVega(S) << endl;
	cout << "Theta on call stock option: " << stockOption.CallTheta(S) << endl;

	return 0;
}
