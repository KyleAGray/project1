#pragma once
#include "AudioNode.h"
class CPianoPlayer :
	public CAudioNode
{
public:
	CPianoPlayer();
	virtual ~CPianoPlayer();

	virtual void Start();
	virtual bool Generate();

	void SetFreq(double f) { m_freq = f; }
	void SetSamples(short *s, int n) { m_samples = s; m_numsamples = n; }
	void SetPower(double p) { m_power = p; }
private:
	short *m_samples;
	int    m_numsamples;
	int    m_position;

	double m_power;
	double m_freq;
};

