import QtQuick 2.4
import QtQuick.Window 2.2

Window {
    visible: true
    width: mainView.width
    height: mainView.height

    Loader {
        id: mainView
        source: appController.viewSource
    }
}
