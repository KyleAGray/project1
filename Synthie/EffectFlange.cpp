#include "stdafx.h"
#include "EffectFlange.h"


CEffectFlange::CEffectFlange()
{
}


CEffectFlange::~CEffectFlange()
{
}

void CEffectFlange::Process(double * frame, double * eframe)
{
	wrloc = (wrloc + 2) % QUEUESIZE;
	queue[wrloc] = eframe[0];
	queue[wrloc + 1] = eframe[1];


	delay = 0.006 + sin(0.25 * 2 * 3.14159265359 * time) * 0.004;
	int delaylength = int((delay * 44100 + 0.5)) * 2;
	int rdloc = (wrloc + QUEUESIZE - delaylength) % QUEUESIZE;

	frame[0] = eframe[0] + queue[rdloc++ % QUEUESIZE];
	frame[1] = eframe[1] + queue[rdloc];

	time += 1. / 44100;

	double fuck = queue[wrloc];
}
