#pragma once
#include "Effect.h"

#define M_PI acos(-1.0)
const int QUEUESIZE = 200000;
class CEffectFlange :
	public CEffect
{
public:
	CEffectFlange();
	virtual ~CEffectFlange();
	virtual void Process(double *frame, double *eframe) override;


private:


	double delay = 1.0;

	double queue[QUEUESIZE] = {};


	int wrloc = 0;

	double time = 0;
};

