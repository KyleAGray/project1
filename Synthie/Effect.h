#pragma once
class CEffect
{
public:
	CEffect();
	virtual ~CEffect();

	virtual void Process(double *frame) = 0;

};

