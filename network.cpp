#include "network.h"


UDP::UDP(QObject *parent) :
        QObject(parent)
{
    // create a QUDP socket
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress("192.168.1.4"), 1235);
    connect(socket, SIGNAL(readyRead()),this,SLOT(readReady()));

    notificationSocket = new QUdpSocket(this);
    notificationSocket->bind(QHostAddress::Any,2020);
    connect(notificationSocket, SIGNAL(readyRead()),this,SLOT(notification()));

}


void UDP::sendUDP(char *data, qint64 len)
{
    socket->writeDatagram(data,len, QHostAddress("192.168.1.2"), 1235);
}

void UDP::requestCall(qint16 phoneNumber,qint16 myPhoneNumber)
{
    QString sendNotif = QString("<phone><call>%1</call><callerid>%2</callerid></phone>").arg(phoneNumber).arg(myPhoneNumber);
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
    qDebug() << "Message port: " << senderPort;
    emit dataReady();
}

void UDP::notification()
{
    qDebug() << "miad tu notif";
    QByteArray notifData(notificationSocket->pendingDatagramSize(),0);
    QHostAddress sender;
    quint16 senderPort;
    notificationSocket->readDatagram(notifData.data(),notifData.size(),&sender,&senderPort);


    qDebug() << "Message from: " << sender.toString();
    qDebug() << "Message port: " << senderPort;
    qDebug() << "notif data:" << notifData.data();

// Manage incomming calls
    QDomDocument doc;
    doc.setContent(notifData);
    QDomNodeList PN= doc.elementsByTagName("call");
    QDomNodeList cID = doc.elementsByTagName("callerid");
    if (PN.count()) {
        emit callNotif(PN.at(0).toElement().text().toInt(),cID.at(0).toElement().text().toInt(),sender);
    }
}
