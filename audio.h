#ifndef AUDIO_H
#define AUDIO_H

#include <QObject>
#include <QByteArray>
//#include <SoundTouch.h>
#include <QAudioInput>
#include <QAudioOutput>
#include<qaudiooutput.h>
#include <QBuffer>


class audio : public QObject
{
    Q_OBJECT
public:
    explicit audio(QObject *parent = nullptr);
    void initializeAudio();
    void createAudioInput();
    void createAudioOutput();

    int ApplyVolumeToSample(short iSample);
private:
    QAudioDeviceInfo m_Inputdevice;
    QAudioDeviceInfo m_Outputdevice;
    QAudioFormat m_format;
    QAudioInput *m_audioInput;
    QAudioOutput *m_audioOutput;
    QIODevice *m_input;
    QIODevice *m_output;
    QByteArray m_buffer;
    int m_iVolume;
};

#endif // AUDIO_H
