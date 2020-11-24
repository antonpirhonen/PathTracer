CC = g++
SRC = ./*.cpp ./*.hpp
OPTS = -fopenmp

all:
	$(CC) $(OPTS) -O3 $(SRC) -o ./main

debug:
	$(CC) $(OPTS) -g $(SRC) -o ./main

clean:
	rm -f ./main
