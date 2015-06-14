// Game.cpp – xminar27/xvitas02

#include "Game.h"

/**
 * The class containing the primary game–generating code
 * and setting up the rudimental functionality (scene).
 */
Game::Game(int numOfPlayers, int boardWidth, int numOfTreasures)
{
    count = 0;
    rotCount = 0;

    // creating a scene
    scene = new QGraphicsScene();

    // setting up screen dimensions
    switch(boardWidth)
    {
        case 5:
            screenWidth = 800;
            screenHeight = 600;
            break;
        case 6:
            screenWidth = 800;
            screenHeight = 600;
            break;
        case 7:
            screenWidth = 800;
            screenHeight = 600;
            break;
        case 8:
            screenWidth = 1024;
            screenHeight = 768;
            break;
        case 9:
            screenWidth = 1024;
            screenHeight = 768;
            break;
        case 10:
            screenWidth = 1024;
            screenHeight = 768;
            break;
        case 11:
            screenWidth = 1024;
            screenHeight = 800;
            break;
    }

    // so the scene does not autosize
    scene->setSceneRect(0, 0, screenWidth, screenHeight);
    setBackgroundBrush(QBrush(QImage(":/images/bg2.png")));

    // drawing help
    help = new QGraphicsPixmapItem;
    help->setPos(screenWidth-350, screenHeight-222);
    help->setPixmap(QPixmap(":/images/help.png"));
    scene->addItem(help);

    // visualising the scene
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // so the scene does not autosize
    setFixedSize(screenWidth, screenHeight);

    // setting the initial width
    width = boardWidth;

    // creating the info panel
    drawPanel(0, screenHeight-100, screenWidth, 100, Qt::gray, 0.5);

    // creating the player counter
    player = new Player(numOfPlayers);
    player->drawText(screenHeight);
    scene->addItem(player);

    // adding the game stones
    srand(time(NULL));
    for(int row = 0; row < width; row++)
    {
        for(int col = 0; col < width; col++)
        {
            Stone* stone = new Stone;
            // random T stone (0 – 3 -> 4 numbers)
            int randomT = rand() % 4;
            // random stone (0 – 5 -> 6 numbers)
            int randomC = rand() % 6;
            // dimensions
            int stone_width = stone->getStoneWidth();
            int stone_height = stone->getStoneHeight();
            int x = col * stone_width;
            int y = row * stone_height;
            // placing the stones
            if(col == 0 && row == 0) stone->rightToBottom();
            else if(col == width-1 && row == 0) stone->leftToBottom();
            else if(col == 0 && row == width-1) stone->rightToTop();
            else if(col == width-1 && row == width-1) stone->leftToTop();
            // placing the Tstones to position–specific locations
            else if(col%2 == 0 && row%2 == 0 && row == 0) stone->TleftRightDown();
            else if(col%2 == 0 && row%2 == 0 && row == width-1) stone->TleftRightUp();
            else if(col%2 == 0 && row%2 == 0 && col == 0) stone->TupDownRight();
            else if(col%2 == 0 && row%2 == 0 && col == width-1) stone->TupDownLeft();
            // placing random Tstones
            else if(col%2 == 0 && row%2 == 0) stone->TgenerateRandom(randomT);
            // placing random stones
            else stone->CgenerateRandom(randomC);
            stone->setPos(x, y);
            // enabling switching on specific stones
            if(row == 0 && col%2)
            {
                stone->switchableDown = true;
            }
            else if(row%2 && col == 0)
            {
                stone->switchableRight = true;
            }
            else if(row%2 && col == width-1)
            {
                stone->switchableLeft = true;
            }
            else if(col%2 && row == width-1)
            {
                stone->switchableUp = true;
            }
            stones.append(stone);
            scene->addItem(stone);
        }
    }

    // adding the freestone
    Stone* stone = new Stone;
    freestone_pos.setX(width*stone->getStoneWidth() + 30);
    freestone_pos.setY(0);
    stone->generateRandom(rand() % 10);
    stone->setPos(freestone_pos);
    stone->freestoneActive = 1;
    stones.append(stone);
    scene->addItem(stone);

    // adding the free stone rotator button
    rotateBtn = new QPushButton("Rotate Freestone");
    rotateBtn->setObjectName("rotateBtn");
    rotateBtn->setGeometry(width*stone->getStoneWidth()
                           + 40 + stone->getStoneWidth(),
                           15,
                           150, 35);
    scene->addWidget(rotateBtn);
    connect(rotateBtn, SIGNAL(released()), this, SLOT(handleButton()));

    // populating the board with treasures
    int generatedCount = 0;
    // container to hold all treasure coords
    QList<QPointF> coords;
    for(int i = 0; generatedCount < numOfTreasures; i++)
    {
        Treasure* treasure = new Treasure(numOfTreasures);
        int retval = treasure->generateTreasure(rand() % 4, width-1, coords);
        generatedCount += retval;
        if(retval != 0)
        {
            treasures.append(treasure);
            scene->addItem(treasure);
        }
        else
        {
            delete treasure;
        }
    }

    // setting up the first player
    setWhoseTurn(1);

    // treasure image
    treasureImg = new Treasure(numOfTreasures);
    treasureImg->setPos(0, screenHeight-60);
    scene->addItem(treasureImg);

    // getting all the current treasure types
    for(int i = 0; i < treasures.size(); i++)
    {
        treasureTypes.append(treasures.at(i)->getType());
    }

    // removing duplicates
    QSet<int> uniq = treasureTypes.toSet();
    treasureTypes = uniq.toList();

    // score descriptor
    scoreText = new QGraphicsTextItem;
    scoreText->setDefaultTextColor(Qt::blue);
    scoreText->setFont(QFont("Time", 20));
    scoreText->setPos(0, screenHeight-100);
    scene->addItem(scoreText);

    // treasure descriptor
    treasureText = new QGraphicsTextItem;
    treasureText->setPlainText(QString("-> Treasure Type"));
    treasureText->setDefaultTextColor(Qt::red);
    treasureText->setFont(QFont("Time", 20));
    treasureText->setPos(50, screenHeight-40);
    scene->addItem(treasureText);

    // spawning the players
    for(int i = 0; i < numOfPlayers; i++)
    {
        Spawn* spawn = new Spawn(i, ((width-1)*stone->getStoneWidth()));
        spawn->setPlayerNo(i+1);
        int randTres = treasureTypes.at(rand() % treasureTypes.size());
        spawn->setTreasureType(randTres);
        // first player
        if(i == 0)
        {
            // showing the target treasure
            treasureImg->drawTreasure(spawn->getTreasureType());
            scoreText->setPlainText("Score: " + QString::number(spawn->getScore()));
        }
        spawns.append(spawn);
        scene->addItem(spawn);
    }

    // finding the stone the player is standing on
    for(int i = 0; i < spawns.size(); i++)
    {
        Spawn* spawn = spawns.at(i);

        // found the player
        if(spawn->getPlayerNo() == getWhoseTurn())
        {
            // finding the stone the player is standing on
            for(int idx = 0; idx < stones.size(); idx++)
            {
                // standing on this stone
                if(stones.at(idx)->pos() == spawn->pos())
                {
                    standingAt = stones.at(idx);
                }
            } // end finding the stone
        }
    }

    // showing the scene
    show();
}

