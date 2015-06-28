#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <QObject>
#include <QScopedPointer>
#include <QSharedPointer>

#include "src/matrix.h"
#include "src/cell.h"

class AppController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString viewSource READ viewSource NOTIFY stateChanged)
    Q_PROPERTY(int boardWidth READ boardWidth NOTIFY boardChanged)
    Q_PROPERTY(int boardHeight READ boardHeight NOTIFY boardChanged)

public:
    explicit AppController(QObject *parent = 0);

    QString viewSource() const;

    int boardWidth() const;
    int boardHeight() const;

signals:
    void stateChanged();
    void boardChanged();

public slots:
    void showPreparation();
    void showAction();
    void showStatistics();

    void createBoard(int width, int height, int capacity);

private:
    enum State {
        NONE,
        PREPARATION,
        ACTION,
        STATISTICS,
    };

    void setState(State state);

    State m_state;

    typedef QSharedPointer<Cell> CellPtr;
    typedef Matrix<CellPtr> Board;
    typedef QScopedPointer<Board> BoardPtr;
    BoardPtr m_board;
};

#endif // APPCONTROLLER_H
