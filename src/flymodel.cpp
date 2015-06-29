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

bool FlyModel::placeFly(int x, int y, int stupidity, Board *board) {
    int maxAge = stupidity * (board->width() + board->height()) / 2;

    Fly* fly;
    try {
        fly = new Fly(stupidity, maxAge, QPoint(x, y), board);
    } catch (FlyCreationException& e) {
        return false;
    }

    QThread* thread = new QThread;
    fly->moveToThread(thread);

    connect(thread, &QThread::started, fly, &Fly::start);
    connect(fly, &Fly::stopped, thread, &QThread::quit);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    connect(fly, &Fly::positionChanged, this, &FlyModel::positionChanged);
    connect(fly, &Fly::deadChanged, this, &FlyModel::deadChanged);

    connect(this, &FlyModel::deactivateFlies, fly, &Fly::stop);

    connect(qApp, &QCoreApplication::aboutToQuit, fly, &Fly::deleteLater);

    int index = m_flies.size();
    beginInsertRows(QModelIndex(), index, index);
    m_flies.append(fly);
    endInsertRows();

    thread->start();
    return true;
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
