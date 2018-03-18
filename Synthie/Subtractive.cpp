#include "stdafx.h"
#include "Subtractive.h"
#include "Notes.h"

CSubtractive::CSubtractive()
{
	m_duration = 0.1;
}


CSubtractive::~CSubtractive()
{
}

void CSubtractive::Start()
{
	m_subPlayer.SetSampleRate(GetSampleRate());
	m_subPlayer.Start();
	m_time = 0;
	
	m_envelope = new CSubEnvenlope();
	m_envelope->SetAttack(0.05);
	m_envelope->SetRelease(0.05);

	m_filterEnvelope.SetEnvelope(m_envelope);
	m_filterEnvelope.SetSource(&m_subPlayer);
	m_filterEnvelope.SetSampleRate(GetSampleRate());
	m_filterEnvelope.SetDuration(m_duration);
	
	m_filterEnvelope.Start();
}

bool CSubtractive::Generate()
{
	m_subPlayer.Generate();
	m_envelope->Generate();
	bool valid = m_filterEnvelope.Generate();

	m_frame[0] = m_filterEnvelope.Frame(0);
	m_frame[1] = m_filterEnvelope.Frame(1);

	m_time += GetSamplePeriod();
	return valid;
}

void CSubtractive::SetNote(CNote * note)
{
	// Get a list of all attribute nodes and the
	// length of that list
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	note->Node()->get_attributes(&attributes);
	long len;
	attributes->get_length(&len);

	// Loop over the list of attributes
	for (int i = 0; i<len; i++)
	{
		// Get attribute i
		CComPtr<IXMLDOMNode> attrib;
		attributes->get_item(i, &attrib);

		// Get the name of the attribute
		CComBSTR name;
		attrib->get_nodeName(&name);

		CComVariant value;
		attrib->get_nodeValue(&value);

		if (name == "duration")
		{
			value.ChangeType(VT_R8);
			SetDuration(value.dblVal);
		}
		else if (name == "note")
		{
			SetFreq(NoteToFrequency(value.bstrVal));
		}
		else if (name == "waveform")
		{
			m_subPlayer.SetWaveform((wstring)value.bstrVal);
		}
		else if (name == "reson")
		{
			m_subPlayer.SetReson(true);
			value.ChangeType(VT_R8);
			m_subPlayer.SetResonFreq(value.dblVal);
		}
		else if (name == "bandwidth")
		{
			m_subPlayer.SetReson(true);
			value.ChangeType(VT_R8);
			m_subPlayer.SetResonBW(value.dblVal);
		}
		else if (name == "sweep")
		{
			m_subPlayer.SetFilter((wstring)value.bstrVal);
		}
	}

}

