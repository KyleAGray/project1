#pragma once
#include "Instrument.h"
#include "CSineWaveHarmonics.h"
#include "AR.h"
#include "AudioNode.h"
#include "string.h"

class CAdditive :
	public CInstrument
{
public:
	CAdditive();
	virtual ~CAdditive();
public:
	virtual void Start();
	virtual bool Generate();

	void SetNote(CNote * note);
	void SetSource(CAudioNode *source) { m_audio = source; }
	void SetFreq(double f) { m_sinewave.SetFreq(f); }
	void SetAmplitude0(double a) { m_sinewave.SetAmplitude0(a); }
	void SetAmplitude1(double a) { m_sinewave.SetAmplitude1(a); }
	void SetAmplitude2(double a) { m_sinewave.SetAmplitude2(a); }
	void SetAmplitude3(double a) { m_sinewave.SetAmplitude3(a); }
	void SetAmplitude4(double a) { m_sinewave.SetAmplitude4(a); }
	void SetAmplitude5(double a) { m_sinewave.SetAmplitude5(a); }
	void SetAmplitude6(double a) { m_sinewave.SetAmplitude6(a); }
	void SetAmplitude7(double a) { m_sinewave.SetAmplitude7(a); }
	void SetVibrato(double v) { m_sinewave.SetVibrato(v); }
	void SetVibratoChange(double v) { m_sinewave.SetVibratoChange(v); }
	void SetDuration(double d);
private:
	CSineWaveHarmonics   m_sinewave;
	double m_duration;
	double m_time;
	CAR m_ar;
	double m_phase;
	CAudioNode *m_audio;
	double m_amp[8];
	std::string val;
	double vibrato;
	double vibrato_change;
	double m_amp_crossfade_change[8];

};

