#include "stdafx.h"
#include "PianoFactory.h"
#include "audio/DirSoundSource.h"

CPianoFactory::CPianoFactory()
{
	for (double time = 0; time<2; time += 1. / 44100.)
	{
		m_piano.push_back(short(3267 * sin(2 * 3.1415 * 1000 * time)));
	}
}


CPianoFactory::~CPianoFactory()
{
}

CPiano *CPianoFactory::CreateInstrument()
{
	CPiano *instrument = new CPiano();
	instrument->GetPlayer()->SetSamples(&m_piano[0], (int)m_piano.size());

	return instrument;
}

bool CPianoFactory::LoadFile(const char * filename)
{
	m_piano.clear();

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
		m_piano.push_back(frame[0]);
	}

	m_file.Close();
	return true;
}

void CPianoFactory::SetNote(CNote *note)
{
}