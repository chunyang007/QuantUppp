#include <vector>
#include <cmath>
#include <iostream>
#include "CIR.hpp"
using namespace std;


// dr = (a - br)dt + sig r^1/2 dW
double kappa; // speed of mean reversion
double theta; // long-term mean level
double sig;	  // volatility

/*
r = current short rate at time t
t = time to maturity

returns bond price (P)
*/
double priceCIR(double r, double t)
{ // CIR zero-coupon bond
	double h = sqrt(kappa * kappa + 2.0 * sig * sig);

	double tmp1 = exp(h * t) - 1.0;
	double tmp2 = kappa + h;

	double B = 2.0 * tmp1 / (tmp2 * tmp1 + 2.0 * h);

	double factor = 2.0 * h * exp(tmp2 * t / 2) / (tmp2 * tmp1 + 2.0 * h);
	double A = pow(factor, 2.0 * kappa * theta / (sig * sig));
	double P = A * exp(-B * r);

	return P;
}

int main()
{
	theta = 0.0025;
	sig = sqrt(0.01);
	kappa = 0.05;
	double T = 0.5;
	double P = priceCIR(0.49, T);
	cout << "Bond price: " << P << endl;
	return 0;
}