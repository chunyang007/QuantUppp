#include <vector>
#include <cmath>
#include <iostream>
#include "ATSM.hpp"
using namespace std;

ATSM::ATSM(double kappa, double theta, double sig) : kappa(kappa), theta(theta), sig(sig)
{
	if (kappa <= 0 || theta < 0 || sig <= 0) {
		throw std::invalid_argument("Invalid parameters");
	}
}

void ATSM::setParameters(double kappa, double theta, double sig)
{
	if (kappa <= 0 || theta < 0 || sig <= 0) {
		throw std::invalid_argument("Invalid parameters");
	}
	this->kappa = kappa;
	this->theta = theta;
	this->sig = sig;
}


AffineCIR::AffineCIR(double kappa, double theta, double sig) : ATSM(kappa, theta, sig) {}

/*
* r = current short rate at time t
* t = time to maturity
* returns bond price (P)
*/
double AffineCIR::price(double r, double t) const
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


AffineVasicek::AffineVasicek(double kappa, double theta, double sig) : ATSM(kappa, theta, sig) {}

/*
* r = current short rate at time t
* t = time to maturity
* returns bond price (P)
*/
double AffineVasicek::price(double r, double t) const
{
	double B = (1.0 - exp(-kappa * t)) / kappa;
	double A = exp((theta - sig * sig / (2.0 * kappa * kappa)) * (B - t) - (sig * sig * B * B) / (4.0 * kappa));

	double P = A * exp(-B * r);
	return P;
}

