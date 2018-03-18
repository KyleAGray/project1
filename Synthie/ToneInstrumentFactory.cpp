#include "stdafx.h"
#include "ToneInstrumentFactory.h"


CToneInstrumentFactory::CToneInstrumentFactory()
{
}


CToneInstrumentFactory::~CToneInstrumentFactory()
{
}

CToneInstrument * CToneInstrumentFactory::CreateInstrument()
{
	CToneInstrument *instrument = new CToneInstrument();

	// Set Effect values
	instrument->SetSend(0, m_dry);
	instrument->SetSend(1, m_gateing);
	instrument->SetSend(2, m_compression);
	instrument->SetSend(3, m_reverb);
	instrument->SetSend(4, m_flange);
	return instrument;
}
