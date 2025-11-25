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
class DraggableBox : public juce::Component
{
public:
    DraggableBox (int number, juce::DragAndDropContainer& containerIn)
        : boxNumber (number), dndContainer (containerIn) {}

    void paint (juce::Graphics& g) override
    {
        g.fillAll (juce::Colours::black);
        g.setColour (juce::Colours::white);
        g.setFont (juce::Font (16.0f, juce::Font::bold));
        g.drawText (juce::String (boxNumber), getLocalBounds(), juce::Justification::centred);
    }

    void mouseDown (const juce::MouseEvent&) override
    {
        dndContainer.startDragging (juce::String (boxNumber), this);
    }

private:
    int boxNumber;
    juce::DragAndDropContainer& dndContainer;
};

//==============================================================================
// Drop area
class DropArea : public juce::Component,
                 public juce::DragAndDropTarget
{
public:
    DropArea() {}

    void paint (juce::Graphics& g) override
    {
        g.fillAll (isDragOver ? juce::Colours::darkred : juce::Colours::black);

        g.setColour (juce::Colours::white);
        g.setFont (juce::Font (18.0f, juce::Font::bold));
        g.drawText ("Drop Here", getLocalBounds().removeFromTop (40),
                    juce::Justification::centred, false);

        g.setFont (14.0f);
        g.drawText ("Last Dropped : " + juce::String (lastDropped),
                    getLocalBounds().removeFromBottom (30),
                    juce::Justification::centred, false);
    }

    bool isInterestedInDragSource (const SourceDetails&) override { return true; }
    void itemDragEnter (const SourceDetails&) override { isDragOver = true; repaint(); }
    void itemDragExit  (const SourceDetails&) override { isDragOver = false; repaint(); }
    void itemDropped   (const SourceDetails& details) override
    {
        isDragOver = false;
        lastDropped = details.description.toString().getIntValue();
        repaint();
    }

private:
    bool isDragOver = false;
    int lastDropped = 0;
};

class TrainPIAudioProcessorEditor  : public juce::AudioProcessorEditor,public juce::DragAndDropContainer{
public:
    TrainPIAudioProcessorEditor (TrainPIAudioProcessor&);
    ~TrainPIAudioProcessorEditor() override;
    void paint(juce::Graphics&) override;
    void resized() override;

private:
    TrainPIAudioProcessor& audioProcessor;

    DraggableBox box1 {1, *this}, box2 {2, *this}, box3 {3, *this}, box4 {4, *this};
    DropArea dropArea;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrainPIAudioProcessorEditor)
};
