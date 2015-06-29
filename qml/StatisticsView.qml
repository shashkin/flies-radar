import QtQuick 2.0
import QtQuick.Controls 1.3

TableView {
    width: 605

    model: appController.flyModel

    TableViewColumn {
        role: "index"
        title: qsTr("Fly number")
        width: 120
        delegate: Text {
            text: styleData.value + 1
            horizontalAlignment: Text.AlignRight
        }
    }

    TableViewColumn {
        role: "isDead"
        title: qsTr("Is Dead?")
        width: 120
        horizontalAlignment: Text.AlignHCenter
        delegate: Text {
            text: styleData.value ? qsTr("Yes") : qsTr("No")
            horizontalAlignment: Text.AlignHCenter
        }
    }

    TableViewColumn {
        role: "ageMs"
        title: qsTr("Age")
        width: 120
        horizontalAlignment: Text.AlignHCenter
        delegate: Text {
            text: (styleData.value / 1000).toFixed(2)
            horizontalAlignment: Text.AlignHCenter
        }
    }

    TableViewColumn {
        role: "distance"
        title: qsTr("Distance")
        width: 120
        horizontalAlignment: Text.AlignHCenter
    }

    TableViewColumn {
        role: "avgSpeed"
        title: qsTr("Avg Speed")
        width: 120
        delegate: Text {
            text: styleData.value.toFixed(2)
            horizontalAlignment: Text.AlignHCenter
        }
    }

}

