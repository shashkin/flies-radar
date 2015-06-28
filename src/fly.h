#ifndef FLY_H
#define FLY_H

#include <QObject>
#include <QPoint>
#include <QTimer>

#include "src/board.h"

class Fly : public QObject
{
    Q_OBJECT
public:
    Fly(int stupidity, const QPoint& position, Board* board, QObject* parent = 0);

    const QPoint& position() const;

signals:
    void positionChanged();
    void stopped();

public slots:
    void start();
    void stop();

private slots:
    void tryJump();

private:
    typedef QSharedPointer<Cell> CellPtr;
    typedef Matrix<CellPtr> Board;

    int m_stupidity;
    QPoint m_position;
    Board* m_board;
    QTimer m_thinkTimer;
};

#endif // FLY_H
