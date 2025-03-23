#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "controllers/tcpcontroller.h"
#include <QJsonDocument>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // Create TcpController instance
    TcpController tcpController("127.0.0.1", 12345);

    // Connect signals to lambda functions for debugging
    QObject::connect(&tcpController, &TcpController::connected, []() {
        qDebug() << "Connected to server!";
    });

    QObject::connect(&tcpController, &TcpController::dataReceived, [](const QJsonObject& data) {
        qDebug() << "Received data from server:" << QJsonDocument(data).toJson();
    });

    // Start connection
    tcpController.connectToServer();

    engine.loadFromModule("AstraSpecs", "Main");
    return app.exec();
}
