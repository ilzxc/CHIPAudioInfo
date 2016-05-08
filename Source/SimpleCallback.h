/*
  ==============================================================================

    SimpleCallback.h
    Created: 8 May 2016 3:47:10pm
    Author:  Ilya Rostovtsev

  ==============================================================================
*/

#ifndef SIMPLECALLBACK_H_INCLUDED
#define SIMPLECALLBACK_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class SimpleCallback : public AudioIODeviceCallback {
  public:
    SimpleCallback() {}
    ~SimpleCallback() override {}

    void audioDeviceIOCallback( const float** inputChannelData, int numInputChannels,
                                float** outputChannelData, int numOutputChannels,
                                int numSamples ) override;
    void audioDeviceAboutToStart( AudioIODevice* device ) override;
    void audioDeviceStopped() override;
    void audioDeviceError( const String& errorMessage ) override;

  private:
    double frequency;
    double phase, phaseDelta;
    double sr;
};

#endif // SIMPLECALLBACK_H_INCLUDED
