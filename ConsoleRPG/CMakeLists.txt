cmake_minimum_required(VERSION 3.12)
project(console_rpg)

# Set the C++ standard

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Add the source files to the project
set(SOURCES
  src/main.cpp
  src/Game.cpp
  src/Character.cpp
  src/Boss.cpp
  src/Enemy.cpp
  src/Event.cpp
  src/Inventory.cpp
  src/Item.cpp
  src/Armor.cpp
  src/Weapon.cpp
  src/Puzzle.cpp
  src/gui_functions.cpp
)

# Create the executable
add_executable(console_rpg ${SOURCES})