// Settings.cpp – xminar27/xvitas02

#include "Settings.h"

/**
 * Constructor for a settings object.
 */
Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
}

/**
 * Destructor for a settings object.
 */
Settings::~Settings()
{
    delete ui;
}

/**
 * Handles showing the game when settings are accepted.
 */
void Settings::on_buttonBox_accepted()
{
    // setting up game parameters from spinners
    int numOfPlayers = ui->playersSpin->value();
    int boardWidth = ui->widthSpin->value();
    int numOfTreasures = ui->treasureSpin->value();

    // hides and deletes the settings dialog
    hide();
    deleteLater();

    // new game
    QPointer<Game> game = new Game(numOfPlayers, boardWidth, numOfTreasures);
    game->show();
}
