#pragma once
#include "Piano.h"
#include <vector>

class CPianoFactory
{
public:
	CPianoFactory();
	virtual ~CPianoFactory();

	void SetNote(CNote *note);
	CPiano *CreateInstrument();

	bool LoadFile(const char *filename);
private:
	std::vector<short> m_piano;
};

