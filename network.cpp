#include "network.h"


UDP::UDP(QObject *parent) :
        QObject(parent)
{
    // create a QUDP socket
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::Any, 1235);
    connect(socket, SIGNAL(readyRead()),this,SLOT(readReady()));
}


void UDP::sendUDP(char *data, qint64 len)
{
    qDebug() << "mige befresta";
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
