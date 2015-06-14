// Game.h – xminar27/xvitas02

#ifndef GAME
#define GAME

// Qt libraries
#include <QGraphicsView>
#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <QColor>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPushButton>
#include <QBrush>
#include <QGraphicsPixmapItem>
#include <QPointer>

// C++ libraries
#include <cstdlib>
#include <set>
#include <ctime>
#include <algorithm>

// custom libraries
#include "Player.h"
#include "Spawn.h"
#include "Treasure.h"
#include "End.h"
#include "Stone.h"

class Game: public QGraphicsView
{
    Q_OBJECT
    public:
        // constructor
        Game(int numOfPlayers, int boardWidth, int numOfTreasures);
        // destructor
        ~Game();

        // public member functions
        int getWidth();
        int getScreenWidth();
        int getScreenHeight();
        int getWhoseTurn();
        void setWhoseTurn(int playerNo);
        void nextPlayersTurn();
        void keyPressEvent(QKeyEvent* event);
        void mousePressEvent(QMouseEvent* event);

        // public member attribute objects
        Player* player;
        Stone* stone;
        Spawn* spawn;
        Treasure* treasure;
        Treasure* treasureImg;
        Stone* standingAt;
        Stone* goingTo;
        Stone* newFreestone;

        // public member attribute Qt–specific variables
        QList<QPointF *> coords;
        QPointF freestone_pos;
        QGraphicsTextItem* treasureText;
        QGraphicsTextItem* scoreText;
        QGraphicsScene* scene;

    private:
        // private member functions
        void drawPanel(int x, int y, int width,
                       int height, QColor color, double opacity);

        // private member attribute variables
        int width;
        int whoseTurn;
        int count;
        int rotCount;
        int screenWidth;
        int screenHeight;

        // private member attribute Qt–specific variables
        QList<Spawn *> spawns;
        QList<Stone *> stones;
        QList<Treasure *> treasures;
        QList<Stone *> switch_stones;
        QList<Treasure *> switch_treasures;
        QList<Spawn *> switch_spawns;
        QList<int> treasureTypes;
        QPushButton* rotateBtn;
        QGraphicsPixmapItem* help;

    private slots:
        // slot function
        void handleButton();

};

#endif // GAME

