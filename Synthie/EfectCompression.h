#pragma once
#include "Effect.h"
class CEfectCompression :
	public CEffect
{
public:
	CEfectCompression();
	virtual ~CEfectCompression();
	virtual void Process(double *frame, double *eframe) override;

private:
	double m_clip = 0.05;
};

