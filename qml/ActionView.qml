import QtQuick 2.0
import QtQuick.Controls 1.3
import QtGraphicalEffects 1.0
import QtQuick.Window 2.2

ScrollView {
    Column {
        id: root
        property int defaultCellWidth: 75
        property int defaultCellHeight: 75
        property int defaultFlyWidth: 30
        property int defaultFlyHeight: 30
        property real scale:
            Math.min(Screen.desktopAvailableWidth / (defaultCellWidth * appController.boardWidth),
                     (Screen.desktopAvailableHeight
                          - placeFlyRow.height
                          - errorText.height
                          - stopButton.height
                          - 3 * spacing)
                        / (defaultCellHeight * appController.boardHeight),
                     1)
        property int cellWidth: 75 //defaultCellWidth * scale
        property int cellHeight:75 // defaultCellHeight * scale
        property int flyWidth: 30 //defaultFlyWidth * scale
        property int flyHeight: 30 //defaultFlyHeight * scale

        spacing: 2

        Row {
            id: placeFlyRow

            spacing: 5
            enabled: board.selected !== -1

            Button {
                text: qsTr("Place fly")
                onClicked: {
                    if (board.selected === -1)
                        return;

                    if(appController.placeFly(
                        board.selected % appController.boardWidth,
                        Math.floor(board.selected / appController.boardWidth),
                        stupidityBox.value)) {
                        errorText.color = "#FFFFFF";
                    } else {
                        errorText.color = "#AA0000";
                    }
                }
            }

            Text {
                text: qsTr("with stupidity:")
                anchors.verticalCenter: parent.verticalCenter
            }

            PreparationSpinBox {
                id: stupidityBox
            }
        }

        Text {
            id: errorText
            text: qsTr("can not place a fly into cell!")
            color: "#FFFFFF"
        }

        Item {
            width: root.cellWidth * appController.boardWidth
            height: root.cellHeight * appController.boardHeight

            Grid {
                id: board

                property int selected: -1

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
                        color: board.selected === index ? "#FFFF00" : "#FFFFFF"

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                if (board.selected == index) {
                                    board.selected = -1;
                                } else {
                                    board.selected = index;
                                }
                            }
                        }
                    }
                }
            }

            Repeater {
                anchors.fill: board

                model: appController.flyModel

                delegate: Item {
                    width: root.flyWidth
                    height: root.flyHeight

                    x: root.cellWidth * position.x + Math.floor(Math.random() * (root.cellWidth - root.flyWidth))
                    y: root.cellHeight * position.y + Math.floor(Math.random() * (root.cellHeight - root.flyHeight));

                    Behavior on x {
                        NumberAnimation { duration: 200 }
                    }
                    Behavior on y {
                        NumberAnimation { duration: 200 }
                    }

                    Image {
                        id: fly
                        anchors.fill: parent
                        source: isDead ? "qrc:/img/dead_fly.png" : "qrc:/img/fly.png"
                    }

                    ColorOverlay {
                        anchors.fill: fly
                        source: fly
                        color: Qt.rgba(1, 0, 0, stupidity)
                    }
                }
            }
        }

        Button {
            id: stopButton
            text: qsTr("Stop")
            onClicked: {
                appController.deactivateFlies();
                appController.showStatistics();
            }
        }
    }
}
