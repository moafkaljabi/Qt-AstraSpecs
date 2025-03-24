import QtQuick 2.15
import QtQuick.Controls 2.15


ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "Server Control"

    // Button to start the server
    Button {
        text: "Start Server"
        anchors.centerIn: parent
        onClicked: {
            tcpServer.startServer(); // Call the startServer() method

        }
    }

    // Button to stop the server
    Button {
        text: "Stop Server"
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: 20
        onClicked: {
            tcpServer.stopServer(); // Call the stopServer() method
        }
    }
}
