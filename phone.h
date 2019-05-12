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
#include <QStandardPaths>
#include <QFile>
#include <QDir>

#include "network.h"
class phone : public QObject
{
    Q_OBJECT
public:
    explicit phone(QObject *parent = nullptr);
    void initializeAudio();
    void createAudioInput();
    void createAudioOutput();
    Q_INVOKABLE void startAudioRead();
    Q_INVOKABLE void stopAndPlay();
    Q_INVOKABLE void requestCall(qint16 phoneNumber);
    Q_INVOKABLE void requestAnswer(qint16 callerID);
    Q_INVOKABLE void savePhoneNumber(qint16 phoneNumber);
    Q_INVOKABLE qint16 loadPhoneNumber();
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
    UDP *client;
    qint16 myPhoneNumber;

    qint16 callingNumber;
private slots:
    void readMore();
    void playSound();
public slots:
    void handleCall(qint16 phoneNumber, qint16 callerID, QHostAddress callerIP);
    void handleAnswer(qint16 destNumber, qint16 callerID, QHostAddress destIP);
signals:
    void onCalling(QVariant callerNum);
};

#endif // AUDIO_H
