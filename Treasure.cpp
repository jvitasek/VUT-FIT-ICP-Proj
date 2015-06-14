// Treasure.cpp – xminar27/xvitas02

#include "Treasure.h"
#include "Game.h"

/**
 * Constructor for a treasure object.
 */
Treasure::Treasure(int number): QObject(), QGraphicsPixmapItem()
{
    // initializing the number of treasures
    numberOfTreasures = number;
    // initializing the type of the treasure
    type = -1;
}

/**
 * Generate a treasure to a specified position.
 * @param  random      Random number from 0 to 3.
 * @param  board_width The width of the board.
 * @param  coords      Where to generate the treasure.
 * @return             0 on failure, 1 on success.
 */
int Treasure::generateTreasure(int random, int board_width, QList<QPointF>& coords)
{
    int random_row = (rand() % (board_width));
    int random_col = (rand() % (board_width));
    int stone_width = 60;
    int stone_height = 60;

    // new point to test with
    QPointF current;
    current.setX(random_row*stone_width);
    current.setY(random_col*stone_height);

    // if there's anything inside
    if(coords.size() > 0)
    {
        // iterate over the treasure coords
        for(int i = 0; i < coords.size(); i++)
        {
            // if there is the same position as another treasure, return 0
            if((coords.at(i).x() == current.x()) && (coords.at(i).y() == current.y()))
            {
                return 0;
            }
        }
    }

    // if we have unique coords, append
    coords.append(current);

    switch(random)
    {
        case 0:
            setPixmap(QPixmap(":/images/treasure1.png"));
            type = 1;
            this->setPos(random_row*stone_width, random_col*stone_height);
            break;
        case 1:
            type = 2;
            setPixmap(QPixmap(":/images/treasure2.png"));
            this->setPos(random_row*stone_width, random_col*stone_height);
            break;
        case 2:
            type = 3;
            setPixmap(QPixmap(":/images/treasure3.png"));
            this->setPos(random_row*stone_width, random_col*stone_height);
            break;
        case 3:
            type = 4;
            setPixmap(QPixmap(":/images/treasure4.png"));
            this->setPos(random_row*stone_width, random_col*stone_height);
            break;
    }
    return 1;
}

/**
 * Draw the treasure image.
 * @param number The type of the treasure.
 */
void Treasure::drawTreasure(int number)
{
    switch(number)
    {
        case 1:
            this->setPixmap(QPixmap(":/images/treasure1.png"));
            break;
        case 2:
            this->setPixmap(QPixmap(":/images/treasure2.png"));
            break;
        case 3:
            this->setPixmap(QPixmap(":/images/treasure3.png"));
            break;
        case 4:
            this->setPixmap(QPixmap(":/images/treasure4.png"));
            break;
    }
}

/**
 * Getter member function.
 * @return The type of the treasure.
 */
int Treasure::getType()
{
    return type;
}
