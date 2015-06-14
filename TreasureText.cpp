#include "TreasureText.h"
#include <QFont>

TreasureText::TreasureText(): QGraphicsTextItem()
{
}

void TreasureText::drawText(int type)
{
    // drawing the text
    setPlainText(QString("Treasure Type: ") + QString::number(type));
    setDefaultTextColor(Qt::red);
    setFont(QFont("Time", 20));
    this->setPos(0, 560);
}

int TreasureText::generate()
{
    return (rand() % 4);
}
