#include "stdafx.h"
#include "Synthesizer.h"
#include "ToneInstrument.h"
#include "msxml2.h"
#include "xmlhelp.h"
#include "EffectNoisGrate.h"
#include "DrumInstrument.h"
#include "DrumFactory.h"
#include "CAdditive.h"
#include <algorithm>
#include <cmath>
#include "Subtractive.h"


CSynthesizer::CSynthesizer()
{
	CoInitialize(NULL);

	m_channels = 2;
	m_sampleRate = 44100.;
	m_samplePeriod = 1 / m_sampleRate;

	m_drumfactory.LoadFile("Drums/step_snare.wav", 3);
	m_drumfactory.LoadFile("Drums/alien_hihats_01.wav", 4);
	m_drumfactory.LoadFile("Drums/alien_hihats_02.wav", 5);
	m_drumfactory.LoadFile("Drums/alien_hihats_03.wav", 6);
	m_drumfactory.LoadFile("Drums/alien_hihats_04.wav", 7);
	m_drumfactory.LoadFile("Drums/alien_hihats_05.wav", 8);
	m_drumfactory.LoadFile("Drums/alien_hihats_06.wav", 9);
	m_drumfactory.LoadFile("Drums/alien_hihats_07.wav", 10);
	m_drumfactory.LoadFile("Drums/dirty_snare01.wav", 11);
	m_drumfactory.LoadFile("Drums/dirty_snare02.wav", 12);
	m_drumfactory.LoadFile("Drums/dirty_snare03.wav", 13);
	m_drumfactory.LoadFile("Drums/jp_deep_bass_06.wav", 14);
	m_drumfactory.LoadFile("Drums/perturbed_hit01.wav", 15);
	m_drumfactory.LoadFile("Drums/V_04Floor_tom.wav", 16);
	m_drumfactory.LoadFile("Drums/V_08Floor_tom.wav", 17);
	m_drumfactory.LoadFile("Drums/V28_loose_skin.wav", 18);
	m_drumfactory.LoadFile("Drums/V55_loose_skin.wav", 19);
}


CSynthesizer::~CSynthesizer()
{
}

void CSynthesizer::Start(void)
{
	m_instruments.clear();
	m_currentNote = 0;
	m_measure = 0;
	m_beat = 0;
	m_time = 0;
}

