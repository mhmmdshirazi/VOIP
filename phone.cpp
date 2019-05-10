#include "phone.h"
const int BufferSize = 500;

phone::phone(QObject *parent) : QObject(parent),m_Inputdevice(QAudioDeviceInfo::defaultInputDevice())
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
    myPhoneNumber = loadPhoneNumber();
    connect(client,SIGNAL(callNotif(qint16)),this,SLOT(handleCall(qint16)));
}

//Initialize audio
void phone::initializeAudio()
{

    m_format.setSampleRate(8000); //set frequency to 8000
    m_format.setChannelCount(1); //set channels to mono
    m_format.setSampleSize(16); //set sample sze to 16 bit
    m_format.setSampleType(QAudioFormat::SignedInt); //Sample type as usigned integer sample
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

void phone::createAudioOutput()
{
    qDebug() << m_Outputdevice.deviceName();
    m_audioOutput = new QAudioOutput(m_Outputdevice, m_format, this);
    qreal linearVolume = QAudio::convertVolume(100 / qreal(100),
                                               QAudio::LogarithmicVolumeScale,
                                               QAudio::LinearVolumeScale);
    m_audioOutput->setVolume(linearVolume);
}



void phone::createAudioInput()
{
    if (m_input != 0) {
        disconnect(m_input, 0, this, 0);
        m_input = 0;
    }
    m_audioInput = new QAudioInput(m_Inputdevice, m_format, this);

    qreal linearVolume = QAudio::convertVolume(100 / qreal(100),
                                               QAudio::LogarithmicVolumeScale,
                                               QAudio::LinearVolumeScale);
//    m_audioInput->setBufferSize(500);
    m_audioInput->setVolume(linearVolume);
    qDebug() << m_Inputdevice.preferredFormat();
}


//////////////////////
/// \brief audio::startAudioRead
///

void phone::startAudioRead()
{
//    m_pushTimer->start(50);
    m_input = m_audioInput->start();
    //connect readyRead signal to readMore slot.
    //Call readmore when audio samples fill in inputbuffer
    connect(m_input, SIGNAL(readyRead()), SLOT(readMore()));
//    connect(m_pushTimer, SIGNAL(timeout()), SLOT(readMore()));
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
//            while(m_audioOutput->bytesFree() < saveData[i].count()) {}
//            io->write(saveData[i].data(),saveData[i].count());
//            qDebug() <<"free"<< m_audioOutput->bytesFree();
//            qDebug() <<"num"<< i;
//        }
//    }
//}


void phone::stopAndPlay()
{
    m_output = m_audioOutput->start();
    m_audioInput->stop();
    connect(client,SIGNAL(dataReady()),this,SLOT(playSound()));
}

void phone::requestCall(qint16 phoneNumber)
{
    client->requestCall(phoneNumber);
}

void phone::savePhoneNumber(qint16 phoneNumber)
{
    auto path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    auto fileName= path + "/myNumber.txt";
    QDir _dir;
    // check if path exists
    int _dirExists = _dir.exists(path);
    // if not, create it
    if( !_dirExists )
        _dir.mkpath(path);

    QFile myFile(fileName);
    if ( myFile.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &myFile );
        stream << QString("%1").arg(phoneNumber);
    }
    myPhoneNumber = phoneNumber;
}

qint16 phone::loadPhoneNumber()
{
    auto path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    auto fileName= path + "/myNumber.txt";
    QDir _dir;
    // check if path exists
    int _dirExists = _dir.exists(path);
    // if not, create it
    if( !_dirExists )
        _dir.mkpath(path);

    QFile myFile(fileName);
    if ( myFile.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &myFile );
        return stream.readAll().toInt();
    }
    return -1;
}

void phone::readMore()
{
    //Return if audio input is null
    if(!m_audioInput)
        return;
    qint64 len = m_audioInput->bytesReady();
    const int BufferSize = 4096;
    if (len > BufferSize)
        len = BufferSize;

    QByteArray buffer(len, 0);

    qint64 l = m_input->read(buffer.data(), len);
    //if (l > 0) {
        qDebug() << "l is " << l <<" len is" << len << " ye data is :" << (int)buffer.at(0) ;
        client->sendUDP(buffer.data(),l);
    //}
    //client->sendUDP("salam fatemeye man",strlen("salam fatemeye man"));
    //buffer.resize(l);
    //saveData.append(buffer);
}

void phone::playSound()
{
//    qDebug()<< "net :" << client->netData.count() << "audio :"<< m_audioOutput->bytesFree();
//    while(m_audioOutput->bytesFree() < client->netData.count()) {}
    m_output->write(client->netData.data(),client->netData.count());
    //qDebug() << (int)client->netData.data()[100];

}

void phone::handleCall(qint16 phoneNumber)
{
    if (phoneNumber == myPhoneNumber) {
        qDebug() << "calling "<< phoneNumber;
        emit onCalling(phoneNumber);
    }
}
