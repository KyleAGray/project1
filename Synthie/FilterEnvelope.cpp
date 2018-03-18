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

	// set the duration, sample rate of the envelope
	m_envelope->SetDuration(m_duration);
	m_envelope->SetSampleRate(GetSampleRate());

	// start envelope generation
	m_envelope->Start();
}

bool CFilterEnvelope::Generate()
{
	auto amplitude_factor = m_envelope->GetEnvelope();

	// set the frames 
	m_frame[0] = m_source->Frame(0) * amplitude_factor;
	m_frame[1] = m_source->Frame(1) * amplitude_factor;

	// update the time
	m_time += GetSamplePeriod();

	return m_duration > m_time;
}
