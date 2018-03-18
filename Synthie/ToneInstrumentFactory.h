#pragma once

#include "ToneInstrument.h"
class CToneInstrumentFactory
{
public:
	CToneInstrumentFactory();
	virtual ~CToneInstrumentFactory();

	void SetDry(double d) { m_dry = d; }
	void SetGateing(double g) { m_gateing = g; }
	void SetCompression(double c) { m_compression = c; }
	void SetReverb(double r) { m_reverb = r; }


	CToneInstrument *CreateInstrument();

private:
	double m_dry = 1;
	double m_gateing = 0;
	double m_compression = 0;
	double m_reverb = 0;
};

