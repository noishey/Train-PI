/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginEditor.h"

struct Tab1_DawSyncComponent : public juce::Component, private juce::Timer
{
    Tab1_DawSyncComponent(TrainPIAudioProcessor& p) : proc(p)
    {
        startTimerHz(20);
        addAndMakeVisible(infoLabel);
        infoLabel.setJustificationType(juce::Justification::left);
    }
    void paint(juce::Graphics& g) override
    {
        g.fillAll(juce::Colours::darkslategrey);
        g.setColour(juce::Colours::white);
        auto r = getLocalBounds().reduced(12);
        g.fillRect(r.removeFromTop(r.proportionOfHeight(0.75f)));
        g.setColour(juce::Colours::black);
        g.fillRect(r.removeFromTop(24));
    }
    void resized() override
    {
        infoLabel.setBounds(getLocalBounds().removeFromBottom(60).reduced(8));
    }
    void timerCallback() override
    {
        auto info = proc.getPlayHeadInfo();
        juce::String s;
        s << "BPM: " << info.bpm << "    ppq pos: " << info.ppqPosition << "    time sig: "
          << info.timeSigNumerator << "/" << info.timeSigDenominator << "    playing: " << (info.isPlaying ? "yes" : "no");
        infoLabel.setText(s, juce::dontSendNotification);
    }
    TrainPIAudioProcessor& proc;
    juce::Label infoLabel;
};

struct Tab2_SynthComponent : public juce::Component
{
    Tab2_SynthComponent(TrainPIAudioProcessor& p) : proc(p), keyboardComponent(p.keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard)
    {
        addAndMakeVisible(waveToggle);
        waveToggle.addItem("Sine", 1);
        waveToggle.addItem("Square", 2);
        waveToggle.setSelectedId(1);
        waveToggle.onChange = [this] {
            int id = waveToggle.getSelectedId();
            setWaveform(id == 1 ? 0 : 1);
        };
        addAndMakeVisible(keyboardComponent);
    }
    void paint(juce::Graphics& g) override
    {
        g.fillAll(juce::Colours::lightgrey);
        g.setColour(juce::Colours::black);
        g.drawFittedText("Synth", getLocalBounds().withTrimmedTop(4).removeFromTop(24), juce::Justification::left, 1);
    }
    void resized() override
    {
        auto r = getLocalBounds().reduced(12);
        waveToggle.setBounds(r.removeFromTop(28).removeFromLeft(120));
        keyboardComponent.setBounds(getWidth() - 32, getHeight() - 120, getWidth() - 24, 100);
    }
    void setWaveform(int w)
    {
        proc.setSynthWaveform(w);
    }
    TrainPIAudioProcessor& proc;
    juce::ComboBox waveToggle;
    juce::MidiKeyboardComponent keyboardComponent;
};

struct Tab3_SamplerComponent : public juce::Component
{
    Tab3_SamplerComponent(TrainPIAudioProcessor& p) : proc(p), keyboardComponent(p.keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard)
    {
        addAndMakeVisible(nameLabel);
        nameLabel.setText("Sampler: Generated 1s kick-like", juce::dontSendNotification);
        addAndMakeVisible(keyboardComponent);
    }
    void paint(juce::Graphics& g) override
    {
        g.fillAll(juce::Colour::fromRGB(34,34,34));
        g.setColour(juce::Colours::orange);
        auto r = getLocalBounds().reduced(12);
        auto waveArea = r.removeFromTop(r.proportionOfHeight(0.7f));
        g.drawLine((float)waveArea.getX(), (float)waveArea.getCentreY(), (float)waveArea.getRight(), (float)waveArea.getCentreY(), 1.0f);
    }
    void resized() override
    {
        auto r = getLocalBounds().reduced(12);
        nameLabel.setBounds(r.removeFromTop(24));
        keyboardComponent.setBounds(getWidth() - 32, getHeight() - 120, getWidth() - 24, 100);
    }
    TrainPIAudioProcessor& proc;
    juce::Label nameLabel;
    juce::MidiKeyboardComponent keyboardComponent;
};

TrainPIAudioProcessorEditor::TrainPIAudioProcessorEditor (TrainPIAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (900, 620);
    addAndMakeVisible(topBox1);
    addAndMakeVisible(topBox2);
    addAndMakeVisible(topBox3);
    topBox1.setButtonText("TAB 1");
    topBox2.setButtonText("TAB 2");
    topBox3.setButtonText("TAB 3");
    topBox1.onClick = [this] { switchToTab(1); };
    topBox2.onClick = [this] { switchToTab(2); };
    topBox3.onClick = [this] { switchToTab(3); };
    switchToTab(1);
}

TrainPIAudioProcessorEditor::~TrainPIAudioProcessorEditor()
{
    window.reset();
}

void TrainPIAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colour::fromRGB (18, 18, 18));
}

void TrainPIAudioProcessorEditor::resized()
{
    topBox1.setBounds (60, 16, 120, 28);
    topBox2.setBounds (200, 16, 120, 28);
    topBox3.setBounds (340, 16, 120, 28);
    tabBounds = juce::Rectangle<int> (24, 56, getWidth() - 48, getHeight() - 80);
    if (window.get() != nullptr)
        window->setBounds(tabBounds);
}

void TrainPIAudioProcessorEditor::switchToTab(int index)
{
    if (window.get() != nullptr)
        removeChildComponent(window.get());

    if (index == 1) window.create<Tab1_DawSyncComponent>(audioProcessor);
    else if (index == 2) window.create<Tab2_SynthComponent>(audioProcessor);
    else window.create<Tab3_SamplerComponent>(audioProcessor);

    addAndMakeVisible(window.get());
    window->setBounds(tabBounds);

    topBox1.setToggleState(index == 1, juce::dontSendNotification);
    topBox2.setToggleState(index == 2, juce::dontSendNotification);
    topBox3.setToggleState(index == 3, juce::dontSendNotification);
}
