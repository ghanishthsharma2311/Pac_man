#include <QApplication>
#include "Game.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    // Create and show game
    Game game;
    QWidget* mainWidget = game.getMainWidget();
    mainWidget->setWindowTitle("Pac-Man");
    mainWidget->show();
    
    return app.exec();
}