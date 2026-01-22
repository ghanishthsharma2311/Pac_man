#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QLabel>
#include <QVBoxLayout>
#include <vector>
#include <memory>
#include "Player.h"
#include "Enemy.h"
#include "Ghost.h"
#include "Collectible.h"

/**
 * Main game controller
 * Manages game loop, collision detection, and game state
 */
class Game : public QObject {
    Q_OBJECT

public:
    explicit Game(QWidget* parent = nullptr);
    ~Game();

    QWidget* getMainWidget() { return mainWidget; }

private slots:
    void gameLoop();

private:
    // UI Components
    QWidget* mainWidget;
    QGraphicsScene* scene;
    QGraphicsView* view;
    QLabel* scoreLabel;
    QLabel* statusLabel;
    
    // Game objects
    Player* player;
    std::vector<Ghost*> enemies;
    std::vector<Collectible*> collectibles;
    
    // Game state
    QTimer* timer;
    int score;
    int totalPellets;
    int collectedPellets;
    bool gameOver;
    bool won;
    
    // Maze layout (1 = wall, 0 = empty, 2 = pellet, 3 = power pellet)
    std::vector<std::vector<int>> maze;
    
    // Initialization
    void initializeMaze();
    void createMaze();
    void setupUI();
    
    // Game logic
    void checkCollisions();
    void checkPlayerEnemyCollision();
    void checkPlayerCollectibleCollision();
    void updateScore();
    void updateGameState();
    void endGame(bool playerWon);
    
    // Input handling
    bool eventFilter(QObject* obj, QEvent* event) override;
};

#endif // GAME_H