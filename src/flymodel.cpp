#include "flymodel.h"

#include <QCoreApplication>
#include <QThread>

FlyModel::FlyModel(QObject* parent)
    : QAbstractListModel(parent)
{}

int FlyModel::rowCount(const QModelIndex& /*parent*/) const {
    return m_flies.size();
}

QVariant FlyModel::data(const QModelIndex& index, int /*role*/) const {
    return m_flies.at(index.row())->position();
}

QHash<int, QByteArray> FlyModel::roleNames() const
{
    static QHash<int, QByteArray> roles;
    if (roles.empty()) {
        roles[Qt::DisplayRole] = "position";
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

        QThread* thread = new QThread;
        Fly* fly = new Fly(personalStupidity, vacantCells.at(cellIndex).first, board);
        fly->moveToThread(thread);

        connect(fly, &Fly::positionChanged, this, &FlyModel::positionChanged);
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
    Fly* fly = qobject_cast<Fly*>(sender());
    if (!fly)
        return;

    int row = m_flies.indexOf(fly);
    if (row == -1)
        return;

    QModelIndex modelIndex = createIndex(row, 1);

    emit dataChanged(modelIndex, modelIndex);
}
