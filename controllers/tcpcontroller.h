
#pragma once

#include <string>
#include <QTcpSocket>
#include <QJsonObject>

class TcpController : public QObject {

    Q_OBJECT        // Enables Signals and Slots


public:
    explicit TcpController(const std::string& address, quint16 port, QObject* parent = nullptr);
    ~TcpController();

    void connectToServer();
    void sendData(const QJsonObject& data);
    void disconnectFromServer();


signals:
    void connected();
    void disconnected();
    void errorOccurred(const QString& error);
    void dataReceived(const QJsonObject &data);



private slots:

    void onConnected();
    void onDisconnected();
    void onReadyRead();
    void onErrorOccurred(QAbstractSocket::SocketError socketError);


private:
    QTcpSocket* m_socket;
    QString m_address;
    quint16 m_port;
};
