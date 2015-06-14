// Stone.cpp – xminar27/xvitas02

#include "Stone.h"
#include "Game.h"

/**
 * Constructor for a stone object.
 */
Stone::Stone(): QObject(), QGraphicsPixmapItem()
{
    // the stone image is 60x60px
    stoneWidth = 60;
    stoneHeight = 60;
    freestoneActive = -1;
    removeSwitch();
}

/**
 * Draw the left to bottom stone and set the
 * directions.
 */
void Stone::leftToBottom()
{
    setPixmap(QPixmap(":/images/stonelb.jpg"));
    this->eways[0] = LEFT;
    this->eways[1] = LEFT;
    this->eways[2] = DOWN;

    this->iways[0] = RIGHT;
    this->iways[1] = RIGHT;
    this->iways[2] = UP;
}

/**
 * Draw the left to right stone and set the
 * directions.
 */
void Stone::leftToRight()
{
    setPixmap(QPixmap(":/images/stonelr.jpg"));
    this->eways[0] = LEFT;
    this->eways[1] = LEFT;
    this->eways[2] = RIGHT;

    this->iways[0] = RIGHT;
    this->iways[1] = RIGHT;
    this->iways[2] = LEFT;
}

/**
 * Draw the left to top stone and set the
 * directions.
 */
void Stone::leftToTop()
{
    setPixmap(QPixmap(":/images/stonelt.jpg"));
    this->eways[0] = LEFT;
    this->eways[1] = LEFT;
    this->eways[2] = UP;

    this->iways[0] = RIGHT;
    this->iways[1] = RIGHT;
    this->iways[2] = DOWN;
}

/**
 * Draw the right to bottom stone and set the
 * directions.
 */
void Stone::rightToBottom()
{
    setPixmap(QPixmap(":/images/stonerb.jpg"));
    this->eways[0] = RIGHT;
    this->eways[1] = RIGHT;
    this->eways[2] = DOWN;

    this->iways[0] = LEFT;
    this->iways[1] = LEFT;
    this->iways[2] = UP;
}

/**
 * Draw the right to top stone and set the
 * directions.
 */
void Stone::rightToTop()
{
    setPixmap(QPixmap(":/images/stonert.jpg"));
    this->eways[0] = RIGHT;
    this->eways[1] = RIGHT;
    this->eways[2] = UP;

    this->iways[0] = LEFT;
    this->iways[1] = LEFT;
    this->iways[2] = DOWN;
}

/**
 * Draw the top to bottom stone and set the
 * directions.
 */
void Stone::topToBottom()
{
    setPixmap(QPixmap(":/images/stonetb.jpg"));
    this->eways[0] = UP;
    this->eways[1] = UP;
    this->eways[2] = DOWN;

    this->iways[0] = DOWN;
    this->iways[1] = DOWN;
    this->iways[2] = UP;
}

/**
 * Draw the T left-right-up stone and set the
 * directions.
 */
void Stone::TleftRightUp()
{
    setPixmap(QPixmap(":/images/Tstonelrt.jpg"));
    this->eways[0] = LEFT;
    this->eways[1] = RIGHT;
    this->eways[2] = UP;

    this->iways[0] = RIGHT;
    this->iways[1] = LEFT;
    this->iways[2] = DOWN;
}

/**
 * Draw the T left-right-down stone and set the
 * directions.
 */
void Stone::TleftRightDown()
{
    setPixmap(QPixmap(":/images/Tstonelrb.jpg"));
    this->eways[0] = LEFT;
    this->eways[1] = RIGHT;
    this->eways[2] = DOWN;

    this->iways[0] = RIGHT;
    this->iways[1] = LEFT;
    this->iways[2] = UP;
}

/**
 * Draw the T up-down-left stone and set the
 * directions.
 */
