#include <vector>
#include <cmath>
#include <iostream>
#include "ATSM.hpp"
using namespace std;

// dr = (a - br)dt + sig r^1/2 dW
double kappa; // speed of mean reversion
double theta; // long-term mean level
double sig;	  // volatility

/*
* // CIR zero-coupon bond
* r = current short rate at time t
* t = time to maturity
* returns bond price (P)
*/
double priceCIR(double r, double t)
{ 
	double h = sqrt(kappa * kappa + 2.0 * sig * sig);

	double tmp1 = exp(h * t) - 1.0;
	double tmp2 = kappa + h;

	double B = 2.0 * tmp1 / (tmp2 * tmp1 + 2.0 * h);

	double factor = 2.0 * h * exp(tmp2 * t / 2) / (tmp2 * tmp1 + 2.0 * h);
	double A = pow(factor, 2.0 * kappa * theta / (sig * sig));
	double P = A * exp(-B * r);

	return P;
}

/*
* // Vasicek zero-coupon bond
* r = current short rate at time t
* t = time to maturity
* returns bond price (P)
*/
double priceVasicek(double r, double t)
{	
	double B = (1.0 - exp(-kappa * t)) / kappa;
	double A = exp((theta - sig * sig / (2.0 * kappa * kappa)) * (B - t) - (sig * sig * B * B) / (4.0 * kappa));
	
	double P = A * exp(-B * r);
	return P;
}

vector<double> priceAffine(const vector<double>& xarr, double t, double (*affineModel)(double x, double t))
{ // priceCIR for a variation of x values, returns an array of bond prices
	// function pointer to replace polymorphism, can feed in any affine model, eg: CIR, Vasicek, etc.
	vector<double> result(xarr.size());
	for (size_t n = 0; n < result.size(); ++n)
	{
		result[n] = affineModel(xarr[n], t);
	}

	return result;
}

vector<vector<double> > priceAffine(const vector<double>& xarr, const vector<double>& tarr, double (*affineModel)(double x, double t))
{	// priceCIR for a variation of x and t values, returns a 2d matrix of bond prices
	
	vector<vector<double>> result(xarr.size(), vector<double>(tarr.size()));
	for (std::size_t j = 0; j < xarr.size(); ++j)
	{
		result[j] = std::vector<double>(tarr.size());
	}

	for (std::size_t n = 0; n < tarr.size(); ++n)
	{
		for (std::size_t i = 0; i < xarr.size(); ++i)
		{
			result[i][n] = affineModel(xarr[i], tarr[n]);

		}
	}

	return result;
}

//int main()
//{
//	theta = 0.0025;
//	sig = sqrt(0.01);
//	kappa = 0.05;
//	double T = 0.5;
//	double P = priceCIR(0.49, T);
//	cout << "Bond price: " << P << endl;
//	return 0;
//}