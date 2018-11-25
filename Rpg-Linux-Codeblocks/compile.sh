#!/bin/bash

echo "Compile script ...";

g++ -c main.cpp;
g++ -c Game.cpp;
g++ -c Character.cpp;
g++ -c Enemy.cpp;
g++ -c Event.cpp;
g++ -c Inventory.cpp;
g++ -c Item.cpp;
g++ -c Armor.cpp;
g++ -c Weapon.cpp;
g++ -c Puzzle.cpp;
g++ -Wall -O2 -o main main.o Game.o Character.o Enemy.o Event.o Inventory.o Item.o Armor.o Weapon.o Puzzle.o;

echo "Script complete ...";