/**
 * Getter member function.
 * @return The width of the playing board.
 */
int Game::getWidth()
{
    return width;
}

/**
 * Getter member function.
 * @return The number of the current player.
 */
int Game::getWhoseTurn()
{
    return whoseTurn;
}

/**
 * Setter member function.
 * @param playerNo Set the current player to this number.
 */
void Game::setWhoseTurn(int playerNo)
{
    whoseTurn = playerNo;
}

/**
 * Switches the current player based on the number of players
 * and the current player.
 */
void Game::nextPlayersTurn()
{
    // finding out whose turn it is
    int player_no = getWhoseTurn();
    int numOfPlayers = player->getNumberOfPlayers();
    if(player_no == 1)
    {
        setWhoseTurn(2);
    }
    else if(player_no == 2)
    {
        if(numOfPlayers == 3 || numOfPlayers == 4)
        {
            setWhoseTurn(3);
        }
        else
        {
            setWhoseTurn(1);
        }
    }
    else if(player_no == 3)
    {
        if(numOfPlayers == 4)
        {
            setWhoseTurn(4);
        }
        else
        {
            setWhoseTurn(1);
        }
    }
    else if(player_no == 4)
    {
        setWhoseTurn(1);
    }
}

/**
 * Draws the main panel outputting the score, turn and treasure type.
 * @param x       The x coordinate of the panel.
 * @param y       The y coordinate of the panel.
 * @param width   The width of the panel.
 * @param height  The height of the panel.
 * @param color   The color of the panel.
 * @param opacity The opacity of the panel.
 */
