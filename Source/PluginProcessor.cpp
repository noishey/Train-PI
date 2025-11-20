#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================

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
}

TrainPIAudioProcessor::~TrainPIAudioProcessor() {}

//==============================================================================

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

//==============================================================================

int TrainPIAudioProcessor::getNumPrograms() { return 1; }
int TrainPIAudioProcessor::getCurrentProgram() { return 0; }
void TrainPIAudioProcessor::setCurrentProgram (int) {}
const juce::String TrainPIAudioProcessor::getProgramName (int) { return {}; }
void TrainPIAudioProcessor::changeProgramName (int, const juce::String&) {}

//==============================================================================

void TrainPIAudioProcessor::prepareToPlay (double, int) {}
void TrainPIAudioProcessor::releaseResources() {}

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

//==============================================================================

void TrainPIAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                          juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;

    // Clear audio (silent plugin)
    buffer.clear();

    // Read incoming MIDI
    for (const auto meta : midiMessages)
    {
        const auto msg = meta.getMessage();

        if (msg.isNoteOn())
        {
            int note = msg.getNoteNumber();
            state.lastNoteNumber.store(note);
        }
    }
}

//==============================================================================

bool TrainPIAudioProcessor::hasEditor() const { return true; }

juce::AudioProcessorEditor* TrainPIAudioProcessor::createEditor()
{
    return new TrainPIAudioProcessorEditor (*this);
}

//==============================================================================

void TrainPIAudioProcessor::getStateInformation (juce::MemoryBlock&) {}
void TrainPIAudioProcessor::setStateInformation (const void*, int) {}

//==============================================================================

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TrainPIAudioProcessor();
}
