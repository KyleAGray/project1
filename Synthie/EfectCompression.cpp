#include "stdafx.h"
#include "EfectCompression.h"


CEfectCompression::CEfectCompression()
{
}


CEfectCompression::~CEfectCompression()
{
}


// reduce any sound below the threshold to 0
// Takes in stereo sound frame array 
void CEfectCompression::Process(double * frame, double * eframe)
{

	if (eframe[0] > m_clip)
	{
		frame[0] = 0;
	}
	else {
		frame[0] = eframe[0];
	}
	if (eframe[1] > m_clip)
	{
		frame[1] = 0;
	}
	else {
		frame[1] = eframe[1];
	}


}
