// End.cpp – xminar27/xvitas02

#include "End.h"

/**
 * Constructor function for an end object.
 */
End::End(int player) :
    QDialog(),
    ui(new Ui::End)
{
    ui->setupUi(this);
    if(player != -1)
    {
        ui->winnerNumber->setText(QString::number(player));
    }
    else
    {
        ui->winnerNumber->hide();
        ui->winnerNumber->deleteLater();
        ui->winnerText->setText("NO WINNER!");
        ui->winnerText->setAlignment(Qt::AlignCenter);
    }
    ui->buttonLayout->setAlignment(Qt::AlignCenter);
}

/**
 * Destructor function for an end object.
 */
End::~End()
{
    delete ui;
}

/**
 * Handles the action of clicking the quit button.
 */
void End::on_quitBtn_clicked()
{
    exit(0);
}

/**
 * Handles the action of clicking the replay button.
 */
void End::on_replayBtn_clicked()
{
    hide();
    deleteLater();
    QPointer<Settings> settings = new Settings;
    settings->show();
}
