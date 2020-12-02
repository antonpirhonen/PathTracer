CC = g++
SRC = ./*.cpp
OPTS = -fopenmp -std=c++17

all:
	$(CC) $(OPTS) -O3 $(SRC) -o ./main

debug:
	$(CC) $(OPTS) -g $(SRC) -o ./main

sanitize:
	$(CC) $(OPTS) -g -fsanitize=address $(SRC) -o ./main

clean:
	rm -f ./main
