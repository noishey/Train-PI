/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include <ea_data_structures/Pointers/OwningPointer.h>

class TrainPIAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    TrainPIAudioProcessorEditor (TrainPIAudioProcessor&);
    ~TrainPIAudioProcessorEditor() override;
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    TrainPIAudioProcessor& audioProcessor;

    juce::TextButton topBox1, topBox2, topBox3;
    juce::Rectangle<int> tabBounds;
    EA::OwningPointer<juce::Component> window;

    void switchToTab(int index);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrainPIAudioProcessorEditor)
};
