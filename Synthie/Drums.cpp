#include "StdAfx.h"
#include "Drums.h"
#include <cmath>

CDrums::CDrums(void)
{
	m_phase = 0;
	m_amp = 6;
	m_freq = 440;
	kit = 1;
	time = 0;
	v.resize(3);
	filt = 1;
}

CDrums::~CDrums(void)
{
}


void CDrums::Start()
{
	m_phase = m_freq;
	time = 0;
}

bool CDrums::Generate()
{
	time++;
	if (kit == 1) {//Kick Drum
		m_frame[0] = m_amp * sin(m_freq * 2 * PI * time * GetSamplePeriod());
		m_frame[1] = m_frame[0];
	}
	else if (kit == 2) {//Tom 1
		m_frame[0] = 0.05*m_amp * sin(m_freq * 2 * PI * time * GetSamplePeriod()) + 0.2 * white_noise();
		m_frame[1] = m_frame[0];
	}
	else if (kit == 3) {//Tom 2
		m_frame[0] = m_amp * sin(m_freq * 2 * PI * time * GetSamplePeriod()) + 0.05 * white_noise() + m_amp/2 * sin(m_freq * 4 * PI * time * GetSamplePeriod());
		m_frame[1] = m_frame[0];
	}

	return true;
}

double CDrums::white_noise()
{

	double f1;
	double f2;
	int j;

	j = 1;

	f2 = (rand() / ((double)RAND_MAX));

	f1 = cos((2.0 * (double)PI) * f2);

	double B = 0.01;
	double f = 0.02;
	double R = 1 - B / 2;
	double theta = 2 * R * cos(2 * PI * f) / (1 + R * R);
	double A = (1 - R * R) * sqrt(1 - theta * theta);
	A = A * 10;

	f1 = A * f1 + (2 * R * theta) * v[2] - R * R * v[1];

	v[0] = v[1];
	v[1] = v[2];
	v[2] = f1;

	return f1;

}