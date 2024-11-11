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
class ADC24RockSolidReleasesAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    ADC24RockSolidReleasesAudioProcessorEditor (ADC24RockSolidReleasesAudioProcessor&);
    ~ADC24RockSolidReleasesAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ADC24RockSolidReleasesAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ADC24RockSolidReleasesAudioProcessorEditor)
};
