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

	std::vector<string> GetFiles();
	bool LoadFile(const char *filename);

private:
	std::vector<short> m_piano;
};

