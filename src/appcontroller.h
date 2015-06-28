#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <QObject>
#include <QScopedPointer>

#include "src/board.h"
#include "src/fly.h"

class AppController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString viewSource READ viewSource NOTIFY stateChanged)
    Q_PROPERTY(int boardWidth READ boardWidth NOTIFY boardChanged)
    Q_PROPERTY(int boardHeight READ boardHeight NOTIFY boardChanged)
    Q_PROPERTY(int numFlies READ numFlies NOTIFY fliesChanged)

public:
    explicit AppController(QObject *parent = 0);

    QString viewSource() const;

    int boardWidth() const;
    int boardHeight() const;

    int numFlies() const;

signals:
    void stateChanged();
    void boardChanged();
    void fliesChanged();

public slots:
    void showPreparation();
    void showAction();
    void showStatistics();

    void createBoard(int width, int height, int capacity);
    void placeFlies(int numFlies, int stupidity);

    QObject* fly(int i) const;

private:
    enum State {
        NONE,
        PREPARATION,
        ACTION,
        STATISTICS,
    };

    void setState(State state);

    State m_state;

    typedef QScopedPointer<Board> BoardPtr;
    BoardPtr m_board;

    QList<QObject*> m_flies;
};

#endif // APPCONTROLLER_H
