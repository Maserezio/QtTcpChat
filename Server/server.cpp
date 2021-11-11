#include "server.h"

Server::Server(QObject *parent) : QObject(parent)
{
    _server = new QTcpServer(this);

    connect(_server, &QTcpServer::newConnection, this, &Server::onNewConnection);
    connect(this, &Server::newMessage, this, &Server::onNewMessage);

    if(_server->listen(QHostAddress::LocalHost, 3333)) {
        qInfo() << "Listening ...";
    }
}

void Server::onNewConnection()
{
    _socket = _server->nextPendingConnection();
    qDebug() << "Client connected.";

    connect(_socket, &QTcpSocket::readyRead, this, &Server::onReadyRead);
    emit newMessage("Hi from server!");
}

void Server::onReadyRead()
{
    emit newMessage("Server received message \"" +_socket->readAll() + "\"");
}

void Server::onNewMessage(const QByteArray &ba)
{
    _socket->write(ba);
}



