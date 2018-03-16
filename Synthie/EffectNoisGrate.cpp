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
void CEffectNoisGrate::Process(double * frame, double * eframe)
{
	
	if (eframe[0] < 50)
	{
		frame[0] = 0;
	}
	else {
		frame[0] = eframe[0];
	}
	if (eframe[1] < 50)
	{
		frame[1] = 0;
	}
	else {
		frame[1] = eframe[1];
	}

	frame[0] = eframe[0];
	frame[1] = eframe[1];
	
}