//! Generate one audio frame
bool CSynthesizer::Generate(double * frame)
{

	//
	// Phase 1: Determine if any notes need to be played.
	//

	while (m_currentNote < (int)m_notes.size())
	{
		// Get a pointer to the current note
		CNote *note = &m_notes[m_currentNote];

		// If the measure is in the future we can't play
		// this note just yet.
		if (note->Measure() > m_measure)
			break;

		// If this is the current measure, but the
		// beat has not been reached, we can't play
		// this note.
		if (note->Measure() == m_measure && note->Beat() > m_beat)
			break;

		//
		// Play the note!
		//

		// Create the instrument object
		CInstrument *instrument = NULL;
		if (note->Instrument() == L"ToneInstrument")
		{
			//instrument = new CToneInstrument();
			instrument = m_tonefactory.CreateInstrument();
		}
		
		else if (note->Instrument() == L"DrumInstrument")
		{
			m_drumfactory.SetNote(note);
			instrument = m_drumfactory.CreateInstrument();
		}
		else if (note->Instrument() == L"Additive")
		{
			instrument = new CAdditive();
		}
		else if (note->Instrument() == L"Subtractive")
		{
			instrument = new CSubtractive();
		}
		/// TODO
		/// check if not is each of the effects

		// Configure the instrument object
		if (instrument != NULL)
		{
			instrument->SetSampleRate(GetSampleRate());
			instrument->Setbpm(GetBpm());
			instrument->SetNote(note);
			instrument->Start();

			m_instruments.push_back(instrument);
		}

		m_currentNote++;
	}

	//
	// Phase 2: Clear all channels to silence 
	//
	double channelFrames[NUMEFFECTCHANNELS][2];
	for (int i = 0; i < NUMEFFECTCHANNELS; i++)
	{
		for (int c = 0; c < GetNumChannels(); c++)
		{
			channelFrames[i][c] = 0;
			frame[c] = 0;
		}
	}


	//
	// Phase 3: Play an active instruments
	//

	//
	// We have a list of active (playing) instruments.  We iterate over 
	// that list.  For each instrument we call generate, then add the
	// output to our output frame.  If an instrument is done (Generate()
	// returns false), we remove it from the list.
	//

	for (list<CInstrument *>::iterator node = m_instruments.begin(); node != m_instruments.end(); )
	{
		// Since we may be removing an item from the list, we need to know in 
		// advance, what is after it in the list.  We keep that node as "next"
		list<CInstrument *>::iterator next = node;
		next++;

		// Get a pointer to the allocated instrument
		CInstrument *instrument = *node;

		// Call the generate function
		if (instrument->Generate())
		{
			// If we returned true, we have a valid sample.  Add it 
			// to the frame.
			for (int i = 0; i < NUMEFFECTCHANNELS; i++)
			{
				for (int c = 0; c < GetNumChannels(); c++)
				{
					channelFrames[i][c] += instrument->Frame(c) *instrument->Send(i);	///TODO send
				}
			}

		}
		else
		{
			// If we returned false, the instrument is done.  Remove it
			// from the list and delete it from memory.
			m_instruments.erase(node);
			delete instrument;
		}

		// Move to the next instrument in the list
		node = next;
	}


	//
	// Phase 3-2: Effects
	//
	double gateframe[2];
	m_gate.Process(gateframe, channelFrames[1]);

	double compressionframe[2];
	m_compression.Process(compressionframe, channelFrames[2]);

	double chorusframe[2];
	m_chorus.Process(chorusframe, channelFrames[3]);

	double flangeframe[2];
	m_flange.Process(flangeframe, channelFrames[4]);

	for (int c = 0; c < 2; c++)
	{
		frame[c] += channelFrames[0][c] +  gateframe[c] + compressionframe[c] + flangeframe[c] + chorusframe[c];
	}
	//
	// Phase 4: Advance the time and beats
	//

	// Time advances by the sample period
	m_time += GetSamplePeriod();

	// Beat advances by the sample period divided by the 
	// number of seconds per beat.  The inverse of seconds
	// per beat is beats per second.
	m_beat += GetSamplePeriod() / m_secperbeat;

	// When the measure is complete, we move to
	// a new measure.  We might be a fraction into
	// the new measure, so we subtract out rather 
	// than just setting to zero.
	if (m_beat > m_beatspermeasure)
	{
		m_beat -= m_beatspermeasure;
		m_measure++;
	}

	//
	// Phase 5: Determine when we are done
	//

	// We are done when there is nothing to play.  We'll put something more 
	// complex here later.
	return !m_instruments.empty() || m_currentNote < (int)m_notes.size();
}

void CSynthesizer::Clear(void)
{
	m_instruments.clear();
	m_notes.clear();
}

void CSynthesizer::OpenScore(CString & filename)
{
	Clear();

	//
	// Create an XML document
	//

	CComPtr<IXMLDOMDocument>  pXMLDoc;
	bool succeeded = SUCCEEDED(CoCreateInstance(CLSID_DOMDocument, NULL, CLSCTX_INPROC_SERVER,
		IID_IXMLDOMDocument, (void**)&pXMLDoc));
	if (!succeeded)
	{
		AfxMessageBox(L"Failed to create an XML document to use");
		return;
	}

	// Open the XML document
	VARIANT_BOOL ok;
	succeeded = SUCCEEDED(pXMLDoc->load(CComVariant(filename), &ok));
	if (!succeeded || ok == VARIANT_FALSE)
	{
		AfxMessageBox(L"Failed to open XML score file");
		return;
	}

	//
	// Traverse the XML document in memory!!!!
	// Top level tag is <score>
	//

	CComPtr<IXMLDOMNode> node;
	pXMLDoc->get_firstChild(&node);
	for (; node != NULL; NextNode(node))
	{
		// Get the name of the node
		CComBSTR nodeName;
		node->get_nodeName(&nodeName);

		if (nodeName == "score")
		{
			XmlLoadScore(node);
		}
	}

	sort(m_notes.begin(), m_notes.end());
}

