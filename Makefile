all:
	g++ -I src/include -L src/lib -o main main.cpp -lmingw32 -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-system -lsfml-window