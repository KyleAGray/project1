#include "stdafx.h"
#include "AR.h"


CAR::CAR()
{
	m_attack = 0.05;
	m_release = 0.05;
	m_time = 0;
}


CAR::~CAR()
{
}

void CAR::Start()
{
}

bool CAR::Generate()
{
	m_time += GetSamplePeriod();

	double a = 1.;
	if (m_time < m_attack)
	{
		a = m_time / m_attack;
	}
	else if (m_duration - m_time < m_release)
	{
		a = (m_duration - m_time) / m_release;
	}
	m_frame[0] = a * m_source->Frame(0);
	m_frame[1] = a * m_source->Frame(1);

	return m_time < m_duration;

}
