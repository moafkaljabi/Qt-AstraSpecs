// TopBar.qml
import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    width: parent.width
    height: 50

    Rectangle {
        width: parent.width
        height: 50
        color: "#2C3E50"

        Text {
            anchors.centerIn: parent
            color: "white"
            text: "AstraSpecs - Control Panel"
            font.pixelSize: 20
        }

        // Start Server Button
        Button {
            text: "Start Server"
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.margins: 10
            onClicked: {
                // Trigger start server logic from main application
                startServer()
            }
        }
    }

    // Function to be triggered on button click
    function startServer() {
        console.log("Starting server...");
        // You would connect this to your C++ backend to start the TCP server
        appAstraSpecs.startServer()  // Placeholder to trigger startServer() from C++
    }
}
