#pragma once

#ifndef INC_ATMOSPHERE_H
#define INC_ATMOSPHERE_H


#include "ErrCodes.h"
#include "Gases.h"


class Atmosphere
{
public:

	Atmosphere();

	double& T() { return t; }
	const double& T() const { return t; }

	double& V() { return v; }
	const double& V() const { return v; }

	double P();

	double GetGasMass(Gas pGas);
	double GetGasPercentage(Gas pGas);

private:

	const double R = 8.3144598;

	double t;						///< K°
	double v;						///< m^3
	std::vector<double> m_gases;	///

};


#endif // INC_ATMOSPHERE_H
