#include "ATSM.hpp"

#include <vector>
#include <iostream>
using namespace std;

int main()
{
	theta = 0.0025;
	sig = 0.1;
	kappa = 0.05;

	double T = 0.5;

	double d = priceCIR(0.49, T);
	cout << "Bond price: " << d << endl;

	return 0;
}