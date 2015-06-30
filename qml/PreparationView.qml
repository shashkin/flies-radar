import QtQuick 2.0
import QtQuick.Controls 1.3

Rectangle {
    width: 200
    height: 300
    anchors.centerIn: parent

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

        Button {
            text: qsTr("Start!")
            onClicked: {
                appController.createBoard(widthBox.value, heightBox.value, capacityBox.value);
                appController.showAction();
            }
        }
    }
}

