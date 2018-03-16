#include "StdAfx.h"
#include "DrumInstrument.h"
#include "Notes.h"
#include "instrument.h"


CDrumInstrument::CDrumInstrument()
{
}


CDrumInstrument::~CDrumInstrument()
{
}

void CDrumInstrument::Start()
{
	//m_ar.SetSampleRate(GetSampleRate());
	//m_ar.Start();
	m_time = 0;

	m_sines.SetSampleRate(GetSampleRate());
	m_sines.Start();
	m_drumPlayer.Start();
	v.resize(3);
	//m_ar.SetSource(&m_sines);
}


void CDrumInstrument::SetNote(CNote *note)
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
			double a = 60 / m_bpm * value.dblVal;
			SetDuration(a);
		}
		else if (name == "note")
		{
			SetFreq(NoteToFrequency(value.bstrVal));
		}
		else if (name == "kit")
		{
			value.ChangeType(VT_R8);
			int b = int(value.dblVal + 0.4);
			m_sines.SetKit(b);
		}
		else if (name == "filt")
		{
			value.ChangeType(VT_R8);
			m_sines.SetFilt(value.dblVal);
		}
		/*else if (name == "attack")
		{
			value.ChangeType(VT_R8);
			m_ar.SetAttack(value.dblVal);
		}
		else if (name == "release")
		{
			value.ChangeType(VT_R8);
			m_ar.SetRelease(value.dblVal);
		}*/
	}

}


bool CDrumInstrument::Generate()
{
	if(m_sines.GetKit() == 1)
		SetFreq((m_sines.GetFreq()-20) * exp(-0.5 * m_time / m_duration)+20);
	else
		SetFreq(m_sines.GetFreq() * (m_duration - m_time) / m_duration);
	
	if (m_sines.GetKit() < 3)
	{
		m_sines.Generate();

		//bool valid = m_ar.Generate();

		m_frame[0] = m_sines.Frame(0) * (m_duration - m_time) / m_duration;
		m_frame[1] = m_sines.Frame(1) * (m_duration - m_time) / m_duration;
	}

	else {
		bool valid = m_drumPlayer.Generate();

		if(m_sines.GetFilt() != 1){
			double B = 0.01;
			double f = m_sines.GetFilt();
			double R = 1 - B / 2;
			double theta = 2 * R * cos(2 * PI * f) / (1 + R * R);
			double A = (1 - R * R) * sqrt(1 - theta * theta);
			A = A * 10;


			m_frame[0] = A * m_drumPlayer.Frame(0) + (2 * R * theta) * v[2] - R * R * v[1];
			m_frame[1] = m_frame[0];

			v[0] = v[1];
			v[1] = v[2];
			v[2] = m_frame[0];
		}
		else {
			m_frame[0] = m_drumPlayer.Frame(0);
			m_frame[1] = m_frame[0];
		}

		return valid;
	}

	m_time += GetSamplePeriod();
	return m_time < m_duration;
}