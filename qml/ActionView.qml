import QtQuick 2.0
import QtQuick.Controls 1.3

Column {
    spacing: 2

    Row {
        spacing: 5

        Button {
            text: qsTr("Start")
        }

        Button {
            text: qsTr("Stop")
        }
    }

    Grid {
        columns: appController.boardWidth

        Repeater {
            model: appController.boardWidth * appController.boardHeight

            Rectangle {
                width: 50
                height: 50
                border {
                    width: 1
                    color: "#555555"
                }
            }
        }
    }
}
