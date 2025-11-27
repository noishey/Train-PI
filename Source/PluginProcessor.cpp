#include "PluginProcessor.h"
#include "PluginEditor.h"

struct SimpleSynthSound : public juce::SynthesiserSound
{
    bool appliesToNote (int /*midiNoteNumber*/) override        { return true; }
    bool appliesToChannel (int /*midiChannel*/) override       { return true; }
};

TrainPIAudioProcessor::TrainPIAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    for (int i = 0; i < 8; ++i)
        synth.addVoice(new OscillatorVoice());
    synth.addSound(new SimpleSynthSound());
    createSamplerFromGeneratedBuffer(44100.0);
}

TrainPIAudioProcessor::~TrainPIAudioProcessor()
{
}

const juce::String TrainPIAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TrainPIAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TrainPIAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TrainPIAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TrainPIAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TrainPIAudioProcessor::getNumPrograms()
{
    return 1;
}

int TrainPIAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TrainPIAudioProcessor::setCurrentProgram (int index)
{
    juce::ignoreUnused(index);
}

const juce::String TrainPIAudioProcessor::getProgramName (int index)
{
    juce::ignoreUnused(index);
    return {};
}

void TrainPIAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused(index, newName);
}

void TrainPIAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);
    for (int i = 0; i < synth.getNumVoices(); ++i)
        if (auto* v = dynamic_cast<OscillatorVoice*>(synth.getVoice(i)))
            v->setSampleRate(sampleRate);

    samplerSynth.setCurrentPlaybackSampleRate(sampleRate);
    createSamplerFromGeneratedBuffer(sampleRate);
}

void TrainPIAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TrainPIAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void TrainPIAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    juce::AudioPlayHead::CurrentPositionInfo posInfo;
    if (getPlayHead() != nullptr && getPlayHead()->getCurrentPosition(posInfo))
    {
        const juce::ScopedLock sl(playHeadLock);
        lastPlayHeadInfo.bpm = posInfo.bpm;
        lastPlayHeadInfo.ppqPosition = posInfo.ppqPosition;
        lastPlayHeadInfo.timeSigNumerator = posInfo.timeSigNumerator;
        lastPlayHeadInfo.timeSigDenominator = posInfo.timeSigDenominator;
        lastPlayHeadInfo.isPlaying = posInfo.isPlaying;
    }

    keyboardState.processNextMidiBuffer(midiMessages, 0, buffer.getNumSamples(), true);

    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    samplerSynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

void TrainPIAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    juce::ignoreUnused(destData);
}

void TrainPIAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    juce::ignoreUnused(data, sizeInBytes);
}

TrainPIAudioProcessor::PlayHeadInfo TrainPIAudioProcessor::getPlayHeadInfo()
{
    const juce::ScopedLock sl(playHeadLock);
    return lastPlayHeadInfo;
}

void TrainPIAudioProcessor::createSamplerFromGeneratedBuffer(double sampleRate)
{
    samplerSynth.clearSounds();
    samplerSynth.clearVoices();

    for (int i = 0; i < 8; ++i)
        samplerSynth.addVoice(new juce::SamplerVoice());

    const int length = (int) std::round(sampleRate); // 1 second
    juce::AudioBuffer<float> buffer(1, length);
    buffer.clear();

    for (int i = 0; i < length; ++i)
    {
        float t = (float)i / (float)length;
        float value = std::sin(juce::MathConstants<float>::twoPi * 440.0f * t) * std::exp(-3.0f * t);
        buffer.setSample(0, i, value);
    }

    // Write buffer into an in-memory WAV
    juce::WavAudioFormat wavFormat;
    juce::MemoryOutputStream memOut(true);

    {
        std::unique_ptr<juce::AudioFormatWriter> writer (
            wavFormat.createWriterFor(&memOut,
                                      sampleRate,
                                      (unsigned int) buffer.getNumChannels(),
                                      16,
                                      {}, 0));

        if (writer == nullptr)
            return;

        writer->writeFromAudioSampleBuffer(buffer, 0, buffer.getNumSamples());
        writer.reset(); // flush and finalize WAV into memOut
    }

    // Make MemoryInputStream own its copy of the data (avoid referencing memOut's internal buffer)
    auto* memIn = new juce::MemoryInputStream(memOut.getData(), memOut.getDataSize(), true);

    // createReaderFor takes a raw InputStream*, so hand memIn to it and tell reader to delete the stream
    auto* readerRaw = wavFormat.createReaderFor(memIn, true);

    if (readerRaw != nullptr)
    {
        std::unique_ptr<juce::AudioFormatReader> reader(readerRaw);

        juce::BigInteger allNotes;
        allNotes.setRange(0, 128, true);

        auto* sound = new juce::SamplerSound("gen", *reader, allNotes, 60, 0.0, 0.0, 10.0);
        samplerSynth.addSound(sound);
    }
}

void TrainPIAudioProcessor::setSynthWaveform (int newWaveform) noexcept
{
    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto* v = dynamic_cast<OscillatorVoice*>(synth.getVoice(i)))
            v->setWaveform(newWaveform);
    }
}

bool TrainPIAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* TrainPIAudioProcessor::createEditor()
{
    return new TrainPIAudioProcessorEditor(*this);
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TrainPIAudioProcessor();
}
