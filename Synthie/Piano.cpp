#include "stdafx.h"
#include "Piano.h"


CPiano::CPiano()
{
}


CPiano::~CPiano()
{
}

void CPiano::Start()
{
	m_pianoPlayer.SetSampleRate(m_pianoPlayer.GetSampleRate());
	m_pianoPlayer.Start();
}


void CPiano::SetNote(CNote *note)
{
}


bool CPiano::Generate()
{
	bool valid = m_pianoPlayer.Generate();

	m_frame[0] = m_pianoPlayer.Frame(0);
	m_frame[1] = m_frame[0];

	return valid;
}