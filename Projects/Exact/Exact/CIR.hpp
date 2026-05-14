#pragma once
#include <vector>

using namespace std;

extern double kappa;
extern double theta;
extern double sig;

double priceCIR(double r, double t);
double priceVasicek(double r, double t);
vector<double> priceAffine(const vector<double>& xarr, double t, double (*affineModel)(double x, double t));
vector<vector<double> > priceAffine(const vector<double>& xarr, const vector<double>& tarr, double (*affineModel)(double x, double t));