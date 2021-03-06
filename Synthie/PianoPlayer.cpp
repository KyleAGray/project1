#include "stdafx.h"
#include "PianoPlayer.h"


CPianoPlayer::CPianoPlayer()
{
	m_samples = NULL;
	m_numsamples = 0;
	m_power = 0;
}

CPianoPlayer::~CPianoPlayer(void)
{
}

void CPianoPlayer::Start()
{
	m_position = 0;
}

bool CPianoPlayer::Generate()
{
	if (m_position < m_numsamples)
	{
		m_frame[0] = m_samples[m_position++] / 32768.0;
		m_frame[1] = m_frame[0];
		return true;
	}
	else
	{
		m_frame[1] = m_frame[0] = 0;
		return false;
	}
}


