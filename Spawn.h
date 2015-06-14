// Spawn.h – xminar27/xvitas02

#ifndef SPAWN
#define SPAWN

// Qt libraries
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

class Spawn: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

    public:
        // constructor
        Spawn(int pos, int boundary);

        // public member functions
        void setPlayerNo(int number);
        int getPlayerNo();
        void moveToStone(QPointF coords);
        void setTreasureType(int number);
        int getTreasureType();
        int getScore();
        void increaseScore();

    private:
        // private member attributes
        int playerNo;
        int treasureType; // rand 0 – 3 (4 types of treasures)
        int score;
};

#endif // SPAWN

