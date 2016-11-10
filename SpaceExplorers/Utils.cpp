#include "stdafx.h"
#include "Utils.h"


std::string round2(float pValue)
{
	std::ostringstream ss;
	ss << std::fixed << std::setprecision(2) << pValue;
	return ss.str();
}

std::string round2(double pValue)
{
	std::ostringstream ss;
	ss << std::fixed << std::setprecision(2) << pValue;
	return ss.str();
}
