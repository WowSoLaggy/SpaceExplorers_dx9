#pragma once

#ifndef INC_ATMOSPHERE_H
#define INC_ATMOSPHERE_H


#include "ErrCodes.h"


enum class Gas
{
	None = 0,
	Oxygen,
	Nitrogen,

	SIZE
};


class Atmosphere
{
public:

	Atmosphere();

	double& T() { return t; }
	const double& T() const { return t; }

	double& V() { return v; }
	const double& V() const { return v; }

	double GetGasMass(Gas pGas);
	double GetGasPercentage(Gas pGas);

private:

	double t;						///< K°
	double v;						///< m^3
	std::vector<double> m_gases;	///

};


#endif // INC_ATMOSPHERE_H
