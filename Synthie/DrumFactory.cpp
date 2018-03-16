#include "stdafx.h"
#include "DrumFactory.h"
#include <cmath>
#include "audio/DirSoundSource.h"


CDrumFactory::CDrumFactory()
{
	v.push_back(0);
	for (int j = 0; j < 22; j++) {
		m_drum.push_back(v);
	}
	kit = 1;
	filt = 1;
}


CDrumFactory::~CDrumFactory()
{
}

CDrumInstrument *CDrumFactory::CreateInstrument() {
	CDrumInstrument *instrument = new CDrumInstrument();

	instrument->SetKit(kit);
	instrument->SetFilt(filt);
	instrument->GetPlayer()->SetSamples(&m_drum[kit][0], (int)m_drum[kit].size());

	return instrument;
}

void CDrumFactory::SetNote(CNote* note) 
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
		if (name == "kit")
		{
			value.ChangeType(VT_R8);
			int b = int(value.dblVal + 0.4);
			kit = b;
		}
		else if (name == "filt")
		{
			value.ChangeType(VT_R8);
			filt = value.dblVal;
		}
	}
}

bool CDrumFactory::LoadFile(const char *filename, int j)
{
	m_drum[j].clear();

	CDirSoundSource m_file;
	if (!m_file.Open(filename))
	{
		CString msg = L"Unable to open audio file: ";
		msg += filename;
		AfxMessageBox(msg);
		return false;
	}

	for (int i = 0; i<m_file.NumSampleFrames(); i++)
	{
		short frame[2];
		m_file.ReadFrame(frame);
		m_drum[j].push_back(frame[0]);
	}

	m_file.Close();
	return true;
}