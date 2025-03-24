#include <QCoreApplication>
#include <QQuickView>
#include <QQmlContext>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include "network/tcpserver.h"

int main(int argc, char *argv[]) {

    QCoreApplication a(argc, argv);

    // Set up command line options
    QCommandLineParser parser;
    parser.setApplicationDescription("TCP Server Example");
    parser.addHelpOption();

    // Define a port option
    QCommandLineOption portOption(QStringList() << "p" << "port", "Port to run the server on.", "port", "12345");
    parser.addOption(portOption);
    parser.process(a);

    // Get the port number from the command line argument (default to 12345 if not provided)
    quint16 port = parser.value(portOption).toUInt();

    // Initialize the TcpServer on the specified port
    TcpServer server(port);

    // Create the QML view
    QQuickView view;
    view.rootContext()->setContextProperty("tcpServer", &server); // Expose TcpServer instance to QML
    view.setSource(QUrl::fromLocalFile("qml/main.qml"));
    view.show();

    // Start the event loop
    return a.exec();
}
