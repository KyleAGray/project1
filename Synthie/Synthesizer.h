#pragma once
#include <list>
#include <vector>
#include "Instrument.h"
#include "Note.h"
#include "EffectNoisGrate.h"
#include "EfectCompression.h"
#include "ReverbEffect.h"
#include "DrumFactory.h"
#include "ToneInstrumentFactory.h"

using namespace std;

// Effect Channels
// 0 -> no effect
// 1 -> grating (actually gating but I can't spell)
//const int NUMEFFECTCHANNELS = 2;

class CSynthesizer
{
public:
	CSynthesizer();
	virtual ~CSynthesizer();

	void Start(void);

	bool Generate(double * frame);

	void Clear(void);

	void OpenScore(CString & filename);

	

	//! Number of audio channels
	int GetNumChannels() { return m_channels; }

	//! Sample rate in samples per second
	double GetSampleRate() { return m_sampleRate; }

	//! Sample period in seconds (1/samplerate)
	double GetSamplePeriod() { return m_samplePeriod; }

	//! Set the number of channels
	void SetNumChannels(int n) { m_channels = n; }

	//! Set the sample rate
	void SetSampleRate(double s) { m_sampleRate = s;  m_samplePeriod = 1.0 / s; }

	//! Get the time since we started generating audio
	double GetTime() { return m_time; }

	//! Get the beats per minute
	double GetBpm() { return m_bpm; }

private:
	int		m_channels;
	double	m_sampleRate;
	double	m_samplePeriod;
	double m_time;	// Current time
	std::list<CInstrument *>  m_instruments;
	double  m_bpm;                  //!< Beats per minute
	int     m_beatspermeasure;  //!< Beats per measure
	double  m_secperbeat;        //!< Seconds per beat
	std::vector<CNote> m_notes;


	void XmlLoadScore(IXMLDOMNode * xml);
	void XmlLoadInstrument(IXMLDOMNode * xml);
	void XmlLoadNote(IXMLDOMNode * xml, std::wstring & instrument);
	void SetEffects(std::wstring & instrument, double * effects);

	int m_currentNote;          //!< The current note we are playing
	int m_measure;              //!< The current measure
	double m_beat;              //!< The current beat within the measure

	/// Gate effect
	CEffectNoisGrate m_gate;
	/// Compression effect
	CEfectCompression m_compression;
	/// Reverb effect
	CReverbEffect m_reverb;

	/// Instrument Facotries
	CDrumFactory m_drumfactory;
	CToneInstrumentFactory m_tonefactory;
};

