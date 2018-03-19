#include "stdafx.h"
#include "NoteEffect.h"


CNoteEffect::CNoteEffect()
{
	m_isEffect = true;
}


CNoteEffect::~CNoteEffect()
{
}

void CNoteEffect::SetEffect(int i, double e)
{
	effects[i] = e;
}

void CNoteEffect::Seteffected(std::wstring s)
{
	m_instrumenteffected = s;
}

