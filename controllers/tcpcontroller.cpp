#include "tcpcontroller.h"
#include <QJsonDocument>
#include <QByteArray>
#include <iostream>

TcpController::TcpController(const std::string& address, quint16 port, QObject* parent)
    : QObject(parent), m_address(QString::fromStdString(address)), m_port(port), m_socket(new QTcpSocket(this)) {

    // Connect QTcpSocket signals to our slots
    connect(m_socket, &QTcpSocket::connected, this, &TcpController::onConnected);
    connect(m_socket, &QTcpSocket::disconnected, this, &TcpController::onDisconnected);
    connect(m_socket, &QTcpSocket::readyRead, this, &TcpController::onReadyRead);
    connect(m_socket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::errorOccurred),
            this, &TcpController::onErrorOccurred);
}

TcpController::~TcpController() {
    disconnectFromServer();
}

void TcpController::connectToServer() {
    if (m_socket->state() == QAbstractSocket::ConnectedState) {
        std::cout << "Already connected to server." << std::endl;
        return;
    }

    std::cout << "Connecting to server..." << std::endl;
    m_socket->connectToHost(m_address, m_port);
}




void TcpController::sendData(const QJsonObject& data)
{
    if (m_socket->state() == QAbstractSocket::ConnectedState) {
        QJsonDocument doc(data);
        QByteArray byteArray = doc.toJson();
        m_socket->write(byteArray);
    } else {
        std::cerr << "Cannot send data. Not connected to server." << std::endl;
    }
}

void TcpController::disconnectFromServer()
{
    if (m_socket->state() == QAbstractSocket::ConnectedState)
    {
        std::cout << "Disconnecting from server..." << std::endl;
        m_socket->disconnectFromHost();
    }
}

// ** Slot Implementations **

void TcpController::onConnected()
{
    std::cout << "Connected to server!" << std::endl;
    emit connected();
}

void TcpController::onDisconnected()
{
    std::cout << "Disconnected from server." << std::endl;
    emit disconnected();
}

void TcpController::onReadyRead()
{
    QByteArray receivedData = m_socket->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(receivedData);

    if (!doc.isNull())
    {
        QJsonObject jsonData = doc.object();
        emit dataReceived(jsonData);
    } else
    {
        std::cerr << "Received invalid JSON data!" << std::endl;
    }
}

void TcpController::onErrorOccurred(QAbstractSocket::SocketError socketError)
{
    QString errorString = m_socket->errorString();
    std::cerr << "Socket error: " << errorString.toStdString() << std::endl;
    emit errorOccurred(errorString);
}
