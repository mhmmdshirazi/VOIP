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
    m_pushTimer = new QTimer(this);
    client = new UDP;
    initializeAudio();
}

//Initialize audio
void audio::initializeAudio()
{

    m_format.setSampleRate(44100); //set frequency to 8000
    m_format.setChannelCount(1); //set channels to mono
    m_format.setSampleSize(16); //set sample sze to 16 bit
    m_format.setSampleType(QAudioFormat::SignedInt ); //Sample type as usigned integer sample
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
    qDebug() << m_Outputdevice.deviceName();
    m_audioOutput = new QAudioOutput(m_Outputdevice, m_format, this);
    qreal linearVolume = QAudio::convertVolume(100 / qreal(100),
                                               QAudio::LogarithmicVolumeScale,
                                               QAudio::LinearVolumeScale);

    m_audioOutput->setVolume(linearVolume);
}



void audio::createAudioInput()
{
    if (m_input != 0) {
        disconnect(m_input, 0, this, 0);
        m_input = 0;
    }
    m_audioInput = new QAudioInput(m_Inputdevice, m_format, this);
    qreal linearVolume = QAudio::convertVolume(100 / qreal(100),
                                               QAudio::LogarithmicVolumeScale,
                                               QAudio::LinearVolumeScale);
    m_audioInput->setVolume(linearVolume);
    qDebug() << m_Inputdevice.preferredFormat();
}


//////////////////////
/// \brief audio::startAudioRead
///

void audio::startAudioRead()
{

    m_input = m_audioInput->start();
    //connect readyRead signal to readMore slot.
    //Call readmore when audio samples fill in inputbuffer
    connect(m_input, SIGNAL(readyRead()), SLOT(readMore()));
}


//void audio::stopAndPlay()
//{
//    m_audioInput->stop();
//    int l = saveData.count();
//    m_pushTimer->disconnect();
//    if(l > 0)
//    {
//        auto io = m_audioOutput->start();
//        int chunks = m_audioOutput->bytesFree() / m_audioOutput->periodSize();
//        //while (chunks) {
//        for (int i = 0; i < l; i++) {
//            io->write(saveData[i].data(),saveData[i].count());
//            while(m_audioOutput->bytesFree() < 4096) {}
//            qDebug() << m_audioOutput->bytesFree();
//            qDebug()<< i;
//        }
//    }
//}


void audio::stopAndPlay()
{
    connect(client,SIGNAL(dataReady()),this,SLOT(playSound()));
}


void audio::test()
{
    qDebug() << "len is ::" ;
}

///////////////////////////////////
/// \brief audio::readMore
///
void audio::readMore()
{
    //Return if audio input is null
    if(!m_audioInput)
        return;
    //Check the number of samples in input buffer
    qint64 len = m_audioInput->bytesReady();
    qDebug() <<len;
    //Read sound samples from input device to buffer
    QByteArray temp;
    qint64 l = m_input->read(m_buffer.data(), len);

    client->sendUDP(m_buffer.data(),len);
    //saveData.append(m_buffer);
}

void audio::playSound()
{
    qDebug("s");
    auto io = m_audioOutput->start();
        io->write(client->netData.data(),client->netData.count());
        //while(m_audioOutput->bytesFree() < 4095) {}

}
