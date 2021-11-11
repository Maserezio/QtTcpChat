#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

signals:
    void newMessage(const QByteArray &ba);

private slots:
    void onNewConnection();
    void onReadyRead();
    void onNewMessage(const QByteArray &ba);

private:
    QTcpServer* _server;
    QTcpSocket* _socket;
};

#endif // SERVER_H
