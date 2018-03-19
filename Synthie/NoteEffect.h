#pragma once
#include "Note.h"

class CNoteEffect :
	public CNote
{
public:
	CNoteEffect();
	virtual ~CNoteEffect();
	void SetEffect(int i, double e);
	double *GetEffects(){return effects;}
	void Seteffected(std::wstring s);

	const std::wstring &GetEffected() const  { return m_instrumenteffected; }

private:
	std::wstring m_instrumente = L"effectnote";

	std::wstring m_instrumenteffected;

	double effects[5] = { 1,0,0,0,0 };

};

