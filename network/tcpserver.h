#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <vector>
#include <memory>
#include <mutex>
#include <QObject>

class TcpServer : public QTcpServer {
    Q_OBJECT  // ✅ Required for Qt's meta-object system

public:
    explicit TcpServer(quint16 port, QObject* parent = nullptr);
    ~TcpServer();

    Q_INVOKABLE void startServer();  // ✅ Now callable from QML
    Q_INVOKABLE void stopServer();   // ✅ Now callable from QML

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private:
    void handleClient(std::unique_ptr<QTcpSocket> clientSocket);

    std::vector<QTcpSocket*> m_clients;
    std::mutex m_mutex;
};

#endif // TCPSERVER_H
