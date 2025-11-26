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
    setSize(800, 600);
    // Add Button
    addAndMakeVisible(addButton);
    addButton.onClick = [this]()
    {
        audioProcessor.counterValue++;
        updateLabel();
    };

    // Subtract Button
    addAndMakeVisible(subtractButton);
    subtractButton.onClick = [this]()
    {
        audioProcessor.counterValue--;
        updateLabel();
    };

    // Label
    addAndMakeVisible(counterLabel);
    counterLabel.setFont (juce::Font (24.0f, juce::Font::bold));
    counterLabel.setJustificationType (juce::Justification::centred);
    updateLabel();
}

TrainPIAudioProcessorEditor::~TrainPIAudioProcessorEditor() {}

void TrainPIAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkgrey);

}

void TrainPIAudioProcessorEditor::resized()
{
    addButton.setBounds (20, 20, 100, 30);
    subtractButton.setBounds (140, 20, 100, 30);
    counterLabel.setBounds (100, 80, 200, 50);
}

void TrainPIAudioProcessorEditor::updateLabel()
{
    counterLabel.setText (juce::String (audioProcessor.counterValue), juce::dontSendNotification);
}
