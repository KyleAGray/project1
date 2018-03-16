#include "stdafx.h"
#include "DrumPlayer.h"


CDrumPlayer::CDrumPlayer()
{
	m_samples = NULL;
	m_numsamples = 0;
}


CDrumPlayer::~CDrumPlayer()
{
}

void CDrumPlayer::Start()
{
	m_position = 0;
}

bool CDrumPlayer::Generate()
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