# build!

bin/shell-bar: src/*.cc
	g++ -std=c++17 src/*.cc -lcurses -Wall -o bin/shell-bar

