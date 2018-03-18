#include "stdafx.h"
#include "EffectNoisGrate.h"
#include <cmath>
using namespace std;
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
	


	if (abs(eframe[0]) < m_clip)
	{
		frame[0] = 0;
	}
	else {
		frame[0] = eframe[0];
	}
	if (abs(eframe[1]) < m_clip)
	{
		frame[1] = 0;
	}
	else {
		frame[1] = eframe[1];
	}

	
}
 