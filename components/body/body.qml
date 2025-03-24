// Body.qml
import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    width: parent.width
    height: parent.height - topBar.height - bottomBar.height

    Rectangle {
        width: parent.width
        height: parent.height
        color: "#BDC3C7"

        Column {
            anchors.centerIn: parent

            Text {
                text: "IMU Data"
                font.pixelSize: 24
                color: "#2C3E50"
            }

            Rectangle {
                width: 300
                height: 200
                color: "#ECF0F1"
                border.color: "#2C3E50"
                radius: 10
                anchors.centerIn: parent

                Column {
                    spacing: 10
                    anchors.centerIn: parent

                    Text {
                        text: "IMU X: 0"
                        font.pixelSize: 18
                    }

                    Text {
                        text: "IMU Y: 0"
                        font.pixelSize: 18
                    }

                    Text {
                        text: "IMU Z: 0"
                        font.pixelSize: 18
                    }

                    // Button to update IMU data (this would be connected to the backend)
                    Button {
                        text: "Update IMU Data"
                        onClicked: {
                            // Trigger update logic from main application (C++ backend)
                            updateIMUData()
                        }
                    }
                }
            }
        }
    }

    // Function to be triggered on button click
    function updateIMUData() {
        console.log("Updating IMU data...");
        // Connect to C++ backend to fetch the latest IMU data
        appAstraSpecs.updateIMUData()  // Placeholder to trigger IMU data update from C++
    }
}
