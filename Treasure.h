// Treasure.h – xminar27/xvitas02

#ifndef TREASURE
#define TREASURE

// Qt libraries
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QPointF>

// custom libraries
#include "Stone.h"

class Treasure: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    public:
        // constructor
        Treasure(int number);

        // public member functions
        int generateTreasure(int random, int board_width, QList<QPointF> &coords);
        void drawTreasure(int number);
        int getType();

    private:
        // private member attributes
        int numberOfTreasures;
        int type;
};

#endif // TREASURE

