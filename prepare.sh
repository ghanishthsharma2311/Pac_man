#!/bin/bash
# Generate the .pro file (Project configuration)
qmake -project

# Generate the Makefile with Widgets and C++17 support
# This setup will generate the executable with the same name as your folder
qmake "QT+=widgets" "CONFIG+=c++17"

echo "Setup complete. Run 'make' to build."
