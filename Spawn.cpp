// Spawn.cpp – xminar27/xvitas02

#include "Spawn.h"

/**
 * Constructor for a spawn object.
 */
Spawn::Spawn(int pos, int boundary): QObject(), QGraphicsPixmapItem()
{
    score = 0;
    switch(pos)
    {
    case 0:
        setPixmap(QPixmap(":/images/player1.png"));
        this->setPos(0, 0);
        break;
    case 1:
        setPixmap(QPixmap(":/images/player2.png"));
        this->setPos(boundary, boundary);
        break;
    case 2:
        setPixmap(QPixmap(":/images/player3.png"));
        this->setPos(boundary, 0);
        break;
    case 3:
        setPixmap(QPixmap(":/images/player4.png"));
        this->setPos(0, boundary);
        break;
    }
}

/**
 * Setter member function.
 * @param number Set the number of the player.
 */
void Spawn::setPlayerNo(int number)
{
    playerNo = number;
}

/**
 * Getter member function.
 * @return Get the number of the player.
 */
int Spawn::getPlayerNo()
{
    return playerNo;
}

/**
 * Move the player to a different stone.
 * @param coords Coordinates of the stone.
 */
void Spawn::moveToStone(QPointF coords)
{
    setPos(coords.x(), coords.y());
}

/**
 * Setter member function.
 * @param number The type of the treasure.
 */
void Spawn::setTreasureType(int number)
{
    treasureType = number;
}

/**
 * Getter member function.
 * @return The target treasure type.
 */
int Spawn::getTreasureType()
{
    return treasureType;
}

/**
 * Getter member function.
 * @return The score of the player.
 */
int Spawn::getScore()
{
    return score;
}

/**
 * Increase the score of the player by one.
 */
void Spawn::increaseScore()
{
    score++;
}
