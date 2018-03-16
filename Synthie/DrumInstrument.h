#pragma once
#include "instrument.h"
#include "Drums.h"
#include "AR.h"
#include "DrumPlayer.h"

class CDrumInstrument :
	public CInstrument
{
public:
	CDrumInstrument(void);
	~CDrumInstrument(void);

	virtual void Start();
	virtual bool Generate();
	virtual void SetNote(CNote *note);
	double GetDuration() { return m_duration; }

	void SetDuration(double d) { m_duration = d; }
	void SetFreq(double f) { m_sines.SetFreq(f); }
	void SetKit(int i) { m_sines.SetKit(i); }

	CDrumPlayer *GetPlayer() { return &m_drumPlayer; }

private:
	//CAR         m_ar;
	CDrumPlayer m_drumPlayer;
	double		m_time;
	CDrums		m_sines;
	double		m_duration;
};
