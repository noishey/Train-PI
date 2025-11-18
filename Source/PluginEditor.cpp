/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
TrainPIAudioProcessorEditor::TrainPIAudioProcessorEditor (TrainPIAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    setSize(400, 300);
    showWindow1();
}

TrainPIAudioProcessorEditor::~TrainPIAudioProcessorEditor() {}

void TrainPIAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void TrainPIAudioProcessorEditor::resized()
{
    if (currentWindow)
        currentWindow->setBounds(getLocalBounds());
}

void TrainPIAudioProcessorEditor::showWindow1()
{
    currentWindow.reset();
    currentWindow = new Window(*this, Window::Type::One);
    addAndMakeVisible(currentWindow.get());
    resized();
}

void TrainPIAudioProcessorEditor::showWindow2()
{
    currentWindow.reset();
    currentWindow = new Window(*this, Window::Type::Two);
    addAndMakeVisible(currentWindow.get());
    resized();
}
