all: output run

build:
	g++ -I src/include -c main.cpp ./Engine/*.cpp ./Tokens/*.cpp ./DS/*.cpp ./Animation/*.cpp
output: *.o
	g++ *.o -o game.exe -L src/lib -l sfml-graphics -l sfml-window -l sfml-audio -l sfml-system -l openal32

./main.o: main.cpp
	g++ -I src/include -c main.cpp -o main.o

./Game.o: ./Engine/Game.cpp
	g++ -I src/include -c ./Engine/Game.cpp -o Game.o

./Lifes.o: ./Engine/Lifes.cpp
	g++ -I src/include -c ./Engine/Lifes.cpp -o Lifes.o

./TokenHandler.o: ./Engine/TokenHandler.cpp
	g++ -I src/include -c ./Engine/TokenHandler.cpp -o TokenHandler.o

./Token.o: ./Tokens/Token.cpp
	g++ -I src/include -c ./Tokens/Token.cpp -o Token.o

./Character.o: ./Tokens/Character.cpp
	g++ -I src/include -c ./Tokens/Character.cpp -o Character.o

./Player.o: ./Tokens/Player.cpp
	g++ -I src/include -c ./Tokens/Player.cpp -o Player.o

./Hitbox.o: ./DS/Hitbox.cpp
	g++ -I src/include -c ./DS/Hitbox.cpp -o Hitbox.o

./Animation.o: ./Animation/Animation.cpp
	g++ -I src/include -c ./Animation/Animation.cpp -o Animation.o

./DeltaTime.o: ./DS/DeltaTime.cpp
	g++ -I src/include -c ./DS/DeltaTime.cpp -o DeltaTime.o

./Button.o: ./DS/Button.cpp
	g++ -I src/include -c ./DS/Button.cpp -o Button.o

./Functions.o: ./DS/Functions.cpp
	g++ -I src/include -c ./DS/Functions.cpp -o Functions.o

./Dice.o: ./Tokens/Dice.cpp
	g++ -I src/include -c ./Tokens/Dice.cpp -o Dice.o

run:
	./game.exe