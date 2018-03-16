#include "stdafx.h"
#include "CSineWaveHarmonics.h"


CSineWaveHarmonics::CSineWaveHarmonics()
{
	m_amp[0] = .1;
	m_amp[1] = 0;
	m_amp[2] = 0;
	m_amp[3] = 0;
	m_amp[4] = 0;
	m_amp[5] = 0;
	m_amp[6] = 0;
	m_amp[7] = 0;
	m_phase = 0;
	m_freq = 440;
	m_vibrato = 0;
	m_vibrato_change = 0;
	m_time = 0;

}


CSineWaveHarmonics::~CSineWaveHarmonics()
{ 
}

void CSineWaveHarmonics::Start()
{
	m_phase = 0;
}

bool CSineWaveHarmonics::Generate()
{
	if (m_vibrato != 0) {
		m_frame[0] = m_amp[0] * sin(m_time * (m_freq + m_vibrato_change * sin(2 * PI * m_time * m_vibrato )) * 2 * PI) + m_amp[1] * sin(m_time * (m_freq + m_vibrato_change * sin(2 * PI * m_time * m_vibrato)) * 2 * 2 * PI) + m_amp[2] * sin(m_time * (m_freq + m_vibrato_change * sin(2 * PI * m_time * m_vibrato)) * 2 * 3 * PI) + m_amp[3] * sin(m_time * (m_freq + m_vibrato_change * sin(2 * PI * m_time * m_vibrato)) * 2 * 4 * PI) + m_amp[4] * sin(m_time * (m_freq + m_vibrato_change * sin(2 * PI * m_time * m_vibrato)) * 2 * 5 * PI) + m_amp[5] * sin(m_time * (m_freq + m_vibrato_change * sin(2 * PI * m_time * m_vibrato)) * 2 * 6 * PI) + m_amp[6] * sin(m_time * (m_freq + m_vibrato_change * sin(2 * PI * m_time * m_vibrato)) * 2 * 7 * PI) + m_amp[7] * sin(m_time * (m_freq + m_vibrato_change * sin(2 * PI * m_time * m_vibrato)) * 2 * 8 * PI);
		m_frame[1] = m_frame[0];


	}
	else {
		m_frame[0] = m_amp[0] * sin(m_phase * 2 * PI) + m_amp[1] * sin(m_phase * 2 * 2 * PI) + m_amp[2] * sin(m_phase * 2 * 3 * PI) + m_amp[3] * sin(m_phase * 2 * 4 * PI) + m_amp[4] * sin(m_phase * 2 * 5 * PI) + m_amp[5] * sin(m_phase * 2 * 6 * PI) + m_amp[6] * sin(m_phase * 2 * 7 * PI) + m_amp[7] * sin(m_phase * 2 * 8 * PI);
		m_frame[1] = m_frame[0];
	}
	m_phase += m_freq * GetSamplePeriod();
	m_time += GetSamplePeriod();
	return true;
}