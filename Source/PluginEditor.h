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

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void showWindow1();
    void showWindow2();
    

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TrainPIAudioProcessor& audioProcessor;
    
    class Window1 : public juce::Component
    {
        public:
            Window1(TrainPIAudioProcessorEditor& e) : editor(e)
            {
                addAndMakeVisible(btn);
                btn.setButtonText("Create Window 2");
                btn.onClick = [&] {
                    editor.showWindow2();
                };
            }
            
            void paint(juce::Graphics& g) override
            {
                g.fillAll(juce::Colours::darkslategrey);
                g.setColour(juce::Colours::white);
                g.drawText("Window 1", getLocalBounds(),
                           juce::Justification::centred);
            }

            void resized() override
            {
                btn.setBounds(210, 0, 140, 50);
            }
        
        private:
            TrainPIAudioProcessorEditor& editor;
            juce::TextButton btn;
    };
    
    class Window2 : public juce::Component
        {
        public:
            Window2(TrainPIAudioProcessorEditor& e) : editor(e)
            {
                addAndMakeVisible(btn);
                btn.setButtonText("Create Window 1");
                btn.onClick = [&] { editor.showWindow1(); };
            }

            void paint(juce::Graphics& g) override
            {
                g.fillAll(juce::Colours::darkmagenta);
                g.setColour(juce::Colours::white);
                g.drawText("Window 2", getLocalBounds(),
                           juce::Justification::centred);
            }

            void resized() override
            {
                btn.setBounds(210, 0, 140, 50);
            }

        private:
            TrainPIAudioProcessorEditor& editor;
            juce::TextButton btn;
        };
    
    EA::OwningPointer<juce::Component> currentWindow;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrainPIAudioProcessorEditor)
};
