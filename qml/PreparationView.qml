import QtQuick 2.0
import QtQuick.Controls 1.3

Rectangle {
    width: 200
    height: 300

    Grid {
        columns: 2
        spacing: 5
        anchors.centerIn: parent

        Text {
            text: qsTr("Width:")
        }

        PreparationSpinBox {
            id: widthBox
        }

        Text {
            text: qsTr("Height:")
        }

        PreparationSpinBox {
            id: heightBox
        }

        Text {
            text: qsTr("Cell capacity:")
        }

        PreparationSpinBox {
            id: capacityBox
        }


        Text {
            text: qsTr("Number of flies:")
        }

        PreparationSpinBox {
            id: numFliesBox
        }

        Text {
            text: qsTr("Max stupidity:")
        }

        PreparationSpinBox {
            id: stupidityBox
        }

        Button {
            text: qsTr("Start!")
            onClicked: {
                if (numFliesBox.value > widthBox.value * heightBox.value * capacityBox.value)
                    return;

                appController.createBoard(widthBox.value, heightBox.value, capacityBox.value);
                appController.placeFlies(numFliesBox.value, stupidityBox.value);
                appController.showAction();
            }
        }
    }
}

