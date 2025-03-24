#include "tcpserver.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <iostream>
#include <thread>
#include <mutex>
#include <memory>
#include <vector>
#include <algorithm>

TcpServer::TcpServer(quint16 port, QObject* parent)
    : QTcpServer(parent) {
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
    std::lock_guard lock(m_mutex);
    m_clients.clear();
    std::cout << "Server stopped." << std::endl;
}

void TcpServer::incomingConnection(qintptr socketDescriptor) {
    auto clientSocket = std::make_unique<QTcpSocket>();
    clientSocket->setSocketDescriptor(socketDescriptor);
    std::cout << "New client connected: " << socketDescriptor << std::endl;

    {
        std::lock_guard lock(m_mutex);
        m_clients.push_back(clientSocket.get());
    }

    std::thread(&TcpServer::handleClient, this, std::move(clientSocket)).detach();
}

void TcpServer::handleClient(std::unique_ptr<QTcpSocket> clientSocket) {
    while (clientSocket->waitForReadyRead()) {
        QByteArray receivedData = clientSocket->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(receivedData);
        if (!doc.isNull() && doc.isObject()) {
            QJsonObject obj = doc.object();
            std::cout << "Received Data: " << QString::fromUtf8(receivedData).toStdString() << std::endl;
        }
    }
    std::cout << "Client disconnected." << std::endl;

    {
        std::lock_guard lock(m_mutex);
        m_clients.erase(std::remove(m_clients.begin(), m_clients.end(), clientSocket.get()), m_clients.end());
    }
}
