#ifndef FLY_H
#define FLY_H

#include <QObject>
#include <QPoint>
#include <QTimer>
#include <QException>

#include "src/board.h"

class Fly : public QObject
{
    Q_OBJECT
public:
    Fly(int stupidity,
        int maxAge,
        const QPoint& position,
        Board* board,
        QObject* parent = 0);

    const QPoint& position() const;
    bool dead() const;

signals:
    void positionChanged();
    void deadChanged();
    void stopped();

public slots:
    void start();
    void stop();

private slots:
    void tryJump();
    void makeDead();

private:
    void think();

    int m_stupidity;
    QPoint m_position;
    Board* m_board;
    QTimer m_thinkTimer;
    QTimer m_lifeTimer;
    bool m_dead;
};

class FlyCreationException : public QException
{
public:
    void raise() const { throw *this; }
    FlyCreationException *clone() const { return new FlyCreationException(*this); }
};

#endif // FLY_H
