#pragma once
#include "AudioNode.h"
class CSineWaveHarmonics :
	public CAudioNode
{
public:
	CSineWaveHarmonics();
	~CSineWaveHarmonics();
public:
	//! Start audio generation
	virtual void Start(); 

	//! Generate one frame of audio
	virtual bool Generate();

	//! Set the sine wave frequency
	void SetFreq(double f) { m_freq = f; }

	//! Set the sine wave amplitude
	void SetAmplitude0(double a) { m_amp[0] = a; }
	void SetAmplitude1(double a) { m_amp[1] = a; }
	void SetAmplitude2(double a) { m_amp[2] = a; }
	void SetAmplitude3(double a) { m_amp[3] = a; }
	void SetAmplitude4(double a) { m_amp[4] = a; }
	void SetAmplitude5(double a) { m_amp[5] = a; }
	void SetAmplitude6(double a) { m_amp[6] = a; }
	void SetAmplitude7(double a) { m_amp[7] = a; }
	void SetVibrato(double v) { m_vibrato = v; }
	void SetVibratoChange(double v) { m_vibrato_change = v; }

private:
	double m_freq;
	double m_amp[8];
	double m_phase;
	double m_vibrato;
	double m_vibrato_change;
	double m_time;

};

