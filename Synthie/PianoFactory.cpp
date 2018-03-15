#include "stdafx.h"
#include "PianoFactory.h"
#include "audio/DirSoundSource.h"
#include <filesystem>
namespace fs = std::experimental::filesystem;

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

	// Set Effect values
	instrument->SetSend(0, m_dry);
	instrument->SetSend(1, m_gateing);

	return instrument;
}

void CPianoFactory::GetFiles()
{
	namespace stdfs = std::experimental::filesystem;
	const stdfs::directory_iterator end{};
	std::experimental::filesystem::path path = "CompletePiano";

	for (stdfs::directory_iterator iter(path); iter != end; ++iter)
	{
		if (stdfs::is_regular_file(*iter)) 
			files.push_back(iter->path().c_str());
	}
}

bool CPianoFactory::LoadFile()
{
	m_piano.clear();
	
	CDirSoundSource m_file;
	GetFiles();

	for (auto filename:files)
	{
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
			// Load all piano sample into wavetable
			m_piano.push_back(frame[0]);
		}

		m_file.Close();
	}
	
	return true;
}

void CPianoFactory::SetNote(CNote *note)
{
}