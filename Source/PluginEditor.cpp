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

NoteButton::NoteButton(const juce::String& labelText,
                       int midiNote,
                       TrainPIAudioProcessor& p)
: processor(p), label(labelText), note(midiNote)
{
}

void NoteButton::paint(juce::Graphics& g)
{
    auto area = getLocalBounds().toFloat();
    g.setColour(isPressed ? juce::Colours::darkgrey : juce::Colours::lightgrey);
    g.fillRoundedRectangle(area, 20.0f);

    g.setColour(juce::Colours::black);
    g.setFont(18.0f);
    g.drawFittedText(label, getLocalBounds(), juce::Justification::centred, 1);
}

void NoteButton::mouseDown(const juce::MouseEvent&)
{
    isPressed = true;
    processor.sendNoteOn(note);
    repaint();
}

void NoteButton::mouseUp(const juce::MouseEvent&)
{
    isPressed = false;
    processor.sendNoteOff(note);
    repaint();
}
//==============================================================================
TrainPIAudioProcessorEditor::TrainPIAudioProcessorEditor (TrainPIAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p), c3("C3", 60, p),
        d3("D3", 62, p),
        e3("E3", 64, p),
        f3("F3", 65, p)
{
    addAndMakeVisible(c3);
    addAndMakeVisible(d3);
    addAndMakeVisible(e3);
    addAndMakeVisible(f3);

    setSize(900, 500);
    startTimerHz(30);
}

void TrainPIAudioProcessorEditor::timerCallback()
{
    // Just repaint the editor so paint() reads the latest state atomics.
    // Keep the method tiny (fast) — it just triggers a repaint on UI thread.
    repaint();
}

TrainPIAudioProcessorEditor::~TrainPIAudioProcessorEditor() {}

void TrainPIAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour::fromRGB(120, 150, 255));

    // Display box
    auto box = juce::Rectangle<int>(350, 200, 300, 100);
    g.setColour(juce::Colours::white);
    g.fillRoundedRectangle(box.toFloat(), 15.0f);

    g.setColour(juce::Colours::black);
    g.setFont(20.0f);
    g.drawFittedText("Midi Received", box.removeFromTop(40),
                     juce::Justification::centred, 1);

    // Show last message
    int lastNote = audioProcessor.state.lastNoteNumber.load();
    bool lastOn = audioProcessor.state.lastNoteOn.load();

    juce::String msg =
        (lastOn ? "Note On : " : "Note Off : ")
        + getNoteName(lastNote);

    g.setColour(juce::Colours::red);
    g.drawFittedText(msg, box, juce::Justification::centred, 1);
}

void TrainPIAudioProcessorEditor::resized()
{
    int leftX = 80;
        int y = 80;

        c3.setBounds(leftX, y, 120, 60);
        d3.setBounds(leftX, y + 100, 120, 60);
        e3.setBounds(leftX, y + 200, 120, 60);
        f3.setBounds(leftX, y + 300, 120, 60);
}
