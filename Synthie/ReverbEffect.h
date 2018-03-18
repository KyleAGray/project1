#pragma once
#include "Effect.h"
class CReverbEffect :
	public CEffect
{
public:
	CReverbEffect();
	virtual ~CReverbEffect();
	virtual void Process(double *frame, double *eframe) override;


private:
	double m_prevFrame[2] = {};

	
};

