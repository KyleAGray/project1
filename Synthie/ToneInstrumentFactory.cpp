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

	return instrument;
}
