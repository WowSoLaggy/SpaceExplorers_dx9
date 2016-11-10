#include "stdafx.h"
#include "Gases.h"


namespace
{

	const std::vector<std::string> GAS_NAMES =
	{
		"Oxygen",
		"Nitrogen",
	};


	const std::vector<std::string> GAS_NAMES_SHORT =
	{
		"O2",
		"N2",
	};

}


std::string GetGasName(Gas pGas)
{
	return GAS_NAMES[static_cast<int>(pGas)];
}

std::string GetGasShortName(Gas pGas)
{
	return GAS_NAMES_SHORT[static_cast<int>(pGas)];
}
