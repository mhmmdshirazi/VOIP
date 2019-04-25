#include "audio.h"
const int BufferSize = 14096;

audio::audio(QObject *parent) : QObject(parent),m_Inputdevice(QAudioDeviceInfo::defaultInputDevice())
  ,   m_Outputdevice(QAudioDeviceInfo::defaultOutputDevice())
  ,   m_audioInput(0)
  ,   m_audioOutput(0)
  ,   m_input(0)
  ,   m_iVolume(0)
  ,   m_buffer(BufferSize, 0)
{
    initializeAudio();
}

//Initialize audio
void audio::initializeAudio()
{

    m_format.setSampleRate(8000); //set frequency to 8000
    m_format.setChannelCount(1); //set channels to mono
    m_format.setSampleSize(16); //set sample sze to 16 bit
    m_format.setSampleType(QAudioFormat::UnSignedInt ); //Sample type as usigned integer sample
    m_format.setByteOrder(QAudioFormat::LittleEndian); //Byte order
    m_format.setCodec("audio/pcm"); //set codec as simple audio/pcm

    QAudioDeviceInfo infoIn(QAudioDeviceInfo::defaultInputDevice());
    if (!infoIn.isFormatSupported(m_format))
    {
        //Default format not supported - trying to use nearest
        m_format = infoIn.nearestFormat(m_format);
    }

    QAudioDeviceInfo infoOut(QAudioDeviceInfo::defaultOutputDevice());

    if (!infoOut.isFormatSupported(m_format))
    {
       //Default format not supported - trying to use nearest
        m_format = infoOut.nearestFormat(m_format);
    }
    createAudioInput();
    createAudioOutput();
}

void audio::createAudioOutput()
{
    m_audioOutput = new QAudioOutput(m_Outputdevice, m_format, this);
}
void audio::createAudioInput()
{
    if (m_input != 0) {
        disconnect(m_input, 0, this, 0);
        m_input = 0;
    }

    m_audioInput = new QAudioInput(m_Inputdevice, m_format, this);

}
