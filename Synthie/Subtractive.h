#pragma once
#include "Instrument.h"
#include "SubtractivePlayer.h"
#include <string>
#include "SubEnvenlope.h"
#include "FilterEnvelope.h"

using namespace std;

class CSubtractive :
	public CInstrument
{
public:
	CSubtractive();
	virtual ~CSubtractive();

	virtual void Start() override;
	virtual bool Generate() override;
	virtual void SetNote(CNote *note) override;

	void SetFreq(double f) { m_subPlayer.SetFreq(f); }
	void SetAmplitude(double a) { m_subPlayer.SetAmplitude(a); }
	void SetDuration(double d) { m_duration = d * 60 / m_bpm; }
private:
	double m_duration;
	double m_time;

	//wstring waveform;
	CSubtractivePlayer m_subPlayer;
	CSubEnvenlope* m_envelope;
	CFilterEnvelope m_filterEnvelope;
};

