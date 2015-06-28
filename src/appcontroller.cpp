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

int AppController::numFlies() const {
    return m_flies.size();
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

void AppController::placeFlies(int numFlies, int stupidity) {
    if (!m_board)
        return;

    QList<QPair<QPoint, CellPtr> > vacantCells;
    for (int i = 0; i < m_board->width(); ++i) {
        for (int j = 0; j < m_board->height(); ++j) {
            vacantCells.append(qMakePair(QPoint(i, j), m_board->at(i, j)));
        }
    }

    for (int i = 0; i < numFlies; ++i) {
        int cellIndex = qrand() % vacantCells.size();
        m_flies.append(new Fly(stupidity, vacantCells.at(cellIndex).first, m_board.data(), this));
        if (vacantCells.at(cellIndex).second->full()) {
            vacantCells.removeAt(cellIndex);
        }
    }
    emit fliesChanged();
}

QObject* AppController::fly(int i) const {
    return m_flies.at(i);
}
