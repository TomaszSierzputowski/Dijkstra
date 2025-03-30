CC = g++
CFLAGS = -Wall -Iinclude

all: dijkstra dial radixheap

dijkstra: ./build/miscellaneous.o ./build/Graph.o ./build/PriorityQueue.o ./build/dijkstra.o ./build/main.o
	mkdir -p ./bin/
	$(CC) $(CFLAGS) ./build/miscellaneous.o ./build/Graph.o ./build/PriorityQueue.o ./build/dijkstra.o ./build/main.o -o ./bin/dijkstra

dial: ./build/miscellaneous.o ./build/Graph.o ./build/Buckets.o ./build/dial.o ./build/main.o
	mkdir -p ./bin/
	$(CC) $(CFLAGS) ./build/miscellaneous.o ./build/Graph.o ./build/Buckets.o ./build/dial.o ./build/main.o -o ./bin/dial

radixheap: ./build/miscellaneous.o ./build/Graph.o ./build/RadixHeap.o ./build/radixheap.o ./build/main.o
	mkdir -p ./bin/
	$(CC) $(CFLAGS) ./build/miscellaneous.o ./build/Graph.o ./build/RadixHeap.o ./build/radixheap.o ./build/main.o -o ./bin/radixheap

./build/main.o: ./src/main.cpp
	mkdir -p ./build/
	$(CC) $(CFLAGS) -c ./src/main.cpp -o ./build/main.o

./build/dijkstra.o: ./src/dijkstra.cpp ./include/dijkstra.hpp
	mkdir -p ./build/
	$(CC) $(CFLAGS) -DDIJKSTRA -c ./src/dijkstra.cpp -o ./build/dijkstra.o


./build/dial.o: ./src/dijkstra.cpp ./include/dijkstra.hpp
	mkdir -p ./build/
	$(CC) $(CFLAGS) -DDIAL -c ./src/dijkstra.cpp -o ./build/dial.o

	
./build/radixheap.o: ./src/dijkstra.cpp ./include/dijkstra.hpp
	mkdir -p ./build/
	$(CC) $(CFLAGS) -DRADIXHEAP -c ./src/dijkstra.cpp -o ./build/radixheap.o

./build/%.o: ./src/%.cpp ./include/%.hpp
	mkdir -p ./build/
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf ./build/ ./bin/