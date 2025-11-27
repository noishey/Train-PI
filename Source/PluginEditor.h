/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include <ea_data_structures/Pointers/OwningPointer.h>

//==============================================================================
/**
*/
struct Tab1Component : public juce::Component
{
    void paint(juce::Graphics& g) override
    {
        g.fillAll(juce::Colours::darkgrey);
        g.setColour(juce::Colours::white);
        g.drawFittedText("TAB 1", getLocalBounds(), juce::Justification::centred, 1);
    }
};

struct Tab2Component : public juce::Component
{
    void paint(juce::Graphics& g) override
    {
        g.fillAll(juce::Colours::darkgreen);
        g.setColour(juce::Colours::white);
        g.drawFittedText("TAB 2", getLocalBounds(), juce::Justification::centred, 1);
    }
};

struct Tab3Component : public juce::Component
{
    void paint(juce::Graphics& g) override
    {
        g.fillAll(juce::Colours::darkred);
        g.setColour(juce::Colours::white);
        g.drawFittedText("TAB 3", getLocalBounds(), juce::Justification::centred, 1);
    }
};

class TrainPIAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    TrainPIAudioProcessorEditor (TrainPIAudioProcessor&);
    ~TrainPIAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    TrainPIAudioProcessor& audioProcessor;
    juce::TextButton tab1Button { "TAB 1" };
    juce::TextButton tab2Button { "TAB 2" };
    juce::TextButton tab3Button { "TAB 3" };

    juce::Rectangle<int> tabBounds;

    EA::OwningPointer<juce::Component> window;

    void switchToTab(int index);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrainPIAudioProcessorEditor)
};
