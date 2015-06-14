#include "Score.h"
#include <QFont>

Score::Score(): QGraphicsTextItem()
{

}

void Score::drawText()
{
    // drawing the text
    setPlainText(QString("Score: ") + QString::number(score));
    setDefaultTextColor(Qt::blue);
    setFont(QFont("Time", 20));
    this->setPos(0, 500);
}
