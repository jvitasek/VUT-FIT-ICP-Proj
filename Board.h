#ifndef BOARD
#define BOARD

#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QObject>

class Board: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Board(QGraphicsItem* parent = 0);
};

#endif // BOARD

