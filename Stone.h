// Stone.h – xminar27/xvitas02

#ifndef STONE
#define STONE

// Qt libraries
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

class Stone: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    public:
        // constructor
        Stone();

        // member functions
        int getStoneWidth();
        int getStoneHeight();
        void leftToBottom();
        void leftToRight();
        void leftToTop();
        void rightToBottom();
        void rightToTop();
        void topToBottom();
        void TleftRightUp();
        void TleftRightDown();
        void TupDownLeft();
        void TupDownRight();
        void TgenerateRandom(int random);
        void CgenerateRandom(int random);
        void generateRandom(int random);
        void removeSwitch();

        // public member attributes
        enum CANGO{DOWN, UP, RIGHT, LEFT};
        CANGO eways[3];
        CANGO iways[3];
        bool switchableDown;
        bool switchableUp;
        bool switchableLeft;
        bool switchableRight;
        int freestoneActive;

    private:
        // private member attributes
        int stoneWidth;
        int stoneHeight;
};

#endif // STONE
