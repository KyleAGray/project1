#pragma once
#include "AudioNode.h"
#include "Note.h"

const int NUMEFFECTCHANNELS = 1;	// The number of effects channels including one with no effect added
class CInstrument :
	public CAudioNode
{
public:
	CInstrument();
	virtual ~CInstrument();

	virtual void SetNote(CNote *note) = 0;

	double Sent(int i) { return sends[i]; }

private:
	/// List of send ammounts for each effect
	double sends[NUMEFFECTCHANNELS];	
};

