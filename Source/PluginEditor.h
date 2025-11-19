/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include <pi_gui/Buttons/ImageButton.h>

//==============================================================================
/**
*/
class TrainPIAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    TrainPIAudioProcessorEditor (TrainPIAudioProcessor&);
    ~TrainPIAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    

private:
    TrainPIAudioProcessor& audioProcessor;
    
    PI::ImageButton normalButton;
    PI::ImageButton toggleButton;
    PI::ImageButton switchButton;
    PI::ImageButton unclickableButton;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrainPIAudioProcessorEditor)
};
