#include "Game.h"
#include "Ghost.h"
#include "Pellet.h"
#include "PowerPellet.h"
#include "Wall.h"
#include <QKeyEvent>
#include <QMessageBox>
#include <cmath>

Game::Game(QWidget* parent) 
    : QObject(parent), score(0), totalPellets(0), collectedPellets(0), 
      gameOver(false), won(false) {
    
    // Initialize maze layout
    initializeMaze();
    
    // Setup UI
    setupUI();
    
    // Create maze and game objects
    createMaze();
    
    // Create player
    player = new Player();           // player object
    player->setGridPosition(1, 1);
    scene->addItem(player);
    
    // Create ghosts with different colors
    // Spawn in the middle (Ghost House) at 7, 7
    Ghost* ghost1 = new Ghost(QColor(255, 0, 0), 7, 7);    // Red ghost object
    
    scene->addItem(ghost1);
    
    enemies.push_back(ghost1);
    
    // Setup game loop timer (30 FPS) 
    timer = new QTimer(this);     // timer object that calls gameLoop() every 33 ms
   
    connect(timer, &QTimer::timeout, this, &Game::gameLoop);
    timer->start(35); 

    
    updateScore();
}

Game::~Game() {
    if (timer) timer->stop();
    // Scene owns items, so it deletes them.
    // View does not own scene.
    // MainWidget owns View.
    delete mainWidget; 
    delete scene;      
}

void Game::initializeMaze() {
    // Pac-Man style maze layout
    // 0 = empty, 1 = wall, 2 = pellet, 3 = power pellet
    maze = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1},
        {1, 3, 1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 3, 1},
        {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
        {1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1},
        {1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1},
        {1, 1, 1, 1, 2, 1, 0, 0, 0, 1, 2, 1, 1, 1, 1},
        {1, 2, 2, 2, 2, 1, 0, 0, 0, 1, 2, 2, 2, 2, 1},
        {1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1},
        {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
        {1, 2, 1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 2, 1},
        {1, 3, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 3, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
}

void Game::setupUI() {
    mainWidget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(mainWidget);
    
    // Score label
    scoreLabel = new QLabel("Score: 0");
    scoreLabel->setStyleSheet("font-size: 18px; font-weight: bold;");
    layout->addWidget(scoreLabel);
    
    // Status label
    statusLabel = new QLabel("Use arrow keys to move. Collect all pellets!");
    statusLabel->setStyleSheet("font-size: 14px;");
    layout->addWidget(statusLabel);
    
    // Graphics view
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setBackgroundBrush(Qt::black);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    
    int width = maze[0].size() * TILE_SIZE;
    int height = maze.size() * TILE_SIZE;
    scene->setSceneRect(0, 0, width, height);
    view->setFixedSize(width + 2, height + 2);
    
    layout->addWidget(view);
    
    // Install event filter for keyboard input
    //to ensure we catch keys
    mainWidget->installEventFilter(this);
    view->installEventFilter(this);
    mainWidget->setFocusPolicy(Qt::StrongFocus);
}

void Game::createMaze() {
    for (size_t y = 0; y < maze.size(); ++y) {
        for (size_t x = 0; x < maze[y].size(); ++x) {
            int tile = maze[y][x];
            
            if (tile == 1) {
                // Wall
                Wall* wall = new Wall();
                wall->setGridPosition(x, y);
                scene->addItem(wall);
            }
            else if (tile == 2) {
                // Regular pellet
                Pellet* pellet = new Pellet();
                pellet->setGridPosition(x, y);
                scene->addItem(pellet);
                collectibles.push_back(pellet);
                totalPellets++;
            }
            else if (tile == 3) {
                // Power pellet
                PowerPellet* powerPellet = new PowerPellet();
                powerPellet->setGridPosition(x, y);
                scene->addItem(powerPellet);
                collectibles.push_back(powerPellet);
                totalPellets++;
            }
        }
    }
}

void Game::gameLoop() {
    if (gameOver) return;
    
    // Move player
    player->move(maze);
    player->updatePowerMode();
    
    // Move enemies
    for (Ghost* ghost : enemies) {
        ghost->moveGhost(maze);
    }
    
    // Animate power pellets
    for (auto* collectible : collectibles) {
        PowerPellet* powerPellet = dynamic_cast<PowerPellet*>(collectible);
        if (powerPellet && !powerPellet->isCollected()) {
            powerPellet->animate();
        }
    }
    
    // Check collisions
    checkCollisions();
    
    // Update display
    scene->update();
    updateGameState();
}

void Game::checkCollisions() {
    checkPlayerCollectibleCollision();
    checkPlayerEnemyCollision();
}

void Game::checkPlayerCollectibleCollision() {
    int px = player->getGridX();
    int py = player->getGridY();
    
    for (auto* collectible : collectibles) {
        if (collectible->isCollected()) continue;
        
        if (collectible->getGridX() == px && collectible->getGridY() == py) {
            // Collect the item
            score += collectible->getPoints();
            collectible->setCollected(true);
            collectedPellets++;
            
            // Activate power mode if it's a power pellet
            if (collectible->isPowerPellet()) {
                player->activatePowerMode();
                
                // Make all ghosts frightened
                for (auto& enemy : enemies) {
                    enemy->setFrightened(true);
                }
            }
            
            updateScore();
            collectible->hide();
        }
    }
}

void Game::checkPlayerEnemyCollision() {
    int px = player->getGridX();
    int py = player->getGridY();
    
    for (auto& enemy : enemies) {
        int ex = enemy->getGridX();
        int ey = enemy->getGridY();
        
        // Check if player and enemy are on same tile
        if (px == ex && py == ey) {
            if (player->isPowerMode()) {
                // Eat the ghost
                score += 200;
                updateScore();
                enemy->respawn();
                enemy->setFrightened(false);
            } else {
                // Game over
                endGame(false);
                return;
            }
        }
    }
    
    // Update ghost frightened state based on power mode
    if (!player->isPowerMode()) {
        for (auto& enemy : enemies) {
            enemy->setFrightened(false);
        }
    }
}

void Game::updateScore() {
    scoreLabel->setText(QString("Score: %1").arg(score));
    
    // Update power mode indicator
    if (player->isPowerMode()) {
        int timeLeft = player->getPowerModeTime() / 30; // Convert frames to seconds
        statusLabel->setText(QString("POWER MODE! Time left: %1s").arg(timeLeft));
    } else {
        statusLabel->setText("Use arrow keys to move. Collect all pellets!");
    }
}

void Game::updateGameState() {
    // Check win condition
    if (collectedPellets >= totalPellets && !gameOver) {
        endGame(true);
    }
}

void Game::endGame(bool playerWon) {
    gameOver = true;
    won = playerWon;
    timer->stop();
    
    QString message;
    if (won) {
        message = QString("You Win!\n\nFinal Score: %1\n\nPress OK to close.").arg(score);
        statusLabel->setText("YOU WIN!");
    } else {
        message = QString("Game Over!\n\nFinal Score: %1\n\nPress OK to close.").arg(score);
        statusLabel->setText("GAME OVER!");
    }
    
    QMessageBox::information(mainWidget, won ? "Victory!" : "Game Over", message);
}

bool Game::eventFilter(QObject* obj, QEvent* event) {
    if (event->type() == QEvent::KeyPress && !gameOver) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        player->handleKeyPress(keyEvent->key());
        return true;
    }
    return QObject::eventFilter(obj, event);
}