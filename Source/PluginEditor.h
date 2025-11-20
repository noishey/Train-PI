/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include <ea_events/Events/SharedTimer.h>

//==============================================================================
/**
*/

class TrainPIAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    TrainPIAudioProcessorEditor (TrainPIAudioProcessor&);
    ~TrainPIAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    TrainPIAudioProcessor& audioProcessor;

    int currentNote = -1;

    EA::AtomicListener<int> listener;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrainPIAudioProcessorEditor)
};
