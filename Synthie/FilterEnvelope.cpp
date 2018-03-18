#include "stdafx.h"
#include "FilterEnvelope.h"


CFilterEnvelope::CFilterEnvelope()
{
}


CFilterEnvelope::~CFilterEnvelope()
{
}

void CFilterEnvelope::Start()
{
	m_time = 0;

	m_envelope->SetDuration(m_duration);
	m_envelope->SetSampleRate(GetSampleRate());

	m_envelope->Start();
}

bool CFilterEnvelope::Generate()
{
	auto envelopeLevel = m_envelope->GetEnvelope();

	// set the frames 
	m_frame[0] = m_source->Frame(0) * envelopeLevel;
	m_frame[1] = m_source->Frame(1) * envelopeLevel;

	// update the time
	m_time += GetSamplePeriod();

	return m_time < m_duration;
}
