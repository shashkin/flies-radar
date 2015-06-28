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

int AppController::boardWidth() const {
    return m_board
            ? m_board->width()
            : 0;
}

int AppController::boardHeight() const {
    return m_board
            ? m_board->height()
            : 0;
}

void AppController::createBoard(int width, int height, int capacity) {
    m_board.reset(new Board(width, height));
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            (*m_board)[i][j].reset(new Cell(capacity));
        }
    }
    emit boardChanged();
}
