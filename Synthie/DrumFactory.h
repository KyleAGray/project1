#pragma once
#include "DrumInstrument.h"
#include <vector>
using namespace std;

class CDrumFactory
{
public:
	CDrumFactory();
	virtual ~CDrumFactory();

	void SetNote(CNote *note);
	CDrumInstrument *CreateInstrument();

	bool LoadFile(const char *filename, int j);

	void SetDry(double d) { m_dry = d; }
	void SetGateing(double g) { m_gateing = g; }

private:
	vector<vector<short>> m_drum;
	vector<short> v;
	int kit;

	double m_dry = 1;
	double m_gateing = 0;

	
};

