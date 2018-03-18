#include "stdafx.h"
#include "ReverbEffect.h"


CReverbEffect::CReverbEffect()
{
}


CReverbEffect::~CReverbEffect()
{
}

void CReverbEffect::Process(double * frame, double * eframe)
{
	frame[0] = m_prevFrame[0] * 0.4 + eframe[0];
	frame[1] = m_prevFrame[1] * 0.4 + eframe[1];

	m_prevFrame[0] = frame[0];
	m_prevFrame[1] = frame[1];
}
