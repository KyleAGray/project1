#pragma once
#include "Subtractive.h"
class CSubtractiveFactory
{
public:
	CSubtractiveFactory();
	virtual ~CSubtractiveFactory();

	void SetDry(double d) { m_dry = d; }
	void SetGateing(double g) { m_gateing = g; }
	void SetCompression(double c) { m_compression = c; }
	void SetChorus(double r) { m_chorus = r; }
	void SetFlange(double r) { m_flange = r; }


	CSubtractive *CreateInstrument();

private:
	double m_dry = 1;
	double m_gateing = 0;
	double m_compression = 0;
	double m_chorus = 0;
	double m_flange = 0;
};