void CSynthesizer::XmlLoadScore(IXMLDOMNode * xml)
{
	// Get a list of all attribute nodes and the
	// length of that list
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	xml->get_attributes(&attributes);
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

		if (name == L"bpm")
		{
			value.ChangeType(VT_R8);
			m_bpm = value.dblVal;
			m_secperbeat = 1 / (m_bpm / 60);
		}
		else if (name == L"beatspermeasure")
		{
			value.ChangeType(VT_I4);
			m_beatspermeasure = value.intVal;
		}

	}


	CComPtr<IXMLDOMNode> node;
	xml->get_firstChild(&node);
	for (; node != NULL; NextNode(node))
	{
		// Get the name of the node
		CComBSTR name;
		node->get_nodeName(&name);

		if (name == L"instrument")
		{
			XmlLoadInstrument(node);
		}
	}
}

void CSynthesizer::XmlLoadInstrument(IXMLDOMNode * xml)
{
	wstring instrument = L"";

	// Get a list of all attribute nodes and the
	// length of that list
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	xml->get_attributes(&attributes);
	long len;
	attributes->get_length(&len);

	double effects[NUMEFFECTCHANNELS] = { 1,0,0,0,0 };
	// Loop over the list of attributes
	for (int i = 0; i<len; i++)
	{
		// Get attribute i
		CComPtr<IXMLDOMNode> attrib;
		attributes->get_item(i, &attrib);

		// Get the name of the attribute
		CComBSTR name;
		attrib->get_nodeName(&name);

		// Get the value of the attribute.  
		CComVariant value;
		attrib->get_nodeValue(&value);

		if (name == "instrument")
		{
			instrument = value.bstrVal;
		}
		else if (name == "dry")
		{
			value.ChangeType(VT_R8);
			effects[0] = value.dblVal;
		}
		else if (name == "gateing")
		{
			value.ChangeType(VT_R8);
			effects[1] = value.dblVal;
		}
		else if (name == "compression")
		{
			value.ChangeType(VT_R8);
			effects[2] = value.dblVal;
		}
		else if (name == "chorus")
		{
			value.ChangeType(VT_R8);
			effects[3] = value.dblVal;
		}
		else if (name == "flange")
		{
			value.ChangeType(VT_R8);
			effects[4] = value.dblVal;
		}
	}

	SetEffects(instrument, effects);

	CComPtr<IXMLDOMNode> node;
	xml->get_firstChild(&node);
	for (; node != NULL; NextNode(node))
	{
		// Get the name of the node
		CComBSTR name;
		node->get_nodeName(&name);

		if (name == L"note")
		{
			XmlLoadNote(node, instrument);
		}

	}

}

void CSynthesizer::XmlLoadNote(IXMLDOMNode * xml, std::wstring & instrument)
{
	m_notes.push_back(CNote());
	m_notes.back().XmlLoad(xml, instrument);
}

void CSynthesizer::SetEffects(std::wstring & instrument, double * effects)
{

	if (instrument == L"DrumInstrument")
	{
		m_drumfactory.SetDry(effects[0]);
		m_drumfactory.SetGateing(effects[1]);
		m_drumfactory.SetCompression(effects[2]);
		m_drumfactory.SetReverb(effects[3]);
	}
	else if (instrument == L"ToneInstrument")
	{
		m_tonefactory.SetDry(effects[0]);
		m_tonefactory.SetGateing(effects[1]);
		m_tonefactory.SetCompression(effects[2]);
		m_tonefactory.SetChorus(effects[3]);
		m_tonefactory.SetFlange(effects[3]);
	}
	
}
