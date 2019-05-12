#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QUdpSocket>
#include <QCoreApplication>
#include <QString>
#include <QDomDocument>
#include <QDomNodeList>
#include <QNetworkInterface>


class UDP : public QObject
{
    Q_OBJECT
public:
    explicit UDP(QObject *parent = nullptr);
    void HelloUDP();
    void sendUDP(char *data, qint64 len, QHostAddress destinationIP);
    void requestCall(qint16 phoneNumber,qint16 myPhoneNumber);
    void answerCall(qint16 myPhoneNumber,qint16 callerID);
    QByteArray netData;
    QHostAddress myAddress;
public slots:
    void readReady();
    void notification();
private:
    QUdpSocket *socket;
    QUdpSocket *notificationSocket;
signals:
    void dataReady();
    void callNotif(qint16 destNumber, qint16 callerID, QHostAddress callerIP);
    void answerNotif(qint16 destNumber, qint16 callerID, QHostAddress destIP);

};


#endif // NETWORK_H
