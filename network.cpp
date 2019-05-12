#include "network.h"


UDP::UDP(QObject *parent) :
        QObject(parent)
{

    notificationSocket = new QUdpSocket(this);
    notificationSocket->bind(QHostAddress::Any,2020);
    connect(notificationSocket, SIGNAL(readyRead()),this,SLOT(notification()));
    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost && address.toString().contains("192"))
            myAddress = address;
    }
    // create a QUDP socket for voice
    qDebug()<<"my ip address is "<<myAddress.toString();
    socket = new QUdpSocket(this);
    socket->bind(myAddress, 1235);
    connect(socket, SIGNAL(readyRead()),this,SLOT(readReady()));


}


void UDP::sendUDP(char *data, qint64 len, QHostAddress destinationIP)
{
    socket->writeDatagram(data,len, destinationIP, 1235);
}

void UDP::requestCall(qint16 phoneNumber,qint16 myPhoneNumber)
{
    QString sendNotif = QString("<phone><call>%1</call><callerid>%2</callerid></phone>").arg(phoneNumber).arg(myPhoneNumber);
    notificationSocket->writeDatagram(sendNotif.toLocal8Bit(),sendNotif.count(),QHostAddress::Broadcast,2020);
}

void UDP::answerCall(qint16 myPhoneNumber, qint16 callerID)
{
    QString sendNotif = QString("<phone><answer>%1</answer><to>%2</to></phone>").arg(myPhoneNumber).arg(callerID);
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

//    qDebug() << "Message from: " << sender.toString();
//    qDebug() << "Message port: " << senderPort;
    emit dataReady();
}

void UDP::notification()
{
    QByteArray notifData(notificationSocket->pendingDatagramSize(),0);
    QHostAddress sender;
    quint16 senderPort;
    notificationSocket->readDatagram(notifData.data(),notifData.size(),&sender,&senderPort);
//    qDebug()<<"sende: "<<sender.toString();


    QDomDocument doc;
    doc.setContent(notifData);
    // Manage incomming calls
    QDomNodeList PN= doc.elementsByTagName("call");
    QDomNodeList cID = doc.elementsByTagName("callerid");
    if (PN.at(0).toElement().text().toInt() != 0 && PN.count()) {
        emit callNotif(PN.at(0).toElement().text().toInt(),cID.at(0).toElement().text().toInt(),sender);
    }
    // Manage Answer
    QDomNodeList PNAns= doc.elementsByTagName("answer");
    QDomNodeList cIDAns = doc.elementsByTagName("to");
    if (PNAns.at(0).toElement().text().toInt() != 0 && PNAns.count()) {
        emit answerNotif(PNAns.at(0).toElement().text().toInt(),cIDAns.at(0).toElement().text().toInt(),sender);
    }

// Manage answer msg

}
