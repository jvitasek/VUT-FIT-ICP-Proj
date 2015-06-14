// Player.h – xminar27/xvitas02

#ifndef PLAYER
#define PLAYER

// Qt libraries
#include <QGraphicsTextItem>
#include <QFont>

class Player: public QGraphicsTextItem
{
    public:
        // constructor
        Player(int number);

        // public member functions
        void setCurrentPlayer(int number);
        int getNumberOfPlayers();
        int getCurrentPlayer();
        void drawText(int height);

    private:
        // private member attributes
        int numberOfPlayers;
        int currentPlayer;
};

#endif // PLAYER

