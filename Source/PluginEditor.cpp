/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ADC24RockSolidReleasesAudioProcessorEditor::ADC24RockSolidReleasesAudioProcessorEditor (ADC24RockSolidReleasesAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

ADC24RockSolidReleasesAudioProcessorEditor::~ADC24RockSolidReleasesAudioProcessorEditor()
{
}

//==============================================================================
void ADC24RockSolidReleasesAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
    g.drawFittedText ("ADC24: Rock Solid Releases!", getLocalBounds(), juce::Justification::centred, 1);
}

void ADC24RockSolidReleasesAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
