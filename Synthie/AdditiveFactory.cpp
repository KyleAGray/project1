#include "stdafx.h"
#include "AdditiveFactory.h"


CAdditiveFactory::CAdditiveFactory()
{
}


CAdditiveFactory::~CAdditiveFactory()
{
}

CAdditive * CAdditiveFactory::CreateInstrument()
{
	CAdditive *instrument = new CAdditive();

	// Set Effect values
	instrument->SetSend(0, m_dry);
	instrument->SetSend(1, m_gateing);
	instrument->SetSend(2, m_compression);
	instrument->SetSend(3, m_chorus);
	instrument->SetSend(4, m_flange);
	return instrument;
}
