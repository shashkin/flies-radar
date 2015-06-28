#ifndef FLY_H
#define FLY_H

#include <QObject>
#include <QPoint>
#include <QTimer>

#include "src/board.h"

class Fly : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int x READ x NOTIFY positionChanged)
    Q_PROPERTY(int y READ y NOTIFY positionChanged)
public:
    Fly(int stupidity, const QPoint& position, Board* board, QObject* parent = 0);

    int x() const;
    int y() const;

signals:
    void positionChanged();

public slots:

private:
    typedef QSharedPointer<Cell> CellPtr;
    typedef Matrix<CellPtr> Board;

    int m_stupidity;
    QPoint m_position;
    Board* m_board;
    QTimer m_thinkTimer;
};

#endif // FLY_H
