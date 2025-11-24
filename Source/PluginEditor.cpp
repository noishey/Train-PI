/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
TrainPIAudioProcessorEditor::TrainPIAudioProcessorEditor (TrainPIAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p), svgIcon1("IconOpenPlugin.svg", true)
{
    addAndMakeVisible(svgIcon1);
    setSize(800, 600);
}

TrainPIAudioProcessorEditor::~TrainPIAudioProcessorEditor() {}

void TrainPIAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.setColour(Colours::yellow);

    AffineTransform t = AffineTransform::scale(
        37.0f / svgIcon4.getBounds().getWidth(),
        38.0f / svgIcon4.getBounds().getHeight()
    ).translated(417, 112);

    g.fillPath(svgIcon4, t);
}

void TrainPIAudioProcessorEditor::resized()
{
    svgIcon1.setBounds(75, 111, 40, 40);
}

