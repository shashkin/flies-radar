#include "fly.h"

#include <QMutexLocker>
#include <QThread>

Fly::Fly(int stupidity, const QPoint& position, Board* board, QObject* parent)
    : QObject(parent)
    , m_stupidity(stupidity)
    , m_position(position)
    , m_board(board)
    , m_thinkTimer(this)
{
    (*m_board)[position.x()][position.y()]->increasePopulation();
    m_thinkTimer.setSingleShot(true);

    connect(&m_thinkTimer, &QTimer::timeout, this, &Fly::tryJump);
}

const QPoint& Fly::position() const {
    return m_position;
}

void Fly::start() {
    m_thinkTimer.setInterval((qrand() % (m_stupidity * 1000)) + 1);
    m_thinkTimer.start();
}

void Fly::stop() {
    m_thinkTimer.stop();
    emit stopped();
}

void Fly::tryJump() {
    QList<QPoint> availablePositions;
    if (m_position.x() > 0) {
        availablePositions.append(m_position - QPoint(1, 0));
    }
    if (m_position.y() > 0) {
        availablePositions.append(m_position - QPoint(0, 1));
    }
    if (m_position.x() < m_board->width() - 1) {
        availablePositions.append(m_position + QPoint(1, 0));
    }
    if (m_position.y() < m_board->height() - 1) {
        availablePositions.append(m_position + QPoint(0, 1));
    }
    if (availablePositions.empty()) {
        stop();
        return;
    }

    int i = qrand() % availablePositions.size();
    QPoint newPosition = availablePositions.at(i);
    QPoint oldPosition = m_position;

    bool canJump;
    CellPtr cell = m_board->at(newPosition);
    {
        QMutexLocker lock(cell->populationMutex());
        canJump = !cell->full();
        if (canJump) {
            cell->increasePopulation();
        }
    }
    if (canJump) {
        m_board->at(oldPosition)->decreasePopulation();
        m_position = newPosition;
        emit positionChanged();
    }

    start();
}
