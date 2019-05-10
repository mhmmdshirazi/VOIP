#include "network.h"


UDP::UDP(QObject *parent) :
        QObject(parent)
{
    // create a QUDP socket
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::Any, 1235);
    connect(socket, SIGNAL(readyRead()),this,SLOT(readReady()));
}

void UDP::HelloUDP()
{
    QByteArray Data;
    Data.append("Hello from UDP");

    // Sends the datagram datagram
    // to the host address and at port.
    // qint64 QUdpSocket::writeDatagram(const QByteArray & datagram,
    //                      const QHostAddress & host, quint16 port)
    socket->writeDatagram(Data, QHostAddress::LocalHost, 1234);
    qDebug("s");

}

void UDP::sendUDP(char *data, qint64 len)
{
    socket->writeDatagram(data,len, QHostAddress::Broadcast, 1234);
}

void UDP::readReady()
{
    // when data comes in
    qDebug("miad inja");
    netData.resize(socket->pendingDatagramSize());
    QHostAddress sender;
    quint16 senderPort;
    socket->readDatagram(netData.data(), netData.size(),
                         &sender, &senderPort);

//    qDebug() << "Message from: " << sender.toString();
//    qDebug() << "Message port: " << senderPort;
    emit dataReady();
}
