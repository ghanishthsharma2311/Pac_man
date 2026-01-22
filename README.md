# Pac-Man (C++ / Qt)

A simplified clone of the classic Pac-Man arcade game, built using C++ and the Qt framework.

## Features
- **Smooth Gameplay**: Pixel-perfect movement system for fluid animation.
- **Classic Mechanics**: Collect pellets, avoid ghosts, and use Power Pellets to turn the tables.
- **Ghost AI**: Features a single, relentless Red Ghost that chases you through the maze.
- **Qt Graphics**: Utilizes `QGraphicsScene` and `QGraphicsView` for rendering.

## Requirements
- C++17 compatible compiler
- Qt 5 (Widgets module)
- `qmake` build tool

## How to Build and Run
Follow these simple commands to build and play the game:

1.  **Prepare the project**:
    ```bash
    ./prepare.sh
    ```
    This generates the necessary configuration files (Makefile, etc.).

2.  **Compile**:
    ```bash
    make
    ```
    This compiles the source code.
    
3.  **Run**:
    ```bash
    ./Pac_man1
    ```
    (Note: The executable name defaults to the folder name)

## Controls
- **Arrow Keys**: Move Pac-Man (Up, Down, Left, Right)
- **Objective**: Eat all the pellets to win!

## Project Structure
- `prepare.sh`: Helper script to generate project files using `qmake`.
- `Game.cpp`: Core game loop and logic.
- `Player.cpp`: Pac-Man movement and input handling.
- `Ghost.cpp`: Enemy AI and behavior.
- `MovableObject.cpp`: Shared logic for entity movement and collision.


