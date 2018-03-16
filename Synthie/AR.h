#pragma once
#include "AudioNode.h"
class CAR :
	public CAudioNode
{
public:
	CAR();
	~CAR();

	void SetSource(CAudioNode *source) { m_source = source; }
	void SetDuration(double d) { m_duration = d; }
	void Start();
	bool Generate();

	void SetAttack(double a) { m_attack = a; }
	void SetRelease(double r) { m_release = r; }

private:
	double m_attack;
	double m_release;
	double m_duration;
	double m_time;
	CAudioNode *m_source;

};

