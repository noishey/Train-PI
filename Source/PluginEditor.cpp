/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

static juce::String getNoteName (int note)
{
    if (note < 0 || note > 127)
        return "-";

    return juce::MidiMessage::getMidiNoteName(note, true, true, 3);
}

//==============================================================================

TrainPIAudioProcessorEditor::TrainPIAudioProcessorEditor (TrainPIAudioProcessor& p)
    : AudioProcessorEditor (&p), 
      audioProcessor (p),
      listener ( audioProcessor.state.lastNoteNumber,
                 [&]
                 {
                     currentNote = audioProcessor.state.lastNoteNumber.load();
                     repaint();
                 })
{
    setSize (400, 300);
}

TrainPIAudioProcessorEditor::~TrainPIAudioProcessorEditor() {}

//==============================================================================

void TrainPIAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::cyan);

    auto area = getLocalBounds();
    auto box = area.withSizeKeepingCentre (300, 120);

    // Green rounded rectangle
    g.setColour (juce::Colour::fromRGB (50, 120, 50));
    g.fillRoundedRectangle (box.toFloat(), 30.0f);

    g.setColour (juce::Colours::white);
    g.setFont (20.0f);

    juce::String numText  = "MIDI Note Number :  " + juce::String (currentNote);
    juce::String nameText = "MIDI Note Name :    " + getNoteName (currentNote);

    g.drawFittedText (numText,  box.reduced (20), juce::Justification::centredTop, 1);
    g.drawFittedText (nameText, box.reduced (20).withY (box.getY() + 50),
                      juce::Justification::centredTop, 1);
}

//==============================================================================
// IMPORTANT: resized() does NOT draw
void TrainPIAudioProcessorEditor::resized()
{
    // Leave empty unless you add components
}
