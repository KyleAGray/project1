#pragma once
#include "audionode.h"
#include <vector>
using namespace std;

class CDrums :
	public CAudioNode
{
public:
	CDrums(void);
	~CDrums(void);

public:
	virtual void Start();
	virtual bool Generate();

	void SetFreq(double f) { m_freq = f; }
	double GetFreq() { return m_freq; }
	void SetAmplitude(int i, double a) { m_amp = a; }
	double white_noise();
	void SetKit(int i) { kit = i; }
	void SetFilt(double i) { filt = i; }
	int GetKit() { return kit; }
	double GetFilt() { return filt; }

private:
	double m_freq;
	double m_phase;
	double m_amp;
	int kit;
	int time;
	double filt;
	vector<double> v;
};