#pragma once
#include "AudioNode.h"
#include "Note.h"

const int NUMEFFECTCHANNELS = 5;	// The number of effects channels including one with no effect added
class CInstrument :
	public CAudioNode
{
public:
	CInstrument();
	virtual ~CInstrument();

	virtual void SetNote(CNote *note) = 0;

	double Send(int i) { return sends[i]; }

	void SetSend(int i, double ammount) { sends[i] = ammount; }
private:
	/// List of send ammounts for each effect
	double sends[NUMEFFECTCHANNELS] = { 1,0,0,0,0};
};

