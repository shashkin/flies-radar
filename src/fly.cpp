#include "fly.h"

Fly::Fly(int stupidity, const QPoint& position, Board* board, QObject* parent)
    : QObject(parent)
    , m_stupidity(stupidity)
    , m_position(position)
    , m_board(board)
{
    (*m_board)[position.x()][position.y()]->increasePopulation();
}

int Fly::x() const {
    return m_position.x();
}

int Fly::y() const {
    return m_position.y();
}
