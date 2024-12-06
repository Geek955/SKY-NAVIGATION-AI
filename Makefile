all: compile link run

compile:
	g++ -I src/include -c main.cpp

link:
	g++ *.o -o main -L src/lib -lsfml-graphics -lsfml-window -lsfml-system -lopengl32 -lsfml-audio

run:
	./main.exe