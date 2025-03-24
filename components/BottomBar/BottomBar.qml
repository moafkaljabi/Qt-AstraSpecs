// BottomBar.qml
import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    width: parent.width
    height: 50

    Rectangle {
        width: parent.width
        height: 50
        color: "#34495E"

        Text {
            anchors.centerIn: parent
            color: "white"
            text: "Server Status: Waiting for connection..."
            font.pixelSize: 16
        }
    }
}
