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
class TrainPIAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    TrainPIAudioProcessorEditor (TrainPIAudioProcessor&);
    ~TrainPIAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void showWindow1();
    void showWindow2();

private:
    TrainPIAudioProcessor& audioProcessor;

    class Window : public juce::Component
    {
    public:
        enum class Type { One, Two };

        Window(TrainPIAudioProcessorEditor& e, Type t)
            : editor(e), type(t)
        {
            addAndMakeVisible(btn);
            applyTypeSettings();

            btn.onClick = [&] {
                switch (type)
                {
                    case Type::One: editor.showWindow2(); break;
                    case Type::Two: editor.showWindow1(); break;
                }
            };
        }

        void paint(juce::Graphics& g) override
        {
            g.fillAll(bgColour);
            g.setColour(juce::Colours::white);
            g.drawText(title, getLocalBounds(), juce::Justification::centred);
        }

        void resized() override
        {
            btn.setBounds(210, 0, 140, 50);
        }

    private:
        TrainPIAudioProcessorEditor& editor;
        juce::TextButton btn;
        Type type;
        juce::Colour bgColour;
        juce::String title;

        void applyTypeSettings()
        {
            switch (type)
            {
                case Type::One:
                    bgColour = juce::Colours::darkslategrey;
                    title    = "Window 1";
                    btn.setButtonText("Create Window 2");
                    break;

                case Type::Two:
                    bgColour = juce::Colours::darkmagenta;
                    title    = "Window 2";
                    btn.setButtonText("Create Window 1");
                    break;
            }
        }
    };

    EA::OwningPointer<juce::Component> currentWindow;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrainPIAudioProcessorEditor)
};
