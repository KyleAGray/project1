#pragma once
#include "AudioNode.h"
#include "SubEnvenlope.h"

class CFilterEnvelope :
	public CAudioNode
{
public:
	CFilterEnvelope();
	virtual ~CFilterEnvelope();

	virtual void Start() override;
	virtual bool Generate() override;

	void SetEnvelope(CSubEnvenlope* envelope) { m_envelope = envelope; }
	void SetSource(CAudioNode* source) { m_source = source; }
	void SetDuration(double duration) { m_duration = duration; }

protected:
	// source of the audio node
	CAudioNode * m_source;
	// envelope object
	CSubEnvenlope* m_envelope;
	// audio duration
	double m_duration;
	// keep track of time
	double m_time;
};

