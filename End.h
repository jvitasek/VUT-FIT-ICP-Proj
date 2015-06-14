// End.h – xminar27/xvitas02

#ifndef END_H
#define END_H

// Qt libraries
#include <QString>
#include <QGraphicsTextItem>
#include <QDialog>
#include <QPointer>

// custom libraries
#include "ui_end.h"
#include "Settings.h"

// UI namespace
namespace Ui {
class End;
}

class End : public QDialog
{
    Q_OBJECT

    public:
        // constructor
        explicit End(int player);
        // destructor
        ~End();

    private slots:
        // private slot handlers
        void on_quitBtn_clicked();
        void on_replayBtn_clicked();

    private:
        // private ui object
        Ui::End *ui;
};

#endif // END_H
