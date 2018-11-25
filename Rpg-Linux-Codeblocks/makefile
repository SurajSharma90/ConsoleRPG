PROG = main
CC = g++
CPPFLAGS = -Wall -O2
OBJS = main.o Game.o Character.o Enemy.o Event.o Inventory.o Item.o Armor.o Weapon.o Puzzle.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS) 

main.o :
	$(CC) $(CPPFLAGS) -c main.cpp

Game.o : Game.h
	$(CC) $(CPPFLAGS) -c Game.cpp
    
Character.o : Character.h
	$(CC) $(CPPFLAGS) -c Character.cpp

Enemy.o : Enemy.h
	$(CC) $(CPPFLAGS) -c Enemy.cpp

Event.o : Event.h
	$(CC) $(CPPFLAGS) -c Event.cpp

Inventory.o : Inventory.h
	$(CC) $(CPPFLAGS) -c Inventory.cpp
    
Item.o : Item.h
	$(CC) $(CPPFLAGS) -c Item.cpp

Armor.o : Armor.h
	$(CC) $(CPPFLAGS) -c Armor.cpp

Weapon.o : Weapon.h
	$(CC) $(CPPFLAGS) -c Weapon.cpp

Puzzle.o : Puzzle.h
	$(CC) $(CPPFLAGS) -c Puzzle.cpp
    
clean :
	rm -f core $(PROG) $(OBJS)