void Game::drawPanel(int x, int y, int width,
                     int height, QColor color, double opacity)
{
    QGraphicsRectItem* panel = new QGraphicsRectItem(x, y, width, height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    panel->setBrush(brush);
    panel->setOpacity(opacity);
    scene->addItem(panel);
}

/**
 * Handles the rotation of the free stone.
 */
void Game::handleButton()
{
    rotCount++;
    for(int i = 0; i < stones.size(); i++)
    {
        if(stones.at(i)->freestoneActive == 1)
        {
            newFreestone = stones.at(i);
        }
    }

    newFreestone->setTransformOriginPoint(newFreestone->getStoneWidth()/2,
                                          newFreestone->getStoneHeight()/2);
    newFreestone->setRotation(rotCount*90);

    for(int i = 0; i < 3; i++)
    {
        // new exit ways
        if(newFreestone->eways[i] == 0) newFreestone->eways[i] = Stone::LEFT;
        else if(newFreestone->eways[i] == 1) newFreestone->eways[i] = Stone::RIGHT;
        else if(newFreestone->eways[i] == 2) newFreestone->eways[i] = Stone::DOWN;
        else if(newFreestone->eways[i] == 3) newFreestone->eways[i] = Stone::UP;

        // new entry ways
        if(newFreestone->iways[i] == 0) newFreestone->iways[i] = Stone::LEFT;
        else if(newFreestone->iways[i] == 1) newFreestone->iways[i] = Stone::RIGHT;
        else if(newFreestone->iways[i] == 2) newFreestone->iways[i] = Stone::DOWN;
        else if(newFreestone->iways[i] == 3) newFreestone->iways[i] = Stone::UP;
    }
}

/**
 * Handles a pressed key.
 * @param event The event containing the information about the key press.
 */
void Game::keyPressEvent(QKeyEvent *event)
{
    // coords of the stone
    QPointF stonePos;

    // looping through player
    for(int i = 0; i < spawns.size(); i++)
    {
        Spawn* spawn = spawns.at(i);

        // found the player
        if(spawn->getPlayerNo() == getWhoseTurn())
        {
            // quitting
            if(event->key() == Qt::Key_Q)
            {
                hide();
                // get the total number of players
                int numOfPlayers = player->getNumberOfPlayers();
                QList<int> scores;
                bool tie = false;

                // getting the score of all players
                for(int l = 0; l < spawns.size(); l++)
                {
                    scores.append(spawns.at(l)->getScore());
                }

                // finding ties
                if(numOfPlayers == 2)
                {
                    if(spawns.at(0)->getScore() == spawns.at(1)->getScore())
                    {
                        tie = true;
                    }
                }
                else if(numOfPlayers == 3)
                {
                    if(spawns.at(0)->getScore() == spawns.at(1)->getScore() == spawns.at(2)->getScore())
                    {
                        tie = true;
                    }
                }
                else if(numOfPlayers == 4)
                {
                    if(spawns.at(0)->getScore() == spawns.at(1)->getScore() == spawns.at(2)->getScore() == spawns.at(3)->getScore())
                    {
                        tie = true;
                    }
                }

                int maxScore = -1;
                int winnerNo = -1;

                // if there is a winner, find him
                if(tie == false)
                {
                    maxScore = *std::max_element(scores.begin(), scores.end());
                    // finding the winning player
                    for(int m = 0; m < spawns.size(); m++)
                    {
                        if(spawns.at(m)->getScore() == maxScore)
                        {
                            winnerNo = spawns.at(m)->getPlayerNo();
                        }
                    }
                }

                // passing the winner to the endgame dialog
                QPointer<End> end = new End(winnerNo);
                // showing the end dialog
                end->show();
            }
            // UP -> x, y-height
            if(event->key() == Qt::Key_Up)
            {
                stonePos.setX(spawn->x());
                stonePos.setY(spawn->y()-standingAt->getStoneHeight());
            }
            // DOWN -> x, y+height
            else if(event->key() == Qt::Key_Down)
            {
                stonePos.setX(spawn->x());
                stonePos.setY(spawn->y()+standingAt->getStoneHeight());
            }
            // LEFT -> x-width, y
            else if(event->key() == Qt::Key_Left)
            {
                stonePos.setX(spawn->x()-standingAt->getStoneWidth());
                stonePos.setY(spawn->y());
            }
            // RIGHT -> x+width, y
            else if(event->key() == Qt::Key_Right)
            {
                stonePos.setX(spawn->x()+standingAt->getStoneWidth());
                stonePos.setY(spawn->y());
            }
            else
            {
                if(event->key() != Qt::Key_Space)
                {
                    return;
                }
            }

            // if the position is out of the board
            if((stonePos.x() > ((width-1)*standingAt->getStoneWidth())) ||
            (stonePos.y() > ((width-1)*standingAt->getStoneHeight())) ||
            (stonePos.x() < 0 || stonePos.y() < 0))
            {
                return;
            }

            // finding the stone the player wants to go to
            for(int idx = 0; idx < stones.size(); idx++)
            {
                // found the go-to stone
                if(stones.at(idx)->pos() == stonePos)
                {
                    goingTo = stones.at(idx);
                }
            } // end finding the go-to stone

            bool canGoFrom = false;
            bool canGoTo = false;
            for(int i = 0; i < 3; i++)
            {
                if(event->key() == Qt::Key_Down)
                {
                    if(standingAt->eways[i] == 0)
                        canGoFrom = true;
                    if(goingTo->iways[i] == 0)
                        canGoTo = true;
                }
                else if(event->key() == Qt::Key_Up)
                {
                    if(standingAt->eways[i] == 1)
                        canGoFrom = true;
                    if(goingTo->iways[i] == 1)
                        canGoTo = true;
                }
                else if(event->key() == Qt::Key_Left)
                {
                    if(standingAt->eways[i] == 3)
                        canGoFrom = true;
                    if(goingTo->iways[i] == 3)
                        canGoTo = true;
                }
                else if(event->key() == Qt::Key_Right)
                {
                    if(standingAt->eways[i] == 2)
                        canGoFrom = true;
                    if(goingTo->iways[i] == 2)
                        canGoTo = true;
                }
            }

            if(event->key() == Qt::Key_Space)
                goto nextplay;

            if(canGoFrom != true || canGoTo != true)
            {
                return;
            }

            // looping through the treasure list
            for(int j = 0; j < treasures.size(); j++)
            {
                // finding the object
                if(stonePos == treasures.at(j)->pos())
                {
                    // is the treasure on the stone the object in the list?
                    if(treasures.at(j)->getType() == spawn->getTreasureType())
                    {
                        // removing the acquired treasure from the scene
                        treasures.at(j)->hide();
                        treasures.at(j)->deleteLater();
                        // removing the acquired treasure from the list
                        treasures.removeAt(j);
                        treasureTypes.clear();
                        for(int k = 0; k < treasures.size(); k++)
                        {
                            treasureTypes.append(treasures.at(k)->getType());
                        }

                        // game over
                        if(treasures.size() == 0)
                        {
                            QList<int> scores;

                            // getting the score of all players
                            for(int l = 0; l < spawns.size(); l++)
                            {
                                scores.append(spawns.at(l)->getScore());
                            }

                            // setting the max score
                            int maxScore = *std::max_element(scores.begin(), scores.end());
                            // initializing the winner variable
                            int winnerNo = -1;
                            // finding the winning player
                            for(int m = 0; m < spawns.size(); m++)
                            {
                                if(spawns.at(m)->getScore() == maxScore)
                                {
                                    winnerNo = spawns.at(m)->getPlayerNo();
                                }
                            }
                            hide();
                            // passing the winner to the endgame dialog
                            QPointer<End> end = new End(winnerNo);
                            // showing the end dialog
                            end->show();
                            break;
                        }

                        // removing duplicates
                        QSet<int> uniq = treasureTypes.toSet();
                        treasureTypes = uniq.toList();

                        // increasing the player's score
                        spawn->increaseScore();
                        // setting a new target treasure
                        int randTres = treasureTypes.at(rand() % treasureTypes.size());
                        spawn->setTreasureType(randTres);
                        // drawing the target
                        treasureImg->drawTreasure(spawn->getTreasureType());
                        break;
                    }
                }
            }

            nextplay:
            // moving the pawn to the stone
            if(event->key() != Qt::Key_Space)
            {
                spawn->moveToStone(stonePos);
            }
            // outputting the score
            scoreText->setPlainText("Score: " + QString::number(spawn->getScore()));
        }
    }

    if(event->key() == Qt::Key_Space)
    {
        nextPlayersTurn();
    }

    // finding the stone the player is standing on
    for(int i = 0; i < spawns.size(); i++)
    {
        Spawn* spawn = spawns.at(i);

        // found the player
        if(spawn->getPlayerNo() == getWhoseTurn())
        {
            // finding the stone the player is standing on
            for(int idx = 0; idx < stones.size(); idx++)
            {
                // standing on this stone
                if(stones.at(idx)->pos() == spawn->pos())
                {
                    standingAt = stones.at(idx);
                }
            } // end finding the stone
        }
    }

    // looping through the player list
    for(int i = 0; i < spawns.size(); i++)
    {
        Spawn* spawn = spawns.at(i);
        // is the player the one whose turn it is?
        if(spawn->getPlayerNo() == getWhoseTurn())
        {
            // outputting the score
            scoreText->setPlainText("Score: " + QString::number(spawn->getScore()));
            // drawing the target treasure
            treasureImg->drawTreasure(spawn->getTreasureType());
        }
    }
    // player descriptor
    player->setCurrentPlayer(getWhoseTurn());
    player->drawText(screenHeight);
}

/**
 * Handles a pressed mouse key.
 * @param event The event containing the information about the mouse key press.
 */
void Game::mousePressEvent(QMouseEvent *event)
{
    // the list of items on the clicked position
    QList<QGraphicsItem *> items_list = items(event->pos());
    // if no items
    if(items_list.empty())
    {
        return;
    }

    // rotate button
    if(items_list.first()->type() == 12)
    {
        handleButton();
    }

    QGraphicsItem* clicked = items_list.takeFirst();
    QPointF clicked_stone_pos = clicked->pos();
    QPointer<Stone> clicked_stone;

    // getting the stone on the clicked position
    for(int i = 0; i < stones.size(); i++)
    {
        if(stones.at(i)->pos() == clicked_stone_pos)
        {
            clicked_stone = stones.at(i);
            break;
        }
        else
        {
            clicked_stone = NULL;
        }
    }

    // if the stone is switchable
    if((clicked_stone != NULL)
            && (clicked_stone->switchableDown == true
            || clicked_stone->switchableLeft == true
            || clicked_stone->switchableRight == true
            || clicked_stone->switchableUp == true))
    {
        QPointF shift;

        // getting all the stones in the switch path
        for(int j = 1; j < getWidth(); j++)
        {
            if(clicked_stone->switchableDown == true
                    || clicked_stone->switchableUp)
            {
                shift.setX(clicked_stone->x());
                if(clicked_stone->switchableDown == true)
                {
                    shift.setY(clicked_stone->y() + j*clicked_stone->getStoneHeight());
                }
                else if(clicked_stone->switchableUp == true)
                {
                    shift.setY(clicked_stone->y() - j*clicked_stone->getStoneHeight());
                }
            }
            else if(clicked_stone->switchableLeft == true
                    || clicked_stone->switchableRight)
            {
                shift.setY(clicked_stone->y());
                if(clicked_stone->switchableLeft == true)
                {
                    shift.setX(clicked_stone->x() - j*clicked_stone->getStoneWidth());
                }
                else if(clicked_stone->switchableRight == true)
                {
                    shift.setX(clicked_stone->x() + j*clicked_stone->getStoneWidth());
                }
            }
            else
            {
                break;
            }

            // adding the stone to the list
            for(int i = 0; i < stones.size(); i++)
            {
                if(stones.at(i)->pos() == shift)
                {
                    switch_stones.append(stones.at(i));
                    break;
                }
            }
        }

        // if there's no item in the list
        if(switch_stones.empty())
        {
            // BUG HERE!
            return;
        }

        QPointF next_pos;
        QPointF begin_pos = clicked_stone->pos();
        switch_stones.prepend(clicked_stone);

        // find the treasures at the stone positions
        for(int i = 0; i < switch_stones.size(); i++)
        {
            for(int j = 0; j < treasures.size(); j++)
            {
                if(switch_stones.at(i)->pos() == treasures.at(j)->pos())
                {
                    switch_treasures.append(treasures.at(j));
                }
            }
        }

        // find the player pawn at the stone position
        for(int i = 0; i < switch_stones.size(); i++)
        {
            for(int j = 0; j < spawns.size(); j++)
            {
                if(switch_stones.at(i)->pos() == spawns.at(j)->pos())
                {
                    switch_spawns.append(spawns.at(j));
                }
            }
        }

        // THE MAIN LOOP
        for(int i = 0; i < switch_stones.size(); i++)
        {
            // first pass
            if(i == 0)
            {
                for(int k = 0; k < stones.size(); k++)
                {
                    if(stones.at(k)->freestoneActive == 1)
                    {
                        newFreestone = stones.at(k);
                    }
                }
                if(clicked_stone->switchableDown == true)
                {
                    newFreestone->switchableDown = true;
                }
                else if(clicked_stone->switchableUp == true)
                {
                    newFreestone->switchableUp = true;
                }
                else if(clicked_stone->switchableRight == true)
                {
                    newFreestone->switchableRight = true;
                }
                else if(clicked_stone->switchableLeft == true)
                {
                    newFreestone->switchableLeft = true;
                }

                newFreestone->setPos(switch_stones.at(i)->pos());
                newFreestone->freestoneActive = -1;
                // removing switchability from the clicked stone
                switch_stones.at(i)->removeSwitch();

                // getting the treasures and switching
                for(int t = 0; t < switch_treasures.size(); t++)
                {
                    if(switch_treasures.at(t)->pos() == switch_stones.at(i)->pos())
                    {
                        switch_treasures.at(t)->setPos(switch_stones.at(i+1)->pos());
                        break;
                    }
                }

                // getting the players and switching
                for(int t = 0; t < switch_spawns.size(); t++)
                {
                    if(switch_spawns.at(t)->pos() == switch_stones.at(i)->pos())
                    {
                        switch_spawns.at(t)->setPos(switch_stones.at(i+1)->pos());
                        break;
                    }
                }
                switch_stones.at(i)->setPos(switch_stones.at(i+1)->pos());
                next_pos = switch_stones.at(i+2)->pos();
                continue;
            }

            // last pass
            if(i == switch_stones.size()-1)
            {
                // getting the treasures and switching
                for(int t = 0; t < switch_treasures.size(); t++)
                {
                    if(switch_treasures.at(t)->pos() == switch_stones.at(i)->pos())
                    {
                        switch_treasures.at(t)->setPos(begin_pos);
                        switch_treasures.removeAt(t);
                        break;
                    }
                }

                // getting the players and switching
                for(int t = 0; t < switch_spawns.size(); t++)
                {
                    if(switch_spawns.at(t)->pos() == switch_stones.at(i)->pos())
                    {
                        switch_spawns.at(t)->setPos(begin_pos);
                        switch_spawns.removeAt(t);
                        break;
                    }
                }
                // moving the last stone to freestone position
                switch_stones.at(i)->setPos(freestone_pos);
                switch_stones.at(i)->freestoneActive = 1;
                break;
            }

            // getting the treasures and switching
            for(int t = 0; t < switch_treasures.size(); t++)
            {
                if(switch_treasures.at(t)->pos() == switch_stones.at(i)->pos())
                {
                    switch_treasures.at(t)->setPos(switch_stones.at(i+1)->pos());
                    switch_treasures.removeAt(t);
                    break;
                }
            }
            // getting the players and switching
            for(int t = 0; t < switch_spawns.size(); t++)
            {
                if(switch_spawns.at(t)->pos() == switch_stones.at(i)->pos())
                {
                    switch_spawns.at(t)->setPos(switch_stones.at(i+1)->pos());
                    switch_spawns.removeAt(t);
                    break;
                }
            }

            switch_stones.at(i)->setPos(next_pos);

            if(i != switch_stones.size()-2)
            {
                next_pos = switch_stones.at(i+2)->pos();
            }
            else // penultimate pass
            {
                if(clicked_stone->switchableDown == true)
                {
                    switch_stones.at(i+1)->switchableUp = true;
                    continue;
                }
                else if(clicked_stone->switchableUp == true)
                {
                    switch_stones.at(i+1)->switchableDown = true;
                    continue;
                }
                else if(clicked_stone->switchableRight == true)
                {
                    switch_stones.at(i+1)->switchableLeft = true;
                    continue;
                }
                else if(clicked_stone->switchableLeft == true)
                {
                    switch_stones.at(i+1)->switchableRight = true;
                    continue;
                }
            }
        }
    }
    // clearing the item lists
    switch_stones.clear();
    switch_treasures.clear();
    switch_spawns.clear();

}

/**
 * Getter member function.
 * @return The screen width.
 */
int Game::getScreenWidth()
{
    return screenWidth;
}

/**
 * Getter member function.
 * @return The screen height.
 */
int Game::getScreenHeight()
{
    return screenHeight;
}

/**
 * Destructor.
 */
Game::~Game()
{
    delete treasureText;
    delete scoreText;
    delete scene;
    delete rotateBtn;
    delete help;

    delete player;
    delete stone;
    delete spawn;
    delete treasure;
    delete treasureImg;
    delete standingAt;
    delete goingTo;
    delete newFreestone;

    for(int i = 0; i < spawns.size(); i++)
    {
        delete spawns.at(i);
    }
    for(int i = 0; i < stones.size(); i++)
    {
        delete stones.at(i);
    }
    for(int i = 0; i < treasures.size(); i++)
    {
        delete treasures.at(i);
    }
    for(int i = 0; i < switch_stones.size(); i++)
    {
        delete switch_stones.at(i);
    }
    for(int i = 0; i < switch_treasures.size(); i++)
    {
        delete switch_treasures.at(i);
    }
}
