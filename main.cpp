// main.cpp – xminar27/xvitas02

#include <QApplication>
#include "Settings.h"

int main(int argc, char *argv[])
{
    // running the application
    QApplication a(argc, argv);

    // new game settings dialog
    QPointer<Settings> settings = new Settings;
    settings->show();

    return a.exec();
}
