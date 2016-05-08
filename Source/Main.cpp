/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "SimpleCallback.h"
#include <unistd.h>

#define logMessage DBG

static String getListOfActiveBits( const BitArray& b )
{
    StringArray bits;

    for ( int i = 0; i <= b.getHighestBit(); ++i )
        if ( b[ i ] )
            bits.add( String( i ) );

    return bits.joinIntoString( ", " );
}

//==============================================================================
int main( int argc, char* argv[] )
{
    AudioDeviceManager* dm = new AudioDeviceManager();
    auto callback = new SimpleCallback();

    const OwnedArray< AudioIODeviceType >* deviceTypes = &( dm->getAvailableDeviceTypes() );

    for ( auto& t : *( deviceTypes ) ) {
        DBG( "+-- device type  : ------------+" );
        DBG( "  " + t->getTypeName() );
        t->scanForDevices();
        if ( t->hasSeparateInputsAndOutputs() ) {
            DBG( "+-- inputs   : ------------+" );
            auto deviceNames = t->getDeviceNames( true );
            for ( auto& name : deviceNames ) {
                DBG( "    +-- device name  : ------------+" );
                DBG( "      " + name );
            }
            DBG( "+-- outputs  : ------------+" );
            deviceNames = t->getDeviceNames( false );
            for ( auto& name : deviceNames ) {
                DBG( "    +-- device name  : ------------+" );
                DBG( "      " + name );
            }
        } else {
        }
        DBG( "has separate inputs and outputs : " << t->hasSeparateInputsAndOutputs() );
    }

    // initialize audio with the following requirements:
    auto result =
      dm->initialise( /* num inputs */ 2, /* num outputs */ 2, /* xml settings file */ nullptr,
                      /* select default device on failure */ true );

    if ( !result.isEmpty() ) {
        DBG( "Error on initialize : " + result );
    }

    logMessage( "--------------------------------------" );
    logMessage( "Current audio device type: " +
                ( dm->getCurrentDeviceTypeObject() != nullptr
                    ? dm->getCurrentDeviceTypeObject()->getTypeName()
                    : "<none>" ) );

    if ( AudioIODevice* device = dm->getCurrentAudioDevice() ) {
        logMessage( "Current audio device: " + device->getName().quoted() );
        logMessage( "Sample rate: " + String( device->getCurrentSampleRate() ) + " Hz" );
        logMessage( "Block size: " + String( device->getCurrentBufferSizeSamples() ) + " samples" );
        logMessage( "Output Latency: " + String( device->getOutputLatencyInSamples() ) +
                    " samples" );
        logMessage( "Input Latency: " + String( device->getInputLatencyInSamples() ) + " samples" );
        logMessage( "Bit depth: " + String( device->getCurrentBitDepth() ) );
        logMessage( "Input channel names: " +
                    device->getInputChannelNames().joinIntoString( ", " ) );
        logMessage( "Active input channels: " +
                    getListOfActiveBits( device->getActiveInputChannels() ) );
        logMessage( "Output channel names: " +
                    device->getOutputChannelNames().joinIntoString( ", " ) );
        logMessage( "Active output channels: " +
                    getListOfActiveBits( device->getActiveOutputChannels() ) );
    } else {
        logMessage( "No audio device open" );
    }

    dm->addAudioCallback( callback );

//    sleep( 3 ); // 3 seconds of audio
    while ( true ) {
    }

    dm->removeAudioCallback( callback );
    delete callback;

    delete dm;

    return 0;
}
