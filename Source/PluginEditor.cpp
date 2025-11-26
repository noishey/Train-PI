/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/
#include "PluginProcessor.h"
#include "PluginEditor.h"

TrainPIAudioProcessorEditor::TrainPIAudioProcessorEditor(TrainPIAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    viewportComponent = std::make_unique<ViewportRowsComponent>();
    addAndMakeVisible(*viewportComponent);
    setSize(600, 400);

    if (audioProcessor.savedState.getSize() > 0)
        viewportComponent->loadStateFromMemoryBlock(audioProcessor.savedState);
}

TrainPIAudioProcessorEditor::~TrainPIAudioProcessorEditor()
{
    if (viewportComponent)
        viewportComponent->saveStateToMemoryBlock(audioProcessor.savedState);
}

void TrainPIAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void TrainPIAudioProcessorEditor::resized()
{
    if (viewportComponent)
        viewportComponent->setBounds(getLocalBounds());
}
