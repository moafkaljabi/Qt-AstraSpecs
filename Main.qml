import QtQuick
import QtQuick.Controls
import AstraSpecs 1.0  // ✅ Import the module where TcpServer is registered

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "Server Control"

    // ✅ Create an instance of TcpServer
    TcpServer {
        id: tcpServer
    }

    Column {
        anchors.centerIn: parent
        spacing: 20

        Button {
            text: "Start Server"
            onClicked: tcpServer.startServer();
        }

        Button {
            text: "Stop Server"
            onClicked: tcpServer.stopServer();
        }
    }
}
