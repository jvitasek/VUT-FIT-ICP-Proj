// Settings.h – xminar27/xvitas02

#ifndef SETTINGS_H
#define SETTINGS_H

// Qt libraries
#include <QDialog>
#include <QPointer>

// custom libraries
#include "ui_settings.h"
#include "Game.h"

// UI namespace
namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

    public:
        // constructor
        explicit Settings(QWidget *parent = 0);
        // destructor
        ~Settings();

    private slots:
        // private slot handler
        void on_buttonBox_accepted();

    private:
        // private ui object
        Ui::Settings *ui;
};

#endif // SETTINGS_H
