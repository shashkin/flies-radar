#include "flymodel.h"

#include <Qt>
#include <QCoreApplication>
#include <QThread>

namespace {

enum ModelDataRole {
    PositionRole = Qt::UserRole + 1,
    IsDeadRole,
};

}

FlyModel::FlyModel(QObject* parent)
    : QAbstractListModel(parent)
{}

int FlyModel::rowCount(const QModelIndex& /*parent*/) const {
    return m_flies.size();
}

QVariant FlyModel::data(const QModelIndex& index, int role) const {
    Fly* fly = m_flies.at(index.row());

    switch (role) {
    case PositionRole:
        return fly->position();
    case IsDeadRole:
        return fly->dead();
    default:
        return QVariant(QVariant::Invalid);
    }

    return m_flies.at(index.row())->position();
}

QHash<int, QByteArray> FlyModel::roleNames() const
{
    static QHash<int, QByteArray> roles;
    if (roles.empty()) {
        roles[PositionRole] = "position";
        roles[IsDeadRole] = "isDead";
    }
    return roles;
}

void FlyModel::placeFlies(int numFlies, int stupidity, Board* board) {
    beginResetModel();

    QList<QPair<QPoint, CellPtr> > vacantCells;
    for (int i = 0; i < board->width(); ++i) {
        for (int j = 0; j < board->height(); ++j) {
            vacantCells.append(qMakePair(QPoint(i, j), board->at(i, j)));
        }
    }

    for (int i = 0; i < numFlies; ++i) {
        int cellIndex = qrand() % vacantCells.size();
        int personalStupidity = (qrand() % stupidity) + 1;
        int maxAge = personalStupidity * (board->width() + board->height()) / 2;

        QThread* thread = new QThread;
        Fly* fly = new Fly(personalStupidity, maxAge, vacantCells.at(cellIndex).first, board);
        fly->moveToThread(thread);

        connect(fly, &Fly::positionChanged, this, &FlyModel::positionChanged);
        connect(fly, &Fly::deadChanged, this, &FlyModel::deadChanged);
        connect(thread, &QThread::finished, thread, &QThread::deleteLater);
        connect(this, &FlyModel::activateFlies, fly, &Fly::start);
        connect(this, &FlyModel::deactivateFlies, fly, &Fly::stop);
        connect(fly, &Fly::stopped, thread, &QThread::quit);
        connect(qApp, &QCoreApplication::aboutToQuit, fly, &Fly::deleteLater);
        thread->start();

        m_flies.append(fly);
        if (vacantCells.at(cellIndex).second->full()) {
            vacantCells.removeAt(cellIndex);
        }
    }

    endResetModel();
}

void FlyModel::positionChanged() {
    changed(qobject_cast<Fly*>(sender()), PositionRole);
}

void FlyModel::deadChanged() {
    changed(qobject_cast<Fly*>(sender()), IsDeadRole);
}

void FlyModel::changed(Fly* fly, int role) {
    if (!fly)
        return;

    int row = m_flies.indexOf(fly);
    if (row == -1)
        return;

    QModelIndex modelIndex = createIndex(row, 1);

    emit dataChanged(modelIndex, modelIndex, QVector<int>(1, role));
}
