#include "fly.h"

#include <QMutexLocker>

Fly::Fly(int stupidity, int maxAgeSeconds, const QPoint& position, Board* board, QObject* parent)
    : QObject(parent)
    , m_stupidity(stupidity)
    , m_position(position)
    , m_board(board)
    , m_thinkTimer(this)
    , m_lifeTimer(this)
    , m_dead(false)
{
    CellPtr cell = (*m_board)[position.x()][position.y()];
    {
        QMutexLocker lock(cell->populationMutex());
        if (cell->full()) {
            throw FlyCreationException();
        } else {
            cell->increasePopulation();
        }
    }

    m_thinkTimer.setSingleShot(true);
    m_lifeTimer.setSingleShot(true);
    m_lifeTimer.setInterval(maxAgeSeconds * 1000);

    connect(&m_thinkTimer, &QTimer::timeout, this, &Fly::tryJump);
    connect(&m_lifeTimer, &QTimer::timeout, this, &Fly::makeDead);
}

const QPoint& Fly::position() const {
    return m_position;
}

bool Fly::dead() const {
    return m_dead;
}

void Fly::makeDead() {
    m_dead = true;
    emit deadChanged();
    stop();
}

void Fly::start() {
    m_lifeTimer.start();
    think();
}

void Fly::think() {
    m_thinkTimer.setInterval((qrand() % (m_stupidity * 1000)) + 1);
    m_thinkTimer.start();
}

void Fly::stop() {
    m_thinkTimer.stop();
    m_lifeTimer.stop();
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
        think();
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

    think();
}
