#include "cell.h"

#include <QDebug>

Cell::Cell(QObject *parent)
    : Cell(0, parent)
{}

Cell::Cell(int capacity, QObject *parent)
    : Cell(capacity, 0, parent)
{}

Cell::Cell(int capacity, int population, QObject *parent)
    : QObject(parent)
    , m_capacity(capacity)
    , m_population(population)
{}


int Cell::capacity() const {
    return m_capacity;
}

void Cell::setCapacity(int capacity) {
    m_capacity = capacity;
    emit capacityChanged();
}

int Cell::population() const {
    return m_population;
}

void Cell::setPopulation(int population) {
    m_population.store(population);
    emit populationChanged();
}

void Cell::increasePopulation() {
    ++m_population;
    emit populationChanged();
}

void Cell::decreasePopulation() {
    --m_population;
    emit populationChanged();
}

const QMutex& Cell::populationMutex() const {
    return m_populationMutex;
}
