# ---------------------------------------------------------------------------
# Shell-bar Makefile
#
# To build, just run `make`. To install, set the prefix in this file, and run
# `make install`.

# ---------------------------------------------------------------------------
# Set the prefix of the installation. To install shell-bar directly in your
# ~/.local/bin, use the following:
# 
#   PREFIX=${HOME}/.local
# 
# I prefer installing packages in their own folder and make symlinks using
# stow, then something like this:
#
#   PREFIX=${HOME}/.local/pkg/shell-bar
# 
# is more appropriate.

PREFIX=${HOME}/.local/pkg/shell-bar

# ---------------------------------------------------------------------------
# Choose your compiler. Shell-bar is written in C++17, so make sure the
# compiler supports that.

CPP=g++

# ===========================================================================

.PHONY: install clean

bin/shell-bar: src/*.cc
	${CPP} -std=c++17 src/*.cc -lcurses -Wall -o bin/shell-bar

install:
	mkdir -p ${PREFIX}/bin
	install -m 557 bin/shell-bar bin/*.sh ${PREFIX}/bin

clean:
	rm -f bin/shell-bar
