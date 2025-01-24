# Builds main.cpp using G++ as the "bin/main" file.
LDFLAGS = -rdynamic -O3
CFLAGS = $(LDFLAGS)

bin/main : src/main.cpp src/tqp.hpp
	mkdir -p bin
	g++ $(CFLAGS) -o bin/main src/main.cpp

.PHONY : clear
clean :
	rm bin/main
