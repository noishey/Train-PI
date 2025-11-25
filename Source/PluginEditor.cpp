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
    addAndMakeVisible (box1);
    addAndMakeVisible (box2);
    addAndMakeVisible (box3);
    addAndMakeVisible (box4);
    addAndMakeVisible (dropArea);
}

TrainPIAudioProcessorEditor::~TrainPIAudioProcessorEditor() {}

void TrainPIAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkgrey);

}

void TrainPIAudioProcessorEditor::resized()
{
    box1.setBounds(36, 30, 120, 30);
    box2.setBounds(36, 90, 120, 30);
    box3.setBounds(36, 150, 120, 30);
    box4.setBounds(36, 210, 120, 30);

    dropArea.setBounds(231, 60, 228, 139);
}
