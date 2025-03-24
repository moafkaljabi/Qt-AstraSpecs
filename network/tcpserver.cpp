#include "tcpserver.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <iostream>
#include <thread>
#include <mutex>

TcpServer::TcpServer(quint16 port, QObject* parent)
    : QTcpServer(parent), m_dbConnection("dbname=mydatabase user=myuser password=mypass hostaddr=127.0.0.1 port=5432") {
    if (!m_dbConnection.is_open()) {
        std::cerr << "Failed to connect to PostgreSQL!" << std::endl;
        return;
    }
    if (!listen(QHostAddress::Any, port)) {
        std::cerr << "Server failed to start on port " << port << std::endl;
    } else {
        std::cout << "Server started on port " << port << std::endl;
    }
}

TcpServer::~TcpServer() {
    stopServer();
}

void TcpServer::startServer() {
    std::cout << "Waiting for incoming connections..." << std::endl;
}

void TcpServer::stopServer() {
    close();
    std::lock_guard<std::mutex> lock(m_mutex);
    // Handle cleanup of active client threads here (optional)
    m_clients.clear();
    std::cout << "Server stopped." << std::endl;
}

void TcpServer::incomingConnection(qintptr socketDescriptor) {
    auto clientSocket = std::make_unique<QTcpSocket>();
    clientSocket->setSocketDescriptor(socketDescriptor);
    std::cout << "New client connected: " << socketDescriptor << std::endl;

    // Optionally, store the client socket if needed
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_clients.push_back(std::move(clientSocket));
    }

    std::thread clientThread(&TcpServer::handleClient, this, std::move(clientSocket));
    clientThread.detach();
}

void TcpServer::handleClient(std::unique_ptr<QTcpSocket> clientSocket) {
    while (clientSocket->waitForReadyRead()) {
        QByteArray receivedData = clientSocket->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(receivedData);
        if (!doc.isNull() && doc.isObject()) {
            QJsonObject obj = doc.object();
            QString imuData = QString::fromUtf8(receivedData);
            saveToDatabase(imuData);
            std::cout << "Received IMU Data: " << imuData.toStdString() << std::endl;
        }
    }
    std::cout << "Client disconnected." << std::endl;

    // Remove the client socket when done (optional)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        // Remove client from the list, you could match it based on socketDescriptor or other info
        // In this case, we are just clearing for now
        m_clients.erase(std::remove(m_clients.begin(), m_clients.end(), clientSocket), m_clients.end());
    }
}

void TcpServer::saveToDatabase(const QString& imuData) {
    try {
        pqxx::work txn(m_dbConnection);
        txn.exec("INSERT INTO imu_logs (data) VALUES (" + txn.quote(imuData.toStdString()) + ")");
        txn.commit();
    } catch (const std::exception& e) {
        std::cerr << "Database error: " << e.what() << std::endl;
    }
}
