#include "network.h"


UDP::UDP(QObject *parent) :
        QObject(parent)
{
    // create a QUDP socket
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::Any, 1235);
    connect(socket, SIGNAL(readyRead()),this,SLOT(readReady()));

    notificationSocket = new QUdpSocket(this);
    notificationSocket->bind(QHostAddress::Any,2020);
    connect(notificationSocket, SIGNAL(readyRead()),this,SLOT(notification()));

}


void UDP::sendUDP(char *data, qint64 len)
{
    socket->writeDatagram(data,len, QHostAddress::Broadcast, 1234);
}

void UDP::requestCall(qint16 phoneNumber)
{
    QString sendNotif = QString("<call>%1</call>").arg(phoneNumber);
    notificationSocket->writeDatagram(sendNotif.toLocal8Bit(),sendNotif.count(),QHostAddress::Broadcast,2020);
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

    qDebug() << "Message from: " << sender.toString();
//    qDebug() << "Message port: " << senderPort;
    emit dataReady();
}

void UDP::notification()
{
    qDebug() << "miad tu notif";
    QByteArray notifData(notificationSocket->pendingDatagramSize(),0);
    QHostAddress sender;
    quint16 senderPort;
    notificationSocket->readDatagram(notifData.data(),notifData.size(),&sender,&senderPort);

    //Get your xml into xmlText(you can use QString instead og QByteArray)
    QDomDocument doc;
    doc.setContent(notifData);
    QDomNodeList list= doc.elementsByTagName("call");
    //QString helloWorld=list.at(0).toElement().text();
    qDebug() << "Message from: " << sender.toString();
    qDebug() << "Message port: " << senderPort;
    qDebug() << "notif data:" << notifData.data();
    if (list.count()) {
        emit callNotif(list.at(0).toElement().text().toInt());
    }
}
