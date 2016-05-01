/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"

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
    
    const OwnedArray< AudioIODeviceType >* deviceTypes = &( dm->getAvailableDeviceTypes() );
    
    for ( auto& t : *( deviceTypes ) ) {
        DBG( "+-- device type  : ------------+" );
        DBG( "  " + t->getTypeName() );
        auto deviceNames = t->getDeviceNames();
        
        for ( auto& name : deviceNames ) {
            DBG( "    +-- device name  : ------------+" );
            DBG( "      " + name );
        }
    }

    // initialize audio with the following requirements:
    auto result = dm->initialise( 2, 2, nullptr, true );
    
    if ( ! result.isEmpty() ) {
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
    
    delete dm;

    return 0;
}
