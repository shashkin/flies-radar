import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Controls 1.3

Window {
    visible: true
    width: 640
    height: 480
    minimumWidth: 200
    minimumHeight: 300
    title: qsTr("Flies Radar")

    Loader {
        anchors.fill: parent
        source: appController.viewSource
    }
}
