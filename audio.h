#ifndef AUDIO_H
#define AUDIO_H

#include <QObject>
#include <QByteArray>
#include <QAudioInput>
#include <QAudioOutput>
#include<qaudiooutput.h>
#include <QBuffer>
#include <QDebug>

#include <QTimer>
class audio : public QObject
{
    Q_OBJECT
public:
    explicit audio(QObject *parent = nullptr);
    void initializeAudio();
    void createAudioInput();
    void createAudioOutput();
    Q_INVOKABLE void startAudioRead();
    Q_INVOKABLE void test();
    Q_INVOKABLE void stopAndPlay();
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
    QList<QByteArray> saveData;
    int m_iVolume;
    QTimer *m_pushTimer = nullptr;

private slots:
    void readMore();

};

#endif // AUDIO_H
