#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QUdpSocket>
#include <QCoreApplication>
class UDP : public QObject
{
    Q_OBJECT
public:
    explicit UDP(QObject *parent = nullptr);
    void HelloUDP();
    void sendUDP(char *data, qint64 len);
    QByteArray netData;
public slots:
    void readReady();
private:
    QUdpSocket *socket;
signals:
    void dataReady();
};

#endif // NETWORK_H
