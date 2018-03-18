#pragma once
#include "AudioNode.h"
#include <vector>
using namespace std;

class CSubtractivePlayer :
	public CAudioNode
{
public:
	CSubtractivePlayer();
	virtual ~CSubtractivePlayer();

	//! Start audio generation
	virtual void Start();

	//! Generate one frame of audio
	virtual bool Generate();

	//! Set the sine wave frequency
	void SetFreq(double f) { m_freq = f; }

	//! Set the sine wave amplitude
	void SetAmplitude(double a) { m_amp = a; }
	// Set up what kind of waveform. square, sawtooth or triangle
	void SetWaveform(wstring wave) { m_waveform = wave; }
	// build up wavetable
	void BuildTable();
	// Set reson filter
	void SetReson(bool reson) { m_reson = reson; }
	void SetResonFreq(double f) { m_resonFreq = f; }
	void SetResonBW(double b) { m_resonbw = b; }
	void Reson(double* sample, int pos);

	// Filter Envelope
	void SetFilter(wstring sweep) { m_sweep = sweep; }

private:
	double m_freq;
	double m_amp;
	int m_phase;
	double m_time;
	bool m_reson;
	double m_resonFreq;
	double m_resonbw;

	wstring m_waveform;
	wstring m_sweep;
	vector<double> m_wavetable;
};

