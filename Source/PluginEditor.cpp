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
    
    // --- 1. Normal Button ---
    normalButton.setDefaultImage        ("OffState.png");
    normalButton.setDefaultHoveredImage ("HoveredOff.png");
    normalButton.setClickedImage        ("Clicked.png");
    normalButton.setToggledOnImage      ("OnState.png");
    normalButton.setHoveredOnImage      ("HoveredOn.png");
    addAndMakeVisible (normalButton);

    // --- 2. Toggle Button ---
    toggleButton.setDefaultImage        ("OffState.png");
    toggleButton.setToggledOnImage      ("OnState.png");
    toggleButton.setDefaultHoveredImage ("HoveredOff.png");
    toggleButton.setHoveredOnImage      ("HoveredOn.png");
    toggleButton.setClickedImage        ("Clicked.png");
    toggleButton.setMouseUpCallback ([] (const juce::MouseEvent&, bool& state)
    {
        state = !state;
        DBG ("Toggle Button is now " << (state ? "ON" : "OFF"));
    });
    addAndMakeVisible (toggleButton);

    // --- 3. Switch Button ---
    switchButton.setDefaultImage        ("OffState.png");
    switchButton.setToggledOnImage      ("OnState.png");
    switchButton.setDefaultHoveredImage ("HoveredOff.png");
    switchButton.setHoveredOnImage      ("HoveredOn.png");
    switchButton.setClickedImage        ("Clicked.png");
    switchButton.setMouseUpCallback ([] (const juce::MouseEvent&, bool& state)
    {
        state = !state;
        DBG ("Switch toggled: " << (state ? "ON" : "OFF"));
    });
    addAndMakeVisible (switchButton);

    // --- 4. Unclickable Button ---
    unclickableButton.setUnclickable (true);
    unclickableButton.setUnclickableImage ("Unclickable.png");
    addAndMakeVisible (unclickableButton);
    
    setSize(600, 400);

}

TrainPIAudioProcessorEditor::~TrainPIAudioProcessorEditor() {}

void TrainPIAudioProcessorEditor::paint(juce::Graphics& g)
{
}

void TrainPIAudioProcessorEditor::resized()
{
    normalButton.setBounds      (22, 17, 131, 36);
    toggleButton.setBounds      (22, 82, 131, 36);
    switchButton.setBounds      (22, 141, 131, 36);
    unclickableButton.setBounds (22, 193, 131, 36);
}