void Stone::TupDownLeft()
{
    setPixmap(QPixmap(":/images/Tstonetbl.jpg"));
    this->eways[0] = UP;
    this->eways[1] = DOWN;
    this->eways[2] = LEFT;

    this->iways[0] = DOWN;
    this->iways[1] = UP;
    this->iways[2] = RIGHT;
}

/**
 * Draw the T up-down-right stone and set the
 * directions.
 */
void Stone::TupDownRight()
{
    setPixmap(QPixmap(":/images/Tstonetbr.jpg"));
    this->eways[0] = UP;
    this->eways[1] = DOWN;
    this->eways[2] = RIGHT;

    this->iways[0] = DOWN;
    this->iways[1] = UP;
    this->iways[2] = LEFT;
}

/**
 * Generate a random T stone.
 * @param random Random number from 0 to 3.
 */
void Stone::TgenerateRandom(int random)
{
    switch(random)
    {
        case 0:
            TleftRightUp();
            break;
        case 1:
            TleftRightDown();
            break;
        case 2:
            TupDownLeft();
            break;
        case 3:
            TupDownRight();
            break;
    }
}

/**
 * Generate a random stone (not T stone).
 * @param random Random number from 0 to 5.
 */
void Stone::CgenerateRandom(int random)
{
    // get 6 random numbers from 0 to 5 from argument
    switch(random)
    {
        case 0:
            //setPixmap(QPixmap(":/images/stonelb.jpg"));
            leftToBottom();
            break;
        case 1:
            //setPixmap(QPixmap(":/images/stonelr.jpg"));
            leftToRight();
            break;
        case 2:
            //setPixmap(QPixmap(":/images/stonelt.jpg"));
            leftToTop();
            break;
        case 3:
            //setPixmap(QPixmap(":/images/stonerb.jpg"));
            rightToBottom();
            break;
        case 4:
            //setPixmap(QPixmap(":/images/stonert.jpg"));
            rightToTop();
            break;
        case 5:
            //setPixmap(QPixmap(":/images/stonetb.jpg"));
            topToBottom();
            break;
    }
}

/**
 * Generate any stone (T or normal).
 * @param random Random number from 0 to 9.
 */
void Stone::generateRandom(int random)
{
    // get 10 random numbers from 0 to 9 from argument
    switch(random)
    {
        case 0:
            //setPixmap(QPixmap(":/images/stonelb.jpg"));
            leftToBottom();
            break;
        case 1:
            //setPixmap(QPixmap(":/images/stonelr.jpg"));
            leftToRight();
            break;
        case 2:
            //setPixmap(QPixmap(":/images/stonelt.jpg"));
            leftToTop();
            break;
        case 3:
            //setPixmap(QPixmap(":/images/stonerb.jpg"));
            rightToBottom();
            break;
        case 4:
            //setPixmap(QPixmap(":/images/stonert.jpg"));
            rightToTop();
            break;
        case 5:
            //setPixmap(QPixmap(":/images/stonetb.jpg"));
            topToBottom();
            break;
        case 6:
            //setPixmap(QPixmap(":/images/Tstonelrb.jpg"));
            TleftRightDown();
            break;
        case 7:
            //setPixmap(QPixmap(":/images/Tstonelrt.jpg"));
            TleftRightUp();
            break;
        case 8:
            //setPixmap(QPixmap(":/images/Tstonetbl.jpg"));
            TupDownLeft();
            break;
        case 9:
            //setPixmap(QPixmap(":/images/Tstonetbr.jpg"));
            TupDownRight();
            break;
    }
}

/**
 * Getter member function.
 * @return The width of the stone in px.
 */
int Stone::getStoneWidth()
{
    return stoneWidth;
}

/**
 * Getter member function.
 * @return The height of the stone in px.
 */
int Stone::getStoneHeight()
{
    return stoneHeight;
}

/**
 * Removes the switchability of a stone.
 */
void Stone::removeSwitch()
{
    this->switchableDown = false;
    this->switchableLeft = false;
    this->switchableRight = false;
    this->switchableUp = false;
}
