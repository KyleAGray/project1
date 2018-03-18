#pragma once
#include "Effect.h"
class CEffectNoisGrate :
	public CEffect
{
public:
	CEffectNoisGrate();
	virtual ~CEffectNoisGrate();

	virtual void Process(double *frame, double *eframe) override;

private:
	/// The threshold for allowing a sound to pass through
	/// 100 seemed to work well for aliminating noise in the overture wav file from step 4.
	double m_clip = 0.003;
};

