/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
TrainPIAudioProcessorEditor::TrainPIAudioProcessorEditor (TrainPIAudioProcessor& p)
    : AudioProcessorEditor(&p),
      audioProcessor(p)
{
    
    
    setSize (400, 300);
    showWindow1();
    setResizable(true, true);
}


TrainPIAudioProcessorEditor::~TrainPIAudioProcessorEditor()
{
}

//==============================================================================
void TrainPIAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::transparentBlack);
}

void TrainPIAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    if (currentWindow)
            currentWindow->setBounds(getLocalBounds());
    
}

void TrainPIAudioProcessorEditor::showWindow1()
{
    currentWindow.reset();
    currentWindow = std::make_unique<Window1>(*this);
    addAndMakeVisible(currentWindow.get());
    resized();
}

void TrainPIAudioProcessorEditor::showWindow2()
{
    currentWindow.reset();
    currentWindow = std::make_unique<Window2>(*this);
    addAndMakeVisible(currentWindow.get());
    resized();
}
