#pragma once
#include "AudioNode.h"
class CSubEnvenlope :
	public CAudioNode
{
public:
	CSubEnvenlope();
	virtual ~CSubEnvenlope();

	virtual void Start() override;
	virtual bool Generate() override;

	void SetSource(CAudioNode *source) { m_source = source; }
	void SetDuration(double d) { m_duration = d; }
	void SetAttack(double a) { m_attack = a; }
	void SetDecay(double d) { m_decay = d;}
	void SetSustain(double s) { m_sustain = s; }
	void SetRelease(double r) { m_release = r; }

	double GetEnvelope() { return m_envelope; }

private:
	double m_envelope;
	double m_attack;
	double m_decay;
	double m_sustain;
	double m_release;

	double m_duration;
	double m_time;

	CAudioNode *m_source;
};

