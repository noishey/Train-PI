/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class TrainPIAudioProcessor  : public juce::AudioProcessor
{
public:
    TrainPIAudioProcessor();
    ~TrainPIAudioProcessor() override;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;
    const juce::String getName() const override;
    double getTailLengthSeconds() const override;
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    
    struct PlayHeadInfo
    {
        double bpm{0.0};
        double ppqPosition{0.0};
        int timeSigNumerator{4};
        int timeSigDenominator{4};
        bool isPlaying{false};
    };

    PlayHeadInfo getPlayHeadInfo();
    void setSynthWaveform (int newWaveform) noexcept;
    juce::MidiKeyboardState keyboardState;

private:
    class OscillatorVoice : public juce::SynthesiserVoice
    {
    public:
        OscillatorVoice() {}
        bool canPlaySound (juce::SynthesiserSound* s) override { return dynamic_cast<juce::SynthesiserSound*> (s) != nullptr; }
        void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound*, int /*currentPitchWheelPosition*/) override
        {
            level = velocity;
            currentAngle = 0.0;
            angleDelta = juce::MathConstants<double>::twoPi * juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber) / sampleRate;
        }
        void stopNote (float /*velocity*/, bool allowRampDown) override
        {
            clearCurrentNote();
        }
        void pitchWheelMoved (int) override {}
        void controllerMoved (int, int) override {}
        void renderNextBlock (juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override
        {
            if (sampleRate <= 0.0) return;
            int localWave = waveform.load(std::memory_order_relaxed);
            for (int sample = 0; sample < numSamples; ++sample)
            {
                float value = 0.0f;
                if (waveform == 0)
                    value = (float) std::sin(currentAngle);
                else
                {
                    double s = std::sin(currentAngle);
                    value = (s >= 0.0) ? 1.0f : -1.0f;
                }
                currentAngle += angleDelta;
                for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
                    outputBuffer.addSample(channel, startSample + sample, value * level * 0.2f);
            }
        }
        void setSampleRate (double sr) { sampleRate = sr; }
        void setWaveform(int w) { waveform = w; }
        

    private:
        double sampleRate{44100.0};
        double currentAngle{0.0}, angleDelta{0.0};
        float level{0.0f};
        std::atomic<int> waveform{0};
    };

    juce::Synthesiser synth;
    juce::Synthesiser samplerSynth;

    juce::CriticalSection playHeadLock;
    PlayHeadInfo lastPlayHeadInfo;

    void createSamplerFromGeneratedBuffer(double sampleRate);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrainPIAudioProcessor)
};
