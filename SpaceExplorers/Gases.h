#pragma once

#ifndef INC_GASES_H
#define INC_GASES_H


enum class Gas
{
	Oxygen,
	Nitrogen,

	SIZE,
};


std::string GetGasName(Gas pGas);
std::string GetGasShortName(Gas pGas);


#endif // INC_GASES_H
