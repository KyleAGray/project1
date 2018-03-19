#include "stdafx.h"
#include "EfectCompression.h"
#include <cmath>

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

	if (eframe[0] > m_clip && eframe[0] > 0)
	{
		frame[0] = eframe[0] - 0.01;
	}
	else if (abs(eframe[0]) < m_clip && abs(eframe[0]) < 0)
	{
		frame[0] = eframe[0] + 0.01;
	}
	else {
		frame[0] = eframe[0];
	}
	
	if (eframe[1] > m_clip && eframe[1] > 0)
	{
		frame[1] = eframe[1] - 0.01;
	}
	else if (abs(eframe[1]) < m_clip && abs(eframe[0]) < 0)
	{
		frame[0] = eframe[1] + 0.01;
	}
	else {
		frame[1] = eframe[1];
	}


}
