#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <QObject>

class AppController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString viewSource READ viewSource NOTIFY stateChanged)

public:
    explicit AppController(QObject *parent = 0);

    QString viewSource() const;

signals:
    void stateChanged();

public slots:
    void showPreparation();
    void showAction();
    void showStatistics();

private:
    enum State {
        NONE,
        PREPARATION,
        ACTION,
        STATISTICS,
    };

    void setState(State state);

    State m_state;
};

#endif // APPCONTROLLER_H
