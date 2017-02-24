# build!

bin/shell-bar: src/*.cc
	g++ src/*.cc -lcurses -Wall -o bin/shell-bar

