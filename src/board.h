#ifndef BOARD
#define BOARD

#include <QSharedPointer>

#include "src/matrix.h"
#include "src/cell.h"

typedef QSharedPointer<Cell> CellPtr;
typedef Matrix<CellPtr> Board;

#endif // BOARD

