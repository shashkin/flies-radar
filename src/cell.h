#ifndef CELL_H
#define CELL_H

#include <QObject>
#include <QMutex>
#include <QAtomicInt>

class Cell : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int capacity READ capacity WRITE setCapacity NOTIFY capacityChanged)
    Q_PROPERTY(int population READ population WRITE setPopulation NOTIFY populationChanged)
public:
    explicit Cell(QObject *parent = 0);
    Cell(int capacity, QObject *parent = 0);
    Cell(int capacity, int population, QObject *parent = 0);

    int capacity() const;
    void setCapacity(int capacity);

    int population() const;
    void setPopulation(int population);
    void increasePopulation();
    void decreasePopulation();

    const QMutex& populationMutex() const;

signals:
    void capacityChanged();
    void populationChanged();

public slots:

private:
    int m_capacity;
    QAtomicInt m_population;
    QMutex m_populationMutex;
};

#endif // CELL_H
