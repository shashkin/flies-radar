#include "appcontroller.h"

AppController::AppController(QObject *parent)
    : QObject(parent)
    , m_state(NONE)
{

}

void AppController::setState(State state) {
    m_state = state;
    emit stateChanged();
}

void AppController::showPreparation() {
    setState(PREPARATION);
}

void AppController::showAction() {
    setState(ACTION);
}

void AppController::showStatistics() {
    setState(STATISTICS);
}

QString AppController::viewSource() const {
    switch (m_state) {
    case PREPARATION:
        return QStringLiteral("qrc:/qml/PreparationView.qml");
    case ACTION:
        return QStringLiteral("qrc:/qml/ActionView.qml");
    case STATISTICS:
        return QStringLiteral("qrc:/qml/StatisticsView.qml");
    default:
        return QStringLiteral("");
    }
}
