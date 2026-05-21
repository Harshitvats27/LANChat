#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QUdpSocket>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>

class NetworkManager : public QObject
{
    Q_OBJECT
public:
    explicit NetworkManager(QObject *parent = nullptr);

    // Replaced startBroadcasting with a Toggle method
    Q_INVOKABLE void setVisibility(const QString &username, bool isVisible);
    Q_INVOKABLE void sendMessage(const QString &targetIp, const QString &myUsername, const QString &message);
    Q_INVOKABLE QString loadChatHistory();

signals:
    void userFound(QString ipAddress, QString username);
    void userLeft(QString ipAddress);
    void messageReceived(QString messageDisplay);

private slots:
    void readPendingDatagrams();
    void onNewConnection();
    void onReadyReadTcp();
    void broadcastPresence();

private:
    QUdpSocket *udpSocket;
    QTcpServer *tcpServer;

    QTimer *broadcastTimer;
    QString currentUsername;

    void saveMessageToFile(const QString &msg);
};

#endif