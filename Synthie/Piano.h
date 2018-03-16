#pragma once
#include "Instrument.h"
#include "PianoPlayer.h"
#include "AR.h"

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
	void SetDuration(double d) { m_ar.SetDuration(d); }
	void SetFreq(double f) { m_pianoPlayer.SetFreq(f); }

private:
	CPianoPlayer m_pianoPlayer;
	CAR m_ar;
	double m_time;
	double m_duration;
};

