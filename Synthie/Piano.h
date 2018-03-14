#pragma once
#include "Instrument.h"
#include "PianoPlayer.h"

class CPiano :
	public CInstrument
{
public:
	CPiano();
	virtual ~CPiano();

	virtual void Start();
	virtual bool Generate();
	virtual void SetNote(CNote *note);

	CPianoPlayer *GetPlayer() { return &m_pianoPlayer; }

private:
	CPianoPlayer m_pianoPlayer;
};

