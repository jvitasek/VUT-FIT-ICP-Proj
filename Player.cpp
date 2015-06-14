// Player.cpp – xminar27/xvitas02

#include "Player.h"

/**
 * Constructor for a player object.
 */
Player::Player(int number): QGraphicsTextItem()
{
    // initializing the counter
    numberOfPlayers = number;
    currentPlayer = 1;
}

/**
 * Outputs the text to the scene.
 */
void Player::drawText(int height)
{
    setPlainText(QString("Player: ") + QString::number(currentPlayer) + QString("/") + QString::number(numberOfPlayers));
    setDefaultTextColor(Qt::white);
    setFont(QFont("Arial", 18));
    this->setPos(0, height-78);
}

/**
 * Getter member function.
 * @return The number of players.
 */
int Player::getNumberOfPlayers()
{
    return numberOfPlayers;
}

/**
 * Getter member function.
 * @return The number of the current player.
 */
int Player::getCurrentPlayer()
{
    return currentPlayer;
}

/**
 * Setter member function.
 * @param number The number to set the current number to.
 */
void Player::setCurrentPlayer(int number)
{
    currentPlayer = number;
}
