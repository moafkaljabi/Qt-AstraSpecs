#pragma once

#include <QTcpServer>
#include <QTcpSocket>
#include <memory>
#include <vector>
#include <mutex>
#include <pqxx/pqxx>

class TcpServer : public QTcpServer {
    Q_OBJECT
public:
    explicit TcpServer(quint16 port, QObject* parent = nullptr);
    ~TcpServer();

    Q_INVOKABLE void startServer();  // Expose startServer method to QML
    Q_INVOKABLE void stopServer();   // Expose stopServer method to QML

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private:
    void handleClient(std::unique_ptr<QTcpSocket> clientSocket);
    void saveToDatabase(const QString& imuData);

    std::vector<std::unique_ptr<QTcpSocket>> m_clients;
    std::mutex m_mutex;
    pqxx::connection m_dbConnection;
};
