#include "stdafx.h"
#include "CAdditive.h"
#include "Notes.h" 
#include "string.h"

CAdditive::CAdditive()
{
	m_duration = 0.1;
	vibrato = 0;
	m_amp[0] = .1;
	m_amp[1] = 0;
	m_amp[2] = 0;
	m_amp[3] = 0;
	m_amp[4] = 0;
	m_amp[5] = 0;
	m_amp[6] = 0;
	m_amp[7] = 0;
	m_amp_crossfade_change[0] = .1;
	m_amp_crossfade_change[1] = 0;
	m_amp_crossfade_change[2] = 0;
	m_amp_crossfade_change[3] = 0;
	m_amp_crossfade_change[4] = 0;
	m_amp_crossfade_change[5] = 0;
	m_amp_crossfade_change[6] = 0;
	m_amp_crossfade_change[7] = 0;

}


CAdditive::~CAdditive()
{
}

void CAdditive::Start()
{
	m_sinewave.SetSampleRate(GetSampleRate());
	m_sinewave.Start();
	m_time = 0;
	m_phase = 0;
	SetAmplitude0(m_amp[0]);
	SetAmplitude1(m_amp[1]);
	SetAmplitude2(m_amp[2]);
	SetAmplitude3(m_amp[3]);
	SetAmplitude4(m_amp[4]);
	SetAmplitude5(m_amp[5]);
	SetAmplitude6(m_amp[6]);
	SetAmplitude7(m_amp[7]);


	// Tell the AR object it gets its samples from 
	// the sine wave object.
	m_ar.SetSource(&m_sinewave);
	m_ar.SetSampleRate(GetSampleRate());
	m_ar.SetDuration(m_duration);
	m_ar.Start();
}

bool CAdditive::Generate()
{
	m_amp[0] = m_amp[0] + m_amp_crossfade_change[0];
	m_amp[1] = m_amp[1] + m_amp_crossfade_change[1];
	m_amp[2] = m_amp[2] + m_amp_crossfade_change[2];
	m_amp[3] = m_amp[3] + m_amp_crossfade_change[3];
	m_amp[4] = m_amp[4] + m_amp_crossfade_change[4];
	m_amp[5] = m_amp[5] + m_amp_crossfade_change[5];
	m_amp[6] = m_amp[6] + m_amp_crossfade_change[6];
	m_amp[7] = m_amp[7] + m_amp_crossfade_change[7];

	SetAmplitude0(m_amp[0]);
	SetAmplitude1(m_amp[1]);
	SetAmplitude2(m_amp[2]);
	SetAmplitude3(m_amp[3]);
	SetAmplitude4(m_amp[4]);
	SetAmplitude5(m_amp[5]);
	SetAmplitude6(m_amp[6]);
	SetAmplitude7(m_amp[7]);


	m_sinewave.Generate();
	bool valid = m_ar.Generate();

	m_frame[0] = m_ar.Frame(0);
	m_frame[1] = m_ar.Frame(1);

	m_time += GetSamplePeriod();

	return valid;

}

void CAdditive::SetNote(CNote *note)
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

		// Get the value of the attribute.  A CComVariant is a variable
		// that can have any type. It loads the attribute value as a
		// string (UNICODE), but we can then change it to an integer 
		// (VT_I4) or double (VT_R8) using the ChangeType function 
		// and then read its integer or double value from a member variable.
		CComVariant value;
		attrib->get_nodeValue(&value);

		if (name == "duration")
		{
			value.ChangeType(VT_R8);
			SetDuration(value.dblVal);
		}
		else if (name == "note")
		{
			std::wstring val(value.bstrVal, SysStringLen(value.bstrVal)); 
			for (int i = 0; i < 8; i++) {
				m_amp[i] = stod(val.substr(0,int(val.find(' '))));
				val.erase(0,int(val.substr(0,int(val.find(' '))).length())+1);
			}
			SetAmplitude0(m_amp[0]);
			SetAmplitude1(m_amp[1]);
			SetAmplitude2(m_amp[2]);
			SetAmplitude3(m_amp[3]);
			SetAmplitude4(m_amp[4]);
			SetAmplitude5(m_amp[5]);
			SetAmplitude6(m_amp[6]);
			SetAmplitude7(m_amp[7]);
		}
		else if (name == "frequency")
		{
			
			value.ChangeType(VT_R8);
			SetFreq(value.dblVal);
		}
		else if (name == "vibrato")
		{
			std::wstring str(value.bstrVal, SysStringLen(value.bstrVal));
			vibrato = stod(str.substr(0, int(str.find(' '))));
			str.erase(0, int(str.substr(0, int(str.find(' '))).length()) + 1);
			vibrato_change = stod(str);
			SetVibrato(vibrato);
			SetVibratoChange(vibrato_change);
		}
		else if (name == "crossfade")
		{
			std::wstring val(value.bstrVal, SysStringLen(value.bstrVal));

			for (int i = 0; i < 8; i++) {
				m_amp_crossfade_change[i] = ((stod(val.substr(0, int(val.find(' '))))) - m_amp[i]) / (m_duration * 1 / (GetSamplePeriod()));
				val.erase(0, int(val.substr(0, int(val.find(' '))).length()) + 1);
			}
		}
	}

}



void CAdditive::SetDuration(double d)
{
	m_duration = d * 60 / m_bpm;
}
