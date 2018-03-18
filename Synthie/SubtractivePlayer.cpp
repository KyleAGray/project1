#include "stdafx.h"
#include "SubtractivePlayer.h"
#include <cmath>

using namespace std;
CSubtractivePlayer::CSubtractivePlayer()
{
	m_amp = .1;
	m_phase = 0;
	m_freq = 440;

	m_resonbw = 0.1;
	m_resonFreq = 0.1;
	m_reson = false;
}


CSubtractivePlayer::~CSubtractivePlayer()
{
}

void CSubtractivePlayer::Start()
{
	m_phase = 0;
	m_time = 0;
	BuildTable();
}

bool CSubtractivePlayer::Generate()
{
	m_frame[0] = m_wavetable[m_phase];
	m_frame[1] = m_frame[0];

	m_phase = (m_phase + 1) % m_wavetable.size();

	return true;
}

void CSubtractivePlayer::BuildTable()
{
	m_wavetable.resize(GetSampleRate());
	double ampFilter = 1.0;
	double filterF = m_freq;

	if (m_freq > 1000. / 44100) {
		ampFilter = 0.75;
	}
	if (m_freq > 1200. / 44100) {
		ampFilter = 0.6;
	}
	if (m_freq > 1400. / 44100) {
		ampFilter = 0.45;
	}
	
	for (int i = 0; i < GetSampleRate(); i++, m_time += 1. / GetSampleRate())
	{
		double sample = 0;

		if (m_sweep == L"up")
		{
			filterF += 440. / GetSampleRate();
		}
		else if (m_sweep == L"down")
		{
			filterF -= 440. / GetSampleRate();
		}
		else if (m_sweep == L"up-down")
		{
			if (i < GetSampleRate() / 2)
			{
				filterF += 440. / GetSampleRate();
			}
			filterF -= 440. / GetSampleRate();
		}
		else if (m_sweep == L"down-up")
		{
			if (i < GetSampleRate() / 2)
			{
				filterF -= 440. / GetSampleRate();
			}
			filterF += 440. / GetSampleRate();
		}

		// add every odd harmonics up to nyquist frequency
		if (m_waveform == L"square")
		{
			for (int j = 1; j < GetSampleRate() / (2 * m_freq); j += 2)
			{
				sample += ampFilter * m_amp / j * sin(m_time * 2 * PI * filterF * j);
			}
		}
		// add every harmonics upto nyquist frequency
		else if (m_waveform == L"sawtooth")
		{
			for (int j = 1; j < GetSampleRate() / (2 * m_freq); j ++)
			{
				sample += ampFilter * m_amp / j * sin(m_time * 2 * PI * filterF * j);
			}
		}
		// add every odd harmonics up to nyquist frequency
		else if (m_waveform == L"triangle")
		{
			int sign = -1;
			for (int j = 1; j < GetSampleRate() / (2 * m_freq); j += 2)
			{
				//int n = 2 * j + 1;
				sample += ampFilter * sign * m_amp / pow(j, 2) * sin(m_time * 2 * PI * filterF * j);
				sign = -sign;
			}
		}

		if (m_reson && i > 1)
		{
			Reson(&sample, i);
		}
		
		m_wavetable[i] = sample;
	}
	
}

void CSubtractivePlayer::Reson(double* sample, int pos)
{
	//Calculate reson values for reson equation
	double R = 1.0 - (m_resonbw / 2.0);
	double theta = acos((2 * R * cos(2 * PI * m_resonFreq)) / (1 + pow(R, 2)));
	double A = (1 - pow(R, 2)) * sin(theta);
	int first, second;

	if (pos < 1)
		first = m_wavetable.size() - 1;
	else
		first = pos - 1;
	if (pos - 2 < 0)
		second = m_wavetable.size() - 1;
	else
		second = pos - 2;

	*sample = A * *sample + 2 * R * cos(theta) * m_wavetable[first] - pow(R, 2) * m_wavetable[second];

}
