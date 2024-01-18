all: src/*.cpp
	g++ src/main.cpp src/csv.cpp -o manager
	mkdir -p build
	mv manager build/
clean:
	rm -rf build
