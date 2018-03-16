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

private:
	vector<vector<short>> m_drum;
	vector<short> v;
	int kit;
	double filt;
};

