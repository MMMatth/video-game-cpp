g++ -c cartes.cpp -o cartes.o
g++ -c main.cpp -o main.o
g++ cartes.o main.o -o main -lsfml-graphics -lsfml-window -lsfml-system
./main