#pragma once
#include <vector>

using namespace std;

class ATSM // affine term structure model
{
	/*
	* virtual destructor for abstract/interface class is a must to ensure correct 
	* destructor is called based on the actual object type, not the pointer type. 
	* If the destructor is not virtual, 
	* deleting an object through a pointer to the base class 
	* will result in undefined behavior as there is no implementation of 
	* destructor of the derived class.
	*/

public:	
	ATSM(double kappa = 0.0, double theta = 0.1, double sig = 0.0);
	virtual ~ATSM() = default;
	virtual double price(const double& r, const double& t) const = 0; // pure virtual function by adding "=0", need to be implemented by derived classes
	vector<double> price(const vector<double>& xarr, const double& t) const;
	vector<vector<double> > price(const vector<double>& xarr, const vector<double>& tarr) const;

	void setParameters(const double kappa, const double theta, const double sig);
	double getKappa() const { return kappa; }
	double getTheta() const { return theta; }
	double getSig() const { return sig; }

protected:
	double kappa; // speed of mean reversion
	double theta; // long-term mean level
	double sig;	  // volatility
};

class AffineCIR : public ATSM
{
public:
	AffineCIR(double kappa = 0.0, double theta = 0.1, double sig = 0.0);
	~AffineCIR() override = default;
	double price(const double& r, const double& t) const override;
};

class AffineVasicek : public ATSM
{
public:
	AffineVasicek(double kappa = 0.0, double theta = 0.1, double sig = 0.0);
	~AffineVasicek() override = default;
	double price(const double& r, const double& t) const override;
};