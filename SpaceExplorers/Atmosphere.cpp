#include "stdafx.h"
#include "Atmosphere.h"


Atmosphere::Atmosphere()
{
	t = 273; // 273 K° = 0 C°
	v = 1;
	m_gases.resize((int)Gas::SIZE, 0);
}


double Atmosphere::GetGasMass(Gas pGas)
{
	return m_gases[static_cast<int>(pGas)];
}

double Atmosphere::GetGasPercentage(Gas pGas)
{
	auto lol = m_gases[static_cast<int>(pGas)] / std::accumulate(m_gases.begin(), m_gases.end(), (double)0);
	return 0;
}

double Atmosphere::P()
{
	double pTotal = 0;
	for (int i = 0; i < static_cast<int>(Gas::SIZE); ++i)
		pTotal += m_gases[i] * R * t / v;
	return pTotal;
}
