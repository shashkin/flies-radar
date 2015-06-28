#ifndef FLYMODEL_H
#define FLYMODEL_H

#include <QAbstractListModel>

#include "src/fly.h"

class FlyModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit FlyModel(QObject* parent = 0);

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;

    void placeFlies(int numFlies, int stupidity, Board* board);

signals:
    void activateFlies();
    void deactivateFlies();

private slots:
    void positionChanged();
    void deadChanged();

private:
    void changed(Fly* fly, int role);

    QList<Fly*> m_flies;
};

#endif // FLYMODEL_H
