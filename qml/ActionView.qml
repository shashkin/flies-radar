import QtQuick 2.0
import QtQuick.Controls 1.3

Column {
    id: root
    property int cellWidth: 75
    property int cellHeight: 75
    property int flyWidth: 20
    property int flyHeight: 20

    spacing: 2

    Row {
        spacing: 5

        Button {
            text: qsTr("Start")
            onClicked: {
                appController.activateFlies();
            }
        }

        Button {
            text: qsTr("Stop")
            onClicked: {
                appController.deactivateFlies();
            }
        }
    }

    Item {
        width: root.cellWidth * appController.boardWidth
        height: root.cellHeight * appController.boardHeight

        Grid {
            id: board


            columns: appController.boardWidth

            Repeater {
                model: appController.boardWidth * appController.boardHeight

                Rectangle {
                    width: root.cellWidth
                    height: root.cellHeight
                    border {
                        width: 1
                        color: "#555555"
                    }
                }
            }
        }

        Repeater {
            anchors.fill: board

            model: appController.flyModel

            delegate: Image {
                width: root.flyWidth
                height: root.flyHeight
                source: isDead ? "qrc:/img/dead_fly.png" : "qrc:/img/fly.png"

                x: root.cellWidth * position.x + Math.floor(Math.random() * (root.cellWidth - root.flyWidth))
                y: root.cellHeight * position.y + Math.floor(Math.random() * (root.cellHeight - root.flyHeight));
            }
        }
    }
}
