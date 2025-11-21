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

class NoteButton : public juce::Component
{
public:
    NoteButton(const juce::String& labelText, int midiNote,
               TrainPIAudioProcessor& p);

    void paint(juce::Graphics&) override;
    void mouseDown(const juce::MouseEvent&) override;
    void mouseUp(const juce::MouseEvent&) override;

private:
    TrainPIAudioProcessor& processor;
    juce::String label;
    int note;
    bool isPressed = false;
};

class TrainPIAudioProcessorEditor  : public juce::AudioProcessorEditor,private juce::Timer

{
public:
    TrainPIAudioProcessorEditor (TrainPIAudioProcessor&);
    ~TrainPIAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;


private:
    TrainPIAudioProcessor& audioProcessor;

    NoteButton c3, d3, e3, f3;
    void timerCallback() override; 

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrainPIAudioProcessorEditor)
};
