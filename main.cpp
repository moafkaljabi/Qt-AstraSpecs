#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QCommandLineParser>
#include "network/tcpserver.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("TCP Server Example");
    parser.addHelpOption();

    QCommandLineOption portOption({"p", "port"}, "Port to run the server on.", "port", "12345");
    parser.addOption(portOption);
    parser.process(app);

    quint16 port = parser.value(portOption).toUInt();

    // Register TcpServer as a QML type ✅
    qmlRegisterType<TcpServer>("AstraSpecs", 1, 0, "TcpServer");

    QQmlApplicationEngine engine;
    engine.load(QUrl::fromLocalFile(QStringLiteral("Main.qml")));


    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
