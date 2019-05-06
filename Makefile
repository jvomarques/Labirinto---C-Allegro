labirinto.o: labirinto.cpp labirinto.h
	g++ labirinto.cpp -c

main: main.cpp labirinto.o
	g++ main.cpp labirinto.o -o main -lallegro -lallegro_dialog -lallegro_font -lallegro_ttf -lallegro_primitives

limpar:
	rm main labirinto.o