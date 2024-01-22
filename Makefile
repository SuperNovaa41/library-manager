all: api/*.cpp
	g++ api/main.cpp api/csv.cpp api/isbn-interaction.cpp -o manager
	mkdir -p bin
	mv manager bin/
clean:
	rm -rf bin
