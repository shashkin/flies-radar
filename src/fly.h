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
    int ageMs() const;
    float avgSpeed() const;
    int distance() const;
    int stupidity() const;

    int index() const;
    void setIndex(int i);

signals:
    void positionChanged();
    void deadChanged();
    void distanceChanged();
    void ageChanged();
    void avgSpeedChanged();
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
    int m_age;
    int m_distance;
    int m_index;
};

class FlyCreationException : public QException
{
public:
    void raise() const { throw *this; }
    FlyCreationException *clone() const { return new FlyCreationException(*this); }
};

#endif // FLY_H
