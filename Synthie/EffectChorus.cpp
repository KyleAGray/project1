#include "stdafx.h"
#include "EffectChorus.h"


CEffectChorus::CEffectChorus()
{
}


CEffectChorus::~CEffectChorus()
{
}

void CEffectChorus::Process(double * frame, double * eframe)
{
	wrloc = (wrloc + 2) % SIZE2;
	queue[wrloc] = eframe[0];
	queue[wrloc + 1] = eframe[1];


	delay = 0.05;
	int delaylength = int((delay * 44100 + 0.5)) * 2;
	int rdloc = (wrloc + SIZE2 - delaylength) % SIZE2;

	frame[0] = eframe[0] + queue[rdloc++ % SIZE2];
	frame[1] = eframe[1] + queue[rdloc];

	time += 1. / 44100;

}
