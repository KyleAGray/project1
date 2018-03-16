#pragma once
#include "Piano.h"
#include <vector>
#include <string>

using namespace std;

class CPianoFactory
{
public:
	CPianoFactory();
	virtual ~CPianoFactory();

	void SetNote(CNote *note);
	CPiano *CreateInstrument();

	void GetFiles();
	bool LoadFile();
	void SetDry(double d) { m_dry = d; }
	void SetGateing(double g) { m_gateing = g; }
private:
	// all piano samples
	std::vector<short> m_piano;
	// vector contains all piano sample filename
	std::vector<CString> files;

	double m_dry = 1;
	double m_gateing = 0;
	// effect 2
	// effect 3
	// effect 4
};

