#include "uartcontroller.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <iostream>

UartController::UartController(const QString& portName)
    : m_portName(portName), m_serialPortHandle(-1), m_serialPort(std::make_unique<QSerialPort>()) {}

UartController::~UartController() {
    closeConnection();
}

void UartController::openConnection() {
    m_serialPort->setPortName(m_portName);
    if (m_serialPort->open(QIODevice::ReadWrite)) {
        m_serialPortHandle = m_serialPort->handle();
        std::cout << "Connection opened successfully!" << std::endl;
    } else {
        std::cerr << "Failed to open connection!" << std::endl;
    }
}

void UartController::closeConnection() {
    if (m_serialPortHandle != -1) {
        m_serialPort->close();
        std::cout << "Connection closed successfully!" << std::endl;
    }
}

void UartController::sendData(const QByteArray& data) {
    if (m_serialPort->isOpen()) {
        m_serialPort->write(data);
    } else {
        std::cerr << "Port is not open!" << std::endl;
    }
}

QByteArray UartController::receiveData() {
    if (m_serialPort->waitForReadyRead(3000)) {
        return m_serialPort->readAll();
    }
    return QByteArray();
}
