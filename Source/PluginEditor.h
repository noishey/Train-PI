#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include <ea_data_structures/Structures/OwnedVector.h>

class RowComponent : public juce::Component
{
public:
    RowComponent(int idx = 0) : index(idx) { setSize(300, rowHeight); }
    void setIndex(int i) { index = i; repaint(); }
    int getIndex() const { return index; }

    void paint(juce::Graphics& g) override
    {
        auto r = getLocalBounds().reduced(6, 6);
        g.setColour(juce::Colours::white);
        g.fillRoundedRectangle(r.toFloat(), 3.f);
        g.setColour(juce::Colours::black);
        g.setFont(juce::Font(16.f, juce::Font::bold));
        g.drawText(juce::String(index), r, juce::Justification::centred);
    }

    static constexpr int rowHeight = 36;

private:
    int index = 0;
};

class ContentComponent : public juce::Component
{
public:
    void paint(juce::Graphics& g) override
    {
        g.fillAll(juce::Colour::fromString ("FF009987"));
    }
};

class ViewportRowsComponent : public juce::Component, public juce::Button::Listener
{
public:
    ViewportRowsComponent()
    {
        addAndMakeVisible(addButton);
        addAndMakeVisible(deleteButton);
        addAndMakeVisible(viewport);
        addButton.setButtonText("+ Add Row");
        addButton.setColour(juce::TextButton::buttonColourId, juce::Colours::white);
        addButton.setColour(juce::TextButton::textColourOffId, juce::Colours::black);
        deleteButton.setButtonText("Delete Row");
        deleteButton.setColour(juce::TextButton::buttonColourId, juce::Colours::white);
        deleteButton.setColour(juce::TextButton::textColourOffId, juce::Colours::black);
        addButton.addListener(this);
        deleteButton.addListener(this);
        while (rowsSize() < minRows) addRow();
        updateContentSize();
    }

    ~ViewportRowsComponent()
    {
        addButton.removeListener(this);
        deleteButton.removeListener(this);
        clearAllRows();
    }

    void resized() override
    {
        auto a = getLocalBounds().reduced(8);
        auto h = a.removeFromTop(36);
        addButton.setBounds(h.removeFromLeft(120).reduced(4));
        deleteButton.setBounds(h.removeFromLeft(120).reduced(4));
        viewport.setBounds(a);
        updateContentSize();
    }

    void buttonClicked(juce::Button* b) override
    {
        if (b == &addButton) addRow();
        else if (b == &deleteButton) deleteRow();
    }

    void saveStateToMemoryBlock(juce::MemoryBlock& dest)
    {
        juce::XmlElement xml("ViewportRowsState");
        xml.setAttribute("rowCount", rowsSize());
        TrainPIAudioProcessor::copyXmlToBinary(xml, dest);
    }

    void loadStateFromMemoryBlock(const juce::MemoryBlock& data)
    {
        if (data.getSize() == 0) return;
        auto xml = TrainPIAudioProcessor::getXmlFromBinary(data.getData(), (int)data.getSize());
        if (xml && xml->hasTagName("ViewportRowsState"))
        {
            int count = juce::jmax(minRows, xml->getIntAttribute("rowCount", minRows));
            clearAllRows();
            for (int i = 0; i < count; ++i) addRow();
        }
    }

private:
    EA::OwnedVector<RowComponent> rows;
    ContentComponent content;
    juce::Viewport viewport;
    juce::TextButton addButton, deleteButton;

    static constexpr int minRows = 5;

    int rowsSize() const { return rows.size(); }

    void addRow()
    {
        int idx = rowsSize() + 1;
        auto& r = rows.createNew(idx);
        content.addAndMakeVisible(&r);
        layoutRows();
        updateContentSize();
    }

    void deleteRow()
    {
        if (rowsSize() <= minRows) return;
        int i = rowsSize() - 1;
        if (auto* r = rows.get(i).get()) content.removeChildComponent(r);
        rows.removeAt(i);
        layoutRows();
        updateContentSize();
    }

    void clearAllRows()
    {
        for (int i = rows.getLastElementIndex(); i >= 0; --i)
            if (auto* r = rows.get(i).get()) content.removeChildComponent(r);
        rows.clear();
    }

    void layoutRows()
    {
        int w = juce::jmax(200, viewport.getViewWidth());
        int h = RowComponent::rowHeight;
        for (int i = 0; i < rowsSize(); ++i)
            if (auto* r = rows.get(i).get())
                r->setBounds(11, i * (h + 6), 142, h),
                r->setIndex(i + 1);
    }

    void updateContentSize()
    {
        int h = RowComponent::rowHeight;
        int total = rowsSize() * (h + 6) + 12;
        int w = getWidth() - 32;
        content.setSize(w > 0 ? w : 300, total);
        viewport.setViewedComponent(&content, false);
        layoutRows();
    }
};

class TrainPIAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    TrainPIAudioProcessorEditor(TrainPIAudioProcessor&);
    ~TrainPIAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    ViewportRowsComponent* getViewportComponent() { return viewportComponent.get(); }

private:
    TrainPIAudioProcessor& audioProcessor;
    std::unique_ptr<ViewportRowsComponent> viewportComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TrainPIAudioProcessorEditor)
};
