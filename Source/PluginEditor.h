/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class TrainPIAudioProcessorEditor  : public juce::AudioProcessorEditor,public juce::DragAndDropContainer{
public:
    TrainPIAudioProcessorEditor (TrainPIAudioProcessor&);
    ~TrainPIAudioProcessorEditor() override;
    void paint(juce::Graphics&) override;
    void resized() override;
    
private:
    TrainPIAudioProcessor& audioProcessor;

    juce::TextButton addButton { "+ Add 1" };
    juce::TextButton subtractButton { "- Subtract 1" };
    juce::Label counterLabel;
    
    void updateLabel();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrainPIAudioProcessorEditor)
};
