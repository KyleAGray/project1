#pragma once

#include "ToneInstrument.h"
class CToneInstrumentFactory
{
public:
	CToneInstrumentFactory();
	virtual ~CToneInstrumentFactory();

	void SetDry(double d) { m_dry = d; }
	void SetGateing(double g) { m_gateing = g; }

	CToneInstrument *CreateInstrument();

private:
	double m_dry = 1;
	double m_gateing = 0;
};

