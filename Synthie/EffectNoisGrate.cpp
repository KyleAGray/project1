#include "stdafx.h"
#include "EffectNoisGrate.h"


CEffectNoisGrate::CEffectNoisGrate()
{
}


CEffectNoisGrate::~CEffectNoisGrate()
{
}

// reduce any sound below the threshold to 0
// Takes in stereo sound frame array 
void CEffectNoisGrate::Process(double * frame)
{
	if (frame[0] < 100)
	{
		frame[0] = 0;
	}
	if (frame[1] < 100)
	{
		frame[1] = 0;
	}
}
