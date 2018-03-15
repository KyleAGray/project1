#include "stdafx.h"
#include "Instrument.h"


CInstrument::CInstrument()
{
	sends[0] = 1;	// Normal
	sends[1] = 0;	// Grating (gating)
}


CInstrument::~CInstrument()
{
}
