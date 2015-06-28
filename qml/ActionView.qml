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

    Item {
        width: board.cellWidth * appController.boardWidth
        height: board.cellHeight * appController.boardHeight

        Grid {
            id: board
            property int cellWidth: 50
            property int cellHeight: 50

            columns: appController.boardWidth

            Repeater {
                model: appController.boardWidth * appController.boardHeight

                Rectangle {
                    width: board.cellWidth
                    height: board.cellHeight
                    border {
                        width: 1
                        color: "#555555"
                    }
                }
            }
        }

        Item {
            anchors.fill: board

            Repeater {
                model: appController.numFlies

                Rectangle {
                    width: 10
                    height: 10
                    color: "#000000"

                    x: board.cellWidth * appController.fly(index).x + Math.floor(Math.random() * (board.cellWidth - 10))
                    y: board.cellHeight * appController.fly(index).y + Math.floor(Math.random() * (board.cellHeight - 10));
                }
            }
        }
    }
}
