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

private:
	CPiano * m_piano;
	// all piano samples
	std::vector<short> m_pianosamples;
	// vector contains all piano sample filename
	std::vector<CString> files;
	// how hard to press the key
	double m_power;
};

