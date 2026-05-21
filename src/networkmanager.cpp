#include "networkmanager.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>

NetworkManager::NetworkManager(QObject *parent)
    : QObject{parent}
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(45454, QUdpSocket::ShareAddress);
    connect(udpSocket, &QUdpSocket::readyRead, this, &NetworkManager::readPendingDatagrams);

    tcpServer = new QTcpServer(this);
    if (tcpServer->listen(QHostAddress::Any, 45455)) {
        connect(tcpServer, &QTcpServer::newConnection, this, &NetworkManager::onNewConnection);
    }

    broadcastTimer = new QTimer(this);
    connect(broadcastTimer, &QTimer::timeout, this, &NetworkManager::broadcastPresence);
}

void NetworkManager::setVisibility(const QString &username, bool isVisible)
{
    currentUsername = username;

    if (isVisible) {
        broadcastPresence();
        broadcastTimer->start(2000);
    } else {
        broadcastTimer->stop();

        QByteArray datagram = "OFFLINE:" + currentUsername.toUtf8();
        udpSocket->writeDatagram(datagram, QHostAddress::Broadcast, 45454);
    }
}

void NetworkManager::broadcastPresence()
{
    QByteArray datagram = "ONLINE:" + currentUsername.toUtf8();
    udpSocket->writeDatagram(datagram, QHostAddress::Broadcast, 45454);
}

void NetworkManager::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress senderIp;

        udpSocket->readDatagram(datagram.data(), datagram.size(), &senderIp);

        QString message = QString::fromUtf8(datagram);
        QString cleanIp = senderIp.toString().remove("::ffff:");

        if (message.startsWith("ONLINE:")) {
            QString name = message.split(":")[1];
            emit userFound(cleanIp, name);
        } else if (message.startsWith("OFFLINE:")) {
            emit userLeft(cleanIp);
        }
    }
}

void NetworkManager::sendMessage(const QString &targetIp, const QString &myUsername, const QString &message)
{
    QTcpSocket socket;
    socket.connectToHost(targetIp, 45455);

    if (socket.waitForConnected(3000)) {
        QString fullMessage = "[" + myUsername + "]: " + message;

        socket.write(fullMessage.toUtf8());
        socket.waitForBytesWritten(1000);
        socket.disconnectFromHost();

        saveMessageToFile(fullMessage);
        emit messageReceived(fullMessage);
    }
}

void NetworkManager::onNewConnection()
{
    QTcpSocket *clientSocket = tcpServer->nextPendingConnection();
    connect(clientSocket, &QTcpSocket::readyRead, this, &NetworkManager::onReadyReadTcp);
}

void NetworkManager::onReadyReadTcp()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (clientSocket) {
        QByteArray data = clientSocket->readAll();
        QString fullMessage = QString::fromUtf8(data);

        saveMessageToFile(fullMessage);
        emit messageReceived(fullMessage);

        clientSocket->deleteLater();
    }
}

void NetworkManager::saveMessageToFile(const QString &msg)
{
    QFile file("chat_history.txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << msg << "\n";
        file.close();
    }
}

QString NetworkManager::loadChatHistory()
{
    QFile file("chat_history.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        return in.readAll();
    }
    return "";
}