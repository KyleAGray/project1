#include "stdafx.h"
#include "SubEnvenlope.h"


CSubEnvenlope::CSubEnvenlope()
{
	m_attack = 0.05;
	m_decay = 0.;
	m_sustain = 1.;
	m_release = 0.05;
	m_time = 0;
}


CSubEnvenlope::~CSubEnvenlope()
{
}

void CSubEnvenlope::Start()
{
	m_time = 0.;
}

bool CSubEnvenlope::Generate()
{
	m_time += GetSamplePeriod();

	double m_envelope = 1.;
	// attack
	if (m_time < m_attack)
	{
		m_envelope = m_time / m_attack * m_sustain;
	}
	// decay
	else if (m_time > m_attack && m_time <= m_attack + m_decay)
	{
		m_envelope = (m_envelope - 1) * ((m_time - (m_duration - m_decay)) / m_decay) + 1;
	}
	//release
	else if ((m_duration - m_release) < m_time)
	{
		m_envelope = (1 - (m_time - (m_duration - m_release)) / m_release) * m_sustain;
	}
	// sustain
	else
		m_envelope = m_sustain;

	return m_time < m_duration;
}
