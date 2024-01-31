all: api/*.cpp
	g++ api/main.cpp api/isbn-interaction.cpp -lsqlite3 -o manager
	mkdir -p bin
	mv manager bin/
clean:
	rm -rf bin
