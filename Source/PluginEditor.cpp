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
    setSize(600, 400);
    addAndMakeVisible(tab1Button);
    addAndMakeVisible(tab2Button);
    addAndMakeVisible(tab3Button);

    tab1Button.onClick = [this] { switchToTab(1); };
    tab2Button.onClick = [this] { switchToTab(2); };
    tab3Button.onClick = [this] { switchToTab(3); };

    switchToTab(1);
}

TrainPIAudioProcessorEditor::~TrainPIAudioProcessorEditor() {
    if (window.get() != nullptr)
            removeChildComponent(window.get());
        window.reset();
}

void TrainPIAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void TrainPIAudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced(10);
    auto header = area.removeFromTop(35);

    tab1Button.setBounds(header.removeFromLeft(100));
    tab2Button.setBounds(header.removeFromLeft(100));
    tab3Button.setBounds(header.removeFromLeft(100));

    tabBounds = area;

    if (window.get() != nullptr)
        window->setBounds(tabBounds);
}

void TrainPIAudioProcessorEditor::switchToTab(int index)
{
    if (window.get() != nullptr)
        removeChildComponent(window.get());

    if (index == 1)
        window.create<Tab1Component>();
    else if (index == 2)
        window.create<Tab2Component>();
    else
        window.create<Tab3Component>();

    addAndMakeVisible(window.get());
    window->setBounds(tabBounds);

    tab1Button.setToggleState(index == 1, juce::dontSendNotification);
    tab2Button.setToggleState(index == 2, juce::dontSendNotification);
    tab3Button.setToggleState(index == 3, juce::dontSendNotification);
}
