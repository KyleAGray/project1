#pragma once
#include "Effect.h"

#define M_PI acos(-1.0)
const int SIZE2 = 200000;
class CEffectChorus :
	public CEffect
{
public:
	CEffectChorus();
	virtual ~CEffectChorus();
	virtual void Process(double *frame, double *eframe) override;

private:
	double delay = 1.0;

	double queue[SIZE2] = {};


	int wrloc = 0;

	double time = 0;
};
