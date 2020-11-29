CC = g++
SRC = ./*.cpp ./*.hpp
OPTS = -fopenmp -std=c++17

all:
	$(CC) $(OPTS) -O3 $(SRC) -o ./main

debug:
	$(CC) $(OPTS) -g $(SRC) -o ./main

clean:
	rm -f ./main
