#pragma once

#include <QString>
#include <memory>  // For std::unique_ptr

class QSerialPort;

class UartController {
public:
    UartController(const QString& portName);
    ~UartController();

    void openConnection();
    void closeConnection();
    void sendData(const QByteArray& data);
    QByteArray receiveData();

private:
    QString m_portName;
    int m_serialPortHandle;  // Handle for the UART connection
    std::unique_ptr<QSerialPort> m_serialPort;  // Unique pointer to manage QSerialPort instance
};
