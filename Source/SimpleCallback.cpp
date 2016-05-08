/*
  ==============================================================================

    SimpleCallback.cpp
    Created: 8 May 2016 3:47:10pm
    Author:  Ilya Rostovtsev

  ==============================================================================
*/

#include "SimpleCallback.h"

void SimpleCallback::audioDeviceIOCallback( const float** inputChannelData, int numInputChannels,
                                            float** outputChannelData, int numOutputChannels,
                                            int numSamples )
{
    auto localPhase = phase;
    for ( int chan = 0; chan < 2; ++chan ) {
        float* const channelData = outputChannelData[ chan ];
        localPhase = phase;

        for ( int i = 0; i < numSamples; ++i ) {
            channelData[ i ] = 0.88 * std::sin( localPhase );

            // increment the phase step for the next sample
            localPhase = std::fmod( localPhase + phaseDelta, float_Pi * 2.0 );
        }
    }
    phase = localPhase;
}

void SimpleCallback::audioDeviceAboutToStart( AudioIODevice* device )
{
    sr = device->getCurrentSampleRate();
    phase = 0;
    frequency = 440.0;
    phaseDelta = ( 2.0 * double_Pi * frequency / sr );
}

void SimpleCallback::audioDeviceStopped() { /* nothing for now */ }

void SimpleCallback::audioDeviceError( const String& errorMessage )
{
    DBG( "error: " << errorMessage );
}
