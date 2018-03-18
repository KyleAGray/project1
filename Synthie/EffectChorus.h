#pragma once
#include "Effect.h"

const int BUFFERSIZE = 100000;

class CEffectChorus :
	public CEffect
{
public:
	CEffectChorus();
	virtual ~CEffectChorus();
	virtual void Process(double *frame, double *eframe) override;


};

